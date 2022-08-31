//
//  GuestManager.cpp
//  Project 1
//
//  Created by Sal on 3/2/22.
//
#include "GuestManager.h"
#include <iostream>
#include <vector>
#include <stdio.h>

Guest::Guest(GuestType guesttype,RoomType roomtype, int duration){ //paramterized construvotr
    this->guesttype = guesttype;
    this->roomtype = roomtype;
    this->duration = duration;
}
GuestType Guest::GetGuesttype() const {
    return guesttype;
}
RoomType Guest::GetRoomType() const {
    return roomtype;
}
int Guest::getBookedDays() const {
    return duration;
}
//DERIVED CLASS IMPLEMENTATION
//FAMILY
Family::Family(GuestType guesttype, RoomType roomtype, int duration) : Guest(guesttype, roomtype, duration){};
int Family::GetRoomBusyDays() const{
    return duration;
}
int Family::GetAdditionalIncome() const {
    return 0;
    
//ROCKSTAR
}
Rockstar::Rockstar(GuestType guesttype, RoomType roomtype, int duration) : Guest(guesttype, roomtype, duration){};
int Rockstar::GetRoomBusyDays()const {
    return duration + 10;
}
int Rockstar::GetAdditionalIncome()const {
    return 0;
}
//BUSINESSMAN
Businessman::Businessman(GuestType guesttype, RoomType roomtype, int duration, int additionalIncome) : Guest(guesttype, roomtype, duration){
    this->additionalIncome = additionalIncome;
}
int Businessman::GetRoomBusyDays() const {
    return duration;
}
int Businessman::GetAdditionalIncome() const {
    return additionalIncome;
}

//GUESTMANAGER IMPLEMENTATION
GuestManager::GuestManager(int val_ofStandardRooms,int val_dayPriceStandard, int val_OfComfortRooms, int val_dayPriceComfort){
    ofstandardRooms = val_ofStandardRooms;
    dayPriceStandard = val_dayPriceStandard;
    ofComfortRooms = val_OfComfortRooms;
    dayPriceComfort = val_dayPriceComfort;
}
bool GuestManager::AddGuest(GuestType guesttype, RoomType roomtype, int stayDays, int additionalIncome){
        Guest* g = nullptr;
        switch(guesttype){
            case GuestType::Family:
                g = new Family(guesttype, roomtype, stayDays);
                break;
            case GuestType::Rockstar: //Bad exec code 
                g = new Rockstar(guesttype, roomtype, stayDays);
                break;
            case GuestType::Businessman:
                g = new Businessman(guesttype, roomtype,stayDays, additionalIncome);
        }
        if(g == nullptr){ // check if g is a valid pointer
            return false;
        }
        int counterS = 0;
        int counterC = 0;
    for(int i = 0; i < (int)rooms.size();i++){
        Guest* r = rooms[i];
        if(r->GetRoomType() == RoomType::Standard){
            counterS++;
        }else if(r->GetRoomType() == RoomType::Comfort){
            counterC++;
        }
    }
    if(roomtype == RoomType::Standard){
        if(counterS < ofstandardRooms){
            rooms.emplace_back(g);
            return true;
        }else{
            return false;
        }

    }
    if(roomtype == RoomType::Comfort){
        if(counterC < ofComfortRooms){
            rooms.emplace_back(g);
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool GuestManager::IsAvailable(RoomType roomtype, int inDays){
    int counterS = 0;
    int counterC = 0;
    for(int i = 0; i < (int)rooms.size();i++){
        Guest* r = rooms[i];
        if(r->GetRoomType() == roomtype){
            int duration  = r->GetRoomBusyDays();
            if(duration == inDays){
                return true;
            }
        }
        if(r->GetRoomType() == RoomType::Standard){
            counterS++;
        }else if(r->GetRoomType() == RoomType::Comfort){
            counterC++;
        }
    }
    if(roomtype == RoomType::Standard){
        if(counterS < ofstandardRooms){
            return true;
        }
    }else if(roomtype == RoomType::Comfort){
        if(counterC < ofComfortRooms){
            return true;
        }
    }
    return false;
}

int GuestManager::IncomingProfit(){
    int counter = 0;
    for(int i = 0; i < (int)rooms.size();i++){
        Guest* r = rooms[i];
        if(r != nullptr){
            if(r->GetRoomType() == RoomType::Standard){
                counter += (r->GetAdditionalIncome()*r->getBookedDays()) + (dayPriceStandard * r->getBookedDays());
            }
            if(r->GetRoomType() == RoomType::Comfort){
                counter += (r->GetAdditionalIncome()*r->getBookedDays()) + (dayPriceComfort * r->getBookedDays());
            }
            
        }
    }
    return counter;
}

float GuestManager::EarningEfficiency(){
    double current_per_day_income = 0;
    double max_per_day_income = 0;
    for(int i = 0; i < (int)rooms.size();i++){
        Guest* r = rooms[i];
        if(r != nullptr){
            if(r->GetRoomType() == RoomType::Standard){
                current_per_day_income += r->GetAdditionalIncome() + dayPriceStandard;
            }
            if(r->GetRoomType() == RoomType::Comfort){
                current_per_day_income += r->GetAdditionalIncome() + dayPriceComfort;
            }
        }
    }
    max_per_day_income = dayPriceStandard * ofstandardRooms + dayPriceComfort * ofComfortRooms;
    return current_per_day_income / max_per_day_income;
    
}
bool GuestManager::operator<(GuestManager b1){
    return IncomingProfit() < b1.IncomingProfit();
}
//Notes -----------------------------------------------------------------


// Int casting
// (type)r
// type(r)
// static_cast<int>(r) -- I know it's this type
// dynamic casting --> ran on runtime -- checks if it's this type --> if cast fails, its not that type

// Size_t dependent on OP, treats this type as what I'm calling it --


// two different ways to line break
// std::endl longer clears the buffer
// \n is faster

//Incrementing a variable
//prefer ++i over i++ -- You want to increment and put it in this variable -- faster operation for the CPU

// {} for scoping; anything that is created in that scope exists while the scope is running/is existing






