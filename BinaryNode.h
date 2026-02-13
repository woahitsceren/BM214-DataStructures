#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <memory>

// BinaryNode sınıfı şablonu, bir düğümün veri (item) ve iki child pointer'ını tutar.
// Akıllı işaretçiler (smart pointers) kullanılarak bellek yönetimi sağlanır. Ders içeriğindeki kodlardaki gibi.
template <class ItemType>
class BinaryNode {
private:
    ItemType item; // Düğümün tuttuğu veri
    std::shared_ptr<BinaryNode<ItemType>> leftChildPtr; // Sol child pointer
    std::shared_ptr<BinaryNode<ItemType>> rightChildPtr; // Sağ child pointer

public:
    // Default constructor
    BinaryNode() = default;

    // Parametre alan constructor: Düğümü verilen item ile başlatır, child pointer'lar nullptr olur
    BinaryNode(const ItemType& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) {}

    // Düğümün item'ını ayarlar
    void setItem(const ItemType& anItem) { item = anItem; }
    
    // Düğümün item'ını döndürür
    ItemType getItem() const { return item; }

    // Düğümün leaf (yaprak) olup olmadığını kontrol eder (child pointer'ları nullptr ise true döner)
    bool isLeaf() const { return (leftChildPtr == nullptr && rightChildPtr == nullptr); }

    // Sol child pointer'ı döndürür
    std::shared_ptr<BinaryNode<ItemType>> getLeftChildPtr() const { return leftChildPtr; }

    // Sağ child pointer'ı döndürür
    std::shared_ptr<BinaryNode<ItemType>> getRightChildPtr() const { return rightChildPtr; }

    // Sol child pointer'ı ayarlar
    void setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr) { leftChildPtr = leftPtr; }

    // Sağ child pointer'ı ayarlar
    void setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr) { rightChildPtr = rightPtr; }
};

#endif // BINARY_NODE_H
