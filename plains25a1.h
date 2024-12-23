// 
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef PLAINS25WINTER_WET1_H_
#define PLAINS25WINTER_WET1_H_
#include "Horse.h"
#include "Herd.h"
#include "AVL_TREE.h"
#include "wet1util.h"

class Plains {
private:
    AVL_TREE<Horse>* horses;
    AVL_TREE<Herd>* herds;
    AVL_TREE<Herd>* emptyHerds;

    bool run_check(AVL_TREE<Horse>* tree, int chains){
        if (tree->getData() != nullptr) {
            if (tree->getData()->getLeaderFlag() == 0) {
                tree->getData()->setLeaderFlag(chains);
                shared_ptr<Horse> temp = tree->getData();
                while (temp != nullptr && (temp->getLeaderFlag() != 0 && temp->getLeaderFlag() != chains)){
                    if (temp->getLeaderFlag() == chains){
                        return false;
                    } else if (temp->getLeaderFlag() == 0){
                        temp->setLeaderFlag(chains);
                        temp = temp->getLeader()->getLeader();
                    }
                }
                chains++;
            }
        }
        if (tree->getLeft() != nullptr){
            return run_check (tree->getLeft(), chains);
        }
        if (tree->getRight() != nullptr){
            return run_check (tree->getRight(), chains);
        }
        return true;
    }
    //
    // Here you may add anything you want
    //
    
public:
    // <DO-NOT-MODIFY> {
    Plains();

    ~Plains();

    StatusType add_herd(int herdId);

    StatusType remove_herd(int herdId);

    StatusType add_horse(int horseId, int speed);

    StatusType join_herd(int horseId, int herdId);

    StatusType follow(int horseId, int horseToFollowId);

    StatusType leave_herd(int horseId);

    output_t<int> get_speed(int horseId);

    output_t<bool> leads(int horseId, int otherHorseId);

    output_t<bool> can_run_together(int herdId);
    // } </DO-NOT-MODIFY>
};

#endif // PLAINS25WINTER_WET1_H_
