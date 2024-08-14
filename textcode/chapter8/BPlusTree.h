#ifndef BPTREE_HPP_BPTREE_HPP
#define BPTREE_HPP_BPTREE_HPP

#include <vector>
#include <fstream>
#include "Pair.h"
#include "StorageSearchTable.h"

template<class KeyType, class ValueType, int M = 100, int L = 100>
class BPlusTree : public StorageSearchTable<KeyType, ValueType> {
 private:
  // 保存非叶结点的文件的名字和保存叶结点的文件的名字
  std::string treeNodeFileName, leafFileName;
  // 保存非叶结点和叶结点的文件流对象
  std::fstream treeNodeFile, leafFile;
  // 最后一个非叶结点的位置和最后一个叶结点的位置
  int rearTreeNode, rearLeaf;
  // 数据记录的个数
  int sizeData;
  // 保存非叶结点的文件的头部长度 
  // （前面预留两个整型数空间来保存根结点位置和最后一个非叶结点的位置） 
  const int headerLengthOfTreeNodeFile = 2 * sizeof(int);
  // 保存叶结点的文件的头部长度
  // （前面预留两个整型数空间来保存最后一个叶结点的位置和数据记录的数量）
  const int headerLengthOfLeafFile = 2 * sizeof(int);
  // 被删除的非叶结点和叶结点的位置，在插入的时候优先使用这些位置 
  seqList<int> emptyTreeNode;
  seqList<int> emptyLeaf;

  /* TreeNode定义了B+树的普通结点
      isBottomNode记录是否是最后一层非叶结点
      Pos是结点的位置，dataCount是结点的子结点的个数
      childrenPos保存子结点的位置信息
      septal保存分割各棵子树的键值
  */
  struct TreeNode {
    int pos, dataCount;
    int childrenPos[M];
    KeyType septal[M - 1];
    bool isBottomNode;
  };

  /* Leaf定义了B+树的叶结点
      nxt是下一个叶结点的位置，pos是当前叶结点的位置
      DataCount是当前叶结点中数据记录的个数
      value数组用于保存叶结点的数据记录
  */
  struct Leaf {
    int nxt, pos;
    int dataCount;
    KeyType keys[L];
    ValueType values[L];
  };

  // 树的根结点
  TreeNode root;

 public:
  // 构造函数：从文件中读取必要信息，在内存中记录树的根结点、元素个数等关键信息
  explicit BPlusTree(const std::string &name) {
    treeNodeFileName = name + "_treeNodeFile";
    leafFileName = name + "_leafFile";
    // 打开文件，一个保存非叶结点，另一个保存叶结点
    treeNodeFile.open(treeNodeFileName);
    leafFile.open(leafFileName);
    if (!leafFile || !treeNodeFile) {
      // 如果文件不存在，就创建文件，并初始化数据记录文件
      initialize();
    } else {
      // 读取非叶结点文件的头部，得到树的根结点的位置和最后一个非叶结点的位置
      treeNodeFile.seekg(0), leafFile.seekg(0);
      int rootPos;
      treeNodeFile.read(reinterpret_cast<char *>(&rootPos), sizeof(int));
      treeNodeFile.read(reinterpret_cast<char *>(&rearTreeNode), sizeof(int));
      // 找到并读取树的根结点
      treeNodeFile.seekg(headerLengthOfTreeNodeFile + rootPos * sizeof(TreeNode));
      treeNodeFile.read(reinterpret_cast<char *>(&root), sizeof(TreeNode));
      // 最后一个非叶结点后面保存了被删除的非叶结点
      int treeNodeEmptySize, leafEmptySize;
      treeNodeFile.seekg(headerLengthOfTreeNodeFile + (rearTreeNode + 1) * sizeof(TreeNode));
      // 读取被删除的非叶结点的数量和位置
      treeNodeFile.read(reinterpret_cast<char *>(&treeNodeEmptySize), sizeof(int));
      for (int i = 0; i < treeNodeEmptySize; i++) {
        int data;
        treeNodeFile.read(reinterpret_cast<char *>(&data), sizeof(int));
        emptyTreeNode.insert(emptyTreeNode.length(), data);
      }
      // 读取叶结点文件的头部，得到最后一个叶结点的位置
      leafFile.read(reinterpret_cast<char *>(&rearLeaf), sizeof(int));
      // 插入的数据记录的数量保存在叶结点文件的头部的第二个int中
      leafFile.read(reinterpret_cast<char *>(&sizeData), sizeof(int));
      // 最后一个叶结点后面保存了被删除的叶结点
      leafFile.seekg(headerLengthOfLeafFile + (rearLeaf + 1) * sizeof(Leaf));
      // 读取被删除的叶结点的数量和位置
      leafFile.read(reinterpret_cast<char *>(&leafEmptySize), sizeof(int));
      for (int i = 0; i < leafEmptySize; i++) {
        int data;
        leafFile.read(reinterpret_cast<char *>(&data), sizeof(int));
        emptyLeaf.insert(emptyLeaf.length(), data);
      }
    }
  }

  // 析构函数：将树的根结点、被删除结点的位置等信息写入文件
  ~BPlusTree() {
    // 将树的根结点、最后一个非叶结点的位置写入文件
    treeNodeFile.seekp(0), leafFile.seekp(0);
    treeNodeFile.write(reinterpret_cast<char *>(&root.pos), sizeof(int));
    treeNodeFile.write(reinterpret_cast<char *>(&rearTreeNode), sizeof(int));
    // 将树的根结点写入文件
    writeTreeNode(root);
    // 将最后一个叶结点的位置写入文件
    leafFile.write(reinterpret_cast<char *>(&rearLeaf), sizeof(int));
    // 将插入的数据记录的数量写入文件
    leafFile.write(reinterpret_cast<char *>(&sizeData), sizeof(int));
    // 将被删除的非叶结点和叶结点的位置写入文件
    treeNodeFile.seekp(headerLengthOfTreeNodeFile + (rearTreeNode + 1) * sizeof(TreeNode));
    int emptyTreeNodeCount = emptyTreeNode.length(), emptyLeafCount = emptyLeaf.length();
    treeNodeFile.write(reinterpret_cast<char *>(&emptyTreeNodeCount), sizeof(int));
    for (int i = 0; i < emptyTreeNode.length(); i++) {
      int tmp = emptyTreeNode.visit(i);
      treeNodeFile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    }
    leafFile.seekp(headerLengthOfLeafFile + (rearLeaf + 1) * sizeof(Leaf));
    leafFile.write(reinterpret_cast<char *>(&emptyLeafCount), sizeof(int));
    for (int i = 0; i < emptyLeaf.length(); i++) {
      int tmp = emptyLeaf.visit(i);
      leafFile.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    }
    // 关闭文件
    leafFile.close();
    treeNodeFile.close();
  }

  int size() { return sizeData; }

  // 插入数据记录
  void insert(const KeyType &key, const ValueType &value) {
    if (insert(key, value, root)) {  // 分裂根结点
      TreeNode newRoot;            // 创建一个新的根结点
      TreeNode newNode;            // 新的兄弟结点
      newNode.pos = getNewTreeNodePos();
      newNode.isBottomNode = root.isBottomNode;
      newNode.dataCount = M / 2;
      int mid = M / 2;
      for (int i = 0; i < mid; i++) {
        newNode.childrenPos[i] = root.childrenPos[mid + i];
      }
      for (int i = 0; i < mid - 1; i++) {
        newNode.septal[i] = root.septal[mid + i];
      }
      root.dataCount = mid;
      writeTreeNode(root);
      writeTreeNode(newNode);
      newRoot.dataCount = 2;
      newRoot.pos = getNewTreeNodePos();
      newRoot.isBottomNode = false;
      newRoot.childrenPos[0] = root.pos;
      newRoot.childrenPos[1] = newNode.pos;
      newRoot.septal[0] = root.septal[mid - 1];
      root = newRoot;
      writeTreeNode(root);
    }
  }

  // 查询数据记录：如果查询到，返回true，并将value赋值为查询到的值；否则返回false
  bool find(const KeyType &key, ValueType &value) {
    TreeNode p = root;
    Leaf leaf;
    while (!p.isBottomNode) {  // childrenPos[now]中元素小于或等于Key[now] 
      // 循环找到叶结点
      readTreeNode(p, p.childrenPos[binarySearchTreeNode(key, p)]);
    }
    // 找到叶结点
    readLeaf(leaf, p.childrenPos[binarySearchTreeNode(key, p)]);
    // 在叶结点中二分查找，找到第一个大于或等于key的位置
    int pos = binarySearchLeaf(key, leaf);
    if (pos < leaf.dataCount && leaf.keys[pos] == key) {  // 如果找到了
      value = leaf.values[pos];
      return true;
    } else {
      return false;
    }
  }

  void traverse() {
    TreeNode p = root;
    Leaf leaf;
    while (!p.isBottomNode) { // 首先找到最左叶结点
      readTreeNode(p, p.childrenPos[0]);
    }
    readLeaf(leaf, p.childrenPos[0]);
    int pos = 0;
    do {
      while (pos < leaf.dataCount) { // 输出当前叶结点的所有数据记录
        std::cout << "key = " << leaf.keys[pos] << " value = " << leaf.values[pos] << std::endl;
        ++pos;
      }
      // 如果当前叶结点是最后一个叶结点，则退出循环
      if (!leaf.nxt) break;
      // 否则，就找下一个叶结点
      readLeaf(leaf, leaf.nxt);
      pos = 0;
    } while (true);
  }

  bool contains(const KeyType &key) {
    ValueType tmp;
    return find(key, tmp);
  }

  void remove(const KeyType &key) {
    if (remove(key, root)) {
      // 若根结点只有一个子结点，并且该子结点不是叶结点，则将该子结点设置成新的根结点
      if (!root.isBottomNode && root.dataCount == 1) {
        TreeNode son;
        readTreeNode(son, root.childrenPos[0]);
        emptyTreeNode.insert(emptyTreeNode.length(), root.pos);
        root = son;
      }
    }
  }

  // 修改记录，等价于先删除再插入
  void modify(const KeyType &key, const ValueType &newValue) {
    remove(key);
    insert(key, newValue);
  }

  // 清空B+树
  void clear() {
    treeNodeFile.close();
    leafFile.close();
    emptyTreeNode.clear();
    emptyLeaf.clear();
    initialize();
  }

 private:
  // 递归插入数据记录，返回该结点插入记录后是否满足B+树对子结点数的限制；如不满足，需要递归调整
  bool insert(const KeyType &key, const ValueType &value, TreeNode &currentNode) {
    // 如果是最后一层非叶结点，则直接插入
    if (currentNode.isBottomNode) {
      Leaf leaf;
      // 二分查找出插入的位置
      int nodePos = binarySearchTreeNode(key, currentNode);
      readLeaf(leaf, currentNode.childrenPos[nodePos]);
      int leafPos = binarySearchLeaf(key, leaf);
      if (leafPos < leaf.dataCount &&leaf.keys[leafPos] == key) {
        return false;  // 如果已经存在key，则插入失败，后续不需要调整
      }
      leaf.dataCount++, sizeData++;
      for (int i = leaf.dataCount - 1; i > leafPos; i--) {
        leaf.keys[i] = leaf.keys[i - 1];
        leaf.values[i] = leaf.values[i - 1];
      }
      leaf.keys[leafPos] = key;
      leaf.values[leafPos] = value;

      // 如果叶结点满了，则需要执行分裂
      if (leaf.dataCount == L) {
        Leaf newLeaf;
        newLeaf.pos = getNewLeafPos();
        newLeaf.nxt = leaf.nxt;
        leaf.nxt = newLeaf.pos;
        int mid = L / 2;
        for (int i = 0; i < mid; i++) {
          newLeaf.keys[i] = leaf.keys[i + mid];
          newLeaf.values[i] = leaf.values[i + mid];
        }
        leaf.dataCount = newLeaf.dataCount = mid;
        // 将分裂得到的两个叶结点写入文件
        writeLeaf(leaf);
        writeLeaf(newLeaf);
        // 更新父结点的子结点信息
        for (int i = currentNode.dataCount; i > nodePos + 1; i--) {
          currentNode.childrenPos[i] = currentNode.childrenPos[i - 1];
        }
        currentNode.childrenPos[nodePos + 1] = newLeaf.pos;
        for (int i = currentNode.dataCount - 1; i > nodePos; i--) {
          currentNode.septal[i] = currentNode.septal[i - 1];
        }
        currentNode.septal[nodePos] = leaf.keys[mid - 1];
        currentNode.dataCount++;

        // 如果父结点满了，则需要继续向上分裂
        if (currentNode.dataCount == M) {
          return true;
        } else {
          writeTreeNode(currentNode);
        }
        return false;
      }
      writeLeaf(leaf);
      return false;
    }
    TreeNode son;

    // 查找插入位置
    int now = binarySearchTreeNode(key, currentNode);
    readTreeNode(son, currentNode.childrenPos[now]);

    // 如果子结点插入记录后导致该结点的子结点数超过限制，则需要执行分裂
    if (insert(key, value, son)) {
      TreeNode newNode;
      newNode.pos = getNewTreeNodePos();
      newNode.isBottomNode = son.isBottomNode;
      int mid = M / 2;
      for (int i = 0; i < mid; i++) {
        newNode.childrenPos[i] = son.childrenPos[mid + i];
      }
      for (int i = 0; i < mid - 1; i++) {
        newNode.septal[i] = son.septal[mid + i];
      }
      newNode.dataCount = son.dataCount = mid;

      // 将分裂得到的新结点写入文件
      writeTreeNode(son);
      writeTreeNode(newNode);
      for (int i = currentNode.dataCount; i > now + 1; i--) {
        currentNode.childrenPos[i] = currentNode.childrenPos[i - 1];
      }
      currentNode.childrenPos[now + 1] = newNode.pos;
      for (int i = currentNode.dataCount - 1; i > now; i--) {
        currentNode.septal[i] = currentNode.septal[i - 1];
      }
      currentNode.septal[now] = son.septal[mid - 1];
      currentNode.dataCount++;

      // 父结点的子结点数变多，超过限制，需要继续分裂
      if (currentNode.dataCount == M) {
        return true;
      } else {
        writeTreeNode(currentNode);
      }
      return false;
    } else {
      return false;
    }
  }

  // 递归删除数据记录，返回该结点删除数据记录后是否满足B+树对子结点的限制的判断。如不满足，需要递归调整
  bool remove(const KeyType &key, TreeNode &currentNode) {
    if (currentNode.isBottomNode) {  // 如果已经到了最后一层非叶结点
      Leaf leaf;
      // 找到叶结点的位置
      int nodePos = binarySearchTreeNode(key, currentNode);
      // 读入叶结点
      readLeaf(leaf, currentNode.childrenPos[nodePos]);
      // 找到叶结点中被删除的数据记录的位置
      int leafPos = binarySearchLeaf(key, leaf);
      if (leafPos == leaf.dataCount || !(leaf.keys[leafPos] == key)) {
        return false;  // 如果找不到key，则删除失败，后续不需要调整
      }
      leaf.dataCount--, sizeData--;
      for (int i = leafPos; i < leaf.dataCount; i++) {
        leaf.keys[i] = leaf.keys[i + 1];
        leaf.values[i] = leaf.values[i + 1];
      }
      if (leaf.dataCount < L / 2) {  // 并块
        Leaf pre, nxt;
        // 若左侧兄弟结点存在
        if (nodePos - 1 >= 0) {
          readLeaf(pre, currentNode.childrenPos[nodePos - 1]);
          // 若左侧兄弟结点有足够多的儿子可以借
          if (pre.dataCount > L / 2) {
            leaf.dataCount++, pre.dataCount--;
            for (int i = leaf.dataCount - 1; i > 0; i--) {
              leaf.keys[i] = leaf.keys[i - 1];
              leaf.values[i] = leaf.values[i - 1];
            }
            leaf.keys[0] = pre.keys[pre.dataCount];
            leaf.values[0] = pre.values[pre.dataCount];
            currentNode.septal[nodePos - 1] = pre.keys[pre.dataCount - 1];
            writeLeaf(leaf);
            writeLeaf(pre);
            writeTreeNode(currentNode);
            return false;
          }
        }
        // 若右侧兄弟结点存在
        if (nodePos + 1 < currentNode.dataCount) {
          readLeaf(nxt, currentNode.childrenPos[nodePos + 1]);
          // 若右侧兄弟结点有足够多的儿子可以借
          if (nxt.dataCount > L / 2) {
            leaf.dataCount++, nxt.dataCount--;
            leaf.keys[leaf.dataCount - 1] = nxt.keys[0];
            leaf.values[leaf.dataCount - 1] = nxt.values[0];
            currentNode.septal[nodePos] = nxt.keys[0];
            for (int i = 0; i < nxt.dataCount; i++) {
              nxt.keys[i] = nxt.keys[i + 1];
              nxt.values[i] = nxt.values[i + 1];
            }
            writeLeaf(leaf);
            writeLeaf(nxt);
            writeTreeNode(currentNode);
            return false;
          }
        }
        // 左、右都没有兄弟结点可以借儿子
        // 左侧有兄弟结点，则与其合并
        if (nodePos - 1 >= 0) {
          for (int i = 0; i < leaf.dataCount; i++) {
            pre.keys[pre.dataCount + i] = leaf.keys[i];
            pre.values[pre.dataCount + i] = leaf.values[i];
          }
          pre.dataCount += leaf.dataCount;
          pre.nxt = leaf.nxt;
          writeLeaf(pre);
          emptyLeaf.insert(emptyLeaf.length(), leaf.pos);
          // 更新父结点的键值和数据 
          currentNode.dataCount--;
          for (int i = nodePos; i < currentNode.dataCount; i++) {
            currentNode.childrenPos[i] = currentNode.childrenPos[i + 1];
          }
          for (int i = nodePos - 1; i < currentNode.dataCount - 1; i++) {
            currentNode.septal[i] = currentNode.septal[i + 1];
          }
          // 父结点不满足B+树的性质，需要继续调整
          if (currentNode.dataCount < M / 2) {
            return true;
          } else {

          }
          writeTreeNode(currentNode);
          return false;
        }
        // 右侧有兄弟结点，则与其合并
        if (nodePos + 1 < currentNode.dataCount) {
          for (int i = 0; i < nxt.dataCount; i++) {
            leaf.keys[leaf.dataCount + i] = nxt.keys[i];
            leaf.values[leaf.dataCount + i] = nxt.values[i];
          }
          leaf.dataCount += nxt.dataCount;
          leaf.nxt = nxt.nxt;
          writeLeaf(leaf);
          emptyLeaf.insert(emptyLeaf.length(), nxt.pos);
          currentNode.dataCount--;
          // 更新父结点的键值和数据
          for (int i = nodePos + 1; i < currentNode.dataCount; i++) {
            currentNode.childrenPos[i] = currentNode.childrenPos[i + 1];
          }
          for (int i = nodePos; i < currentNode.dataCount - 1; i++) {
            currentNode.septal[i] = currentNode.septal[i + 1];
          }
          // 父结点不满足B+树的性质，需要继续调整
          if (currentNode.dataCount < M / 2) {
            return true;
          } else {
            writeTreeNode(currentNode);
            return false;
          }
        }
        writeLeaf(leaf);
      } else {
        writeLeaf(leaf);
      }
      return false;
    }

    TreeNode son;
    // 找到删除位置
    int now = binarySearchTreeNode(key, currentNode);
    readTreeNode(son, currentNode.childrenPos[now]);
    // 删完后子结点的个数变少，使得该结点不满足B+树的限制，需要调整
    if (remove(key, son)) {
      TreeNode pre, nxt;
      // 若有左侧兄弟结点
      if (now - 1 >= 0) {
        readTreeNode(pre, currentNode.childrenPos[now - 1]);
        // 若左侧兄弟结点有足够多的儿子可以借
        if (pre.dataCount > M / 2) {
          son.dataCount++, pre.dataCount--;
          for (int i = son.dataCount - 1; i > 0; i--) {
            son.childrenPos[i] = son.childrenPos[i - 1];
          }
          for (int i = son.dataCount - 2; i > 0; i--) {
            son.septal[i] = son.septal[i - 1];
          }
          son.childrenPos[0] = pre.childrenPos[pre.dataCount];
          son.septal[0] = currentNode.septal[now - 1];
          currentNode.septal[now - 1] = pre.septal[pre.dataCount - 1];
          writeTreeNode(son);
          writeTreeNode(pre);
          writeTreeNode(currentNode);
          return false;
        }
      }
      // 若有右侧兄弟结点
      if (now + 1 < currentNode.dataCount) {
        readTreeNode(nxt, currentNode.childrenPos[now + 1]);
        // 若右侧兄弟结点有足够多的儿子可以借 
        if (nxt.dataCount > M / 2) {
          son.dataCount++, nxt.dataCount--;
          son.childrenPos[son.dataCount - 1] = nxt.childrenPos[0];
          son.septal[son.dataCount - 2] = currentNode.septal[now];
          currentNode.septal[now] = nxt.septal[0];
          for (int i = 0; i < nxt.dataCount; i++) {
            nxt.childrenPos[i] = nxt.childrenPos[i + 1];
          }
          for (int i = 0; i < nxt.dataCount - 1; i++) {
            nxt.septal[i] = nxt.septal[i + 1];
          }
          writeTreeNode(son);
          writeTreeNode(nxt);
          writeTreeNode(currentNode);
          return false;
        }
      }
      // 若有左侧兄弟结点，则和左侧兄弟结点合并 
      if (now - 1 >= 0) {
        for (int i = 0; i < son.dataCount; i++) {
          pre.childrenPos[pre.dataCount + i] = son.childrenPos[i];
        }
        pre.septal[pre.dataCount - 1] = currentNode.septal[now - 1];
        for (int i = 0; i < son.dataCount - 1; i++) {
          pre.septal[pre.dataCount + i] = son.septal[i];
        }
        pre.dataCount += son.dataCount;
        writeTreeNode(pre);
        emptyTreeNode.insert(emptyTreeNode.length(), son.pos);
        currentNode.dataCount--;
        for (int i = now; i < currentNode.dataCount; i++) {
          currentNode.childrenPos[i] = currentNode.childrenPos[i + 1];
        }
        for (int i = now - 1; i < currentNode.dataCount - 1; i++) {
          currentNode.septal[i] = currentNode.septal[i + 1];
        }
        if (currentNode.dataCount < M / 2) {
          return true;
        }
        writeTreeNode(currentNode);
        return false;
      }
      // 若有右侧兄弟结点，则和右侧兄弟结点合并
      if (now + 1 < currentNode.dataCount) {
        for (int i = 0; i < nxt.dataCount; i++) {
          son.childrenPos[son.dataCount + i] = nxt.childrenPos[i];
        }
        son.septal[son.dataCount - 1] = currentNode.septal[now];
        for (int i = 0; i < nxt.dataCount - 1; i++) {
          son.septal[son.dataCount + i] = nxt.septal[i];
        }
        son.dataCount += nxt.dataCount;
        writeTreeNode(son);
        emptyTreeNode.insert(emptyTreeNode.length(), nxt.pos);
        currentNode.dataCount--;
        for (int i = now + 1; i < currentNode.dataCount; i++) {
          currentNode.childrenPos[i] = currentNode.childrenPos[i + 1];
        }
        for (int i = now; i < currentNode.dataCount - 1; i++) {
          currentNode.septal[i] = currentNode.septal[i + 1];
        }
        if (currentNode.dataCount < M / 2) {
          return true;
        }
        writeTreeNode(currentNode);
        return false;
      }
    }
    return false;
  }

  // 将非叶结点写入文件
  void writeTreeNode(TreeNode &node) {
    treeNodeFile.seekp(node.pos * sizeof(TreeNode) + headerLengthOfTreeNodeFile);
    treeNodeFile.write(reinterpret_cast<char *>(&node), sizeof(TreeNode));
  }

  // 将叶结点写入文件
  void writeLeaf(Leaf &leaf) {
    leafFile.seekp(leaf.pos * sizeof(Leaf) + headerLengthOfLeafFile);
    leafFile.write(reinterpret_cast<char *>(&leaf), sizeof(Leaf));
  }

  // 读取非叶结点
  void readTreeNode(TreeNode &node, int pos) {
    treeNodeFile.seekg(pos * sizeof(TreeNode) + headerLengthOfTreeNodeFile);
    treeNodeFile.read(reinterpret_cast<char *>(&node), sizeof(TreeNode));
  }

  // 读取叶结点
  void readLeaf(Leaf &lef, int pos) {
    leafFile.seekg(pos * sizeof(Leaf) + headerLengthOfLeafFile);
    leafFile.read(reinterpret_cast<char *>(&lef), sizeof(Leaf));
  }

  // 在叶结点中二分查找，返回第一个键值大于或等于key的位置
  int binarySearchLeaf(const KeyType &key, const Leaf &lef) {
    int l = -1, r = lef.dataCount - 1;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (!(lef.keys[mid] < key)) r = mid - 1;
      else l = mid;
    }
    return l + 1;
  }

  // 在非叶结点中二分查找，返回第一个键值大于或等于key的位置
  int binarySearchTreeNode(const KeyType &key, const TreeNode &node) {
    int l = -1, r = node.dataCount - 2;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (!(node.septal[mid] < key)) r = mid - 1;
      else l = mid;
    }
    return l + 1;
  }

  // 对文件做一些初始化操作
  void initialize() {
    treeNodeFile.open(treeNodeFileName, std::ios::out);
    leafFile.open(leafFileName, std::ios::out);
    root.isBottomNode = root.pos = root.childrenPos[0] = 1, sizeData = 0;
    root.dataCount = 1;
    rearLeaf = rearTreeNode = 1;
    Leaf initLeaf;
    initLeaf.nxt = initLeaf.dataCount = 0;
    initLeaf.pos = 1;
    writeLeaf(initLeaf);
    treeNodeFile.close();
    leafFile.close();
    treeNodeFile.open(treeNodeFileName);
    leafFile.open(leafFileName);
  }

  // 获取一个新的非叶结点的位置
  int getNewTreeNodePos() {
    if (!emptyTreeNode.length()) {  //如果没有之前删除的结点，则直接在后面加
      return ++rearTreeNode;
    } else {  // 否则就从删除的结点中取出一个
      int newIndex = emptyTreeNode.visit(emptyTreeNode.length() - 1);
      emptyTreeNode.remove(emptyTreeNode.length() - 1);
      return newIndex;
    }
  }

  // 获取一个新的叶结点的位置
  int getNewLeafPos() {
    if (!emptyLeaf.length()) {
      return ++rearLeaf;
    } else {
      int newIndex = emptyLeaf.visit(emptyLeaf.length() - 1);
      emptyLeaf.remove(emptyLeaf.length() - 1);
      return newIndex;
    }
  }
};

#endif //BPTREE_HPP_BPTREE_HPP
