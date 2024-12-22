#include "Horse.h"
const int INITIAL_FOLLOWERS_NUM = 0;
Horse::Horse(int id, int speed) : m_id(id), m_speed(speed), m_herd(nullptr),m_follow(nullptr),
    m_followBy(nullptr), m_followersNum(INITIAL_FOLLOWERS_NUM){}

int Horse::getSpeed() const {
    return m_speed;
}

shared_ptr<Herd> Horse::getHerd() const{
    return m_herd;
}

void Horse::setHerd(shared_ptr<Herd> herd){
    m_herd = herd;
}

void Horse::zeroFollowers(){
    m_followersNum = INITIAL_FOLLOWERS_NUM;
}

void Horse::setLeader(shared_ptr<Horse> horse){
    m_follow = horse;
}

void Horse::setFollower(shared_ptr<Horse> horse){
    m_follow = horse;
}

shared_ptr<Horse> Horse::getFollower() const {
    return m_followBy;
}


