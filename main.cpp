#include "BinarySearchTree.h" // İkili Arama Ağacı (BST) yapısını içeren başlık dosyası
#include "PrecondViolatedExcep.h" // Hata yönetimi için eklendi
#include <iostream> // Giriş ve çıkış işlemleri için
#include <queue> // BFS (Seviye sıralı geçiş) için kuyruk veri yapısı
#include <limits> // Geçersiz girişleri temizlemek için

using namespace std;

/**
 * Kullanıcıdan geçerli bir tam sayı girişi almayı sağlayan fonksiyon.
 * Eğer kullanıcı geçersiz bir giriş yaparsa (örneğin, harf veya ondalıklı sayı girerse),
 * hata mesajı gösterilir ve tekrar giriş yapması istenir.
 */
int getValidatedInput() {
    int value;
    while (true) {
        cout << "Enter an integer value: ";
        cin >> value;
        if (cin.fail()) { 
            cin.clear(); // Hata bayrağını temizle
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hatalı girişi temizle
            cout << "Invalid input! Please enter a valid integer.\n";
        } else {
            return value; // Geçerli giriş alındı, döndür
        }
    }
}

/**
 * **Seviye (BFS) Sıralı Geçiş**
 * Ağacın düğümlerini **seviyelere göre** dolaşarak ekrana yazdıran fonksiyon.
 * BFS (Breadth-First Search) algoritması kullanılmıştır.
 */
void levelOrderTraversal(BinarySearchTree<int>& tree) {
    if (tree.getRootPtr() == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    queue<std::shared_ptr<BinaryNode<int>>> q; // BFS için kuyruk oluştur
    q.push(tree.getRootPtr()); // Kök düğümü kuyruğa ekle

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        
        if (node) {
            cout << node->getItem() << " "; // Mevcut düğümün değerini yazdır
            q.push(node->getLeftChildPtr()); // Sol çocuğu kuyruğa ekle
            q.push(node->getRightChildPtr()); // Sağ çocuğu kuyruğa ekle
        }
    }
    cout << endl;
}

/**
 * **Maksimum Elemanın Bulunduğu Seviye**
 * Ağacın en büyük elemanının hangi seviyede olduğunu bulan fonksiyon.
 * BST'de en büyük eleman **her zaman en sağdadır**, bu yüzden sağa giderek seviye sayıyoruz.
 */
int findMaxLevel(std::shared_ptr<BinaryNode<int>> node, int level = 1) { // Ders ve kitabımız kapsamında root level 1  
    if (!node) {
        return level - 1; // Eğer düğüm yoksa, bir önceki seviyeyi döndür.
    }
    return findMaxLevel(node->getRightChildPtr(), level + 1);
}

/**
 * **Düğümleri ekrana yazdıran fonksiyon**
 * BST'nin gezinti işlemlerinde (inorder, preorder, postorder) her düğümü yazdırmak için kullanılır.
 */
void display(int& item) {
    cout << item << " ";
}

/**
 * **Ana fonksiyon (Kullanıcı menüsü)**
 * Kullanıcıya bir menü sunarak BST üzerinde çeşitli işlemler yapmasını sağlar.
 */
int main() {
    BinarySearchTree<int> bst; // BST nesnesi oluştur
    int choice, value;

    do {
        // **Kullanıcıya menüyü göster**
        cout << "\nBinary Search Tree Menu\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Display Inorder\n";
        cout << "4. Display Preorder\n";
        cout << "5. Display Postorder\n";
        cout << "6. Level Order Traversal\n";
        cout << "7. Find Max Element Level\n";
        cout << "8. Print Tree (Graph View)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Kullanıcının yanlış giriş yapmasını önleme
        if (cin.fail()) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please enter a valid number.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    do {
                     value = getValidatedInput();
                } while (!bst.add(value));  // Eğer aynı sayı girilmişse tekrar giriş iste.
                cout << value << " added to the tree.\n";
                break;
                case 2:
                    value = getValidatedInput();
                    if (bst.remove(value))
                        cout << "Deleted successfully.\n";
                    else
                        throw PrecondViolatedExcep("Value not found in tree."); // Hata fırlat
                    break;
                case 3:
                    cout << "Inorder Traversal: ";
                    bst.inorderTraverse(display);
                    cout << endl;
                    break;
                case 4:
                    cout << "Preorder Traversal: ";
                    bst.preorderTraverse(display);
                    cout << endl;
                    break;
                case 5:
                    cout << "Postorder Traversal: ";
                    bst.postorderTraverse(display);
                    cout << endl;
                    break;
                case 6:
                    cout << "Level Order Traversal: ";
                    levelOrderTraversal(bst);
                    break;
                case 7:
                    cout << "Maximum Element Level: " << findMaxLevel(bst.getRootPtr(), 1) << endl;
                    break;
                case 8:
                    bst.printTree(); // Grafiği ekrana yazdır
                    break;
                case 9:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }
        } catch (const PrecondViolatedExcep& e) { 
            cout << e.what() << endl; // Hata mesajını göster
        }
    } while (choice != 9); // Kullanıcı çıkış yapana kadar devam et

    return 0;
}
