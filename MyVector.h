#pragma once
#include <iostream>

class MyVector
{
public:
    MyVector();			//Конструктор по умолчанию
    MyVector(int capacity);	//Создает контейнер заданного размера					//Exception needed
    MyVector(MyVector& other);	//Конструктор копирования
    //!!!
    //! ВОПРОС: А КАК БЫТЬ, ЕСЛИ Я ХОЧУ ПРОИНИЦИАЛИЗИРОВАТЬ МАССИВОМ {1, 2, 3} ВОТ ТАК НАПРИМЕР?
    //! С ПЕРЕГРУЗКОЙ ОПЕРАТОРА = У МЕНЯ ТАК НЕ ПОЛУЧИЛОСЬ, СМ. НИЖЕ
    //!!!
    ~MyVector();
    int GetSize();				//Получить значение size
    int GetCapacity();			//Получить значение capacity
    void Print();							//Вывести в консоль
    void PushBack(int item);	//Добавить в конец массива
    void PushFront(int item);	//Добавить в начало массива, элементы справа подвинутся
    void Replace(int item, int position);	//Добавить в заданное место С заменой по указанному индексу								//Exception needed
    void Insert(int item, int position);	//Добавить в заданное место БЕЗ замены, правая часть подвинется вправо на один элемент	//Exception needed
    void ShrinkToFit();						//Привести значение capacity к значению size
    //void Reallocate(int capacity);		//Метод не был реализован, так как массив и так саморасширяется, смысла переопределять его нет
    bool isEmpty();		//Показывает пуст массив или нет
    bool isFull();		//Показывает полон массив или нет
    MyVector Find(int key);  //попытка найти по каким индесам в массиве находятся значения
    void Sort();            //Пузырьковая сотировка
    friend std::ostream& operator<<(std::ostream& output, const MyVector& v);   //Можно было бы и не перегружать, достаточно перегрузки []
    int& operator[](const int position);    //Внутри квадратных скобок - индекс, на выходе элемент по этому индексу, как в обычном массиве
    MyVector& operator=(const MyVector& other);     //Приравниваем одному объекту класса другой
    //MyVector& operator=(const int* array);          //????? Приравниваем объекту класса массив
private:
    int* arr;			//Сам контейнер с данными
    int size;			//Размер, а вернее та его часть, которая заполнена
    int capacity;		//Допустимый размер, может расширяться автоматически при приближении значения size к capaticy

    void Erase();       //Метод для избежания утечек памяти
    void Exch(int i, int j);    //меняет два элемента местами
};
