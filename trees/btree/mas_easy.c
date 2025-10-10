// Бинарное дерево на основе массива (упрощённая версия)
// Для узла с индексом i:
//   - левый ребёнок: 2*i + 1
//   - правый ребёнок: 2*i + 2
//   - родитель: (i-1) / 2
//
// ============ КРАТКАЯ СПРАВКА ============
//
// СТРУКТУРЫ:
//   typedef struct {
//       int* data;       - массив значений узлов
//       size_t capacity; - ёмкость массива
//   } Tree;
//
// ОСНОВНЫЕ ФУНКЦИИ:
//   void init(Tree* tree, size_t capacity)         - инициализировать пустое дерево
//   Tree* build_from_array(int values[], int n)    - построить из массива значений
//   Tree* build(Tree* left, int val, Tree* right)  - построить из поддеревьев
//   bool is_empty(Tree* tree, int idx)             - проверка пустоты узла
//   int root(Tree* tree)                           - значение корня
//   int left(Tree* tree, int idx)                  - индекс левого ребёнка
//   int right(Tree* tree, int idx)                 - индекс правого ребёнка
//   void destroy(Tree* tree)                       - удалить дерево
//   void preorder(Tree* tree, int idx)             - прямой обход
//   void inorder(Tree* tree, int idx)              - симметричный обход
//   void postorder(Tree* tree, int idx)            - обратный обход
//
// ==========================================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY_NODE -2147483648  // INT_MIN
#define DEFAULT_CAPACITY 127

typedef struct {
    int* data;
    size_t capacity;
} Tree;

// ============ БАЗОВЫЕ ФУНКЦИИ ============

// Инициализация пустого дерева
void init(Tree* tree, size_t capacity) {
    tree->capacity = capacity;
    tree->data = (int*)malloc(tree->capacity * sizeof(int));
    for (size_t i = 0; i < tree->capacity; i++) {
        tree->data[i] = EMPTY_NODE;
    }
}

// Построение дерева из массива значений
Tree* build_from_array(int values[], int n) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    init(tree, DEFAULT_CAPACITY);
    
    for (int i = 0; i < n && i < (int)tree->capacity; i++) {
        tree->data[i] = values[i];
    }
    
    return tree;
}

// Вспомогательная функция: вычисляет новый индекс узла при переносе поддерева
// src_idx - индекс узла в исходном дереве (относительно его корня в позиции 0)
// dst_idx - индекс куда копируем корень поддерева (обычно 1 или 2)
int map_index(int src_idx, int dst_idx) {
    if (src_idx == 0) return dst_idx;
    
    // Строим путь от корня до узла src_idx (0 = левый, 1 = правый)
    int path[32];
    int depth = 0;
    int temp = src_idx;
    
    while (temp > 0) {
        int parent = (temp - 1) / 2;
        path[depth++] = (2 * parent + 1 == temp) ? 0 : 1;
        temp = parent;
    }
    
    // Применяем путь начиная с dst_idx
    int result = dst_idx;
    for (int i = depth - 1; i >= 0; i--) {
        result = 2 * result + 1 + path[i];
    }
    
    return result;
}

// Построение дерева из корня и двух поддеревьев
Tree* build(Tree* left, int root_value, Tree* right) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    init(tree, DEFAULT_CAPACITY);
    
    // Устанавливаем корень
    tree->data[0] = root_value;
    
    // Копируем левое поддерево в позицию 1
    if (left != NULL) {
        for (int i = 0; i < (int)left->capacity; i++) {
            if (left->data[i] != EMPTY_NODE) {
                int target = map_index(i, 1);
                if (target < (int)tree->capacity) {
                    tree->data[target] = left->data[i];
                }
            }
        }
    }
    
    // Копируем правое поддерево в позицию 2
    if (right != NULL) {
        for (int i = 0; i < (int)right->capacity; i++) {
            if (right->data[i] != EMPTY_NODE) {
                int target = map_index(i, 2);
                if (target < (int)tree->capacity) {
                    tree->data[target] = right->data[i];
                }
            }
        }
    }
    
    return tree;
}

// Проверка пустоты узла по индексу
bool is_empty(Tree* tree, int idx) {
    if (tree == NULL || idx < 0 || idx >= (int)tree->capacity) {
        return true;
    }
    return tree->data[idx] == EMPTY_NODE;
}

// Получение значения корня (возвращает EMPTY_NODE если дерево пустое)
int root(Tree* tree) {
    if (tree == NULL || tree->data[0] == EMPTY_NODE) {
        return EMPTY_NODE;
    }
    return tree->data[0];
}

// Получение индекса левого ребёнка
int left(Tree* tree, int idx) {
    if (tree == NULL || idx < 0) return -1;
    
    int left_idx = 2 * idx + 1;
    
    if (left_idx >= (int)tree->capacity || tree->data[left_idx] == EMPTY_NODE) {
        return -1;
    }
    
    return left_idx;
}

// Получение индекса правого ребёнка
int right(Tree* tree, int idx) {
    if (tree == NULL || idx < 0) return -1;
    
    int right_idx = 2 * idx + 2;
    
    if (right_idx >= (int)tree->capacity || tree->data[right_idx] == EMPTY_NODE) {
        return -1;
    }
    
    return right_idx;
}
// Удаление дерева
void destroy(Tree* tree) {
    if (tree == NULL) return;
    free(tree->data);
    free(tree);
}

// ============ АЛГОРИТМЫ ОБХОДА ============

// Прямой обход (pre-order): корень -> левый -> правый
void preorder(Tree* tree, int idx) {
    if (is_empty(tree, idx)) return;
    
    printf("%d ", tree->data[idx]);
    preorder(tree, 2 * idx + 1);
    preorder(tree, 2 * idx + 2);
}

// Симметричный обход (in-order): левый -> корень -> правый
void inorder(Tree* tree, int idx) {
    if (is_empty(tree, idx)) return;
    
    inorder(tree, 2 * idx + 1);
    printf("%d ", tree->data[idx]);
    inorder(tree, 2 * idx + 2);
}

// Обратный обход (post-order): левый -> правый -> корень
void postorder(Tree* tree, int idx) {
    if (is_empty(tree, idx)) return;
    
    postorder(tree, 2 * idx + 1);
    postorder(tree, 2 * idx + 2);
    printf("%d ", tree->data[idx]);
}

// Обход в ширину (level-order)
void levelorder(Tree* tree) {
    if (tree == NULL) return;
    
    printf("Level-order: ");
    for (size_t i = 0; i < tree->capacity; i++) {
        if (tree->data[i] != EMPTY_NODE) {
            printf("%d ", tree->data[i]);
        }
    }
    printf("\n");
}

// ============ СЛОЖНОСТЬ ============
// init: O(capacity) - заполнение массива
// build_from_array: O(n) - копирование n элементов
// build: O(n) - копирование поддеревьев
// left/right: O(1) - просто вычисление индекса
// preorder/inorder/postorder: O(n) - посещаем каждый узел
// destroy: O(1) - просто освобождаем массив
// Память: O(capacity) - массив фиксированного размера

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

int main() {
    printf("=== Бинарное дерево (массив, упрощённая версия) ===\n\n");
    
    // Тест 1: Построение из массива
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    Tree* tree = build_from_array(values, 7);
    
    // Структура:
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7
    
    printf("Тест 1: Полное дерево\n");
    printf("Pre-order: "); preorder(tree, 0); printf("\n");   // 1 2 4 5 3 6 7
    printf("In-order: "); inorder(tree, 0); printf("\n");     // 4 2 5 1 6 3 7
    printf("Post-order: "); postorder(tree, 0); printf("\n"); // 4 5 2 6 7 3 1
    levelorder(tree);
    
    // Тест 2: Работа с индексами
    printf("\nТест 2: Работа с индексами\n");
    printf("Корень: %d (индекс 0)\n", root(tree));
    
    int left_idx = left(tree, 0);
    int right_idx = right(tree, 0);
    
    printf("Левый ребёнок корня: индекс=%d, значение=%d\n", 
           left_idx, tree->data[left_idx]);
    printf("Правый ребёнок корня: индекс=%d, значение=%d\n", 
           right_idx, tree->data[right_idx]);
    
    // Тест 3: Обход левого поддерева
    printf("\nТест 3: Левое поддерево (начиная с индекса %d)\n", left_idx);
    printf("Pre-order: "); preorder(tree, left_idx); printf("\n");  // 2 4 5
    
    // Тест 4: Обход правого поддерева
    printf("\nТест 4: Правое поддерево (начиная с индекса %d)\n", right_idx);
    printf("Pre-order: "); preorder(tree, right_idx); printf("\n"); // 3 6 7
    
    // Тест 5: Построение дерева через build
    Tree* t1 = build_from_array((int[]){2, 4, 5}, 3);
    Tree* t2 = build_from_array((int[]){3, 6, 7}, 3);
    Tree* t3 = build(t1, 1, t2);
    
    printf("\nТест 5: Построение через build\n");
    printf("Pre-order: "); preorder(t3, 0); printf("\n");  // 1 2 4 5 3 6 7
    
    // Очистка
    destroy(tree);
    destroy(t1);
    destroy(t2);
    destroy(t3);
    
    printf("\n=== Готово! ===\n");
    return 0;
}

