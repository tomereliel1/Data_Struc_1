#include "Horse.h"
const int INITIAL_FOLLOWERS_NUM = 0;
Horse::Horse(int id, int speed) : m_id(id), m_speed(speed), m_herd(nullptr),m_follow(nullptr),
    m_followBY(nullptr), m_followersNum(INITIAL_FOLLOWERS_NUM){}

int Horse::getSpeed() const {
    return m_speed;
}

Herd* Horse::getHerd() const{
    return m_herd;
}

void Horse::setHerd(Herd* herd){
    m_herd = herd;
}

void Horse::zeroFollowers(){
    m_followersNum = INITIAL_FOLLOWERS_NUM;
}

void Horse::setFollow(Horse* horse){
    m_follow = horse;
}


