#pragma once
#include <iostream>

class MyVector
{
public:
    MyVector();			//����������� �� ���������
    MyVector(int capacity);	//������� ��������� ��������� �������					//Exception needed
    MyVector(MyVector& other);	//����������� �����������
    //!!!
    //! ������: � ��� ����, ���� � ���� ������������������� �������� {1, 2, 3} ��� ��� ��������?
    //! � ����������� ��������� = � ���� ��� �� ����������, ��. ����
    //!!!
    ~MyVector();
    int GetSize();				//�������� �������� size
    int GetCapacity();			//�������� �������� capacity
    void Print();							//������� � �������
    void PushBack(int item);	//�������� � ����� �������
    void PushFront(int item);	//�������� � ������ �������, �������� ������ ����������
    void Replace(int item, int position);	//�������� � �������� ����� � ������� �� ���������� �������								//Exception needed
    void Insert(int item, int position);	//�������� � �������� ����� ��� ������, ������ ����� ���������� ������ �� ���� �������	//Exception needed
    void ShrinkToFit();						//�������� �������� capacity � �������� size
    //void Reallocate(int capacity);		//����� �� ��� ����������, ��� ��� ������ � ��� ���������������, ������ �������������� ��� ���
    bool isEmpty();		//���������� ���� ������ ��� ���
    bool isFull();		//���������� ����� ������ ��� ���
    MyVector Find(int key);  //������� ����� �� ����� ������� � ������� ��������� ��������
    void Sort();            //����������� ���������
    friend std::ostream& operator<<(std::ostream& output, const MyVector& v);   //����� ���� �� � �� �����������, ���������� ���������� []
    int& operator[](const int position);    //������ ���������� ������ - ������, �� ������ ������� �� ����� �������, ��� � ������� �������
    MyVector& operator=(const MyVector& other);     //������������ ������ ������� ������ ������
    //MyVector& operator=(const int* array);          //????? ������������ ������� ������ ������
private:
    int* arr;			//��� ��������� � �������
    int size;			//������, � ������ �� ��� �����, ������� ���������
    int capacity;		//���������� ������, ����� ����������� ������������� ��� ����������� �������� size � capaticy

    void Erase();       //����� ��� ��������� ������ ������
    void Exch(int i, int j);    //������ ��� �������� �������
};
