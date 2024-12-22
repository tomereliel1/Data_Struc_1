#pragma once
#include "Herd.h"
class Horse {
private:
    int m_id;
    int m_speed;
    shared_ptr<Herd> m_herd; //herd
    shared_ptr<Horse> m_follow; //leader's fake horse
    shared_ptr<Horse> m_followBy;//self fake horse
    int m_followersNum;

public:
    /**
     * Constructor - creates a Horse with a specific id and speed
     *
     * @param id - the unique id of the horse
     * @param speed - the speed of the horse
     */
     Horse(int id, int speed);

    /**
     * Gets the speed of the horse
     *
     * @return - horse's speed
     */
     int getSpeed() const;

     shared_ptr<Herd> getHerd() const;

     void setHerd(shared_ptr<Herd> herd);

     void zeroFollowers();

     void setFollow(shared_ptr<Horse> horse);

};


