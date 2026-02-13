#ifndef BINARY_NODE_TREE_H
#define BINARY_NODE_TREE_H

#include "BinaryNode.h"
#include <memory>
#include <iostream>
#include <iomanip> // std::setw kullanımı için

/**
 * @brief BinaryNodeTree sınıfı, genel bir ikili ağaç yapısını temsil eder.
 * 
 * Bu sınıf, Binary Search Tree (BST) gibi yapıların temelini oluşturur ve 
 * genel ikili ağaç işlemlerini içerir.
 * 
 * - **Kapsülleme:** Ağaç yapısının kök düğümü (rootPtr) korumalı (protected) olarak tanımlanmıştır.
 * - **Özyinelemeli (recursive) fonksiyonlar** 
 * - **Akıllı işaretçiler:** Ders içeriğindeki kodlardaki gibi `std::shared_ptr` kullanılarak bellek yönetimi sağlanmıştır. 
 */


template <class ItemType>
class BinaryNodeTree {
protected:
    std::shared_ptr<BinaryNode<ItemType>> rootPtr; // Ağaç kök düğümü işaretçisi

public:
    BinaryNodeTree(); // Kurucu (constructor)
    ~BinaryNodeTree(); // Yıkıcı (destructor)

    bool isEmpty() const; // Ağacın boş olup olmadığını kontrol eder
    void clear(); // Ağacı temizler
    int getHeight() const; // Ağacın yüksekliğini hesaplar
    int getNumberOfNodes() const; // Ağaçtaki toplam düğüm sayısını döndürür

    // AĞACI ÇİZME FONKSİYONU
    void printTree() const;

protected:
    // Yardımcı fonksiyonlar (Recursive olarak çalışır)
    int getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
    int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

    // Ağacı görsel olarak yazdırmaya yardımcı fonksiyon
    void printTreeHelper(std::shared_ptr<BinaryNode<ItemType>> node, int space) const;
};

// **Kurucu ve Yıkıcı**
template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr) {}

template <class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree() { clear(); }

// **Ağacın boş olup olmadığını kontrol eder**
template <class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const {
    return rootPtr == nullptr;
}

// **Ağacı temizler**
template <class ItemType>
void BinaryNodeTree<ItemType>::clear() {
    rootPtr.reset(); // Kök düğüm işaretçisini sıfırlar (Bellek sızıntısını önler)
}

// **Ağacın yüksekliğini hesaplayan fonksiyon**
template <class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const {
    // Lambda fonksiyonu ile recursive yüksekliği hesapla
    auto getHeightHelper = [&](std::shared_ptr<BinaryNode<ItemType>> node) -> int {
        if (!node) return 0; // Eğer düğüm boşsa yükseklik 0'dır
        return 1 + std::max(getHeightHelper(node->getLeftChildPtr()), getHeightHelper(node->getRightChildPtr()));
    };
    return getHeightHelper(rootPtr);
}

// **Ağaçtaki toplam düğüm sayısını hesaplayan fonksiyon**
template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const {
    // Lambda fonksiyonu ile düğüm sayısını recursive olarak hesapla
    auto countNodes = [&](std::shared_ptr<BinaryNode<ItemType>> node) -> int {
        if (!node) return 0; // Eğer düğüm boşsa, düğüm sayısı 0'dır
        return 1 + countNodes(node->getLeftChildPtr()) + countNodes(node->getRightChildPtr());
    };
    return countNodes(rootPtr);
}

// **AĞACI GÖRSEL OLARAK ÇİZME**
template <class ItemType>
void BinaryNodeTree<ItemType>::printTreeHelper(std::shared_ptr<BinaryNode<ItemType>> node, int space) const {
    if (node == nullptr) return;

    space += 10; // Her seviyede daha sağa kaydır

    // Önce sağ çocuğu yazdır (Ağacın daha üst kısımlarını ekrana yerleştirir)
    printTreeHelper(node->getRightChildPtr(), space);

    // Düğümü yazdır
    std::cout << std::endl;
    for (int i = 10; i < space; i++) std::cout << " ";
    std::cout << node->getItem() << "\n";

    // Sol çocuğu yazdır
    printTreeHelper(node->getLeftChildPtr(), space);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::printTree() const {
    std::cout << "\nBinary Search Tree:\n";
    printTreeHelper(rootPtr, 0);
}

#endif // BINARY_NODE_TREE_H
