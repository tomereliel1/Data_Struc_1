#include "Herd.h"
const int INITIAL_NUM_OF_HORSES = 0;
Herd::Herd(int id) : m_id(id), m_horseNum(INITIAL_NUM_OF_HORSES), m_horseTree(nullptr){}


int Herd::getId() const{
    return m_id;
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

shared_ptr<Horse> Herd::findLeader(){
    int leadersCount = 0, chains = 1;


}

void Herd::horseTreePreOrder() const{

    if (m_horseTree->getData() != nullptr){
        return m_horseTree->getData();
    }
    if (m_left == nullptr && m_right == nullptr){
        std::cout << "back" << std::endl;
        return;
    }
    if (m_left != nullptr){
        std::cout << "going left" << std::endl;
        m_left->printInOrder();
    }
    if (m_right != nullptr){
        std::cout << "going right" << std::endl;

        m_right->printInOrder();
    }
    std::cout << "back" << std::endl;
}

