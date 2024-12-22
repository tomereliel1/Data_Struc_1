#pragma once
#include "AVL_TREE.h"
#include "Horse.h"

class Horse;

class Herd {
private:
    int m_id;
    int m_horseNum;
    AVL_TREE<Horse>* m_horseTree;

public:
    /**
     * Constructor - creates a Horse with a specific id and speed
     *
     * @param id - the unique id of the horse
     * @param speed - the speed of the horse
     */
    Herd(int id);

    void addHorse();

//    Herd(Herd& otherHerd);
//
    int getId() const;

    void subHorse();

    int getHorseNumber() const;
};




