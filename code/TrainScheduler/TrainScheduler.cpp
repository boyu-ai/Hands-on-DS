// 代码清单2-15　TrainScheduler 类的实现

#include "TrainScheduler.h"

namespace trainsys {
TrainScheduler::TrainScheduler() {}

TrainScheduler::~TrainScheduler() {}

void TrainScheduler::addStation(const StationID &station) {
  stations.insert(stations.length(), station);
}

void TrainScheduler::insertStation(int i, const StationID &station) {
  stations.insert(i, station);
}

void TrainScheduler::removeStation(int i) { stations.remove(i); }

int TrainScheduler::findStation(const StationID &station) {
  return stations.search(station);
}

void TrainScheduler::traverseStation() {
  for (int i = 0; i < stations.length(); i++) {
    std::cout << stations.visit(i) << " ";
  }
  std::cout << std::endl;
}

void TrainScheduler::setTrainID(const TrainID &id) {
  this->trainID = id;
}

void TrainScheduler::setSeatNumber(int seatNum) {
  this->seatNum = seatNum;
}

void TrainScheduler::setPrice(int price[]) {
  for (int i = 0; i + 1 < stations.length(); i++) {
    this->price.insert(i, price[i]);
  }
}

void TrainScheduler::setDuration(int duration[]) {
  for (int i = 0; i + 1 < stations.length(); i++) {
    this->duration.insert(i, duration[i]);
  }
}

TrainID TrainScheduler::getTrainID() const { return trainID; }

int TrainScheduler::getSeatNum() const { return seatNum; }

void TrainScheduler::getStations(seqList<StationID> *stations) const {
  stations = new seqList<StationID>(this->stations);
}

void TrainScheduler::getDuration(seqList<int> *duration) const {
  duration = new seqList<int>(this->duration);
}

void TrainScheduler::getPrice(seqList<int> *price) const {
  price = new seqList<int>(this->price);
}

}  // namespace trainsys