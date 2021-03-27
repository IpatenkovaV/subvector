#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct subvector
{
    int* mas; //указатель на первый элемент в массиве
    int capacity; //размер всего массива
    int top; //размер занятой памяти в массиве
};

void init(subvector* qv) {
    qv->mas = new int[1];
    qv->capacity = 1;
    qv->top = 0;
}

// вывод параметров вектора
void print(subvector* qv)
{
    for (int i = 0; i < qv->capacity; ++i)
    {
        cout << endl << qv->mas[i];
    }
    cout << endl << "capacity: " << qv->capacity;
    cout << endl << "top: " << qv->top;
}

//добавление элемента, увеличение памяти
void push_back(subvector* qv, int new_element) {
    if (qv->capacity == qv->top)
    {
        int* new_mas = new int[qv->capacity * 2];
        for (int i = 0; i < qv->top; ++i) {
            new_mas[i] = qv->mas[i];
        }
        new_mas[qv->top] = new_element;
        delete[] qv->mas;
        qv->mas = new_mas;
        qv->capacity *= 2;
        qv->top++;
    }
    else
    {
        qv->mas[qv->top] = new_element;
        qv->top++;
    }
    
    
}

//функция удаляет с конца вектора
int pop_back(subvector* qv) {
    qv->top--;
    return 0;
}

//увеличить емкость вектора
void resize(subvector* qv, unsigned int new_capacity) {
    if (new_capacity > qv->capacity)
    {
        qv->capacity = new_capacity;
    }
}

//очищаем ненужную память
void shrink_to_fit(subvector* qv) {
    qv->capacity = qv->top;
}

//очищаем недовектор, занимаемое место не меняем
void clear(subvector* qv){
    qv->top = 0;
}

void destractor(subvector* qv) {
    delete[] qv->mas; //удаление маcсива

    qv->mas = new int[1];
    qv->capacity = 1;
    qv->top = 0;
}

void init_from_file(subvector* qv, std::string filename) {
    ifstream fromFile(filename, ios::in);
    if (fromFile.is_open())
    {
        int count = 0; // кол-во элементов в файле
        fromFile >> count; // получаем кол-во элементов из файла
        for (int i = 0; i < count; ++i)
        {
            int element;
            fromFile >> element;
            push_back(qv, element); // qv - это уже является указателем, поэтому без &
        }
    }
    else
    {
        cout << "The txt file doesn't open to reading" << endl;
    }
    fromFile.close();
}

int main()
{
    subvector vec;
    init(&vec);

    push_back(&vec, 1);
    push_back(&vec, 2);
    push_back(&vec, 3);
    push_back(&vec, 4);
    push_back(&vec, 5);

    print(&vec);

    init_from_file(&vec, "test.txt");
    print(&vec);

    subvector vec1;
    init(&vec1);
    print(&vec1);
}
