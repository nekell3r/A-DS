#include <stdlib.h>
#include <stdbool.h>

typedef void* T;

/* ============================================================
   ШПАРГАЛКА: Динамический вектор (Vector)
   ============================================================
   СТРУКТУРА:
   typedef struct {
       T* data;     // массив элементов
       int size;    // размер вектора
   } Vector
   ФУНКЦИИ:
   void Create(Vector* v, int sz)           N → V_T,In
   bool Empty(Vector* v)                    V_T,In → boolean
   int Size(Vector* v)                      V_T,In → N
   T Load(Vector* v, int i)                 V_T,In × In → T
   void Save(Vector* v, int i, T t)         V_T,In × In × T → V_T,In
   void Resize(Vector* v, int sz)           V_T,In × N → V_T,Im
   bool Equal(Vector* l, Vector* r)         V_T,In × V_T,In → boolean
   void Destroy(Vector* v)                  V_T,In → ∅
   ============================================================ */

typedef struct
{
    T* data;
    int size;
} Vector;

void Create(Vector* v, int sz)
{
    v->size = sz;
    v->data = malloc(sizeof(T) * v->size);
}

bool Empty(Vector* v)
{
    return v->size == 0;
}

int Size(Vector* v)
{
    return v->size;
}

T Load(Vector* v, int i)
{
    if((i >= 0) && (i < v->size))
        return v->data[i];
}

void Save(Vector* v, int i, T t)
{
    if((i >= 0) && (i < v->size))
        v->data[i] = t;
}

void Resize(Vector* v, int sz)
{
    v->size = sz;
    v->data = realloc(v->data, sizeof(T) * v->size);
}

bool Equal(Vector* l, Vector* r)
{
    if(l->size != r->size)
        return false;
    for(int i = 0; i < l->size; i++)
        if(l->data[i] != r->data[i])
            return false;
    return true;
}

void Destroy(Vector* v)
{
    v->size = 0;
    free(v->data);
}

// ============ СЛОЖНОСТЬ ============
// Create: O(n) - выделение памяти под n элементов
// Load: O(1) - доступ по индексу
// Save: O(1) - запись по индексу
// Resize: O(n) - перевыделение памяти
// Equal: O(n) - сравнение двух векторов
// Empty: O(1) - проверка пустоты
// Size: O(1) - получение размера
// Destroy: O(1) - освобождение памяти
// Память: O(n) - непрерывный массив

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Динамический вектор ===\n\n");
    
    // Тест 1: Создание и доступ
    Vector v1;
    Create(&v1, 5);
    
    printf("Тест 1: Запись и чтение\n");
    Save(&v1, 0, (void*)10);
    Save(&v1, 1, (void*)20);
    Save(&v1, 2, (void*)30);
    printf("v[0]=%d, v[1]=%d, v[2]=%d\n", 
           (int)Load(&v1, 0), (int)Load(&v1, 1), (int)Load(&v1, 2)); // 10, 20, 30
    
    // Тест 2: Изменение размера
    printf("\nТест 2: Resize\n");
    printf("Размер до: %d\n", Size(&v1)); // 5
    Resize(&v1, 10);
    printf("Размер после: %d\n", Size(&v1)); // 10
    
    Save(&v1, 7, (void*)70);
    printf("v[7]=%d\n", (int)Load(&v1, 7)); // 70
    
    // Тест 3: Сравнение векторов
    printf("\nТест 3: Equal\n");
    Vector v2;
    Create(&v2, 5);
    for (int i = 0; i < 5; i++) {
        Save(&v2, i, Load(&v1, i));
    }
    printf("Векторы равны? %s\n", Equal(&v1, &v2) ? "Да" : "Нет"); // Нет (разные размеры)
    
    Resize(&v2, 10);
    printf("После изменения размера равны? %s\n", Equal(&v1, &v2) ? "Да" : "Нет");
    
    Destroy(&v1);
    Destroy(&v2);
    
    return 0;
}
*/
