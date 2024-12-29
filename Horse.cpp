#include "Horse.h"
const int INITIAL_IDX = 0;
const int UNVALID_IDX = -1;
Horse::Horse(int id, int speed) : m_id(id), m_speed(speed), m_herd(nullptr),m_follow(nullptr),
    m_followBy(nullptr), m_chainIdx(INITIAL_IDX){}

Horse::~Horse(){
    if (m_follow != nullptr){
        m_follow->m_follow = nullptr;
    }
    m_follow = nullptr;
    m_followBy = nullptr;
}

int Horse::getSpeed() const {
    return m_speed;
}

int Horse::getId() const{
    return m_id;
}

int Horse::getChainIdx() const{
    return m_chainIdx;
}

shared_ptr<Herd> Horse::getHerd() const{
    return m_herd;
}

shared_ptr<Horse> Horse::getFollower() const {
    return m_followBy;
}

shared_ptr<Horse> Horse::getLeader() const{
    return m_follow;
}

void Horse::setHerd(shared_ptr<Herd> herd){
    m_herd = herd;
}

void Horse::setLeader(shared_ptr<Horse> horse){
    m_follow = horse;
}

void Horse::setFollower(shared_ptr<Horse> horse){
    m_followBy = horse;
}

void Horse::setChainIdx(int idx) {
    m_chainIdx = idx;
}

bool Horse::isFollowing(int leaderId){
    if (m_follow == nullptr){
        return false;
    }
    shared_ptr<Horse> nextHorse = m_follow->getLeader();
    if (nextHorse == nullptr){
        return false;
    }
    int currentId = nextHorse->m_id;
    m_chainIdx = UNVALID_IDX;
    nextHorse->m_chainIdx = UNVALID_IDX;
    while (currentId != leaderId){
        if (nextHorse->getLeader() == nullptr){
            zeroChainIdx();
            return false;
        }
        nextHorse = nextHorse->getLeader()->getLeader();
        if (nextHorse == nullptr){
            zeroChainIdx();
            return false;
        } else if (nextHorse->getChainIdx() == UNVALID_IDX){ //a circle
            zeroChainIdx();
            return false;
        }
        nextHorse->setChainIdx(UNVALID_IDX);
        currentId = nextHorse->getId();
    }
    zeroChainIdx();
    return true;
}

void Horse::zeroChainIdx(){
    m_chainIdx = 0;
    if (m_follow == nullptr){
        return;
    }
    shared_ptr<Horse> nextHorse = m_follow->getLeader();
    if (nextHorse == nullptr){
        return;
    }
    while (nextHorse->getChainIdx() == -1){
        nextHorse->setChainIdx(0);
        if (nextHorse->getLeader() == nullptr){
            return;
        }
        nextHorse = nextHorse->getLeader()->getLeader();
        if (nextHorse == nullptr){
            return;
        }
    }
}