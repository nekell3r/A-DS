#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

/* ============================================================
   ШПАРГАЛКА: Очередь на массиве (Queue Array)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       T data[N];   // кольцевой буфер
       int head;    // индекс головы (первого элемента)
       int size;    // количество элементов
   } QueueArray;
   
   ФУНКЦИИ:
   void QA_Create(QueueArray* q)        ∅ → Queue
   bool QA_Empty(const QueueArray* q)   Queue → boolean
   int QA_Size(const QueueArray* q)     Queue → N
   bool QA_Push(QueueArray* q, T t)     Queue × T → Queue
   T QA_Top(const QueueArray* q)        Queue → T
   bool QA_Pop(QueueArray* q)           Queue → Queue
   void QA_Destroy(QueueArray* q)       Queue → ∅
   ============================================================ */

const int N = 100;
typedef struct {
    T   data[N];  // сам буфер
    int head;     // индекс головы
    int size;     // количество элементов
} QueueArray;

void QA_Create(QueueArray* q) {
    q->head = 0;
    q->size = 0;
}

bool QA_Empty(const QueueArray* q) { return q->size == 0; }
int  QA_Size (const QueueArray* q) { return q->size; }

bool QA_Push(QueueArray* q, T t) {
    if (q->size == N) return false; // переполнение
    int tail = (q->head + q->size) % N;
    q->data[tail] = t;
    q->size++;
    return true;
}

T QA_Top(const QueueArray* q) {
    return q->data[q->head];
}

bool QA_Pop(QueueArray* q) {
    if (q->size == 0) return false;
    q->head = (q->head + 1) % N;
    q->size--;
    return true;
}

void QA_Destroy(QueueArray* q) {  // не обязательно, но лучше
    q->size = 0;
}

// ============ СЛОЖНОСТЬ ============
// QA_Create: O(1) - инициализация
// QA_Push: O(1) - добавление в конец
// QA_Pop: O(1) - удаление из начала
// QA_Top: O(1) - просмотр первого элемента
// QA_Empty: O(1) - проверка пустоты
// QA_Size: O(1) - получение размера
// QA_Destroy: O(1) - очистка
// Память: O(N) - фиксированный массив (N элементов)
// Ограничение: максимум N элементов

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Очередь (Queue) на массиве ===\n\n");
    
    // Тест 1: Базовые операции FIFO
    QueueArray q1;
    QA_Create(&q1);
    
    printf("Тест 1: Push и Pop (FIFO)\n");
    QA_Push(&q1, (void*)10);
    QA_Push(&q1, (void*)20);
    QA_Push(&q1, (void*)30);
    printf("После Push(10,20,30): Front=%d, Size=%d\n", 
           (int)QA_Top(&q1), QA_Size(&q1)); // Front=10, Size=3
    
    QA_Pop(&q1);
    printf("После Pop: Front=%d, Size=%d\n", 
           (int)QA_Top(&q1), QA_Size(&q1)); // Front=20, Size=2
    
    // Тест 2: Проверка переполнения
    printf("\nТест 2: Переполнение\n");
    QueueArray q2;
    QA_Create(&q2);
    
    int count = 0;
    for (int i = 0; i < 105; i++) {
        if (QA_Push(&q2, (void*)i)) {
            count++;
        }
    }
    printf("Добавлено элементов: %d (максимум %d)\n", count, N); // count=100
    
    // Тест 3: Кольцевой буфер
    printf("\nТест 3: Кольцевой буфер\n");
    QueueArray q3;
    QA_Create(&q3);
    
    // Заполняем
    for (int i = 0; i < 5; i++) {
        QA_Push(&q3, (void*)i);
    }
    
    // Удаляем 3, добавляем 3 новых
    QA_Pop(&q3); QA_Pop(&q3); QA_Pop(&q3);
    QA_Push(&q3, (void*)100);
    QA_Push(&q3, (void*)200);
    QA_Push(&q3, (void*)300);
    
    printf("После циклических операций:\n");
    while (!QA_Empty(&q3)) {
        printf("  %d\n", (int)QA_Top(&q3));
        QA_Pop(&q3);
    }
    // Выведет: 3, 4, 100, 200, 300
    
    QA_Destroy(&q1);
    QA_Destroy(&q2);
    QA_Destroy(&q3);
    
    return 0;
}
*/