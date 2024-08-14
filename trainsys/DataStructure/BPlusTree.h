#ifndef BPTREE_HPP_BPTREE_HPP
#define BPTREE_HPP_BPTREE_HPP

#include <vector>
#include <fstream>
#include "Pair.h"
#include "SearchTable.h"

namespace trainsys {

template<class KeyType, class ValueType, int M = 100, int L = 100>
class BPlusTree : public StorageSearchTable<KeyType, ValueType> {
private:
    std::fstream treeNodeFile, leafFile;  // 存放树节点的文件和叶子节点的文件
    int rearTreeNode, rearLeaf;           // 最后一个树节点的位置和最后一个叶子节点的位置
    int sizeData;                         // 数据的个数
    // 存放树节点的文件的头部长度（前面预留两个int的空间用来存储树节点数量和最后一个树节点位置）
    const int headerLengthOfTreeNodeFile = 2 * sizeof(int);
    // 存放叶子节点的文件的头部长度（前面预留两个int的空间用来存储叶子节点数量和最后一个叶子节点位置）
    const int headerLengthOfLeafFile = 2 * sizeof(int);   
    // 被删除的树节点和叶子节点的位置，在插入的时候优先使用这些位置 
    seqList<int> emptyTreeNode;
    seqList<int> emptyLeaf;

    // B+树的节点
    struct TreeNode {
        bool isBottomNode;  // 记录是否是叶子节点上面一层的节点
        int pos, dataCount; // pos是节点的位置，dataCount是节点中子节点的个数
        int childrenPos[M]; // 子节点的位置，0 base
        Pair<KeyType, ValueType> septal[M - 1]; // 各个子树之间的分隔关键字，0 base
    };

    // B+树的叶子节点
    struct Leaf {
        int nxt, pos;  // nxt是下一个叶子节点的位置，pos是当前叶子节点的位置
        int dataCount; // dataCount是当前叶子节点中数据的个数
        Pair<KeyType, ValueType> value[L];  // 存放数据，0 base
    };

    // 存放树节点的文件的名字和叶子节点的文件的名字
    std::string treeNodeFileName, leafFileName;
    // 树的根节点
    TreeNode root;

public:
    // 构造函数；从文件中读取必要信息，在内存中记录树的根节点，元素个数等关键信息
    explicit BPlusTree(const std::string &name) {
        treeNodeFileName = name + "_treeNodeFile", leafFileName = name + "_leafFile";
        // 打开文件，一个存放树节点，一个存放叶子节点
        treeNodeFile.open(treeNodeFileName);
        leafFile.open(leafFileName);
        if (!leafFile || !treeNodeFile) { // 如果文件不存在，就创建文件，并初始化
            initialize();
        } else {
            // 读取树节点文件的头部，得到树的根节点的位置和最后一个树节点的位置
            treeNodeFile.seekg(0), leafFile.seekg(0);
            int rootPos;
            treeNodeFile.read(reinterpret_cast<char *>(&rootPos), sizeof(int));
            treeNodeFile.read(reinterpret_cast<char *>(&rearTreeNode), sizeof(int));
            // 找到并读取树的根节点
            treeNodeFile.seekg(headerLengthOfTreeNodeFile + rootPos * sizeof(TreeNode));
            treeNodeFile.read(reinterpret_cast<char *>(&root), sizeof(TreeNode));
            // 最后一个树节点后面存放了被删除的树节点
            int treeNodeEmptySize, leafEmptySize;
            treeNodeFile.seekg(headerLengthOfTreeNodeFile + (rearTreeNode + 1) * sizeof(TreeNode));
            // 读取被删除的树节点的数量和位置
            treeNodeFile.read(reinterpret_cast<char *>(&treeNodeEmptySize), sizeof(int));
            for (int i = 0; i < treeNodeEmptySize; i++) {
                int data;
                treeNodeFile.read(reinterpret_cast<char *>(&data), sizeof(int));
                emptyTreeNode.pushBack(data);
            }
            // 读取叶子节点文件的头部，得到最后一个叶子节点的位置
            leafFile.read(reinterpret_cast<char *>(&rearLeaf), sizeof(int));
            // 插入的记录的数量存放在叶子节点文件的头部的第二个int中
            leafFile.read(reinterpret_cast<char *>(&sizeData), sizeof(int));
            // 最后一个叶子节点后面存放了被删除的叶子节点
            leafFile.seekg(headerLengthOfLeafFile + (rearLeaf + 1) * sizeof(Leaf));
            // 读取被删除的叶子节点的数量和位置
            leafFile.read(reinterpret_cast<char *>(&leafEmptySize), sizeof(int));
            for (int i = 0; i < leafEmptySize; i++) {
                int data;
                leafFile.read(reinterpret_cast<char *>(&data), sizeof(int));
                emptyLeaf.pushBack(data);
            }
        }
    }

    // 析构函数；将树的根节点，被删除的节点的位置等信息写入文件
    ~BPlusTree() {
        // 将树的根节点、最后一个树节点的位置写入文件
        treeNodeFile.seekp(0), leafFile.seekp(0);
        treeNodeFile.write(reinterpret_cast<char *>(&root.pos), sizeof(int));
        treeNodeFile.write(reinterpret_cast<char *>(&rearTreeNode), sizeof(int));
        // 将树的根节点写入文件
        writeTreeNode(root);
        // 将最后一个叶子节点的位置写入文件
        leafFile.write(reinterpret_cast<char *>(&rearLeaf), sizeof(int));
        // 将插入的记录的数量写入文件
        leafFile.write(reinterpret_cast<char *>(&sizeData), sizeof(int));
        // 将被删除的树节点和叶子节点的位置写入文件
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

    // 插入记录
    void insert(const KeyType &key, const ValueType &value) {
        if (insert(Pair<KeyType, ValueType>(key, value), root)) {  // 分裂根节点
            TreeNode newRoot;  // 创建一个新的根节点
            TreeNode newNode;  // 新的兄弟节点
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

    // 查询记录；返回一个vector，因为可能一个key对应多个value
    seqList<ValueType> find(const KeyType &key) {
        seqList<ValueType> ans;
        TreeNode p = root;
        Leaf leaf;
        if (p.dataCount == 0) {
            return ans;
        }
        while (!p.isBottomNode) {  // childrenPos[now]中元素小于等于Key[now] 循环找到叶节点
            readTreeNode(p, p.childrenPos[binarySearchTreeNode(key, p)]); 
        }
        readLeaf(leaf, p.childrenPos[binarySearchTreeNode(key, p)]);  // 找到叶子节点
        int now = binarySearchLeaf(key, leaf);  // 在叶子节点中二分查找，找到第一个大于等于key的位置
        while (now < leaf.dataCount && leaf.value[now].first == key) {  // 读取所有关键字等于key的记录
            ans.pushBack(leaf.value[now++].second);
        }
        while (leaf.nxt && now == leaf.dataCount) {  // 如果读完了这个叶子节点的信息，则寻找下一块
            readLeaf(leaf, leaf.nxt);
            now = 0;
            while (now < leaf.dataCount && leaf.value[now].first == key) {
                ans.pushBack(leaf.value[now++].second);
            }
        }
        return ans;
    }

    bool contains(const KeyType &key) {
        return !find(key).empty();
    }

    //* 需确保该key存在
    ValueType findFirst(const KeyType &key) {
        return find(key).visit(0);
    }

    void remove(const KeyType &key, const ValueType &value) {
        if (remove(Pair<KeyType, ValueType>(key, value), root)) {
            if (!root.isBottomNode && root.dataCount == 1) {  // 若根只有一个儿子，且根不为叶子，将儿子作为新的根
                TreeNode son;
                readTreeNode(son, root.childrenPos[0]);
                emptyTreeNode.pushBack(root.pos);
                root = son;
            }
        }
    }

    void removeFirst(const KeyType &key) {
        remove(key, findFirst(key));
    }

    // 修改记录，等价于先删除再插入
    void modify(const KeyType &key, const ValueType &oldValue, const ValueType &newValue) {
        remove(key, oldValue);
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
    // 递归插入记录，返回该节点插入记录后是否满足B+树对子节点数的限制；如不满足，需要递归调整
    bool insert(const Pair<KeyType, ValueType> &val, TreeNode &currentNode) {
        if (currentNode.isBottomNode) {  // 如果是叶子节点，直接插入
            Leaf leaf;
            // 查找插入位置
            int nodePos = binarySearchTreeNodeValue(val, currentNode);
            readLeaf(leaf, currentNode.childrenPos[nodePos]);
            int leafPos = binarySearchLeafValue(val, leaf);
            leaf.dataCount++, sizeData++;
            for (int i = leaf.dataCount - 1; i > leafPos; i--) {
                leaf.value[i] = leaf.value[i - 1];
            }
            leaf.value[leafPos] = val;
            if (leaf.dataCount == L) {  // 如果叶子节点满了，需要分裂
                Leaf newLeaf;
                newLeaf.pos = getNewLeafPos();
                newLeaf.nxt = leaf.nxt;
                leaf.nxt = newLeaf.pos;
                int mid = L / 2;
                for (int i = 0; i < mid; i++) {
                    newLeaf.value[i] = leaf.value[i + mid];
                }
                leaf.dataCount = newLeaf.dataCount = mid;
                // 将分裂得到的两个叶子节点写入文件
                writeLeaf(leaf);
                writeLeaf(newLeaf);
                // 更新父节点的子节点信息
                for (int i = currentNode.dataCount; i > nodePos + 1; i--) {
                    currentNode.childrenPos[i] = currentNode.childrenPos[i - 1];
                }
                currentNode.childrenPos[nodePos + 1] = newLeaf.pos;
                for (int i = currentNode.dataCount - 1; i > nodePos; i--) {
                    currentNode.septal[i] = currentNode.septal[i - 1];
                }
                currentNode.septal[nodePos] = leaf.value[mid - 1];
                currentNode.dataCount++;
                if (currentNode.dataCount == M) {  // 如果父亲节点满了，需要继续分裂
                    return true;
                } else writeTreeNode(currentNode);
                return false;
            }
            writeLeaf(leaf);
            return false;
        }
        TreeNode son;
        // 查找插入位置
        int now = binarySearchTreeNodeValue(val, currentNode);
        readTreeNode(son, currentNode.childrenPos[now]);
        if (insert(val, son)) {  // 如果子节点插入记录后导致该节点子节点数超过限制，需要分裂
            TreeNode newNode;
            newNode.pos = getNewTreeNodePos(), newNode.isBottomNode = son.isBottomNode;
            int mid = M / 2;
            for (int i = 0; i < mid; i++) {
                newNode.childrenPos[i] = son.childrenPos[mid + i];
            }
            for (int i = 0; i < mid - 1; i++) {
                newNode.septal[i] = son.septal[mid + i];
            }
            newNode.dataCount = son.dataCount = mid;
            // 将分裂得到的新节点写入文件
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
            if (currentNode.dataCount == M) {  // 父亲节点子节点数变多，超过限制，需要继续分裂
                return true;
            } else writeTreeNode(currentNode);
            return false;
        } else return false;
    }

    // 递归删除记录，返回该节点删除记录后是否满足B+树对子节点数的限制；如不满足，需要递归调整
    bool remove(const Pair<KeyType, ValueType> &val, TreeNode &currentNode) {
        if (currentNode.isBottomNode) {  // 如果已经到了叶子层
            Leaf leaf;
            int nodePos = binarySearchTreeNodeValue(val, currentNode);  // 找到叶节点的位置
            readLeaf(leaf, currentNode.childrenPos[nodePos]);  // 读入叶节点
            int leafPos = binarySearchLeafValue(val, leaf);  // 找到数据在叶节点中的位置
            if (leafPos == leaf.dataCount || !checkPairEqual(leaf.value[leafPos], val)) {
                return false;  // 如果找不到键值对val，删除失败，后续不需要调整
            }
            leaf.dataCount--, sizeData--;
            for (int i = leafPos; i < leaf.dataCount; i++) {
                leaf.value[i] = leaf.value[i + 1];  // 移动删除数据
            }
            if (leaf.dataCount < L / 2) {  // 并块
                Leaf pre, nxt;
                if (nodePos - 1 >= 0) {  // 若有前面的兄弟
                    readLeaf(pre, currentNode.childrenPos[nodePos - 1]);
                    if (pre.dataCount > L / 2) {  // 若前面的兄弟有足够多的儿子可以借
                        leaf.dataCount++, pre.dataCount--;
                        for (int i = leaf.dataCount - 1; i > 0; i--) {
                            leaf.value[i] = leaf.value[i - 1];
                        }
                        leaf.value[0] = pre.value[pre.dataCount];
                        currentNode.septal[nodePos - 1] = pre.value[pre.dataCount - 1];
                        writeLeaf(leaf);
                        writeLeaf(pre);
                        writeTreeNode(currentNode);
                        return false;
                    }
                }
                if (nodePos + 1 < currentNode.dataCount) {  // 若有后面的兄弟
                    readLeaf(nxt, currentNode.childrenPos[nodePos + 1]);
                    if (nxt.dataCount > L / 2) {  // 若后面的兄弟有足够多的儿子借
                        leaf.dataCount++, nxt.dataCount--;
                        leaf.value[leaf.dataCount - 1] = nxt.value[0];
                        currentNode.septal[nodePos] = nxt.value[0];
                        for (int i = 0; i < nxt.dataCount; i++) {
                            nxt.value[i] = nxt.value[i + 1];
                        }
                        writeLeaf(leaf);
                        writeLeaf(nxt);
                        writeTreeNode(currentNode);
                        return false;
                    }
                }
                // 前后都没有兄弟可以借儿子
                if (nodePos - 1 >= 0) {  // 前面有兄弟 和前面合并
                    for (int i = 0; i < leaf.dataCount; i++) {
                        pre.value[pre.dataCount + i] = leaf.value[i];
                    }
                    pre.dataCount += leaf.dataCount;
                    pre.nxt = leaf.nxt;
                    writeLeaf(pre);
                    emptyLeaf.pushBack(leaf.pos);
                    // 更新fa的关键字和数据
                    currentNode.dataCount--;
                    for (int i = nodePos; i < currentNode.dataCount; i++) {
                        currentNode.childrenPos[i] = currentNode.childrenPos[i + 1];
                    }
                    for (int i = nodePos - 1; i < currentNode.dataCount - 1; i++) {
                        currentNode.septal[i] = currentNode.septal[i + 1];
                    }
                    if (currentNode.dataCount < M / 2) {  // 父亲不满足限制，需要继续调整
                        return true;
                    }
                    writeTreeNode(currentNode);
                    return false;
                }
                if (nodePos + 1 < currentNode.dataCount) {  // 后面有兄弟 和后面合并
                    for (int i = 0; i < nxt.dataCount; i++) {
                        leaf.value[leaf.dataCount + i] = nxt.value[i];
                    }
                    leaf.dataCount += nxt.dataCount;
                    leaf.nxt = nxt.nxt;
                    writeLeaf(leaf);
                    emptyLeaf.pushBack(nxt.pos);
                    currentNode.dataCount--;
                    // 更新fa的关键字和数据
                    for (int i = nodePos + 1; i < currentNode.dataCount; i++) {
                        currentNode.childrenPos[i] = currentNode.childrenPos[i + 1];
                    }
                    for (int i = nodePos; i < currentNode.dataCount - 1; i++) {
                        currentNode.septal[i] = currentNode.septal[i + 1];
                    }
                    if (currentNode.dataCount < M / 2) {  // 父亲不满足限制，需要继续调整
                        return true;
                    }
                    writeTreeNode(currentNode);
                    return false;
                }
                writeLeaf(leaf);
            } else writeLeaf(leaf);
            return false;
        }
        TreeNode son;
        int now = binarySearchTreeNodeValue(val, currentNode);
        readTreeNode(son, currentNode.childrenPos[now]);
        if (remove(val, son)) {  // 删完后子节点数目变少了，使得该节点不满足B+树的限制，需要调整
            TreeNode pre, nxt;
            if (now - 1 >= 0) {  // 若有前面的兄弟
                readTreeNode(pre, currentNode.childrenPos[now - 1]);
                if (pre.dataCount > M / 2) {  // 若前面的兄弟有足够多的儿子可以借
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
            if (now + 1 < currentNode.dataCount) {  // 若有后面的兄弟
                readTreeNode(nxt, currentNode.childrenPos[now + 1]);
                if (nxt.dataCount > M / 2) {  // 若后面的兄弟有足够多的儿子借
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
            if (now - 1 >= 0) {  // 若有前面的兄弟，和前面的兄弟合并
                for (int i = 0; i < son.dataCount; i++) {
                    pre.childrenPos[pre.dataCount + i] = son.childrenPos[i];
                }
                pre.septal[pre.dataCount - 1] = currentNode.septal[now - 1];
                for (int i = 0; i < son.dataCount - 1; i++) {
                    pre.septal[pre.dataCount + i] = son.septal[i];
                }
                pre.dataCount += son.dataCount;
                writeTreeNode(pre);
                emptyTreeNode.pushBack(son.pos);
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
            if (now + 1 < currentNode.dataCount) {  // 若有后面的兄弟，和后面的兄弟合并
                for (int i = 0; i < nxt.dataCount; i++) {
                    son.childrenPos[son.dataCount + i] = nxt.childrenPos[i];
                }
                son.septal[son.dataCount - 1] = currentNode.septal[now];
                for (int i = 0; i < nxt.dataCount - 1; i++) {
                    son.septal[son.dataCount + i] = nxt.septal[i];
                }
                son.dataCount += nxt.dataCount;
                writeTreeNode(son);
                emptyTreeNode.pushBack(nxt.pos);
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

    // 将树节点写入文件
    void writeTreeNode(TreeNode &node) {
        treeNodeFile.seekg(node.pos * sizeof(TreeNode) + headerLengthOfTreeNodeFile);
        treeNodeFile.write(reinterpret_cast<char *>(&node), sizeof(TreeNode));
    }

    // 将叶子节点写入文件
    void writeLeaf(Leaf &leaf) {
        leafFile.seekg(leaf.pos * sizeof(Leaf) + headerLengthOfLeafFile);
        leafFile.write(reinterpret_cast<char *>(&leaf), sizeof(Leaf));
    }

    // 读取树节点
    void readTreeNode(TreeNode &node, int pos) {
        treeNodeFile.seekg(pos * sizeof(TreeNode) + headerLengthOfTreeNodeFile);
        treeNodeFile.read(reinterpret_cast<char *>(&node), sizeof(TreeNode));
    }

    // 读取叶子节点
    void readLeaf(Leaf &lef, int pos) {
        leafFile.seekg(pos * sizeof(Leaf) + headerLengthOfLeafFile);
        leafFile.read(reinterpret_cast<char *>(&lef), sizeof(Leaf));
    }

    // 在叶子节点中二分查找，返回第一个关键字大于等于key，且键值大于等于val的位置
    int binarySearchLeafValue(const Pair<KeyType, ValueType> &val, const Leaf &lef) {
        int l = 0, r = lef.dataCount - 1, ans = lef.dataCount;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (checkPairLess(lef.value[mid], val)) l = mid + 1;
            else r = mid - 1, ans = mid;
        }
        return ans;
    }

    // 在树节点中二分查找，返回第一个关键字大于等于key，且键值大于等于val的位置
    int binarySearchTreeNodeValue(const Pair<KeyType, ValueType> &val, const TreeNode &node) {
        int l = -1, r = node.dataCount - 2, ans = node.dataCount - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (checkPairLess(node.septal[mid], val)) l = mid + 1;
            else r = mid - 1, ans = mid;
        }
        return ans;
    }

    // 在叶子节点中二分查找，返回第一个关键字大于等于key的位置
    int binarySearchLeaf(const KeyType &key, const Leaf &lef) {
        int l = 0, r = lef.dataCount - 1, ans = lef.dataCount;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (lef.value[mid].first < key) l = mid + 1;
            else r = mid - 1, ans = mid;
        }
        return ans;
    }

    // 在树节点中二分查找，返回第一个关键字大于等于key的位置
    int binarySearchTreeNode(const KeyType &key, const TreeNode &node) {
        int l = 0, r = node.dataCount - 2, ans = node.dataCount - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (node.septal[mid].first < key) l = mid + 1;
            else r = mid - 1, ans = mid;
        }
        return ans;
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

    // 获取一个新的树节点的位置
    int getNewTreeNodePos() {
        if (emptyTreeNode.empty()) {  // 如果没有先前删除的节点，就直接在后面加
            return ++rearTreeNode;
        } else {  // 否则就从删除的节点中取出一个
            int newIndex = emptyTreeNode.back();
            emptyTreeNode.popBack();
            return newIndex;
        }
    }

    // 获取一个新的叶子节点的位置
    int getNewLeafPos() {
        if (emptyLeaf.empty()) {
            return ++rearLeaf;
        } else {
            int newIndex = emptyLeaf.back();
            emptyLeaf.popBack();
            return newIndex;
        }
    }
};

}

#endif //BPTREE_HPP_BPTREE_HPP
