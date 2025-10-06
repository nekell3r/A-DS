#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* array;
    int size;
} vector;

/* ============================================================
   ШПАРГАЛКА: Дек на двусвязном списке (Deque)
   ============================================================
   
   СТРУКТУРА:
   typedef struct {
       Item* left;   // левый конец дека
       Item* right;  // правый конец дека
       int size;     // размер дека
   } deque;
   
   typedef struct Item {
       int data;           // данные элемента
       struct Item* next;  // следующий элемент
       struct Item* prev;  // предыдущий элемент
   } Item;
   
   ФУНКЦИИ:
   deque* CreateDeque(vector* v)         vector → Deque
   bool isEmptyDeque(deque* d)           Deque → boolean
   bool PushLeftDeque(deque* d, int i)   Deque × int → Deque
   bool PushRightDeque(deque* d, int i)  Deque × int → Deque
   bool PopLeftDeque(deque* d)           Deque → Deque
   bool PopRightDeque(deque* d)          Deque → Deque
   int TopLeftDeque(deque* d)            Deque → int
   int TopRightDeque(deque* d)           Deque → int
   bool DeleteDeque(deque* d)            Deque → ∅
   ============================================================ */

typedef struct Item{
    int data;               // хранимое значение
    struct Item * next;     // указатель на следующий элемент
    struct Item * prev;     // указатель на предыдущий элемент
} Item;

typedef struct deque{
    Item *left;   // указатель на левый конец дека
    Item *right;  // указатель на правый конец дека
    int size;     // размер дека
} deque;

// создание дека из вектора
deque * CreateDeque(vector * v){
    deque * d = (deque*)malloc(sizeof(deque));
    d->size = 0;
    d->left = 0;
    d->right = 0;
    
    for(int i = 0; i < v->size; ++i)
        PushLeftDeque(d, v->array[i]);
    
    return d;
}

// проверка отсутствия элементов в деке
bool isEmptyDeque(deque *d){
    if(d->size == 0)
        return true;
    
    return false;
}

// добавить элемент с левого конца
bool PushLeftDeque(deque * d, int i){
    Item *q = 0;
    
    if(d->left){
        q = d->left;
        d->left = d->left->prev;
    }
    
    d->left = (Item*)malloc(sizeof(Item));
    d->left->data = i;
    d->left->next = q;
    
    if(d->left->next)
        d->left->next->prev=d->left;
    
    d->left->prev = 0;
    
    if(!q)
        d->right=d->left;
    
    d->size++;
    
    return true;
}

// добавить элемент с правого конца
bool PushRightDeque(deque * d, int i){
    Item *q = 0;
    
    if(d->right!=0){
        q = d->right;
        d->right = d->right->next;
    }
    
    d->right = (Item*)malloc(sizeof(Item));
    d->right->data = i;
    d->right->next = 0;
    d->right->prev = q;
    
    if(d->right->prev)
        d->right->prev->next=d->right;
    
    if(!q)
        d->left=d->right;
    
    d->size++;
    
    return true;
}

// взять элемент с левого конца
bool PopLeftDeque(deque * d){
    if(isEmptyDeque(d))
        return false;
    
    Item *q;
    q = d->left->next;
    free(d->left);
    d->size--;
    d->left = q;
    
    if(d->size == 0){
        d->right = d->left;
        return true;
    }
    
    d->left->prev = 0;
    
    return true;
}

// взять элемент с правого конца
bool PopRightDeque(deque * d){
    if(isEmptyDeque(d))
        return false;
    
    Item *q;
    q = d->right->prev;
    free(d->right);
    d->size--;
    d->right=q;
    
    if(d->size == 0){
        d->left = d->right;
        return true;
    }
    d->right->next = 0;
    
    return true;
}

// посмотреть элемент с левого конца
int TopLeftDeque(deque * d){
    if(isEmptyDeque(d))
        return 0; // ошибка, обращение к нулевому указателю
    
    return d->left->data;
}

// посмотреть элемент с правого конца
int TopRightDeque(deque * d){
    if(isEmptyDeque(d))
        return 0; // ошибка, обращение к нулевому указателю
    
    return d->right->data;
}

// удалить дек
bool DeleteDeque(deque * d){
    if(isEmptyDeque(d))
        return false;
    
    Item *q;
    q = d->left->next;
    free(d->left);
    d->size--;
    
    if(q == 0){
        d->left = d->right=q;
        return true;
    }
    
    d->left = q;
    d->left->prev = 0;
    
    return DeleteDeque(d);
}

// ============ СЛОЖНОСТЬ ============
// CreateDeque: O(n) - создание из вектора
// PushLeft/PushRight: O(1) - добавление с любого конца
// PopLeft/PopRight: O(1) - удаление с любого конца
// TopLeft/TopRight: O(1) - просмотр без удаления
// isEmptyDeque: O(1) - проверка пустоты
// DeleteDeque: O(n) - удаление всех элементов
// Память: O(n) - двусвязный список

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Дек (Deque) на двусвязном списке ===\n\n");
    
    // Тест 1: Добавление с левого конца
    deque* d1 = (deque*)malloc(sizeof(deque));
    d1->size = 0; d1->left = d1->right = NULL;
    
    printf("Тест 1: PushLeft\n");
    PushLeftDeque(d1, 10);
    PushLeftDeque(d1, 20);
    PushLeftDeque(d1, 30);
    printf("После PushLeft(10,20,30): Left=%d, Right=%d, Size=%d\n", 
           TopLeftDeque(d1), TopRightDeque(d1), d1->size); // Left=30, Right=10, Size=3
    
    // Тест 2: Добавление с правого конца
    deque* d2 = (deque*)malloc(sizeof(deque));
    d2->size = 0; d2->left = d2->right = NULL;
    
    printf("\nТест 2: PushRight\n");
    PushRightDeque(d2, 1);
    PushRightDeque(d2, 2);
    PushRightDeque(d2, 3);
    printf("После PushRight(1,2,3): Left=%d, Right=%d, Size=%d\n", 
           TopLeftDeque(d2), TopRightDeque(d2), d2->size); // Left=1, Right=3, Size=3
    
    // Тест 3: Удаление с обоих концов
    printf("\nТест 3: PopLeft и PopRight\n");
    PopLeftDeque(d1);  // Удаляем 30
    PopRightDeque(d1); // Удаляем 10
    printf("После Pop: Left=%d, Right=%d, Size=%d\n", 
           TopLeftDeque(d1), TopRightDeque(d1), d1->size); // Left=20, Right=20, Size=1
    
    DeleteDeque(d1);
    DeleteDeque(d2);
    
    return 0;
}
*/
