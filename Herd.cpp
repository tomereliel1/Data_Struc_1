#include "Herd.h"
const int INITIAL_NUM_OF_HORSES = 0;
Herd::Herd(int id) : m_id(id), m_horseNum(INITIAL_NUM_OF_HORSES), m_horseTree(nullptr){}

void Herd::addHorse(){
    m_horseNum++;
}

int Herd::getId() const{
    return m_id;
}

void Herd::subHorse(){
    m_horseNum--;
}

int Herd::getHorseNumber() const{
    return m_horseNum;
}