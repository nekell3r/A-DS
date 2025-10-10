#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

/* ============================================================
   ШПАРГАЛКА: Стек на динамическом списке (Stack)
   ============================================================
   typedef struct {
       struct Item* top;  // вершина стека
       int size;          // размер стека
   } stack;
   struct Item {
       T data;            // данные элемента
       struct Item* prev; // предыдущий элемент
   };
   ФУНКЦИИ:
   void Create(stack* s)           ∅ → Stack
   bool Empty(stack* s)            Stack → boolean
   int Size(stack* s)              Stack → N
   bool Push(stack* s, T t)        Stack × T → Stack
   bool Pop(stack* s)              Stack → Stack
   T Top(stack* s)                 Stack → T
   void Destroy(stack* s)          Stack → ∅
   ============================================================ */

struct Item
{
    T data;
    struct Item* prev;
};

typedef struct
{
    struct Item* top;
    int size;
} stack;

void Create(stack* s)
{
    s->top = 0;
    s->size = 0;
}

bool Empty(stack* s)
{
    return s->size == 0;
}

int Size(stack* s)
{
    return s->size;
}

bool Push(stack* s, T t)
{
    Item* i = malloc(sizeof(struct Item));
    if(!i)
        return false;
    i->data = t;
    i->prev = s->top;
    s->top = i;
    s->size++;
    return true;
}

bool Pop(stack* s)
{
    if(!s->size)
        return false;
    struct Item* i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return true;
}

T Top(stack* s)
{
    if(s->top)
        return s->top->data;
}

void Destroy(stack* s)
{
    while(s->top)
    {
        struct Item* i = s->top;
        s->top = s->top->prev;
        free(i);
    }
    s->top = 0;
    s->size = 0;
}

// ============ СЛОЖНОСТЬ ============
// Create: O(1) - инициализация
// Push: O(1) - добавление в вершину
// Pop: O(1) - удаление из вершины
// Top: O(1) - просмотр вершины
// Empty: O(1) - проверка пустоты
// Size: O(1) - получение размера
// Destroy: O(n) - удаление всех элементов
// Память: O(n) - односвязный список

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Стек (Stack) на динамическом списке ===\n\n");
    
    // Тест 1: Базовые операции
    stack s1;
    Create(&s1);
    
    printf("Тест 1: Push и Pop\n");
    Push(&s1, (void*)10);
    Push(&s1, (void*)20);
    Push(&s1, (void*)30);
    printf("После Push(10,20,30): Top=%d, Size=%d\n", 
           (int)Top(&s1), Size(&s1)); // Top=30, Size=3
    
    Pop(&s1);
    printf("После Pop: Top=%d, Size=%d\n", 
           (int)Top(&s1), Size(&s1)); // Top=20, Size=2
    
    // Тест 2: Проверка на пустоту
    printf("\nТест 2: Empty\n");
    printf("Пуст ли стек? %s\n", Empty(&s1) ? "Да" : "Нет"); // Нет
    
    Pop(&s1);
    Pop(&s1);
    printf("После удаления всех: Пуст? %s\n", Empty(&s1) ? "Да" : "Нет"); // Да
    
    // Тест 3: Работа со строками
    printf("\nТест 3: Стек строк\n");
    stack s2;
    Create(&s2);
    Push(&s2, "first");
    Push(&s2, "second");
    Push(&s2, "third");
    printf("Top: %s\n", (char*)Top(&s2)); // third
    
    Destroy(&s1);
    Destroy(&s2);
    
    return 0;
}
*/

