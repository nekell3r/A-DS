// Общее дерево (general tree) - представление "первый ребёнок - следующий брат"
// Структура: каждый узел хранит ссылку на первого ребёнка и на следующего брата
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node node;
typedef node* tree_ov;

// Структура узла общего дерева
struct node {
    int val;              // Значение узла
    node* main_bro;       // Указатель на следующего брата (next sibling)
    node* first_child;    // Указатель на первого ребёнка
};

// ============ БАЗОВЫЕ ФУНКЦИИ ============

// Инициализация пустого дерева
tree_ov init() {
    return NULL;
}

// Создание узла
node* create_node(int value) {
    node* n = (node*)malloc(sizeof(node));
    n->val = value;
    n->first_child = NULL;
    n->main_bro = NULL;
    return n;
}

// Построение дерева из корня и массива детей
tree_ov build(int root_value, tree_ov* children, int count) {
    tree_ov root = create_node(root_value);
    if (count == 0 || children == NULL) return root;
    
    root->first_child = children[0];
    node* current = children[0];
    for (int i = 1; i < count; i++) {
        current->main_bro = children[i];
        current = children[i];
    }
    return root;
}

// Проверка пустоты дерева
bool is_empty(tree_ov tree) {
    return tree == NULL;
}

// Получение значения корня
int root_value(tree_ov tree) {
    if (is_empty(tree)) return -1;
    return tree->val;
}

// Получение первого ребёнка
tree_ov first_child(tree_ov tree) {
    if (is_empty(tree)) return NULL;
    return tree->first_child;
}

// Получение следующего брата
tree_ov next_sibling(tree_ov tree) {
    if (is_empty(tree)) return NULL;
    return tree->main_bro;
}

// Удаление дерева
void destroy(tree_ov tree) {
    if (tree == NULL) return;
    destroy(tree->first_child);
    destroy(tree->main_bro);
    free(tree);
}

// ============ ПОСТРОЕНИЕ ДЕРЕВА ИЗ МАССИВА ============

// Построение дерева из массива (первый элемент - корень, остальные - дети)
// Простой вариант: одноуровневое дерево
tree_ov build_from_array(int values[], int n) {
    if (n <= 0) return NULL;
    
    tree_ov root = create_node(values[0]);
    if (n == 1) return root;
    
    root->first_child = create_node(values[1]);
    node* current = root->first_child;
    
    for (int i = 2; i < n; i++) {
        current->main_bro = create_node(values[i]);
        current = current->main_bro;
    }
    
    return root;
}

// ============ АЛГОРИТМЫ ОБХОДА ============

// Обход в глубину (pre-order): корень -> дети -> братья
void preorder(tree_ov tree) {
    if (tree == NULL) return;
    printf("%d ", tree->val);
    preorder(tree->first_child);
    preorder(tree->main_bro);
}

// Обход в глубину (post-order): дети -> корень -> братья
void postorder(tree_ov tree) {
    if (tree == NULL) return;
    postorder(tree->first_child);
    printf("%d ", tree->val);
    postorder(tree->main_bro);
}


// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

// ============ СЛОЖНОСТЬ ============
// build_from_array: O(n) - создаём n узлов
// preorder/postorder: O(n) - посещаем каждый узел один раз
// destroy: O(n) - удаляем каждый узел
// Память: O(h) для рекурсии, где h - высота дерева

/*
int main() {
    printf("=== Общее дерево (first child / next sibling) ===\n\n");
    
    // Тест 1: Построение из массива
    int values[] = {1, 2, 3, 4, 5};
    tree_ov tree = build_from_array(values, 5);
    
    // Структура:
    //       1
    //     / | \ \
    //    2  3  4  5
    
    printf("Тест 1: Дерево с 4 детьми\n");
    printf("Pre-order: "); preorder(tree); printf("\n");   // 1 2 3 4 5
    printf("Post-order: "); postorder(tree); printf("\n"); // 2 3 4 5 1
    
    // Тест 2: Построение вручную (многоуровневое)
    tree_ov leaf1 = create_node(4);
    tree_ov leaf2 = create_node(5);
    tree_ov children1[] = {leaf1, leaf2};
    tree_ov child1 = build(2, children1, 2);
    
    tree_ov child2 = create_node(3);
    
    tree_ov children[] = {child1, child2};
    tree_ov root = build(1, children, 2);
    
    // Структура:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    printf("\nТест 2: Многоуровневое дерево\n");
    printf("Pre-order: "); preorder(root); printf("\n");    // 1 2 4 5 3
    printf("Post-order: "); postorder(root); printf("\n");  // 4 5 2 3 1
    
    // Тест 3: Один узел
    tree_ov single = create_node(42);
    printf("\nТест 3: Один узел\n");
    printf("Pre-order: "); preorder(single); printf("\n");  // 42
    
    destroy(tree);
    destroy(root);
    destroy(single);
    
    return 0;
}
*/
