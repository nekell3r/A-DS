// Очередь на основе файла (File-based Queue)
// Реализация очереди с хранением данных в файле
// Используется для работы с большими объемами данных,
// когда данные не помещаются в оперативную память

#include <stdbool.h>
#include <stdio.h>

#define POOL_SIZE 1024
#define QUEUE_EMPTY -1

/* ============================================================
   ШПАРГАЛКА: Очередь на файле (File Queue)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       FILE* buff;  // файловый буфер
       int size;    // количество элементов
       int cap;     // вместимость (POOL_SIZE)
       int head;    // индекс головы
   } Queue;
   
   ФУНКЦИИ:
   void init(Queue* q, const char* filename)  ∅ → Queue
   bool isEmpty(Queue* q)                     Queue → boolean
   int size(Queue* q)                         Queue → N
   bool push(Queue* q, int val)               Queue × int → Queue
   int top(Queue* q)                          Queue → int
   bool pop(Queue* q, int* out)               Queue × int* → Queue
   void destroy(Queue* q)                     Queue → ∅
   ============================================================ */

typedef struct Queue {
    FILE* buff;  // Файловый буфер для хранения данных
    int size;    // Текущее количество элементов
    int cap;     // Максимальная вместимость (POOL_SIZE)
    int head;    // Индекс головы очереди (для извлечения)
} Queue;

// Инициализация очереди с созданием/открытием файла
// Файл открывается в бинарном режиме для чтения/записи
void init(Queue* queue, const char* filename) {
    queue->buff = fopen(filename, "w+b");

    if (!queue->buff)
        return;

    queue->size = 0;
    queue->head = 0;
    queue->cap = POOL_SIZE;
}

// Проверка, пуста ли очередь
bool isEmpty(Queue* queue) {
    return queue->size == 0;
}

// Получение текущего размера очереди
int size(Queue* queue) {
    return queue->size;
}

// Добавление элемента в конец очереди
// Использует кольцевой буфер: (head + size) % cap
// fflush обеспечивает запись на диск
bool push(Queue* queue, int val) {
    if (queue->size >= queue->cap)
        return false;

    // Вычисляем позицию для записи (кольцевой буфер)
    fseek(queue->buff, ((queue->head + queue->size) % queue->cap) * sizeof(int), SEEK_SET);
    fwrite(&val, sizeof(int), 1, queue->buff);
    fflush(queue->buff);  // Принудительная запись на диск

    queue->size++;

    return true;
}

// Извлечение элемента из начала очереди (с удалением)
// Возвращает значение через out параметр
// Голова перемещается циклически: (head + 1) % cap
bool pop(Queue* queue, int* out) {
    if (queue->size == 0)
        return false;

    // Читаем элемент с головы очереди
    fseek(queue->buff, queue->head * sizeof(int), SEEK_SET);
    fread(out, sizeof(int), 1, queue->buff);

    // Сдвигаем голову (кольцевой буфер)
    queue->head = (queue->head + 1) % queue->cap;
    queue->size--;

    return true;
}

// Просмотр первого элемента без удаления
// Возвращает QUEUE_EMPTY (-1) если очередь пуста
int top(Queue* queue) {
    if (queue->size > 0) {
        int val;
        fseek(queue->buff, queue->head * sizeof(int), SEEK_SET);
        fread(&val, sizeof(int), 1, queue->buff);
        return val;
    }

    return QUEUE_EMPTY;
}

// Освобождение ресурсов и закрытие файла
void destroy(Queue* queue) {
    queue->size = 0;

    if (queue->buff) {
        fclose(queue->buff);
        queue->buff = NULL;
    }
}

// ============ СЛОЖНОСТЬ ============
// Все операции: O(1) амортизированное
// Память: O(1) в RAM + O(n) на диске
//
// ВАЖНО: Производительность зависит от скорости диска!
// Файловые операции медленнее RAM, но позволяют работать 
// с данными, не помещающимися в оперативную память.
//
// Применение:
// - Большие объемы данных (не помещаются в RAM)
// - Персистентные очереди сообщений
// - Буферизация данных между процессами

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Очередь на основе файла ===\n\n");
    
    Queue q;
    init(&q, "queue_test.dat");
    
    // Тест FIFO
    push(&q, 10);
    push(&q, 20);
    push(&q, 30);
    printf("Добавлено: 10, 20, 30\n");
    printf("Первый элемент: %d, Размер: %d\n", top(&q), size(&q));
    
    int val;
    pop(&q, &val);
    printf("Извлечен: %d, Теперь первый: %d\n", val, top(&q));
    
    // Проверка FIFO
    while (!isEmpty(&q)) {
        pop(&q, &val);
        printf("Извлечен: %d\n", val);
    }
    
    destroy(&q);
    return 0;
}
*/
