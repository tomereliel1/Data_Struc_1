#include "Herd.h"
const int INITIAL_NUM_OF_HORSES = 0;
Herd::Herd(int id) : m_id(id), m_horseNum(INITIAL_NUM_OF_HORSES), m_horseTree(nullptr){}

//Herd::Herd(Herd& otherHerd){
//    m_id = otherHerd.getId;
//}