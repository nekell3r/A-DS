#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

/* ============================================================
   ШПАРГАЛКА: Очередь на динамическом списке (Queue)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       QNode* head;  // терминатор (голова)
       QNode* tail;  // последний элемент (хвост)
       int size;     // размер очереди
   } QueueDynamic;
   
   typedef struct QNode {
       T data;              // данные элемента
       struct QNode* next;  // следующий элемент
   } QNode;
   
   ФУНКЦИИ:
   void QD_Create(QueueDynamic* q)      ∅ → Queue
   bool QD_Empty(const QueueDynamic* q) Queue → boolean
   int QD_Size(const QueueDynamic* q)   Queue → N
   bool QD_Push(QueueDynamic* q, T t)   Queue × T → Queue
   T QD_Top(const QueueDynamic* q)      Queue → T
   bool QD_Pop(QueueDynamic* q)         Queue → Queue
   void QD_Destroy(QueueDynamic* q)     Queue → ∅
   ============================================================ */

typedef struct QNode {
    T               data;
    struct QNode*   next;
} QNode;

typedef struct {
    QNode* head;  // терминатор
    QNode* tail;  // последний элемент
    int    size;
} QueueDynamic;

void QD_Create(QueueDynamic* q) {
    q->head = q->tail = malloc(sizeof(QNode));
    q->size = 0;
}

bool QD_Empty(const QueueDynamic* q) { return q->size == 0;  } // или return q->head == q->tail
int  QD_Size (const QueueDynamic* q) { return q->size; }

bool QD_Push(QueueDynamic* q, T t) {
    QNode* n = malloc(sizeof(QNode));
    if (!n) return false;
    q->tail->next = n;
    q->tail->data = t; // в последний узел записываем данные, а созданный становится терминатором
    q->tail = q->tail->next;
    q->size++;
    return true;
}

T QD_Top(const QueueDynamic* q) {
    if (q->size != 0) {
        return q->head->data;
    }
    return 0;
}

bool QD_Pop(QueueDynamic* q) {
    if (q->size == 0) return false;
    QNode* first = q->head;
    q->head = q->head->next;
    free(first);
    q->size--;
    return true;
}

void QD_Destroy(QueueDynamic* q) {
    while (!QD_Empty(q)) {
        QNode* pi = q->head;
        q->head = q->head->next;
        free(pi);
    }
    free(q->head);
    q->head = q->tail = 0;
    q->size = 0;
}

// ============ СЛОЖНОСТЬ ============
// QD_Create: O(1) - инициализация
// QD_Push: O(1) - добавление в конец
// QD_Pop: O(1) - удаление из начала
// QD_Top: O(1) - просмотр первого элемента
// QD_Empty: O(1) - проверка пустоты
// QD_Size: O(1) - получение размера
// QD_Destroy: O(n) - удаление всех элементов
// Память: O(n) - односвязный список с терминатором

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Очередь (Queue) на динамических структурах ===\n\n");
    
    // Тест 1: Базовые операции FIFO
    QueueDynamic q1;
    QD_Create(&q1);
    
    printf("Тест 1: Push и Pop (FIFO)\n");
    QD_Push(&q1, (void*)10);
    QD_Push(&q1, (void*)20);
    QD_Push(&q1, (void*)30);
    printf("После Push(10,20,30): Front=%d, Size=%d\n", 
           (int)QD_Top(&q1), QD_Size(&q1)); // Front=10, Size=3
    
    QD_Pop(&q1);
    printf("После Pop: Front=%d, Size=%d\n", 
           (int)QD_Top(&q1), QD_Size(&q1)); // Front=20, Size=2
    
    // Тест 2: Полное опустошение
    printf("\nТест 2: Опустошение очереди\n");
    QD_Pop(&q1);
    QD_Pop(&q1);
    printf("Пуста ли очередь? %s\n", QD_Empty(&q1) ? "Да" : "Нет"); // Да
    
    // Тест 3: Очередь задач
    printf("\nТест 3: Очередь задач\n");
    QueueDynamic q2;
    QD_Create(&q2);
    QD_Push(&q2, "Task 1");
    QD_Push(&q2, "Task 2");
    QD_Push(&q2, "Task 3");
    
    printf("Обработка задач:\n");
    while (!QD_Empty(&q2)) {
        printf("  Выполняется: %s\n", (char*)QD_Top(&q2));
        QD_Pop(&q2);
    }
    
    QD_Destroy(&q1);
    QD_Destroy(&q2);
    
    return 0;
}
*/
