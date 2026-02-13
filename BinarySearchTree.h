#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BinaryNodeTree.h"
#include <memory>
#include <functional>
#include <iostream>
#include <iomanip> // std::setw kullanımı için
#include <vector>  // Ağacı düzgün çizmek için vektör gerekiyor

using namespace std;

template <class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType> {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    bool contains(const ItemType& anEntry) const; //Aynı sayı girme ihtimali için kontrol 
    bool add(const ItemType& newData);
    bool remove(const ItemType& target);

    void inorderTraverse(void (*visit)(ItemType&)) const;
    void preorderTraverse(void (*visit)(ItemType&)) const;
    void postorderTraverse(void (*visit)(ItemType&)) const;

    std::shared_ptr<BinaryNode<ItemType>> getRootPtr() const;

    // AĞACI GÖRSEL OLARAK ÇİZME FONKSİYONU
    void printTree() const;

private:
    std::shared_ptr<BinaryNode<ItemType>> rootPtr;
};

// **Kurucu ve Yıkıcı**
template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr) {}

template <class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() { this->clear(); }

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::getRootPtr() const {
    return this->rootPtr;
}

template <class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const {
    function<bool(std::shared_ptr<BinaryNode<ItemType>>)> searchNode;
    searchNode = [&](std::shared_ptr<BinaryNode<ItemType>> node) {
        if (!node) return false;
        if (node->getItem() == anEntry) return true;
        return anEntry < node->getItem() ? searchNode(node->getLeftChildPtr()) : searchNode(node->getRightChildPtr());
    };
    return searchNode(rootPtr);
}

// **Eleman Ekleme**
template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {
    if (contains(newData)) {
        cout << "Please enter a different integer.\n"; //Aynı sayı girme ihtimali için kontrol
        return false;
    }

    auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
    if (!rootPtr) {
        rootPtr = newNodePtr;
    } else {
        function<std::shared_ptr<BinaryNode<ItemType>>(std::shared_ptr<BinaryNode<ItemType>>, std::shared_ptr<BinaryNode<ItemType>>)> placeNode;
        placeNode = [&](std::shared_ptr<BinaryNode<ItemType>> subTreePtr, std::shared_ptr<BinaryNode<ItemType>> newNodePtr) {
            if (!subTreePtr) return newNodePtr;
            if (newNodePtr->getItem() < subTreePtr->getItem()) {
                subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
            } else {
                subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));
            }
            return subTreePtr;
        };
        rootPtr = placeNode(rootPtr, newNodePtr);
    }
    return true;
}

// **Eleman Silme**
template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target) {
    bool success = false;

    function<std::shared_ptr<BinaryNode<ItemType>>(std::shared_ptr<BinaryNode<ItemType>>, const ItemType&, bool&)> removeValue;
    removeValue = [&](std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType& target, bool& success) -> std::shared_ptr<BinaryNode<ItemType>> {
        if (!subTreePtr) return subTreePtr;
        if (target < subTreePtr->getItem()) {
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
        } else if (target > subTreePtr->getItem()) {
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
        } else {
            success = true;
            if (!subTreePtr->getLeftChildPtr()) return subTreePtr->getRightChildPtr();
            if (!subTreePtr->getRightChildPtr()) return subTreePtr->getLeftChildPtr();
            
            auto findMin = [](std::shared_ptr<BinaryNode<ItemType>> node) {
                while (node->getLeftChildPtr()) node = node->getLeftChildPtr();
                return node;
            };

            std::shared_ptr<BinaryNode<ItemType>> minNode = findMin(subTreePtr->getRightChildPtr());
            subTreePtr->setItem(minNode->getItem());
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), minNode->getItem(), success));
        }
        return subTreePtr;
    };

    rootPtr = removeValue(rootPtr, target, success);
    return success;
}

// **Gezinti (Traversal) Fonksiyonları**
template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void (*visit)(ItemType&)) const {
    function<void(std::shared_ptr<BinaryNode<ItemType>>)> inorder;
    inorder = [&](std::shared_ptr<BinaryNode<ItemType>> node) {
        if (node) {
            inorder(node->getLeftChildPtr());
            int item = node->getItem();  
            visit(item);
            inorder(node->getRightChildPtr());
        }
    };
    inorder(rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void (*visit)(ItemType&)) const {
    function<void(std::shared_ptr<BinaryNode<ItemType>>)> preorder;
    preorder = [&](std::shared_ptr<BinaryNode<ItemType>> node) {
        if (node) {
            int item = node->getItem();  
            visit(item);
            preorder(node->getLeftChildPtr());
            preorder(node->getRightChildPtr());
        }
    };
    preorder(rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void (*visit)(ItemType&)) const {
    function<void(std::shared_ptr<BinaryNode<ItemType>>)> postorder;
    postorder = [&](std::shared_ptr<BinaryNode<ItemType>> node) {
        if (node) {
            postorder(node->getLeftChildPtr());
            postorder(node->getRightChildPtr());
            int item = node->getItem();  
            visit(item);
        }
    };
    postorder(rootPtr);
}

// **AĞACI GRAFİKSEL OLARAK ÇİZME**
template <class ItemType>
void printTreeHelper(std::shared_ptr<BinaryNode<ItemType>> node, int depth, int pos, vector<string>& output) {
    if (node == nullptr) return;

    // Satır genişliğini artır
    if (output.size() <= depth)
        output.resize(depth + 2, string(100, ' '));

    // Düğümü ortala
    string nodeStr = "[" + to_string(node->getItem()) + "]";
    int nodePos = pos - nodeStr.size() / 2;
    output[depth].replace(nodePos, nodeStr.size(), nodeStr);

    // Çizgilerin hizalanması için offset ayarı
    int offset = 5 - depth;  
    if (offset < 2) offset = 3;

    // Çocukları varsa bağlama çizgileri ekle
    if (node->getLeftChildPtr() || node->getRightChildPtr()) {
        if (output.size() <= depth + 1)
            output.resize(depth + 3, string(100, ' '));

        if (node->getLeftChildPtr())
            output[depth + 1].replace(pos - (offset / 2) - 1, 1, "/");  // SOLDAKİ ÇİZGİ BİRAZ SAĞA KAYDIRILDI
        
        if (node->getRightChildPtr())
            output[depth + 1].replace(pos + (offset / 2), 1, "\\"); // SAĞDAKİ ÇİZGİ BİRAZ SOLA KAYDIRILDI
              

        // Çocukları yerleştir
        if (node->getLeftChildPtr())
            printTreeHelper(node->getLeftChildPtr(), depth + 2, pos - offset, output);
        if (node->getRightChildPtr())
            printTreeHelper(node->getRightChildPtr(), depth + 2, pos + offset - 1, output);
    }
}

template <class ItemType>
void BinarySearchTree<ItemType>::printTree() const {
    vector<string> output;
    printTreeHelper(rootPtr, 0, 40, output);

    cout << "\nBST Top-Down Graphical Output:\n";
    for (const string& line : output) {
        cout << line << endl;
    }
}

#endif // BINARY_SEARCH_TREE_H
