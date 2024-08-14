#include "TrainScheduler.h"


namespace trainsys {
    TrainScheduler::TrainScheduler() {
        passingStationNum = 0;
    }

    TrainScheduler::~TrainScheduler() {}

    void TrainScheduler::addStation(const StationID &station) {
        this->stations[passingStationNum++] = station;
    }

    void TrainScheduler::insertStation(int i, const StationID &station) {
        for (int j = passingStationNum; j > i; j--) {
            stations[j] = stations[j - 1];
        }
        stations[i] = station;
        passingStationNum++;
    }

    void TrainScheduler::removeStation(int i) {
        for (int j = i; j < passingStationNum - 1; j++) {
            stations[j] = stations[j + 1];
        }
        passingStationNum--;
    }

    int TrainScheduler::findStation(const StationID &stationID) {
        for (int i = 0; i + 1 < passingStationNum; i++) {
            if (stations[i] == stationID) return i;
        }
        return -1;
    }
    
    void TrainScheduler::traverseStation() {

    }

    void TrainScheduler::setTrainID(const TrainID &id) {
        this->trainID = id;
    }

    void TrainScheduler::setPrice(const int price[]) {
        for (int i = 0; i + 1 < passingStationNum; i++) {
            this->price[i] = price[i];
        }
    }

    void TrainScheduler::setDuration(const int duration[]) {
        for (int i = 0; i + 1 < passingStationNum; i++) {
            this->duration[i] = duration[i];
        }
    }

    void TrainScheduler::setSeatNumber(int seatNum) {
        this->seatNum = seatNum;
    }

    TrainID TrainScheduler::getTrainID() const {
        return trainID;
    }

    int TrainScheduler::getSeatNum() const {
        return seatNum;
    }

    int TrainScheduler::getPassingStationNum() const {
        return passingStationNum;
    }

    StationID TrainScheduler::getStation(int i) const {
        return stations[i];
    }

    int TrainScheduler::getDuration(int i) const {
        return duration[i];
    }

    int TrainScheduler::getPrice(int i) const {
        return price[i];
    }

    void TrainScheduler::getStations(StationID* stations) const {
        stations = new StationID[passingStationNum];
        for (int i = 0; i < passingStationNum; i++) {
            stations[i] = this->stations[i];
        }
    }

    void TrainScheduler::getDuration(int* duration) const {
        duration = new int[passingStationNum - 1];
        for (int i = 0; i + 1 < passingStationNum; i++) {
            duration[i] = this->duration[i];
        }
    }

    void TrainScheduler::getPrice(int* price) const {
        price = new int[passingStationNum - 1];
        for (int i = 0; i + 1 < passingStationNum; i++) {
            price[i] = this->price[i];
        }
    }

    bool TrainScheduler::operator == (const TrainScheduler &rhs) const {
        return trainID == rhs.trainID;
    }

    bool TrainScheduler::operator != (const TrainScheduler &rhs) const {
        return trainID != rhs.trainID;
    }

    bool TrainScheduler::operator < (const TrainScheduler &rhs) const {
        return trainID < rhs.trainID;
    }

    std::ostream &operator << (std::ostream &os, const TrainScheduler &trainScheduler) {
        os << "TrainID: " << trainScheduler.trainID << std::endl;
        os << "SeatNum: " << trainScheduler.seatNum << std::endl;
        os << "PassingStationNum: " << trainScheduler.passingStationNum << std::endl;
        os << "Stations: ";
        for (int i = 0; i < trainScheduler.passingStationNum; i++) {
            os << trainScheduler.stations[i] << " ";
        }
        os << std::endl;
        os << "Duration: ";
        for (int i = 0; i + 1 < trainScheduler.passingStationNum; i++) {
            os << trainScheduler.duration[i] << " ";
        }
        os << std::endl;
        os << "Price: ";
        for (int i = 0; i + 1 < trainScheduler.passingStationNum; i++) {
            os << trainScheduler.price[i] << " ";
        }
        os << std::endl;
        return os;
    }
}
    
    
