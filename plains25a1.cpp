// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"


void Plains::deleteLinkingHorses(AVL_TREE<Horse>* horseTree){
    shared_ptr<Horse> horse = horseTree->getData();
    if (horse != nullptr){
        horse->setLeader(nullptr);
        horse->setHerd(nullptr);
        horse->setFollower(nullptr);
    }
    AVL_TREE<Horse>* leftHorses = horseTree->getLeft();
    AVL_TREE<Horse>* rightHorses = horseTree->getRight();
    if (leftHorses != nullptr){
        deleteLinkingHorses(leftHorses);
    }
    if (rightHorses != nullptr){
        deleteLinkingHorses(rightHorses);
    }
}

Plains::Plains()
{
    horses = new AVL_TREE<Horse>();
    herds = new AVL_TREE<Herd>();
    emptyHerds = new AVL_TREE<Herd>();
}

Plains::~Plains()
{
    deleteLinkingHorses(horses);
    delete(emptyHerds);
    delete(herds);
    delete(horses);
}

StatusType Plains::add_herd(int herdId)
{
    try {
        if (herdId <= 0){
            return StatusType::INVALID_INPUT;
        } else if (emptyHerds->find(herdId) != nullptr) {
            return StatusType::FAILURE;
        } else if (herds->find(herdId) != nullptr) {
            return StatusType::FAILURE;
        } else {
            shared_ptr<Herd> newHerd = make_shared<Herd>(herdId);
            emptyHerds = emptyHerds->insert(herdId, newHerd);
        }
    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::remove_herd(int herdId) {
    try {
        if (herdId <= 0) {
            return StatusType::INVALID_INPUT;
        } else if (emptyHerds->find(herdId) == nullptr) {
            return StatusType::FAILURE;
        } else {
            emptyHerds = emptyHerds->remove(herdId);
            }
        } catch (std::bad_alloc &e) {
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
}


StatusType Plains::add_horse(int horseId, int speed) {
    try {
        if (horseId <= 0 || speed <= 0) {
            return StatusType::INVALID_INPUT;
        } else if (horses->find(horseId) != nullptr) {
            return StatusType::FAILURE;
        } else {
            shared_ptr<Horse> newHorse = make_shared<Horse>(horseId, speed);
            horses = horses->insert(horseId, newHorse);
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType Plains::join_herd(int horseId, int herdId){
    try{
        if (horseId <= 0 || herdId <= 0){
            return StatusType::INVALID_INPUT;
        } else if (horses->find(horseId) == nullptr || horses->find(horseId)->getData()->getHerd() != nullptr){
            return StatusType::FAILURE;
        } else if (herds->find(herdId) == nullptr){
            if (emptyHerds->find(herdId) == nullptr){
                return StatusType::FAILURE;
            }
            herds = herds->insert(herdId, emptyHerds->find(herdId)->getData());
            emptyHerds = emptyHerds->remove(herdId);
        }
        horses->find(horseId)->getData()->setHerd(herds->find(herdId)->getData());
        herds->find(herdId)->getData()->addHorse(horseId, horses->find(horseId)->getData());
    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;


}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
    try {
        if (horseId <= 0 || horseToFollowId <= 0 || horseId == horseToFollowId){
            return StatusType::INVALID_INPUT;
        }
        AVL_TREE<Horse>* followerNode = horses->find(horseId);
        AVL_TREE<Horse>* leaderNode = horses->find(horseToFollowId);
        if (followerNode == nullptr || leaderNode == nullptr){
            return StatusType::FAILURE;
        }
        shared_ptr<Horse> followerHorse = followerNode->getData();
        shared_ptr<Horse> leaderHorse = leaderNode->getData();
        if (followerHorse->getHerd() == nullptr || leaderHorse->getHerd() == nullptr){
            return StatusType::FAILURE;
        }
        int followerHerdId = followerHorse->getHerd()->getId();
        int leaderHerdId = leaderHorse->getHerd()->getId();
        if (followerHerdId != leaderHerdId){
            return StatusType::FAILURE;
        }
        if (leaderHorse->getFollower() == nullptr){
            shared_ptr<Horse> newLinkHorse = make_shared<Horse>(-1,-1);
            newLinkHorse->setLeader(leaderHorse);
            followerHorse->setLeader(newLinkHorse);
            leaderHorse->setFollower(newLinkHorse);
        } else {
            followerHorse->setLeader(leaderHorse->getFollower());
        }
    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId) {
    try {
        AVL_TREE<Horse>* horseNode = horses->find(horseId);
        if (horseId <= 0) {
            return StatusType::INVALID_INPUT;
        } else if (horseNode == nullptr) {
            return StatusType::FAILURE;
        } else if (horseNode->getData()->getHerd() == nullptr) {
            return StatusType::FAILURE;
        } else {
            shared_ptr<Horse> horse = horseNode->getData();
            shared_ptr<Herd> herd = horse->getHerd();
            horse->setLeader(nullptr);
            if (horse->getFollower() != nullptr){
                horse->getFollower()->setLeader(nullptr);
            }
            horse->setFollower(nullptr);
            herd->removeHorse(horseId);
            if (herd->getHorseNumber() == 0) {
                emptyHerds = emptyHerds->insert(herd->getId(), make_shared<Herd>(herd->getId()));
                herds = herds->remove(herd->getId());
            }
            horse->setHerd(nullptr);
            }

        } catch (std::bad_alloc & e){
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
}

output_t<int> Plains::get_speed(int horseId) {
    if (horseId <=0){
        return StatusType::INVALID_INPUT;
    }
    AVL_TREE<Horse>* horse = horses->find(horseId);
    if (horse == nullptr){
        return StatusType::FAILURE;
    } else {
        return horse->getData()->getSpeed();
    }
}

output_t<bool> Plains::leads(int horseId, int otherHorseId) {
    if (horseId <= 0 || otherHorseId <= 0 || horseId == otherHorseId){
        return StatusType::INVALID_INPUT;
    }
    AVL_TREE<Horse>* followerNode = horses->find(horseId);
    AVL_TREE<Horse>* leaderNode = horses->find(otherHorseId);
    if (followerNode == nullptr || leaderNode == nullptr){
        return StatusType::FAILURE;
    }
    shared_ptr<Horse> followerHorse = followerNode->getData();
    shared_ptr<Horse> leaderHorse = leaderNode->getData();
    shared_ptr<Herd> followerHerd = followerHorse->getHerd();
    shared_ptr<Herd> leaderHerd = leaderHorse->getHerd();
    if (followerHerd == nullptr || leaderHerd == nullptr){
        return {false};
    } else if (followerHerd->getId() != leaderHerd->getId()){
        return {false};
    } else {
        int leaderId = leaderNode->getData()->getId();
        return followerHorse->isFollowing(leaderId);
    }
}

output_t<bool> Plains::can_run_together(int herdId) {
    try{
        if (herdId <= 0) {
            return {StatusType::INVALID_INPUT};
        }
        AVL_TREE<Herd>* herdNode = herds->find(herdId);
        if (herdNode == nullptr) {
            return {StatusType::FAILURE};
        } else {
            shared_ptr<Herd> herd = herdNode->getData();
            int leaderCount = 0;
            int* leaderCountPtr = &leaderCount;
            shared_ptr<Horse> leader = herd->findLeader(herd->getHorseTree(), leaderCountPtr);
            if (leader == nullptr) {
                return {false};
            }
            int leaderId = leader->getId();
            int chainNum = 1;
            int *chains = &chainNum;
            if (herd->runCheck(herd->getHorseTree(),leaderId, chains)){
                return {true};
            }
        }
    }catch (std::bad_alloc& e){
        return {StatusType::ALLOCATION_ERROR};
    }
    return {false};
}