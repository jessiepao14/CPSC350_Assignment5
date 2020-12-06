#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_

#include "BinaryNode.hpp"
#include "GenStructures.hpp"
#include <typeinfo>
#include <time.h>

template <class T>
class BinarySearchTree
{
protected:
    BinaryNode<T> *rootPtr; // Pointer to the root node
    int count;              // Number of nodes in the tree
    DoublyLinkList<T> insertedNodes;
    ofstream outFile;

public:
    BinarySearchTree()
    {
        rootPtr = nullptr;
        count = 0;
    }
    ~BinarySearchTree() { 
        delete rootPtr; 
    }

    // Common functions for all binary trees
    bool isEmpty() const { return count == 0; }
    int getsize() const { return count; }
    void printTree(void visit(T *)) const;
    void writeTree(string fileName) const;
    void insert(T *newEntry);
    bool remove(T *anEntry);
    T *find(T *value);
    bool search(T *value);
    T getRandomNode();
    void printAsTree(void visit(T *)) {_printAsTree(visit, 1, rootPtr);}
    void clear() {destroyTree(rootPtr);}

private:
    void _inOrder(void visit(T *), BinaryNode<T> *node) const;
    void _writeInOrder(string fileName, BinaryNode<T> *node) const;
    BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNodePtr);
    BinaryNode<T> *_remove(BinaryNode<T> *nodePtr, T *target, bool &success);
    BinaryNode<T> *deleteNode(BinaryNode<T> *targetNodePtr);
    BinaryNode<T> *removeLeftmostNode(BinaryNode<T> *nodePtr, T *successor);
    void _printAsTree(void visit(T *), int level, BinaryNode<T> *nodePtr) const;
    void destroyTree(BinaryNode<T>* nodePtr);
};

/////////////////////// public function definitions ////////////////////////
template <class T>
void BinarySearchTree<T>::printTree(void visit(T *)) const
{
    _inOrder(visit, rootPtr);
}

template <class T>
void BinarySearchTree<T>::writeTree(string fileName) const
{
    _writeInOrder(fileName, rootPtr);
}

template <class T>
void BinarySearchTree<T>::insert(T *newEntry)
{
    BinaryNode<T> *newNode = new BinaryNode<T>(newEntry);
    rootPtr = _insert(rootPtr, newNode);
    insertedNodes.insertBack(*newEntry);
    count++;
}

template <class T>
bool BinarySearchTree<T>::remove(T *target)
{
    bool isSuccessful = false;
    rootPtr = _remove(rootPtr, target, isSuccessful);
    count--;
    return isSuccessful;
}

template <class T>
T *BinarySearchTree<T>::find(T *value)
{
    if (isEmpty()) {
        cout << "Cannot search empty tree" << endl;
    } else {
        BinaryNode<T>* current = rootPtr;
        while (*current->getData() != *value) {
            if (*value < *current->getData())
                current = current->getLeftPtr();
            else
                current = current->getRightPtr();
            if (current == nullptr) {
                cout << "The ID you searched for cannot be found" << endl;
            }
        }
        return current->getData();
    }
    return NULL;
}

template <class T>
bool BinarySearchTree<T>::search(T *value)
{
    if (isEmpty()) {
        return false;
    } else {
        BinaryNode<T>* current = rootPtr;
        while (*current->getData() != *value) {
            if (*value < *current->getData()) {
                current = current->getLeftPtr();
            } else {
                current = current->getRightPtr();
            }
            if (current == nullptr) {
                return false;
            }
        }
        return true;
    }
}

template <class T>
T BinarySearchTree<T>::getRandomNode() {
    srand (time(NULL));
    int randomNumber = rand() % count;
    return insertedNodes.getPosition(randomNumber);
}

/////////////////////// private function definitions ////////////////////////

template <class T>
void BinarySearchTree<T>::_inOrder(void visit(T *), BinaryNode<T> *node) const
{
    if (node != 0)
    {
        _inOrder(visit, node->getLeftPtr());
        T *item = node->getData();
        visit(item);
        _inOrder(visit, node->getRightPtr());
    }
}

template <class T>
void BinarySearchTree<T>::_writeInOrder(string fileName, BinaryNode<T> *node) const
{
    if (node != 0)
    {
        _writeInOrder(fileName, node->getLeftPtr());
        T *item = node->getData();
        item->writeToFile(fileName);
        _writeInOrder(fileName, node->getRightPtr());
    }
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNodePtr)
{
    if (nodePtr == nullptr)
    {
        nodePtr = newNodePtr;
    }
    else
    {
        T *newNodeItem = newNodePtr->getData();
        T *nodeItem = nodePtr->getData();
        if (*newNodeItem < *nodeItem)
        {
            if (nodePtr->getLeftPtr() == nullptr)
                nodePtr->setLeftPtr(newNodePtr);
            else
                _insert(nodePtr->getLeftPtr(), newNodePtr);
        }
        else
        {

            if (nodePtr->getRightPtr() == nullptr)
            {
                nodePtr->setRightPtr(newNodePtr);
            }
            else
                _insert(nodePtr->getRightPtr(), newNodePtr);
        }
    }
    return nodePtr;
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::_remove(BinaryNode<T> *nodePtr, T *target, bool &success)
{
    if (nodePtr == nullptr)
    {
        success = false;
        return 0;
    }
    T *nodePtrItem = nodePtr->getData();
    T *targetItem = target;
    if (*nodePtrItem > *target) //check if (nodePtr->getData() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtrItem < targetItem) //(nodePtr->getData() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    { //if the node matches target
        target = nodePtr->getData();
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::deleteNode(BinaryNode<T> *nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<T> *nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<T> *nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        T *newNodeValue = nullptr;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setData(newNodeValue);
        return nodePtr;
    }
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T> *nodePtr, T *successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getData();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}

template<class T>
void BinarySearchTree<T>::_printAsTree(void visit(T *), int level, BinaryNode<T> *nodePtr) const
{
    string indent = "     ";
    for (int i = 0; i < level - 1; i++)
    {
        cout << indent;
    }
    cout << "Level " << level << ". ";
    T *item = nodePtr->getData();
    visit(item);
    cout << endl;

    if (nodePtr->getRightPtr() != 0)
        _printAsTree(visit, level + 1, nodePtr->getRightPtr());
    if (nodePtr->getLeftPtr() != 0)
        _printAsTree(visit, level + 1, nodePtr->getLeftPtr());
}

template<class T>
void BinarySearchTree<T>::destroyTree(BinaryNode<T>* nodePtr)
{
    if (nodePtr)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}

#endif