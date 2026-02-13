
Prepared by: Hülya Ceren Lüleci
Student Number: 230206027
Department: Bilgisayar Muhendisliği (Turkce)
2nd Year

-------------------------------------------Algoritmalar2-Homework------------------------------------------

This project is based on the Binary Search Tree (BST) data structure,
allowing users to perform insertion, deletion, and visualization operations on the tree.
Additionally, Level Order (BFS) Traversal and 
Finding the Level of the Maximum Element functionalities have been successfully implemented.

------------------------------------------------------------------------------------------------------------
-----------------------------------**Derleme ve Çaliştirma Komutlari**--------------------------------------
------------------------------------------------------------------------------------------------------------

Compile: 

g++ -std=c++14 -o bst_program main.cpp NotFoundException.cpp PrecondViolatedExcep.cpp -I.


Explanation:
'g++' -> GNU C++ compiler
'-std=c++14' -> Use C++14 standard
'-o bst_program' -> Output executable file name
'main.cpp NotFoundException.cpp PrecondViolatedExcep.cpp' -> Files to compile
'-I.' -> **Includes all header (.h) files in the current directory**
 (This ensures the compiler can find `BinarySearchTree.h`, `BinaryNodeTree.h`, etc.)

------------------------------------------------------------------------------------------------------------

After compiling, run the program with:

.\bst_program.exe 

------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------

Test etmek için Dengeli bir BST: 
50, 30, 70, 20, 40, 60, 80

Beklenen Ciktilar:

Inorder Traversal (Kucukten buyuge siralama) (Left-Root-Right)
20 30 40 50 60 70 80

Preorder Traversal (Root-Left-Right)
50 30 20 40 70 60 80

Postorder Traversal (Left-Right-Root)
20 40 30 60 80 70 50

Level Order Traversal (BFS - Seviye Sirali Geçiş)
50 30 70 20 40 60 80

Find Max Level (En Buyuk Elemanin Seviyesi)
Maximum Element Level: 3

Print Tree (Grafiksel Goruntu)

         [50]
        /    \
     [30]    [70]
    /   \   /    \
  [20] [40] [60] [80]


------------------------------------------------------------------------------------------------------------

Test etmek için Tek Tarafli (Duzgun Zincir) BST:
10, 20, 30, 40, 50

Beklenen Ciktilar:

Inorder Traversal (Kucukten buyuge siralama) (Left-Root-Right)
10 20 30 40 50

Preorder Traversal (Root-Left-Right)
10 20 30 40 50


Postorder Traversal (Left-Right-Root)
50 40 30 20 10


Level Order Traversal (BFS - Seviye Sirali Geçiş)
10 20 30 40 50


Find Max Level (En Buyuk Elemanin Seviyesi)
Maximum Element Level: 5


Print Tree (Grafiksel Goruntu)

[10]
   \
   [20]
       \
       [30]
           \
           [40]
               \
               [50]


------------------------------------------------------------------------------------------------------------
----------------------------------**Karsilasilan Sorunlar ve Cozumlerim**-----------------------------------
------------------------------------------------------------------------------------------------------------

1. Sablon Sinif Kullanimi ve Derleme Hatasi
Problem: Sablon siniflar .cpp dosyalarina konuldugunda “redefinition” hatalari meydana geldi.
Cozum:
Sablon siniflar, template tanimlari derleme zamaninda genisletildigi icin yalnizca .h (header) dosyalarinda tanimlandi.
Ornegin (include "BinarySearchTree.h") diyerek .h dosyalarini cagirmak ise yaramadi 
cunku sablonlar ayri .cpp dosyasinda tanimlanamaz.

------------------------------------------------------------------------------------------------------------

2. Kullanicidan Alinan Girislerin Dogrulanmasi
Problem: Kullanici tam sayi yerine harf veya ondalikli sayi girince program sonsuz donguye giriyordu.
Cozum:
cin.fail() fonksiyonu ile hatali giris kontrol edildi.
cin.clear() ve cin.ignore() ile hatali giris temizlendi.
getValidatedInput() fonksiyonu olusturularak yalnizca gecerli tamsayi girislerinin alinmasi saglandi.

------------------------------------------------------------------------------------------------------------

3. Agaci ASCII Karakterler ile Cizme
Problem: Agac gorsellestirmesi baslangicta hizasiz ve yamuk gorunuyordu.
Cozum:
Dugumler arasindaki mesafe dinamik olarak hesaplandi.
Capraz cizgiler (/ ve \) dugumlerin tam ortasina gelecek sekilde hizalandi.
BFS ile dugumler gezilerek uygun satir pozisyonlari belirlendi.
Ozellikle buyuk agaclarda dugumlerin birbirine cakismasini engellemek icin bosluk ayarlari optimize edildi.

------------------------------------------------------------------------------------------------------------

4. Exception Handling (Hata Yonetimi)
Problem: Silmek istenilen eleman bulunamadiginda program cokuyordu.
Cozum:
PrecondViolatedExcep adinda ozel bir hata sinifi olusturuldu, kitabimizdaki gibi.
throw ile eleman bulunamazsa ozel hata firlatildi.
try-catch blogu ile hatalar yakalanarak kullaniciya hata mesaji gosterildi.

------------------------------------------------------------------------------------------------------------

5. auto Kullanimi ve C++ Surum Hatasi
Problem: auto anahtar kelimesini kullaninca C++ surum farki nedeniyle hata aldim.
Cozum:
Kodumuzu C++14 ile uyumlu hale getirdim.
auto kullanimi yerine degisken turlerini acikca belirttim.
C++11 veya daha dusuk bir surumde calistirinca hata aldigimi fark ettim ve 
zorunlu olarak -std=c++14 ile derlemeye karar verdim.

------------------------------------------------------------------------------------------------------------



