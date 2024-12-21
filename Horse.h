#pragma once
#include "Herd.h"
class Horse {
private:
    int m_id;
    int m_speed;
    Herd* m_herd{};
    Horse* m_follow;
    Horse* m_followBY;
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

     Herd* getHerd() const;

     void setHerd(Herd* herd);

     void zeroFollowers();

    void setFollow(Horse* horse);

};


