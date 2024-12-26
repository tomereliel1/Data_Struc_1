#include "Herd.h"
const int INITIAL_NUM_OF_HORSES = 0;
Herd::Herd(int id) : m_id(id), m_horseNum(INITIAL_NUM_OF_HORSES){
    m_horseTree = new AVL_TREE<Horse>();
}

Herd::~Herd(){
    delete(m_horseTree);
}
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

shared_ptr<Horse> Herd::findLeader(AVL_TREE<Horse>* tree, int* leadersCountPtr){
    shared_ptr<Horse> leader = nullptr;
    shared_ptr<Horse> currentHorse = tree->getData();
    if (currentHorse != nullptr){
        currentHorse->setChainIdx(0);
        if (currentHorse->getLeader() == nullptr){
            (*leadersCountPtr)++;
            leader = tree->getData();
        }else if (currentHorse->getLeader()->getLeader() == nullptr){
            (*leadersCountPtr)++;
            leader = tree->getData();
        }
    }
    shared_ptr<Horse> leftLeader;
    shared_ptr<Horse> rightLeader;
    if (tree->getLeft() != nullptr){
         leftLeader = findLeader(tree->getLeft(), leadersCountPtr);
    }
    if (tree->getRight() != nullptr){
        rightLeader = findLeader(tree->getRight(), leadersCountPtr);
    }
    if ((*leadersCountPtr) > 1){
        return nullptr;
    } else if (leftLeader == nullptr && rightLeader != nullptr){
        return rightLeader;
    } else if (leftLeader != nullptr && rightLeader == nullptr){
        return leftLeader;
    }
    return leader;
}

bool Herd::runCheck(AVL_TREE<Horse>* tree,int leaderId, int* chains){
    shared_ptr<Horse> currentHorse = tree->getData();
    if (currentHorse != nullptr) {
        if (currentHorse->getChainIdx() == 0) {
            currentHorse->setChainIdx(*chains);
            //shared_ptr<Horse> temp = tree->getData();
            int currentChain = *chains;
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
            (*chains)++;
        }
    }
    bool left = true;
    bool right = true;
    if (tree->getLeft() != nullptr){
        left = runCheck (tree->getLeft(),leaderId, chains);
    }
    if (tree->getRight() != nullptr){
        right = runCheck (tree->getRight(),leaderId, chains);
    }
    if (left && right){
        return true;
    }
    return false;
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

