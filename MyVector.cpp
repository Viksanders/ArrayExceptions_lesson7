#pragma once
#include "MyVector.h"
#include "SomeExceptions.h"

MyVector::MyVector()
{
    this->capacity = 10;	//Истинный размер по умолчанию 10
    this->size = 0;			//Поскольку создавался пустой массив, то его размер до добавления туда элементов равен 0
    this->arr = new int[this->capacity];	//Выделение памяти размера capacity
    std::cout << "Default constructor called: " << this << "\n";
}

MyVector::MyVector(int capacity)
{
    //Throw
    //Если меньше 0 или больше предела int
    if ((capacity <= 0) || (capacity > 10000)) throw bad_length();

    this->capacity = capacity;
    this->size = 0;
    this->arr = new int[this->capacity];
    std::cout << "Set-size constructor called: " << this << "\n";
}

MyVector::MyVector(MyVector& other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->arr = new int[this->capacity];

    for (int i = 0; i < this->size; i++)	//Операция глубокого копирования
    {
        this->arr[i] = other.arr[i];
    }
    std::cout << "Copying constructor called: " << this << "\n";
}

MyVector::~MyVector()
{
    delete[] this->arr;
    std::cout << "Destructor called: " << this << "\n";
}

int MyVector::GetSize()
{
    return this->size;
}

int MyVector::GetCapacity()
{
    return this->capacity;
}

void MyVector::Print()
{
    if (this->size == 0)	//Не вижу смысл создавать аж целое исключение до этого случая, тут нет ничего особенного, обычная ситуация
    {
        std::cout << "Контейнер пуст\n";
    }
    else
    {
        for (int i = 0; i < this->size; i++)
        {
            std::cout << this->arr[i] << " ";
        }
        std::cout << "\n";
    }
}

void MyVector::PushBack(int item)
{
    if (this->size < this->capacity)
    {
        this->arr[this->size] = item;
        this->size++;
    }
    else
    {
        this->capacity += 10;	//Если ёмкость заполнена, то увеличиваем её на 10. НА САМОМ ДЕЛЕ ЭТО ОТКРЫТЫЙ ВОПРОС, КАК ЛУЧШЕ УВЕЛИЧИВАТЬ
        int* temp = new int[this->capacity];	//Создаём буфферный массив с увеличенной ёмкостью
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->arr[i];
        }
        temp[this->size] = item;	//Добавляем последним, что должно быть добавлено
        this->size++;
        delete[] this->arr;			//Удаляем старый массив
        this->arr = temp;			//Указатель присваиваем ту область памяти, на которую указывал старый массив
    }
}

void MyVector::PushFront(int item)
{
    if (this->size < (this->capacity - 1))	//Почему -1? Потому что правую часть нужно сдвигать на 1, это нужно предусмотреть
    {											//И в противном случае расширять ёмкость

        if (this->size == 0) { PushBack(item); return; }	//Если пустой массив с ёмкость = 1, то просто вызываем пушбэк и всё

        int* temp = new int[this->capacity];	//Аналогично PushBack
        for (int i = 0; i < this->size; i++)
        {
            temp[i + 1] = this->arr[i];			//+1 потому что на место первого элемента будет поставлен новый, остальные двигаются вправо
        }
        temp[0] = item;
        this->size++;							//Здесь опять аналогично пушбэку
        delete[] this->arr;
        this->arr = temp;
    }
    else
    {
        this->capacity += 10;		//Аналогично методу PushBack
        int* temp = new int[this->capacity];	//В целом здесь всё то же самое, можно было бы создать отдельный закрытый метод для компактности
        for (int i = 0; i < this->size; i++)
        {
            temp[i + 1] = this->arr[i];
        }
        temp[0] = item;
        this->size++;
        delete[] this->arr;
        this->arr = temp;
    }
}

void MyVector::Replace(int item, int position)
{
    //Place for throw
    //Если введенный индекс меньше нуля или находится за пределами размера массива
    if ((position < 0) || (position >= this->size)) throw bad_range();

    this->arr[position] = item;
}

void MyVector::Insert(int item, int position)
{
    //Place for throw
    //А вот здесь в отличии от предыдущего метода используем (position > this->size), а не (position >= this->size)
    //потому что метод Insert допускает вставку нового элемента за самым последним, в отличии от Replace (там заменять просто нечего)
    if ((position < 0) || (position > this->size)) throw bad_range();

    if (this->size >= (this->capacity - 1)) { this->capacity += 10; }	//Если ёмкости не хватает - прибавляем 10ку

    this->size++;
    int* temp = new int[this->capacity];
    for (int i = 0; i < position; i++)
    {
        temp[i] = this->arr[i];
    }
    temp[position] = item;
    for (int i = position + 1; i < this->size; i++)
    {
        temp[i] = this->arr[i - 1];
    }
    delete[] this->arr;
    this->arr = temp;
}

void MyVector::ShrinkToFit()
{
    if (this->size == 0)	//Тоже не стал делать исключение, т.к. ситуация тривиальна и в принципе тут всё безопасно (наверное)
    {
        return;
    }
    else
    {
        this->capacity = this->size;
    }
}

bool MyVector::isEmpty()
{
    return (this->size == 0) ? true : false;
}

bool MyVector::isFull()
{
    return (this->size == this->capacity) ? true : false;
}

MyVector MyVector::Find(int key)
{
    MyVector temp(1);   //Создаем вектор размера 1
    int ctr = 0;
    for (int i = 0; i < this->size; i++) //обычный линейный поиск
    {
        if (this->arr[i] == key) { temp.PushBack(i); ctr++; }
    }
    if (ctr == 0) temp.PushBack(-1);    //Возврат единичного вектора значения -1 говорит о том, что искомого числа в контейнере нет
    temp.ShrinkToFit();
    return temp;    //возвращаем вектор из индексов, которым соответствуют искомые значения key
}

void MyVector::Exch(int i, int j)
{
    //Здесь не стал делать исключение, потому что это закрытый метод, который используется только в Sort
    //А внутри этого метода уже предусмотрено, что индексы не выйдут за границы массива
    int temp = this->arr[i];
    this->arr[i] = this->arr[j];
    this->arr[j] = temp;
}

void MyVector::Sort()
{
    if (this->size == 0) return;

    for (int i = 0; i < this->size; i++)
    {
        for (int j = i + 1; j < this->size; j++)
        {
            if (this->arr[i] > this->arr[j]) Exch(i, j);
        }
    }
}

std::ostream& operator<<(std::ostream& output, const MyVector& v)
{
    if (v.size == 0)
    {
        output << "Array is empty!";
    }
    else
    {
        for (int i = 0; i < v.size; i++)
        {
            output << v.arr[i] << " ";
        }
    }
    return output;
}

int& MyVector::operator[](const int position)
{
    //throw
    if ((position < 0) || (position >= this->size)) throw bad_range();  //Здесь все аналогично

    return this->arr[position];
}

void MyVector::Erase()
{
    delete this->arr;
    this->size = 0;
}

MyVector& MyVector::operator=(const MyVector& other)
{
    if (this == &other) return *this;   //Если самоприсваивание, то не делаем ничего

    Erase();                            //иначе вызываем метод Erase() для избежания утечек памяти
    this->size = other.size;
    this->capacity = other.capacity;
    this->arr = new int[this->capacity];    //И создаём массив заново
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = other.arr[i];
    }
    return *this;
}

/*  //здесь была попытка приравнять контейнеру значения из статического массива, попытка не удалась, оставлю этот вопрос для слака
MyVector& MyVector::operator=(const int* array)     //??????????????????
{
    std::cout << sizeof(*array) / sizeof(int) << "\n"; //ПОЧЕМУ 1????

    Erase();
    this->size = sizeof(*array) / sizeof(int);
    this->capacity = this->size;

    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = array[i];
    }
    return *this;
}
*/
