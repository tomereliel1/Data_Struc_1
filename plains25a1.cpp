// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"


Plains::Plains()
{
    horses = new AVL_TREE<Horse>();
    herds = new AVL_TREE<Herd>();
    emptyHerds = new AVL_TREE<Herd>();
}

Plains::~Plains()
{
    delete(horses);
    delete(herds);
    delete(emptyHerds);
}

StatusType Plains::add_herd(int herdId)
{
    try {
        if (herdId <= 0){
            return StatusType::INVALID_INPUT;
        } else if (emptyHerds->find(herdId) != nullptr){
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
            if (horseId <= 0) {
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
        AVL_TREE<Horse>* follower = horses->find(horseId);
        AVL_TREE<Horse>* leader = horses->find(horseToFollowId);
        if (follower == nullptr || leader == nullptr){
            return StatusType::FAILURE;
        }
        int followerHerdId = follower->getData()->getHerd()->getId();
        int leaderHerdId = leader->getData()->getHerd()->getId();
        if (followerHerdId != leaderHerdId){
            return StatusType::FAILURE;
        }
        shared_ptr<Horse> followerHorse = follower->getData();
        shared_ptr<Horse> leaderHorse = leader->getData();
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
        if (horseId <= 0) {
            return StatusType::INVALID_INPUT;
        } else if (horses->find(horseId) == nullptr) {
            return StatusType::FAILURE;
        } else if (horses->find(horseId)->getData()->getHerd() == nullptr) {
            return StatusType::FAILURE;
        } else {
            shared_ptr<Horse> horse = horses->find(horseId)->getData();
            shared_ptr<Herd> herd = horse->getHerd();
            horse->zeroFollowers();
            horse->getLeader()->setLeader(nullptr);
            horse->nullFollowedBy();
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
            return 0;
        }

        output_t<bool> Plains::leads(int horseId, int otherHorseId) {
            return false;
        }

        output_t<bool> Plains::can_run_together(int herdId) {
    try{
        if (herdId <= 0) {
            return output_t<bool>(StatusType::INVALID_INPUT);
        } else if (herds->find(herdId) == nullptr) {
            return output_t<bool>(StatusType::FAILURE);
        } else {
            shared_ptr<Herd> herd = herds->find(herdId)->getData();
            if (herd->findLeader(herd->getHorseTree(), 0) == nullptr) {
                return output_t<bool>(false);
            }else if (run_check(herd->getHorseTree(), 1)){
                return output_t<bool>(true);
            }
        }
    }catch (std::bad_alloc& e){
        return output_t<bool>(StatusType::ALLOCATION_ERROR);
    }

            return output_t<bool>(false);
}



