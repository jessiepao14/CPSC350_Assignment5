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

        void insert(T *newEntry);
        bool remove(T *anEntry);
        bool getEntry(T *target, T &returnedItem) const;

    private:
        void _inOrder(void visit(T *), BinaryNode<T> *node);
        BinaryNode<T> *_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNodePtr);
        BinaryNode<T> *_remove(BinaryNode<T>* nodePtr, T *target, bool &success);
        BinaryNode<T>* deleteNode(BinaryNode<T>* targetNodePtr);
        BinaryNode<T>* findNode(BinaryNode<T>* treePtr, T *target) const;
};

/////////////////////// public function definitions ////////////////////////
template<class T>
void BinarySearchTree<T>::printTree(void visit(T *)) {
    inOrder(rootPtr, visit);
}

template<class T>
void BinarySearchTree<T>::insert(T *newEntry) {
    BinaryNode<T> *newNode = new BinaryNode<T>(newEntry);
    rootPtr = _insert(rootPtr, newNode);
    count++;
}

template<class T>
bool BinarySearchTree<T>::remove(T *target)
{
    bool isSuccessful = false;
    rootPtr = _remove(rootPtr, target, isSuccessful);
    count--;
    return isSuccessful;
}

template<class T>
bool BinarySearchTree<T>::getEntry(T *anEntry, T &returnedItem) const
{
    BinaryNode<T> *ptr = findNode(this->rootPtr, anEntry);
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
BinaryNode<T> *BinarySearchTree<T>::_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newNodePtr) {
    if (nodePtr == 0) {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    T *newNodeItem = newNodePtr->getData();
    T *nodeItem = nodePtr->getData();
    if (newNodeItem < nodeItem) {  // Check if (newNodePtr->getData() < nodePtr0>getData())
        if (nodePtr->getLeftPtr() == nullptr)
            nodePtr->setLeftPtr(newNodePtr);
        else
            _insert(nodePtr->getLeftPtr, newNodePtr);
    } else {
        if (nodePtr->getRightPtr() == 0)
            nodePtr->setRightPtr(newNodePtr);
        else
            _insert(nodePtr->getRightPtr(), newNodePtr);
    }
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::_remove(BinaryNode<T>* nodePtr, T *target, bool &success) {
    if (nodePtr == 0) {
        success = false;
        return 0;
    }
    T *nodePtrItem = nodePtr->getData();
    T *targetItem = target;
    if (nodePtrItem > target)          //check if (nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtrItem < targetItem)    //(nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else { //if the node matches target
        target = nodePtr->getItem();
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::deleteNode(BinaryNode<T>* nodePtr) {
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
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* nodePtr, T *target) const
{
    T *nodeItem = nodePtr->getItem();
    T *targetItem = target;
    // if (compare(nodeItem, targetItem) == 0)//(nodePtr->getItem() == target)
    if (nodeItem == targetItem)
        return nodePtr;
    if (nodePtr == 0)
        return NULL;
    else if (nodeItem > targetItem)//(nodePtr->getItem() > target)
    {
        if (nodePtr->getLeftPtr() == 0)
            return NULL;
        return findNode(nodePtr->getLeftPtr(), target);
    }
    else //if (compare(nodeItem, targetItem) == -1)//(nodePtr->getItem() < target)
    {
        if (nodePtr->getRightPtr() == 0)
            return NULL;
        return findNode(nodePtr->getRightPtr(), target);
    }
}


#endif