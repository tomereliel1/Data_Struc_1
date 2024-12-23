#include "Herd.h"
const int INITIAL_NUM_OF_HORSES = 0;
Herd::Herd(int id) : m_id(id), m_horseNum(INITIAL_NUM_OF_HORSES), m_horseTree(nullptr){}


int Herd::getId() const{
    return m_id;
}

AVL_TREE<Horse>* Herd::getHorseTree(){
    return m_horseTree;
}

void Herd::removeHorse(int id){
    m_horseNum--;
    m_horseTree = m_horseTree->remove(id);
}

int Herd::getHorseNumber() const{
    return m_horseNum;
}

void Herd::addHorse(int id, shared_ptr<Horse> horse) {
    m_horseTree = m_horseTree->insert(id, horse);
    m_horseNum++;
}

shared_ptr<Horse> Herd::findLeader(AVL_TREE<Horse>* tree, int leadersCount){
    shared_ptr<Horse> leader = nullptr;
    if (tree->getData() != nullptr){
        tree->getData()->setLeaderFlag(0);
        if (tree->getData()->getLeader()->getLeader() == nullptr){
            leadersCount++;
            leader = tree->getData();
        }
    }
    if (m_horseTree->getLeft() != nullptr){
        return findLeader(m_horseTree->getLeft(), leadersCount);
    }
    if (m_horseTree->getRight() != nullptr){
        return findLeader(m_horseTree->getRight(), leadersCount);
    }
    if (leadersCount != 1){
        return nullptr;
    } else{
        return leader;
    }
}

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



