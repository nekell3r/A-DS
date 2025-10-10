// Бинарное дерево на основе массива
// Для узла с индексом i:
//   - левый ребёнок: 2*i + 1
//   - правый ребёнок: 2*i + 2
//   - родитель: (i-1) / 2
//
// ============ КРАТКАЯ СПРАВКА ===========
// СТРУКТУРЫ:
//   typedef struct {
//       int* data;       - массив значений узлов
//       size_t capacity; - ёмкость массива
//   } Tree;
// ОСНОВНЫЕ ФУНКЦИИ:
//   void init(Tree* tree, size_t capacity)         - инициализировать пустое дерево
//   Tree* build(Tree* left, int value, Tree* right) - построить из поддеревьев
//   Tree* build_from_array(int values[], int n)    - построить из массива
//   bool is_empty(Tree* tree)                      - проверка пустоты
//   int root(Tree* tree)                           - значение корня
//   Tree* left(Tree* tree)                         - левое поддерево
//   Tree* right(Tree* tree)                        - правое поддерево
//   void destroy(Tree* tree)                       - удалить дерево
//   void preorder(Tree* tree, int idx)             - прямой обход
//   void inorder(Tree* tree, int idx)              - симметричный обход
//   void postorder(Tree* tree, int idx)            - обратный обход
//
// ==========================================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define EMPTY_NODE -2147483648  // INT_MIN
#define DEFAULT_CAPACITY 15

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


// Построение дерева из корня и двух поддеревьев
Tree* build(Tree* left, int root_value, Tree* right) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    init(tree, DEFAULT_CAPACITY);
    tree->data[0] = root_value;
    
    // Копируем всё левое поддерево в позицию 1 (левый ребёнок корня)
    if (left != NULL) {
        copy_subtree(left->data, left->capacity, 0,
                    tree->data, tree->capacity, 1);
    }
    
    // Копируем всё правое поддерево в позицию 2 (правый ребёнок корня)
    if (right != NULL) {
        copy_subtree(right->data, right->capacity, 0,
                    tree->data, tree->capacity, 2);
    }
    
    return tree;
}

// Проверка пустоты дерева
bool is_empty(Tree* tree) {
    return tree == NULL || tree->data[0] == EMPTY_NODE;
}

// Получение значения корня (возвращает EMPTY_NODE если дерево пустое)
int root(Tree* tree) {
    if (is_empty(tree)) return EMPTY_NODE;
    return tree->data[0];
}

// Вспомогательная функция: копирует поддерево из src[src_idx] в dst[dst_idx]
void copy_subtree(int* src, size_t src_capacity, int src_idx,
    int* dst, size_t dst_capacity, int dst_idx) {
    // Если индекс выходит за границы или узел пустой - останавливаемся
    if (src_idx >= (int)src_capacity || dst_idx >= (int)dst_capacity ||
        src[src_idx] == EMPTY_NODE) {
        return;
    }

    // Копируем текущий узел
    dst[dst_idx] = src[src_idx];

    // Рекурсивно копируем левое и правое поддеревья
    copy_subtree(src, src_capacity, 2 * src_idx + 1,  // левый ребёнок в src
                dst, dst_capacity, 2 * dst_idx + 1);  // левый ребёнок в dst
    copy_subtree(src, src_capacity, 2 * src_idx + 2,  // правый ребёнок в src
                dst, dst_capacity, 2 * dst_idx + 2);  // правый ребёнок в dst
}

// Получение левого поддерева (глубокая копия всего поддерева)
Tree* left(Tree* tree) {
    if (is_empty(tree) || tree->data[1] == EMPTY_NODE) return NULL;
    
    Tree* left_tree = (Tree*)malloc(sizeof(Tree));
    init(left_tree, DEFAULT_CAPACITY);
    
    // Копируем ВСЁ левое поддерево с корнем в индексе 1 -> в индекс 0
    copy_subtree(tree->data, tree->capacity, 1,
                 left_tree->data, left_tree->capacity, 0);
    
    return left_tree;
}

// Получение правого поддерева (глубокая копия всего поддерева)
Tree* right(Tree* tree) {
    if (is_empty(tree) || tree->data[2] == EMPTY_NODE) return NULL;
    
    Tree* right_tree = (Tree*)malloc(sizeof(Tree));
    init(right_tree, DEFAULT_CAPACITY);
    
    // Копируем ВСЁ правое поддерево с корнем в индексе 2 -> в индекс 0
    copy_subtree(tree->data, tree->capacity, 2,
                 right_tree->data, right_tree->capacity, 0);
    
    return right_tree;
}

// Удаление дерева
void destroy(Tree* tree) {
    if (tree == NULL) return;
    free(tree->data);
    free(tree);
}

// ============ ПОСТРОЕНИЕ ДЕРЕВА ИЗ МАССИВА ============

// Построение дерева из массива
Tree* build_from_array(int values[], int n) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    init(tree, DEFAULT_CAPACITY);
    for (int i = 0; i < n && i < (int)tree->capacity; i++) {
        tree->data[i] = values[i];
    }
    return tree;
}

// ============ АЛГОРИТМЫ ОБХОДА ============

// Прямой обход (pre-order): корень -> левый -> правый
void preorder(Tree* tree, int idx) {
    if (idx >= (int)tree->capacity || tree->data[idx] == EMPTY_NODE) return;
    printf("%d ", tree->data[idx]);
    preorder(tree, 2 * idx + 1);
    preorder(tree, 2 * idx + 2);
}

// Симметричный обход (in-order): левый -> корень -> правый
void inorder(Tree* tree, int idx) {
    if (idx >= (int)tree->capacity || tree->data[idx] == EMPTY_NODE) return;
    inorder(tree, 2 * idx + 1);
    printf("%d ", tree->data[idx]);
    inorder(tree, 2 * idx + 2);
}

// Обратный обход (post-order): левый -> правый -> корень
void postorder(Tree* tree, int idx) {
    if (idx >= (int)tree->capacity || tree->data[idx] == EMPTY_NODE) return;
    postorder(tree, 2 * idx + 1);
    postorder(tree, 2 * idx + 2);
    printf("%d ", tree->data[idx]);
}

// ============ СЛОЖНОСТЬ ============
// init: O(capacity) - заполнение массива
// build: O(n) - копирование поддеревьев
// build_from_array: O(n) - копирование n элементов
// left/right: O(n) - глубокая копия поддерева
// preorder/inorder/postorder: O(n) - посещаем каждый узел
// destroy: O(1) - просто освобождаем массив
// Память: O(capacity) - массив фиксированного размера

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Бинарное дерево (массив) ===\n\n");
    
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
    
    // Тест 2: Получение поддеревьев
    Tree* left_subtree = left(tree);
    Tree* right_subtree = right(tree);
    
    printf("\nТест 2: Левое поддерево (корень 2)\n");
    printf("Pre-order: "); preorder(left_subtree, 0); printf("\n");  // 2 4 5
    
    printf("\nТест 3: Правое поддерево (корень 3)\n");
    printf("Pre-order: "); preorder(right_subtree, 0); printf("\n"); // 3 6 7
    
    // Тест 4: Построение через build
    Tree* t1 = build_from_array((int[]){2, 4, 5}, 3);
    Tree* t2 = build_from_array((int[]){3, 6, 7}, 3);
    Tree* t3 = build(t1, 1, t2);
    
    printf("\nТест 4: Построение через build\n");
    printf("Pre-order: "); preorder(t3, 0); printf("\n");  // 1 2 4 5 3 6 7
    
    // Очистка
    destroy(tree);
    destroy(left_subtree);
    destroy(right_subtree);
    destroy(t1);
    destroy(t2);
    destroy(t3);
    
    return 0;
}
*/
