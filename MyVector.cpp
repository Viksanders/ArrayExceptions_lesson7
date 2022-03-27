#pragma once
#include "MyVector.h"
#include "SomeExceptions.h"

MyVector::MyVector()
{
    this->capacity = 10;	//�������� ������ �� ��������� 10
    this->size = 0;			//��������� ���������� ������ ������, �� ��� ������ �� ���������� ���� ��������� ����� 0
    this->arr = new int[this->capacity];	//��������� ������ ������� capacity
    std::cout << "Default constructor called: " << this << "\n";
}

MyVector::MyVector(int capacity)
{
    //Throw
    //���� ������ 0 ��� ������ ������� int
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

    for (int i = 0; i < this->size; i++)	//�������� ��������� �����������
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
    if (this->size == 0)	//�� ���� ����� ��������� �� ����� ���������� �� ����� ������, ��� ��� ������ ����������, ������� ��������
    {
        std::cout << "��������� ����\n";
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
        this->capacity += 10;	//���� ������� ���������, �� ����������� � �� 10. �� ����� ���� ��� �������� ������, ��� ����� �����������
        int* temp = new int[this->capacity];	//������ ��������� ������ � ����������� ��������
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->arr[i];
        }
        temp[this->size] = item;	//��������� ���������, ��� ������ ���� ���������
        this->size++;
        delete[] this->arr;			//������� ������ ������
        this->arr = temp;			//��������� ����������� �� ������� ������, �� ������� �������� ������ ������
    }
}

void MyVector::PushFront(int item)
{
    if (this->size < (this->capacity - 1))	//������ -1? ������ ��� ������ ����� ����� �������� �� 1, ��� ����� �������������
    {											//� � ��������� ������ ��������� �������

        if (this->size == 0) { PushBack(item); return; }	//���� ������ ������ � ������� = 1, �� ������ �������� ������ � ��

        int* temp = new int[this->capacity];	//���������� PushBack
        for (int i = 0; i < this->size; i++)
        {
            temp[i + 1] = this->arr[i];			//+1 ������ ��� �� ����� ������� �������� ����� ��������� �����, ��������� ��������� ������
        }
        temp[0] = item;
        this->size++;							//����� ����� ���������� �������
        delete[] this->arr;
        this->arr = temp;
    }
    else
    {
        this->capacity += 10;		//���������� ������ PushBack
        int* temp = new int[this->capacity];	//� ����� ����� �� �� �� �����, ����� ���� �� ������� ��������� �������� ����� ��� ������������
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
    //���� ��������� ������ ������ ���� ��� ��������� �� ��������� ������� �������
    if ((position < 0) || (position >= this->size)) throw bad_range();

    this->arr[position] = item;
}

void MyVector::Insert(int item, int position)
{
    //Place for throw
    //� ��� ����� � ������� �� ����������� ������ ���������� (position > this->size), � �� (position >= this->size)
    //������ ��� ����� Insert ��������� ������� ������ �������� �� ����� ���������, � ������� �� Replace (��� �������� ������ ������)
    if ((position < 0) || (position > this->size)) throw bad_range();

    if (this->size >= (this->capacity - 1)) { this->capacity += 10; }	//���� ������� �� ������� - ���������� 10��

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
    if (this->size == 0)	//���� �� ���� ������ ����������, �.�. �������� ���������� � � �������� ��� �� ��������� (��������)
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
    MyVector temp(1);   //������� ������ ������� 1
    int ctr = 0;
    for (int i = 0; i < this->size; i++) //������� �������� �����
    {
        if (this->arr[i] == key) { temp.PushBack(i); ctr++; }
    }
    if (ctr == 0) temp.PushBack(-1);    //������� ���������� ������� �������� -1 ������� � ���, ��� �������� ����� � ���������� ���
    temp.ShrinkToFit();
    return temp;    //���������� ������ �� ��������, ������� ������������� ������� �������� key
}

void MyVector::Exch(int i, int j)
{
    //����� �� ���� ������ ����������, ������ ��� ��� �������� �����, ������� ������������ ������ � Sort
    //� ������ ����� ������ ��� �������������, ��� ������� �� ������ �� ������� �������
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
    if ((position < 0) || (position >= this->size)) throw bad_range();  //����� ��� ����������

    return this->arr[position];
}

void MyVector::Erase()
{
    delete this->arr;
    this->size = 0;
}

MyVector& MyVector::operator=(const MyVector& other)
{
    if (this == &other) return *this;   //���� ����������������, �� �� ������ ������

    Erase();                            //����� �������� ����� Erase() ��� ��������� ������ ������
    this->size = other.size;
    this->capacity = other.capacity;
    this->arr = new int[this->capacity];    //� ������ ������ ������
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = other.arr[i];
    }
    return *this;
}

/*  //����� ���� ������� ���������� ���������� �������� �� ������������ �������, ������� �� �������, ������� ���� ������ ��� �����
MyVector& MyVector::operator=(const int* array)     //??????????????????
{
    std::cout << sizeof(*array) / sizeof(int) << "\n"; //������ 1????

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
