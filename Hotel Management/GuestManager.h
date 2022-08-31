//
//  GuestManager.hpp
//  Project 1
//
//  Created by Sal on 3/2/22.
//

#ifndef GuestManager_hpp
#define GuestManager_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <iostream>

 /* GuestManager_hpp */
enum class RoomType{Standard,
    Comfort
    
};
enum class GuestType{Family,
    Businessman,
    Rockstar
};
// -------------------------------------------------------------------------------------------------------------
class Guest
{
protected:
    RoomType roomtype;
    
    GuestType guesttype;
    
    int duration; //unsigned can't be negative,
    
public:
    Guest(); // default constructor
    Guest(GuestType guesttype,RoomType roomtype,int duration);
    
    GuestType GetGuesttype() const;
    
    RoomType GetRoomType() const;
    
    int getBookedDays() const;
    
    virtual int GetRoomBusyDays()  const = 0; //ensures this is an abstract class
    
    virtual int GetAdditionalIncome() const = 0;
    
    //destructor
    virtual ~Guest(){};
};

// DERIVED CLASSES

class Family : public Guest {
public:
    Family(GuestType guesttype, RoomType roomtype, int duration);
    
    virtual int GetRoomBusyDays() const override;
    
    virtual int GetAdditionalIncome() const override;
    
};
class Rockstar : public Guest{
public:
    Rockstar(GuestType guesttype, RoomType roomtype, int duration);
    
    virtual int GetRoomBusyDays() const override;
    
    virtual int GetAdditionalIncome() const override;
};
class Businessman : public Guest {
public:
    Businessman(GuestType guesttype, RoomType roomtype, int duration, int additionalIncome);
    
    virtual int GetRoomBusyDays() const override;
    
    virtual int GetAdditionalIncome() const override;
    
private:
    
    int additionalIncome;
};
//  ---------------------------------------------------------------------------------------------------------------------

class GuestManager
{
public:
    GuestManager(int val_ofStandardRooms,int val_dayPriceStandard, int val_OfComfortRooms, int val_dayPriceComfort);
    
    bool AddGuest(GuestType guesttype, RoomType roomtype, int stayDays, int additionalIncome = 0);
    
    bool IsAvailable(RoomType roomtype, int inDays = 0);
    
    int IncomingProfit();
    
    float EarningEfficiency();
    
    bool operator<(GuestManager b1);
    
protected:
    int ofstandardRooms;
    
    int dayPriceStandard;
    
    int ofComfortRooms;
    
    int dayPriceComfort;
    
    std::vector<Guest*> rooms;
    
};
#endif



