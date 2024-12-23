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
    int m_leaderFlag;
//    int m_followersNum;

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

    int getId() const;

    int getLeaderFlag() const;

    shared_ptr<Herd> getHerd() const;

    shared_ptr<Horse> getFollower() const;

    shared_ptr<Horse> getLeader() const;

    void setHerd(shared_ptr<Herd> herd);

    void setLeader(shared_ptr<Horse> horse);

    void setFollower(shared_ptr<Horse> horse);

    void nullFollowedBy();

    void setLeaderFlag(int flag);

    void zeroFollowers();

//    void subHorse();

};


