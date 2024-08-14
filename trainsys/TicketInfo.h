#ifndef TICKETINFO_H_
#define TICKETINFO_H_

#include "Utils.h"

namespace trainsys {

struct TicketInfo {
    TrainID trainID;
    StationID departureStation;
    StationID arrivalStation;
    int seatNum;
    int price;
    int duration;
    Date date;

    bool operator == (const TicketInfo &rhs) const {
        return trainID == rhs.trainID && departureStation == rhs.departureStation && 
               arrivalStation == rhs.arrivalStation && seatNum == rhs.seatNum && price == rhs.price && 
               duration == rhs.duration && date == rhs.date;
    }

    bool operator != (const TicketInfo &rhs) const {
        return !(*this == rhs);
    }

    bool operator < (const TicketInfo &rhs) const {
        if (trainID != rhs.trainID) {
            return trainID < rhs.trainID;
        } else if (departureStation != rhs.departureStation) {
            return departureStation < rhs.departureStation;
        } else if (arrivalStation != rhs.arrivalStation) {
            return arrivalStation < rhs.arrivalStation;
        } else if (date != rhs.date) {
            return date < rhs.date;
        } else if (seatNum != rhs.seatNum) {
            return seatNum < rhs.seatNum;
        } else if (price != rhs.price) {
            return price < rhs.price;
        } else {
            return duration < rhs.duration;
        }
    }

    friend std::ostream &operator << (std::ostream &os, const TicketInfo &ticketInfo) {
        os << "TrainID: " << ticketInfo.trainID << std::endl;
        os << "Departure Station: " << ticketInfo.departureStation << std::endl;
        os << "Arrival Station: " << ticketInfo.arrivalStation << std::endl;
        os << "Seat Number: " << ticketInfo.seatNum << std::endl;
        os << "Price: " << ticketInfo.price << std::endl;
        os << "Duration: " << ticketInfo.duration << std::endl;
        os << "Date: " << ticketInfo.date << std::endl;
        return os;
    }
};



}

#endif 