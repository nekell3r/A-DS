// Бинарное дерево на основе массива
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
//   Tree* init()                                   - создать пустое дерево
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
Tree* init() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->capacity = DEFAULT_CAPACITY;
    tree->data = (int*)malloc(tree->capacity * sizeof(int));
    for (size_t i = 0; i < tree->capacity; i++) {
        tree->data[i] = EMPTY_NODE;
    }
    return tree;
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

// Построение дерева из корня и двух поддеревьев
Tree* build(Tree* left, int root_value, Tree* right) {
    Tree* tree = init();
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

// Получение левого поддерева
Tree* left(Tree* tree) {
    if (is_empty(tree) || tree->data[1] == EMPTY_NODE) return NULL;
    Tree* left_tree = init();
    left_tree->data[0] = tree->data[1];
    return left_tree;
}

// Получение правого поддерева
Tree* right(Tree* tree) {
    if (is_empty(tree) || tree->data[2] == EMPTY_NODE) return NULL;
    Tree* right_tree = init();
    right_tree->data[0] = tree->data[2];
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
    Tree* tree = init();
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

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

// ============ СЛОЖНОСТЬ ============
// build_from_array: O(n) - копирование n элементов
// preorder/inorder/postorder: O(n) - посещаем каждый узел
// destroy: O(1) - просто освобождаем массив
// Память: O(n) - массив фиксированного размера

/*
int main() {
    printf("=== Бинарное дерево (массив) ===\n\n");
    
    // Тест 1: Полное дерево
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
    
    destroy(tree);
    
    // Тест 2: Неполное дерево (с пробелами)
    int vals2[] = {10, 20, 30, EMPTY_NODE, EMPTY_NODE, 60, 70};
    Tree* tree2 = build_from_array(vals2, 7);
    
    printf("\nТест 2: Неполное дерево\n");
    printf("Pre-order: "); preorder(tree2, 0); printf("\n");  // 10 20 30 60 70
    
    destroy(tree2);
    
    // Тест 3: Только корень
    int vals3[] = {100};
    Tree* tree3 = build_from_array(vals3, 1);
    
    printf("\nТест 3: Один узел\n");
    printf("Pre-order: "); preorder(tree3, 0); printf("\n");  // 100
    
    destroy(tree3);
    
    return 0;
}
*/
