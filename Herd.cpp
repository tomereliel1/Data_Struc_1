#include "Herd.h"
const int INITIAL_NUM_OF_HORSES = 0;
Herd::Herd(int id) : m_id(id), m_horseNum(INITIAL_NUM_OF_HORSES), m_horseTree(nullptr){}

int Herd::getId() const{
    return m_id;
}

int Herd::getHorseNumber() const{
    return m_horseNum;
}

AVL_TREE<Horse>* Herd::getHorseTree(){
    return m_horseTree;
}

void Herd::removeHorse(int id){
    m_horseNum--;
    m_horseTree = m_horseTree->remove(id);
}

void Herd::addHorse(int id, shared_ptr<Horse> horse) {
    m_horseTree = m_horseTree->insert(id, horse);
    m_horseNum++;
}

shared_ptr<Horse> Herd::findLeader(AVL_TREE<Horse>* tree, int leadersCount){
    shared_ptr<Horse> leader = nullptr;
    shared_ptr<Horse> currentHorse = tree->getData();
    if (currentHorse != nullptr){
        currentHorse->setChainIdx(0);
        if (currentHorse->getLeader() == nullptr){
            leadersCount++;
            leader = tree->getData();
        }else if (currentHorse->getLeader()->getLeader() == nullptr){
            leadersCount++;
            leader = tree->getData();
        }
    }
    if (tree->getLeft() != nullptr){
        return findLeader(tree->getLeft(), leadersCount);
    }
    if (tree->getRight() != nullptr){
        return findLeader(tree->getRight(), leadersCount);
    }
    if (leadersCount != 1){
        return nullptr;
    } else{
        return leader;
    }
}

bool Herd::runCheck(AVL_TREE<Horse>* tree,int leaderId, int chains){
    shared_ptr<Horse> currentHorse = tree->getData();
    if (currentHorse != nullptr) {
        if (currentHorse->getChainIdx() == 0) {
            currentHorse->setChainIdx(chains);
            //shared_ptr<Horse> temp = tree->getData();
            int currentChain = chains;
            int currentId = currentHorse->getId();
            while (currentId != leaderId){
                shared_ptr<Horse> nextHorse = currentHorse->getLeader()->getLeader();
                int nextId = nextHorse->getId();
                if (nextId == leaderId){
                    break;
                }
                int nextChain = nextHorse->getChainIdx();
                if (currentChain == nextChain){
                    return false; // a circle
                } else if (currentChain > nextChain && nextChain != 0){
                    break;
                } else { //next chains is 0
                    nextHorse->setChainIdx(currentChain);
                    currentHorse = nextHorse;
                    currentId = nextId;
                }
            }
            chains++;
        }
    }
    if (tree->getLeft() != nullptr){
        return runCheck (tree->getLeft(),leaderId, chains);
    }
    if (tree->getRight() != nullptr){
        return runCheck (tree->getRight(),leaderId, chains);
    }
    return true;
}


/*
bool Herd::run_check(AVL_TREE<Horse>* tree, int chains){
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

*/

