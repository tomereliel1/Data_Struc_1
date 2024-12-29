#include <memory>
using std::shared_ptr;
#include <iostream>
using namespace std;

template <typename T>
class AVL_TREE {
private:
    int m_id;
    shared_ptr<T> m_data;
    AVL_TREE<T>* m_left;
    AVL_TREE<T>* m_right;
    int m_height;

    AVL_TREE<T>* insertAux(int id, shared_ptr<T> data);

    AVL_TREE<T>* removeAux(int id);

    void updateHeight();

public:

    AVL_TREE();

    AVL_TREE(int id, shared_ptr<T> data);

    ~AVL_TREE();

    shared_ptr<T> getData() const;

    AVL_TREE<T>* getLeft();

    AVL_TREE<T>* getRight();

    AVL_TREE<T>* find(int id);

    AVL_TREE<T>* insert(int id, shared_ptr<T> data);

    AVL_TREE<T>* remove(int id);

    int getBalanceFactor() const;

    int getHeight() const;

    AVL_TREE<T>* rrRoll();
    AVL_TREE<T>* rlRoll();
    AVL_TREE<T>* lrRoll();
    AVL_TREE<T>* llRoll();
    AVL_TREE<T>* findMin();

};

template <typename T>
AVL_TREE<T>::AVL_TREE(): m_id(0), m_data(nullptr), m_left(nullptr), m_right(nullptr), m_height(0){}

template <typename T>
AVL_TREE<T>::AVL_TREE(int id, shared_ptr<T> data): m_id(id), m_data(data), m_left(nullptr), m_right(nullptr),
                                                   m_height(0){}

template <typename T>
AVL_TREE<T>::~AVL_TREE(){
    if (m_left != nullptr){
        delete(m_left);
        m_left = nullptr;

    }
    if (m_right != nullptr){
        delete(m_right);
        m_right = nullptr;
    }
    if (m_data != nullptr){
        m_data = nullptr;
    }
}

template <typename T>
shared_ptr<T> AVL_TREE<T>::getData() const{
    return m_data;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::getLeft(){
    return m_left;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::getRight(){
    return m_right;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::find(int id) {
    if (m_id == id) {
        return this;
    } else if (m_id > id && m_left != nullptr) {

        return m_left->find(id);
    } else if (m_right != nullptr) {
        return m_right->find(id);
    }
    return nullptr;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::insert(int id, shared_ptr<T> data) {
    if (m_id == 0){
        m_id = id;
        m_data = data;
        return this;
    } else {
        return insertAux(id, data);
    }
}


template <typename T>
AVL_TREE<T>* AVL_TREE<T>::insertAux(int id, shared_ptr<T> data) {
    if (m_id > id){
        if (m_left == nullptr){
            m_left = new AVL_TREE<T>(id, data);
        } else {
            m_left = m_left->insertAux(id, data);
        }
    } else {
        if (m_right == nullptr){
            m_right = new AVL_TREE<T>(id, data);
        } else {
            m_right = m_right->insertAux(id, data);
        }
    }
    updateHeight();
    int balanceFactor = getBalanceFactor();
    if (balanceFactor == 2){

        if (m_left != nullptr && m_left->getBalanceFactor() == -1){
            return lrRoll();
        } else {
            return llRoll();
        }
    } else if (balanceFactor == -2){
        if (m_right != nullptr && m_right->getBalanceFactor() == 1){
            return rlRoll();
        } else {
            AVL_TREE<T>* temp = rrRoll();
            return temp;
        }
    }
    return this;
}


template <typename T>
AVL_TREE<T>* AVL_TREE<T>::remove(int id) {
    if (m_id == id && (m_right == nullptr && m_left == nullptr)){
        m_data == nullptr;
        m_id = 0;
        return this;
    }   else {
        return removeAux(id);
    }
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::removeAux(int id) {
    if (m_id > id){
        m_left = m_left->removeAux(id);
    } else if (m_id < id){
        m_right = m_right->removeAux(id);
    } else {
        AVL_TREE<T>* temp = nullptr;
        if (m_left != nullptr && m_right != nullptr){
            temp = m_right->findMin();
            m_id = temp->m_id;
            m_data = temp->m_data;
            m_right = m_right->removeAux(m_id);
        } else if (m_left == nullptr && m_right == nullptr){
            delete this;
            return nullptr;
        }else if (m_left == nullptr){
            temp = m_right;
            m_right = nullptr;
            delete this;
            return temp;
        } else if (m_right == nullptr) {
            temp = m_left;
            m_left = nullptr;
            delete this;
            return temp;
        }
    }
    updateHeight();
    int balanceFactor = getBalanceFactor();
    if (balanceFactor == 2){
        if (m_left != nullptr && m_left->getBalanceFactor() == -1){
            return lrRoll();
        } else {
            return llRoll();
        }
    } else if (balanceFactor == -2){
        if (m_right != nullptr && m_right->getBalanceFactor() == 1){
            return rlRoll();
        } else {
            return rrRoll();
        }
    }
    return this;
}

template <typename T>
int AVL_TREE<T>::getBalanceFactor() const {
    int lHeight = -1;
    int rHeight = -1;
    if (m_left != nullptr){
        lHeight = m_left->getHeight();
    }
    if (m_right != nullptr){
        rHeight = m_right->getHeight();
    }
    return lHeight - rHeight;
}

template <typename T>
int AVL_TREE<T>::getHeight() const {
    return m_height;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::llRoll() {
    AVL_TREE<T>* temp = m_left;
    m_left = m_left->m_right;
    temp->m_right = this;
    this->updateHeight();
    temp->updateHeight();
    return temp;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::rrRoll() {
    AVL_TREE<T>* temp = m_right;
    m_right = m_right->m_left;
    temp->m_left = this;
    this->updateHeight();
    temp->updateHeight();
    return temp;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::lrRoll() {
    m_left = m_left->rrRoll();
    return llRoll();
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::rlRoll() {
    m_right = m_right->llRoll();
    return rrRoll();
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::findMin() {
    if (m_left != nullptr){
        return m_left->findMin();
    } else {
        return this;
    }
}

template <typename T>
void AVL_TREE<T>::updateHeight() {
    int leftHeight = (m_left) ? m_left->m_height : -1;
    int rightHeight = (m_right) ? m_right->m_height : -1;
    if (leftHeight > rightHeight){
        m_height = 1 + leftHeight;
    } else {
        m_height = 1 + rightHeight;
    }
}