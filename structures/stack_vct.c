#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

const int POOL_SIZE = 100;

typedef struct {
    T*  data;
    int size;
} Vector;

void Create(Vector* v, int sz);          // выделяет память под массив
void Resize(Vector* v, int sz);          // изменяет размер массива
void Save(Vector* v, int i, T t);        // записывает элемент по индексу
T    Load(Vector* v, int i);             // читает элемент по индексу
void Destroy(Vector* v);                 // освобождает память

/* ===========================
        Стек на векторе
   =========================== */

typedef struct
{
    int size;
    int capacity;
    Vector data;
} stack;

void Stack_Create(stack* s)
{
    s->size = 0;
    s->capacity = POOL_SIZE;
    Create(&s->data, s->capacity);
}

bool Empty(stack* s)
{
    return s->size == 0;
}

int Size(stack* s)
{
    return s->size;
}

void Push(stack* s, T t)
{
    if(s->size >= s->capacity) {
        s->capacity *= 2;
        Resize(&s->data, s->capacity);
    }
    Save(&s->data, s->size, t);
    s->size++;
}

void Pop(stack* s)
{
    if(!s->size)
        return;
    s->size--;
}

T Top(stack* s)
{
    if(s->size)
        return Load(&s->data, s->size-1);
}

void Stack_Destroy(stack* s)
{
    Destroy(&s->data);
}

