// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"


Plains::Plains()
{
    
}

Plains::~Plains()
{
    
}

StatusType Plains::add_herd(int herdId)
{
    return StatusType::FAILURE;
}

StatusType Plains::remove_herd(int herdId)
{
    if (herdId <= 0){
        return StatusType::INVALID_INPUT;
    }else if (emptyHerds->find(herdId) == nullptr) {
        return StatusType::FAILURE;
    } else {
        emptyHerds = emptyHerds->remove(herdId);
    }
}

StatusType Plains::add_horse(int horseId, int speed)
{
    return StatusType::FAILURE;
}

StatusType Plains::join_herd(int horseId, int herdId)
{
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
    horses->find(horseId)->getData()->setHerd(herds->find(herdId)->getData().get());
    //add after write addHorse
    //herds->find(herdId)->addHorse();

}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
    return StatusType::FAILURE;
}

StatusType Plains::leave_herd(int horseId)
{
    return StatusType::FAILURE;
}

output_t<int> Plains::get_speed(int horseId)
{
    return 0;
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)
{
    return false;
}

output_t<bool> Plains::can_run_together(int herdId)
{
    return false;
}
