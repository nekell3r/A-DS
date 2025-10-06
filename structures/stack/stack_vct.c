#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

const int POOL_SIZE = 100;

/* ============================================================
   ШПАРГАЛКА: Стек на векторе (Stack on Vector)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       int size;        // текущий размер стека
       int capacity;    // вместимость (capacity)
       Vector data;     // вектор для хранения данных
   } stack;
   
   ФУНКЦИИ:
   void Stack_Create(stack* s)      ∅ → Stack
   bool Empty(stack* s)             Stack → boolean
   int Size(stack* s)               Stack → N
   void Push(stack* s, T t)         Stack × T → Stack
   void Pop(stack* s)               Stack → Stack
   T Top(stack* s)                  Stack → T
   void Stack_Destroy(stack* s)     Stack → ∅
   ============================================================ */

typedef struct {
    T*  data;
    int size;
} Vector;

void VCT_Create(Vector* v, int sz);          // выделяет память под массив
void VCT_Resize(Vector* v, int sz);          // изменяет размер массива
void VCT_Save(Vector* v, int i, T t);        // записывает элемент по индексу
T    VCT_Load(Vector* v, int i);             // читает элемент по индексу
void VCT_Destroy(Vector* v);                 // освобождает память

typedef struct
{
    int size;
    int capacity;
    Vector data;
} stack;

void Create(stack* s)
{
    s->size = 0;
    s->capacity = POOL_SIZE;
    VCT_Create(&s->data, s->capacity);
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
        VCT_Resize(&s->data, s->capacity);
    }
    VCT_Save(&s->data, s->size, t);
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
        return VCT_Load(&s->data, s->size-1);
}

void Stack_Destroy(stack* s)
{
    VCT_Destroy(&s->data);
}

// ============ СЛОЖНОСТЬ ============
// Create: O(n) - выделение памяти под начальный capacity
// Push: O(1) амортизированное - O(n) при расширении
// Pop: O(1) - уменьшение счетчика
// Top: O(1) - доступ по индексу
// Empty: O(1) - проверка счетчика
// Size: O(1) - получение счетчика
// Stack_Destroy: O(1) - освобождение вектора
// Память: O(capacity) - динамический массив

// Преимущества стека на векторе:
// - Лучшая локальность кэша (элементы рядом в памяти)
// - Нет malloc/free для каждого элемента
// - Быстрый доступ к элементам
// - Амортизированное O(1) для Push

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Стек (Stack) на векторе ===\n\n");
    
    // Тест 1: Базовые операции LIFO
    stack s1;
    Create(&s1);
    
    printf("Тест 1: Push и Pop (LIFO)\n");
    Push(&s1, (void*)10);
    Push(&s1, (void*)20);
    Push(&s1, (void*)30);
    printf("После Push(10,20,30): Top=%d, Size=%d\n", 
           (int)Top(&s1), Size(&s1)); // Top=30, Size=3
    
    Pop(&s1);
    printf("После Pop: Top=%d, Size=%d\n", 
           (int)Top(&s1), Size(&s1)); // Top=20, Size=2
    
    // Тест 2: Проверка пустоты
    printf("\nТест 2: Empty\n");
    printf("Пуст ли стек? %s\n", Empty(&s1) ? "Да" : "Нет"); // Нет
    
    Pop(&s1);
    Pop(&s1);
    printf("После удаления всех: Пуст? %s\n", Empty(&s1) ? "Да" : "Нет"); // Да
    
    // Тест 3: Автоматическое расширение
    printf("\nТест 3: Автоматическое расширение capacity\n");
    stack s2;
    Create(&s2);
    
    printf("Начальный capacity: %d\n", s2.capacity); // 100
    
    // Добавляем больше чем capacity
    for (int i = 0; i < 150; i++) {
        Push(&s2, (void*)i);
    }
    
    printf("После 150 элементов:\n");
    printf("  Size: %d\n", Size(&s2)); // 150
    printf("  Capacity: %d\n", s2.capacity); // 200 (расширился)
    printf("  Top: %d\n", (int)Top(&s2)); // 149
    
    // Тест 4: Обработка выражения
    printf("\nТест 4: Вычисление постфиксного выражения\n");
    printf("Выражение: 3 4 + 2 * (должно быть 14)\n");
    
    stack s3;
    Create(&s3);
    
    // Постфиксная нотация: 3 4 + 2 *
    Push(&s3, (void*)3);
    Push(&s3, (void*)4);
    
    int a = (int)Top(&s3); Pop(&s3);
    int b = (int)Top(&s3); Pop(&s3);
    Push(&s3, (void*)(b + a));
    
    Push(&s3, (void*)2);
    
    a = (int)Top(&s3); Pop(&s3);
    b = (int)Top(&s3); Pop(&s3);
    Push(&s3, (void*)(b * a));
    
    printf("Результат: %d\n", (int)Top(&s3)); // 14
    
    Stack_Destroy(&s1);
    Stack_Destroy(&s2);
    Stack_Destroy(&s3);
    
    return 0;
}
*/
