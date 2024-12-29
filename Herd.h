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
    Herd(int id);

    ~Herd();

    int getId() const;

    int getHorseNumber() const;

    AVL_TREE<Horse>* getHorseTree();

    void removeHorse(int id);

    void addHorse(int id, shared_ptr<Horse> horse);

    shared_ptr<Horse> findLeader(AVL_TREE<Horse>* tree, int* leaderCountPtr);

    bool runCheck(AVL_TREE<Horse>* tree,int leaderId, int* chains);
};




