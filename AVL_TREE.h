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

public:
    int getBalanceFactor() const;
    AVL_TREE<T>* rrRoll();
    AVL_TREE<T>* rlRoll();
    AVL_TREE<T>* lrRoll();
    AVL_TREE<T>* llRoll();
    AVL_TREE<T>* findMin();

    int getHeight() const;

    AVL_TREE();

    AVL_TREE(int id, shared_ptr<T> data);

    ~AVL_TREE();

    AVL_TREE<T>* find(int id);

    AVL_TREE<T>* insert(int id, shared_ptr<T> data);

    AVL_TREE<T>* getLeft();

    AVL_TREE<T>* getRight();

    AVL_TREE<T>* remove(int id);

    shared_ptr<T> getData() const;

    void printInOrder() const;
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
    /*if (this->find(id) != nullptr) {
        return this;
    }*/
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
            //cout << "m_right is " << m_right->m_id << endl;
        }
    }

    m_height = getHeight();
    int balanceFactor = getBalanceFactor();
    //std::cout << m_id <<" value is " << *m_data << " bf is " << balanceFactor << std::endl;
    if (balanceFactor == 2){

        if (m_left != nullptr && m_left->getBalanceFactor() == -1){
            //std::cout << "lr roll"<< std::endl;
            return lrRoll();
        } else {
            //std::cout << "ll roll"<< std::endl;
            return llRoll();
        }
    } else if (balanceFactor == -2){
        if (m_right != nullptr && m_right->getBalanceFactor() == 1){
            //std::cout << "rl roll" << std::endl;
            return rlRoll();
        } else /* if (m_right->m_balanceFactor <= 0)*/ {
            //std::cout << "rr roll on " << m_id << std::endl;
            AVL_TREE<T>* temp = rrRoll();
            //std::cout << "root is " << temp->m_id << std::endl;
            return temp;
        }
    }
    if (m_right != nullptr){
        //cout << "returning " << m_id << " when m_right is " << m_right->m_id << endl;

    }
    return this;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::remove(int id) {
    //cout << "we at " << m_id << "looking to delete " << id << endl;
    if (m_id > id){
        m_left = m_left->remove(id);
    } else if (m_id < id){
        m_right = m_right->remove(id);
    } else {
        AVL_TREE<T>* temp = nullptr;
        if (m_left != nullptr && m_right != nullptr){
            //cout << m_id << " has 2 sons" << endl;
            temp = m_right->findMin();
            //cout << m_id << " has 2 sons and we taking " << temp->m_id << endl;
            m_id = temp->m_id;
            m_data = temp->m_data;
//            cout << " after swap id is " << m_id << " data is " << *m_data << " and temp data is " << *(temp->m_data) << endl;
            m_right = m_right->remove(m_id);
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
    m_height = getHeight();
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
        } else /* if (m_right->m_balanceFactor <= 0)*/ {

        }
    }
    return this;
}

template <typename T>
int AVL_TREE<T>::getHeight() const {
    if (m_left == nullptr && m_right == nullptr){
        return 0;
    } else if (m_left != nullptr) {
        if (m_right == nullptr) {
            return m_left->getHeight() + 1;
        }
        else if (m_left->getHeight() >= m_right->getHeight()) {
            return m_left->getHeight() + 1;
        }
    }
    return m_right->getHeight() + 1;

}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::llRoll() {
    AVL_TREE<T>* temp = m_left;
    m_left = m_left->m_right;
    temp->m_right = this;
    return temp;
}

template <typename T>
AVL_TREE<T>* AVL_TREE<T>::rrRoll() {
    AVL_TREE<T>* temp = m_right;
    m_right = m_right->m_left;
    temp->m_left = this;
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
    AVL_TREE<T>* check = rrRoll();
    return check;
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
AVL_TREE<T>* AVL_TREE<T>::findMin() {
    if (m_left != nullptr){
        return m_left->findMin();
    } else {
        return this;
    }
}

template <typename T>
void AVL_TREE<T>::printInOrder() const{

    if (m_data != nullptr){
        std::cout << m_id << std::endl;
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