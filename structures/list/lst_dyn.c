// list_with_iterators.c
#include <stdlib.h>
#include <stdbool.h>

// Узел двусвязного списка (данные как указатель — см. обобщённый доступ к полю) 
// и итератор над узлом. Терминатор: head->next == head->prev == head. 
// (кольцевой список) [Create/терминатор, First/Last, Equal/NotEqual, Next/Prev, Fetch/Store].
typedef void* T;

/* ============================================================
   ШПАРГАЛКА: Двусвязный список с итераторами (List)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       Item* head;  // терминатор (sentinel)
       int size;    // размер списка
   } List;
   
   typedef struct Item {
       struct Item* prev;  // предыдущий элемент
       struct Item* next;  // следующий элемент
       T data;             // данные
   } Item;
   
   typedef struct {
       Item* node;  // указатель на узел
   } Iterator;
   
   ФУНКЦИИ:
   void Create(List* l)                                ∅ → List
   void Destroy(List* l)                               List → ∅
   bool Empty(const List* l)                           List → boolean
   int Size(const List* l)                             List → N
   Iterator First(const List* l)                       List → Iterator
   Iterator Last(const List* l)                        List → Iterator
   bool Equal(const Iterator* a, const Iterator* b)    Iter × Iter → boolean
   bool NotEqual(const Iterator* a, const Iterator* b) Iter × Iter → boolean
   Iterator Next(Iterator it)                          Iterator → Iterator
   Iterator Prev(Iterator it)                          Iterator → Iterator
   T Fetch(const Iterator* it)                         Iterator → T
   void Store(const Iterator* it, const T t)           Iterator × T → ∅
   Iterator Insert(List* l, Iterator* i, const T t)    List × Iter × T → Iter
   Iterator Delete(List* l, Iterator* i)               List × Iterator → Iterator
   ============================================================ */

typedef struct Item {
    struct Item* prev;
    struct Item* next;
    T            data;
} Item;

typedef struct {
    Item* head; // терминатор (sentinel)
    int   size;
} List;

typedef struct {
    Item* node;
} Iterator;


// --- Итераторы ---

// Первый (после терминатора) и «последний» (сам терминатор) итераторы. 
Iterator First(const List* l)  { Iterator r = { l->head->next }; return r; }
Iterator Last (const List* l)  { Iterator r = { l->head       }; return r; }

// Сравнение итераторов. 
bool Equal   (const Iterator* a, const Iterator* b) { return a->node == b->node; }
bool NotEqual(const Iterator* a, const Iterator* b) { return !Equal(a, b);      }

// Переходы вперёд/назад (за счёт корректной организации кольца это безопасно). 
Iterator Next(Iterator it) { it.node = it.node->next; return it; }
Iterator Prev(Iterator it) { it.node = it.node->prev; return it; }

// Доступ к данным узла итератора (чтение/запись). 
T  Fetch(const Iterator* it)             { return it->node->data; }
void Store(const Iterator* it, const T t){ it->node->data = t;     }

// --- Базовые операции списка ---

// Создание пустого кольцевого списка с терминатором. 
void Create(List* l) {
    l->head = (Item*)malloc(sizeof(Item));
    l->head->next = l->head->prev = l->head;
    l->size = 0;
}

// Пуст ли список (First == Last). 
bool Empty(const List* l) {
    return l->size == 0;
}

// Размер (поддерживается счётчиком). 
int Size(const List* l) { return l->size; }

// --- Модификаторы ---

// Вставка элемента ПЕРЕД узлом, на который указывает итератор i.
// Возвращает итератор на вставленный элемент. Линки — как в источнике. 
Iterator Insert(List* l, Iterator* i, const T t) {
    // выделяем новый узел динамически (в динамической реализации узлы создаются через malloc) 
    Iterator res = {
        malloc(sizeof(struct Item))
    };
    res.node->data = t;
    res.node->next = i->node;
    res.node->prev = i ->node->prev;    
    res.node->prev->next = res.node;
    i->node->prev = res.node;
    l->size++;
    return res;
}

// Удаление узла, на который указывает итератор i.
// Возвращает итератор на следующий узел после удалённого. Узел освобождается. 
Iterator Delete(List* l, Iterator* i) {
    Iterator res = Last(l);      
    if (Equal(i, &res)) { // !!!!!!!!!! если итератор на терминатор, то возвращаем терминатор
        return res;
    }
    res.node = i->node->next;
    res.node->prev = i->node->prev;        
    i->node->prev->next = res.node;        
    l->size--;                             
    free(i->node);
    i->node = 0;
    return res;
}

// Уничтожение: последовательный обход и free всех элементов, затем free(head). 
void Destroy(List* l) {
    struct Item* i = l->head->next;
    while (i != l->head) {
        struct Item* pi = i; // почему struct`?
        i = i->next;
        free(pi);
    }
    free(l->head);
    l->head = 0
    l->size = 0;
}


// ============ СЛОЖНОСТЬ ============
// Create: O(1) - создание терминатора
// Insert: O(1) - вставка перед итератором
// Delete: O(1) - удаление по итератору
// First/Last: O(1) - получение итераторов
// Next/Prev: O(1) - переход по итераторам
// Fetch/Store: O(1) - доступ к данным
// Empty: O(1) - проверка пустоты
// Size: O(1) - получение размера
// Destroy: O(n) - удаление всех узлов
// Память: O(n) - двусвязный список с терминатором

/* Примечания к использованию:
   - Список реализован как кольцевой с терминатором: это упрощает граничные случаи
     (итерация до/через конец и т.п.). 
   - Итераторы — это просто «обёртка» над указателем на узел, сравнение/сдвиги — по указателям. 
   - Доступ к данным через Fetch/Store оставлен плоским (без дополнительных проверок). 
*/

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Двусвязный список с итераторами ===\n\n");
    
    // Тест 1: Вставка элементов
    List list;
    Create(&list);
    
    printf("Тест 1: Insert\n");
    Iterator end = Last(&list);
    Insert(&list, &end, (void*)10);
    Insert(&list, &end, (void*)20);
    Insert(&list, &end, (void*)30);
    
    printf("Размер списка: %d\n", Size(&list)); // 3
    printf("Элементы: ");
    for (Iterator it = First(&list); NotEqual(&it, &end); it = Next(it)) {
        printf("%d ", (int)Fetch(&it));
    }
    printf("\n"); // 10 20 30
    
    // Тест 2: Удаление элемента
    printf("\nТест 2: Delete\n");
    Iterator first = First(&list);
    first = Next(first); // Переходим ко второму элементу (20)
    Delete(&list, &first);
    printf("После удаления второго: ");
    end = Last(&list);
    for (Iterator it = First(&list); NotEqual(&it, &end); it = Next(it)) {
        printf("%d ", (int)Fetch(&it));
    }
    printf("\n"); // 10 30
    
    // Тест 3: Обратный обход
    printf("\nТест 3: Обратный обход\n");
    printf("В обратном порядке: ");
    Iterator last = Last(&list);
    for (Iterator it = Prev(last); NotEqual(&it, &last); it = Prev(it)) {
        printf("%d ", (int)Fetch(&it));
        if (Equal(&it, &First(&list))) break;
    }
    printf("\n"); // 30 10
    
    Destroy(&list);
    
    return 0;
}
*/

