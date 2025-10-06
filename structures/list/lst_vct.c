// Список на векторе (с пулом элементов)
// Вместо malloc для каждого узла используется предвыделенный массив
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 100

typedef void* T;

/* ============================================================
   ШПАРГАЛКА: Список на векторе с пулом (List on Vector)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       Item* pool;    // массив элементов (пул)
       int head;      // индекс терминатора
       int top;       // индекс первого свободного элемента
       int size;      // количество элементов
       int capacity;  // размер пула
   } List;
   
   typedef struct {
       T data;      // данные
       int next;    // индекс следующего (-1 если нет)
       int prev;    // индекс предыдущего (-1 если нет)
   } Item;
   
   typedef struct {
       int index;   // индекс в массиве
   } Iterator;
   
   ФУНКЦИИ:
   void Create(List* l)                       ∅ → List
   void Destroy(List* l)                      List → ∅
   bool Empty(const List* l)                  List → boolean
   int Size(const List* l)                    List → N
   Iterator First(const List* l)              List → Iterator
   Iterator Last(const List* l)               List → Iterator
   Iterator Next(const List* l, Iterator it)  List × Iter → Iter
   Iterator Prev(const List* l, Iterator it)  List × Iter → Iter
   bool Equal(Iterator a, Iterator b)         Iter × Iter → boolean
   bool NotEqual(Iterator a, Iterator b)      Iter × Iter → boolean
   T Fetch(const List* l, Iterator it)        List × Iter → T
   void Store(List* l, Iterator it, T data)   List × Iter × T → ∅
   Iterator Insert(List* l, Iterator i, T t)  List × Iter × T → Iter
   Iterator Delete(List* l, Iterator i)       List × Iterator → Iterator
   ============================================================ */

// Узел списка (хранится в векторе)
typedef struct {
    T data;
    int next;  // Индекс следующего элемента (-1 если нет)
    int prev;  // Индекс предыдущего элемента (-1 если нет)
} Item;

// Список с пулом элементов в векторе
typedef struct {
    Item* pool;      // Массив всех элементов (пул)
    int head;        // Индекс головы (терминатор)
    int top;         // Индекс первого свободного элемента
    int size;        // Количество элементов в списке
    int capacity;    // Размер пула
} List;

// Итератор - просто индекс в векторе
typedef struct {
    int index;
} Iterator;

// ============ БАЗОВЫЕ ФУНКЦИИ ============

// Создание списка с пулом элементов
void Create(List* l) {
    l->capacity = POOL_SIZE;
    l->pool = (Item*)malloc(l->capacity * sizeof(Item));
    l->size = 0;
    
    // Инициализация пула: связываем свободные элементы
    for (int i = 0; i < l->capacity - 1; i++) {
        l->pool[i].next = i + 1;
        l->pool[i].prev = -1;
    }
    l->pool[l->capacity - 1].next = -1;
    
    // head - терминатор (последний элемент пула)
    l->head = l->capacity - 1;
    l->pool[l->head].next = l->head;
    l->pool[l->head].prev = l->head;
    
    // top - первый свободный элемент
    l->top = 0;
}

// Удаление списка
void Destroy(List* l) {
    free(l->pool);
    l->pool = NULL;
    l->size = 0;
    l->capacity = 0;
}

// Проверка пустоты
bool Empty(const List* l) {
    return l->size == 0;
}

// Размер списка
int Size(const List* l) {
    return l->size;
}

// ============ ИТЕРАТОРЫ ============

// Первый элемент (после терминатора)
Iterator First(const List* l) {
    Iterator it = { l->pool[l->head].next };
    return it;
}

// Последний (терминатор)
Iterator Last(const List* l) {
    Iterator it = { l->head };
    return it;
}

// Следующий элемент
Iterator Next(const List* l, Iterator it) {
    it.index = l->pool[it.index].next;
    return it;
}

// Предыдущий элемент
Iterator Prev(const List* l, Iterator it) {
    it.index = l->pool[it.index].prev;
    return it;
}

// Сравнение итераторов
bool Equal(Iterator a, Iterator b) {
    return a.index == b.index;
}

bool NotEqual(Iterator a, Iterator b) {
    return a.index != b.index;
}

// Получение данных
T Fetch(const List* l, Iterator it) {
    return l->pool[it.index].data;
}

// Запись данных
void Store(List* l, Iterator it, T data) {
    l->pool[it.index].data = data;
}

// ============ МОДИФИКАТОРЫ ============

// Вставка элемента ПЕРЕД итератором i
Iterator Insert(List* l, Iterator i, T t) {
    // Берём свободный элемент из пула
    if (l->top == l->head) {
        // Пул заполнен - расширяем (realloc)
        int new_capacity = l->capacity * 2;
        l->pool = (Item*)realloc(l->pool, new_capacity * sizeof(Item));
        
        // Инициализируем новые элементы
        for (int j = l->capacity; j < new_capacity - 1; j++) {
            l->pool[j].next = j + 1;
        }
        l->pool[new_capacity - 1].next = l->head;
        
        l->top = l->capacity;
        l->head = new_capacity - 1;
        l->capacity = new_capacity;
    }
    
    Iterator res;
    res.index = l->top;
    
    // Обновляем top (берём следующий свободный)
    int next_free = l->pool[l->top].next;
    
    // Вставляем элемент в список
    l->pool[res.index].data = t;
    l->pool[res.index].next = i.index;
    l->pool[res.index].prev = l->pool[i.index].prev;
    
    // Обновляем связи соседних элементов
    l->pool[l->pool[res.index].prev].next = res.index;
    l->pool[i.index].prev = res.index;
    
    l->top = next_free;
    l->size++;
    
    return res;
}

// Удаление элемента по итератору
Iterator Delete(List* l, Iterator i) {
    // Нельзя удалить терминатор
    if (i.index == l->head) {
        return i;
    }
    
    // Следующий элемент - результат
    Iterator res;
    res.index = l->pool[i.index].next;
    
    // Перелинковка соседних элементов
    l->pool[l->pool[i.index].prev].next = l->pool[i.index].next;
    l->pool[l->pool[i.index].next].prev = l->pool[i.index].prev;
    
    // Возвращаем элемент в пул свободных
    l->pool[i.index].next = l->top;
    l->pool[i.index].prev = -1;
    l->top = i.index;
    
    l->size--;
    
    return res;
}

// ============ СЛОЖНОСТЬ ============
// Create: O(n) - инициализация пула
// Insert: O(1) - вставка без malloc (обычно), O(n) при расширении
// Delete: O(1) - удаление без free
// First/Last/Next/Prev: O(1) - доступ по индексу
// Fetch/Store: O(1) - прямой доступ
// Destroy: O(1) - один free
// Память: O(n) - предвыделенный массив

// Преимущества над динамическим списком:
// - Нет фрагментации памяти
// - Быстрее (нет malloc/free для каждого элемента)
// - Кэш-дружественнее (элементы рядом в памяти)
// - Предсказуемое использование памяти

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Список на векторе (с пулом) ===\n\n");
    
    List list;
    Create(&list);
    
    // Тест 1: Вставка элементов
    printf("Тест 1: Вставка элементов\n");
    Iterator end = Last(&list);
    
    Insert(&list, end, (void*)10);
    Insert(&list, end, (void*)20);
    Insert(&list, end, (void*)30);
    
    printf("Размер: %d\n", Size(&list)); // 3
    printf("Элементы: ");
    for (Iterator it = First(&list); NotEqual(it, end); it = Next(&list, it)) {
        printf("%d ", (int)Fetch(&list, it));
    }
    printf("\n"); // 10 20 30
    
    // Тест 2: Вставка в середину
    printf("\nТест 2: Вставка в середину\n");
    Iterator it = First(&list);
    it = Next(&list, it); // Переходим ко второму элементу (20)
    Insert(&list, it, (void*)15);
    
    printf("После вставки 15: ");
    end = Last(&list);
    for (Iterator i = First(&list); NotEqual(i, end); i = Next(&list, i)) {
        printf("%d ", (int)Fetch(&list, i));
    }
    printf("\n"); // 10 15 20 30
    
    // Тест 3: Удаление элемента
    printf("\nТест 3: Удаление\n");
    Iterator first = First(&list);
    first = Next(&list, first); // 15
    Delete(&list, first);
    
    printf("После удаления 15: ");
    end = Last(&list);
    for (Iterator i = First(&list); NotEqual(i, end); i = Next(&list, i)) {
        printf("%d ", (int)Fetch(&list, i));
    }
    printf("\n"); // 10 20 30
    printf("Размер: %d\n", Size(&list)); // 3
    
    // Тест 4: Массовая вставка (проверка расширения пула)
    printf("\nТест 4: Массовая вставка (расширение пула)\n");
    end = Last(&list);
    for (int i = 40; i < 120; i++) {
        Insert(&list, end, (void*)i);
    }
    printf("Размер после массовой вставки: %d\n", Size(&list)); // 83
    printf("Capacity: %d\n", list.capacity); // Автоматически расширился
    
    // Тест 5: Обратный обход
    printf("\nТест 5: Обратный обход (последние 5 элементов)\n");
    Iterator last = Last(&list);
    printf("В обратном порядке: ");
    int count = 0;
    for (Iterator i = Prev(&list, last); NotEqual(i, last) && count < 5; i = Prev(&list, i)) {
        printf("%d ", (int)Fetch(&list, i));
        count++;
    }
    printf("\n");
    
    Destroy(&list);
    
    printf("\n=== Преимущества списка на векторе ===\n");
    printf("✓ Нет malloc/free для каждого элемента\n");
    printf("✓ Меньше фрагментации памяти\n");
    printf("✓ Лучшая локальность кэша\n");
    printf("✓ O(1) вставка/удаление (без системных вызовов)\n");
    
    return 0;
}
*/

