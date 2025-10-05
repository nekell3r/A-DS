#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

/* ===========================
   Очередь на массиве
   =========================== */

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