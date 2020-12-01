#ifndef _BINARY_NODE_HPP_
#define _BINARY_NODE_HPP_

template<class T> 
class BinaryNode {
    private:
        T *data;                    // data being stored
        BinaryNode<T> *leftPtr;     // Pointer to the left child
        BinaryNode<T> *rightPtr;    // Pointer to the right child

    public:
        // constructors
        BinaryNode(T *dataIn) { data = dataIn; leftPtr = nullptr; rightPtr = nullptr; }
        BinaryNode(T *dataIn, BinaryNode<T> *left, BinaryNode *right) { data = dataIn; leftPtr = left; rightPtr = right; }

        // Setters
        void setData(T *dataIn) { data = dataIn; }
        void setLeftPtr(BinaryNode<T> *left) { leftPtr = left; }
        void setRightPtr(BinaryNode<T> *right) { rightPtr = right; }

        //getters
        T *getData() const { return data; }
        BinaryNode<T> *getLeftPtr() const { return leftPtr; } 
        BinaryNode<T> *getRightPtr() const { return rightPtr; }

        bool isLeaf() const { return (leftPtr == nullptr && rightPtr == nullptr); }
};
#endif