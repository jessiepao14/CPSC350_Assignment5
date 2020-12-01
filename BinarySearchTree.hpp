#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_

#include "BinaryNode.hpp"
#include "GenStructures.hpp"

template<class T>
class BinarySearchTree
{
    protected:
        BinaryNode<T> *rootPtr;     // Pointer to the root node
        int count;                  // Number of nodes in the tree

    public:
        BinarySearchTree() { rootPtr = nullptr; count = 0; }
        virtual ~BinarySearchTree() {}

        // Common functions for all binary trees
        bool isEmpty() const { return count == 0; }
        int getsize() const { return count; }
        void printTree(void visit(T *));

        void insert(T *newEntry, int compare(T *, T *));
        bool remove(T *anEntry, int compare(T *, T *));
        bool getEntry(T *target, T &returnedItem, int compare(T *, T *)) const;

    private:
        void _inOrder(void visit(T *), BinaryNode<T> *node);
        BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNodePtr, int compare(T *, T *));
        BinaryNode<T> *_remove(BinaryNode<T>* nodePtr, T *target, bool &success, int compare(T *, T *));
        BinaryNode<T>* deleteNode(BinaryNode<T>* targetNodePtr);
        BinaryNode<T>* findNode(BinaryNode<T>* treePtr, T *target, int compare(T *, T *)) const;
};

/////////////////////// public function definitions ////////////////////////
template<class T>
void BinarySearchTree<T>::printTree(void visit(T *)) {
    inOrder(rootPtr, visit);
}

template<class T>
void BinarySearchTree<T>::insert(T *newEntry, int compare(T *, T *)) {
    BinaryNode<T> *newNode = new BinaryNode<T>(newEntry);
    rootPtr = _insert(rootPtr, newNode, compare);
    count++;
}

template<class T>
bool BinarySearchTree<T>::remove(T *target, int compare(T *, T *))
{
    bool isSuccessful = false;
    rootPtr = _remove(rootPtr, target, isSuccessful, compare);
    count--;
    return isSuccessful;
}

template<class T>
bool BinarySearchTree<T>::getEntry(T *anEntry, T &returnedItem, int compare(T *, T *)) const
{
    BinaryNode<T> *ptr = findNode(this->rootPtr, anEntry, compare);
    if (!ptr)
        return false;
    returnedItem = *ptr->getItem();
    return true;
}


/////////////////////// private function definitions ////////////////////////

template<class T>
void BinarySearchTree<T>::_inOrder(void visit(T *), BinaryNode<T> *node) {
    if (node != nullptr) {
        inOrder(visit, node->getLeftPtr());
        T* item = node->getData();
        visit(item);
        inOrder(visit, node->getRightPtr());
    }
}

template<class T>
BinaryNode<T> *BinarySearchTree<T>::_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNodePtr, int compare(T *, T *)) {
    if (nodePtr == 0) {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    T *newNodeItem = newNodePtr->getData();
    T *nodeItem = nodePtr->getData();
    if (compare(newNodeItem, nodeItem) == 1) {  // Check if (newNodePtr->getData() < nodePtr0>getData())
        if (nodePtr->getLeftPtr() == nullptr)
            nodePtr->setLeftPtr(newNodePtr);
        else
            _insert(nodePtr->getLeftPtr, newNodePtr, compare);
    } else {
        if (nodePtr->getRightPtr() == 0)
            nodePtr->setRightPtr(newNodePtr);
        else
            _insert(nodePtr->getRightPtr(), newNodePtr, compare);
    }
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::_remove(BinaryNode<T>* nodePtr, T *target, bool &success, int compare(T *, T *))

{
    if (nodePtr == 0) {
        success = false;
        return 0;
    }
    T *nodePtrItem = nodePtr->getData();
    T *targetItem = target;
    if (compare(nodePtrItem, targetItem) == 1)          //check if (nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, compare));
    else if (compare(nodePtrItem, targetItem) == -1)    //(nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare));
    else { //if the node matches target
        target = nodePtr->getItem();
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::deleteNode(BinaryNode<T>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<T>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        T *newNodeValue = new StatePark();
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* nodePtr,
    T *target, int compare(T *, T *)) const
{
    T *nodeItem = nodePtr->getItem();
    T *targetItem = target;
    if (compare(nodeItem, targetItem) == 0)//(nodePtr->getItem() == target)
        return nodePtr;
    if (nodePtr == 0)
        return NULL;
    else if (compare(nodeItem, targetItem) == 1)//(nodePtr->getItem() > target)
    {
        if (nodePtr->getLeftPtr() == 0)
            return NULL;
        return findNode(nodePtr->getLeftPtr(), target, compare);
    }
    else //if (compare(nodeItem, targetItem) == -1)//(nodePtr->getItem() < target)
    {
        if (nodePtr->getRightPtr() == 0)
            return NULL;
        return findNode(nodePtr->getRightPtr(), target, compare);
    }
}


#endif