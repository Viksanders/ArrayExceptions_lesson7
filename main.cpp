#include <iostream>
#include <exception>
#include <limits>
#include "MyVector.h"
#include "SomeExceptions.h"

int main()
{
    setlocale(LC_ALL, "");

    //std::cout << "INT: " << std::numeric_limits<int>::max() << "\n";

    //*     //Тестирование исключений
    try
    {
        MyVector V_test_0(-23);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        std::cout << "Constructor exception caught\n";
    }

    MyVector V_test_0(10);
    V_test_0.PushBack(24); V_test_0.PushBack(23); V_test_0.PushBack(11); V_test_0.PushBack(777);
    V_test_0.Print();

    try
    {
        int testval = V_test_0[-23];
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        std::cout << "Indexing [] exception caught\n";
    }


    try
    {
        V_test_0.Replace(22, 4);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        std::cout << "Replace fail tested!\n";
        V_test_0.Print();
    }


    try
    {
        V_test_0.Insert(22, 4);
        std::cout << "Insert test completed!\n";
        V_test_0.Print();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        std::cout << "Insert fail tested!\n";
        V_test_0.Print();
    }

    try
    {
        V_test_0.Insert(22, 6);
        std::cout << "Insert test completed!\n";
        V_test_0.Print();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        std::cout << "Insert fail tested!\n";
        V_test_0.Print();
    }

    //*/

    /*      //Тестирование самого по себе контейнера БЕЗ ИСКЛЮЧЕНИЙ
    MyVector V1;
    MyVector V2(1);

    std::cout << V1.GetCapacity() << "\n";
    std::cout << V1.GetSize() << "\n";
    std::cout << V1.isEmpty() << "\n";
    std::cout << V1.isFull() << "\n";
    V1.Print();
    V1.PushBack(10); V1.PushBack(11); V1.PushBack(13432);
    std::cout << V1.GetCapacity() << "\n";
    std::cout << V1.GetSize() << "\n";
    std::cout << V1.isEmpty() << "\n";
    std::cout << V1.isFull() << "\n";
    V1.Print();

    std::cout << "\n\n" << "\n";

    std::cout << V2.GetCapacity() << "\n";
    std::cout << V2.GetSize() << "\n";
    std::cout << V2.isEmpty() << "\n";
    std::cout << V2.isFull() << "\n";
    V2.Print();
    V2.PushBack(42); V2.PushBack(420);
    std::cout << V2.GetCapacity() << "\n";
    std::cout << V2.GetSize() << "\n";
    std::cout << V2.isEmpty() << "\n";
    std::cout << V2.isFull() << "\n";
    V2.Print();

    std::cout << "\n\n" << "\n";

    MyVector V3(V2);
    std::cout << V3.GetCapacity() << "\n";
    std::cout << V3.GetSize() << "\n";
    std::cout << V3.isEmpty() << "\n";
    std::cout << V3.isFull() << "\n";
    V3.Print();
    V3.PushBack(55); V3.PushBack(55); V3.PushBack(55); V3.PushBack(55);
    V3.Print();
    V2.Print();

    std::cout << "\n\n" << "\n";

    MyVector V4(1);
    std::cout << V4.GetCapacity() << "\n";
    std::cout << V4.GetSize() << "\n";
    std::cout << V4.isEmpty() << "\n";
    std::cout << V4.isFull() << "\n";
    V4.Print();
    V4.PushFront(512); V4.PushFront(5122); V4.PushFront(5);
    std::cout << V4.GetCapacity() << "\n";
    std::cout << V4.GetSize() << "\n";
    std::cout << V4.isEmpty() << "\n";
    std::cout << V4.isFull() << "\n";
    V4.Print();
    V4.Replace(11, 0); V4.Replace(133, 1); V4.Replace(21, 2);
    std::cout << V4.GetCapacity() << "\n";
    std::cout << V4.GetSize() << "\n";
    std::cout << V4.isEmpty() << "\n";
    std::cout << V4.isFull() << "\n";
    V4.Print();
    std::cout << "\nINSERT\n\n";
    V4.Insert(4441, 2); V4.Insert(4442, 2); V4.Insert(4443, 2); V4.Insert(4444, 2); V4.Insert(4445, 2); V4.Insert(4446, 2); V4.Insert(4447, 2); V4.Insert(4448, 2);
    std::cout << V4.GetCapacity() << "\n";
    std::cout << V4.GetSize() << "\n";
    std::cout << V4.isEmpty() << "\n";
    std::cout << V4.isFull() << "\n";
    V4.Print();


    std::cout << "\n\n" << "\n";
    MyVector V5(100);
    std::cout << V5.GetCapacity() << "\n";
    std::cout << V5.GetSize() << "\n";
    V5.PushBack(11); V5.PushBack(99);
    std::cout << V5.GetCapacity() << "\n";
    std::cout << V5.GetSize() << "\n";
    V5.Print();
    std::cout << "\nSHRINK TO FIT\n\n";
    V5.ShrinkToFit();
    std::cout << V5.GetCapacity() << "\n";
    std::cout << V5.GetSize() << "\n";
    V5.Print();
    std::cout << "\nADDING SOME STUFF\n\n";
    V5.PushBack(333);
    V5.Print();
    V5.PushFront(2222);
    V5.Print();
    V5.Insert(85, 2); V5.Insert(85, 2); V5.Insert(85, 2);
    V5.Print();
    std::cout << "Peregruzka test\n";
    std::cout << V5 << "\n";
    std::cout << "Operator [] test\n";

    for(int i = 0; i < V5.GetSize(); i++)
    {
        std::cout << V5[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\n\n" << "\n";

    MyVector V6(1);
    V6 = V5;
    V6.Print();
    V6 = V6;
    V6.Print();

    int test_arr[] = {11, 2, 3, 4, 0};
    std::cout << "Sizeof: " << sizeof(test_arr)/sizeof(int) << "\n";    //Почему здесь это работает а внутри класса - нет?!

    std::cout << "\n\n" << "\n";

    
    //MyVector V7(1);
    //V7 = test_arr;
    //std::cout << V7 << "\n";
    

    std::cout << "\nFIND TEST\n";
    MyVector V8;
    V8 = V5.Find(85);
    V8.Print();

    std::cout << "\nSORT TEST\n";
    V5.Print();
    V5.Sort();
    V5.Print();

    //std::cout << << "\n";
    //*/

    return 0;
}
