#ifndef BINARY_TREE_INTERFACE_H
#define BINARY_TREE_INTERFACE_H

template <class ItemType>
class BinaryTreeInterface {
public:
    // Pure virtual functions (abstract interface)
    virtual bool isEmpty() const = 0;
    virtual int getHeight() const = 0;
    virtual int getNumberOfNodes() const = 0;
    virtual ItemType getRootData() const = 0;
    virtual void clear() = 0;
    virtual bool add(const ItemType& newData) = 0;
    virtual bool remove(const ItemType& data) = 0;
    virtual ItemType getEntry(const ItemType& anEntry) const = 0;
    virtual bool contains(const ItemType& anEntry) const = 0;
    
    // Tree traversal methods
    virtual void preorderTraverse(void visit(ItemType&)) const = 0;
    virtual void inorderTraverse(void visit(ItemType&)) const = 0;
    virtual void postorderTraverse(void visit(ItemType&)) const = 0;
    
    // Virtual destructor
    virtual ~BinaryTreeInterface() {}
};

#endif
