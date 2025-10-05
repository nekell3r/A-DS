// Бинарное дерево на указателях (динамическое)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tree_Node_ Tree_Node;
typedef struct Tree_ Tree;

struct Tree_Node_ {
    int data;
    Tree_Node* left;
    Tree_Node* right;
};

struct Tree_ {
    Tree_Node* root;
};

// ============ БАЗОВЫЕ ФУНКЦИИ ============

// Инициализация пустого дерева
Tree* init() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

// Построение дерева из корня и двух поддеревьев (без копирования)
Tree* build(Tree* left, int root_value, Tree* right) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = (Tree_Node*)malloc(sizeof(Tree_Node));
    tree->root->data = root_value;
    tree->root->left = (left != NULL) ? left->root : NULL;
    tree->root->right = (right != NULL) ? right->root : NULL;
    return tree;
}

// Проверка пустоты дерева
bool is_empty(Tree* tree) {
    return tree == NULL || tree->root == NULL;
}

// Получение значения корня
int root_value(Tree* tree) {
    if (is_empty(tree)) return -1;  // Или любое другое значение ошибки
    return tree->root->data;
}

// Получение левого поддерева
Tree* left_subtree(Tree* tree) {
    if (is_empty(tree)) return NULL;
    Tree* left_tree = (Tree*)malloc(sizeof(Tree));
    left_tree->root = tree->root->left;
    return left_tree;
}

// Получение правого поддерева
Tree* right_subtree(Tree* tree) {
    if (is_empty(tree)) return NULL;
    Tree* right_tree = (Tree*)malloc(sizeof(Tree));
    right_tree->root = tree->root->right;
    return right_tree;
}

// Удаление дерева (можно использовать для узлов напрямую)
void destroy(Tree_Node* node) {
    if (node == NULL) return;
    destroy(node->left);
    destroy(node->right);
    free(node);
}

// ============ ПОСТРОЕНИЕ ДЕРЕВА ИЗ МАССИВА ============

// Построение сбалансированного дерева из массива
// values - указатель на текущую позицию в массиве, n - количество узлов
// Например: [1,2,3,4,5] -> дерево:
//       1
//      / \
//     2   3
//    / \
//   4   5
Tree_Node* build_from_array(int** values, int n) {
    if (n == 0) return NULL;
    
    int nl = n / 2;              // Узлов в левом поддереве
    int nr = n - nl - 1;         // Узлов в правом поддереве
    
    Tree_Node* node = (Tree_Node*)malloc(sizeof(Tree_Node));
    node->data = *(*values)++;   // Берём значение и сдвигаем указатель
    node->left = build_from_array(values, nl);
    node->right = build_from_array(values, nr);
    
    return node;
}

// ============ АЛГОРИТМЫ ОБХОДА ============

// Прямой обход (pre-order): корень -> левый -> правый
void preorder(Tree_Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// Симметричный обход (in-order): левый -> корень -> правый
void inorder(Tree_Node* node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Обратный обход (post-order): левый -> правый -> корень
void postorder(Tree_Node* node) {
    if (node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

// ============ СЛОЖНОСТЬ ============
// build_from_array: O(n) - создаём n узлов
// preorder/inorder/postorder: O(n) - посещаем каждый узел один раз
// destroy: O(n) - удаляем каждый узел
// Память: O(h) для рекурсии, где h - высота дерева

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Бинарное дерево (динамическое) ===\n\n");
    
    // Тест 1: Построение дерева из массива
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    int* ptr = values;
    Tree_Node* root = build_from_array(&ptr, 7);
    
    // Структура:
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7
    
    printf("Тест 1: Полное дерево из 7 элементов\n");
    printf("Pre-order: "); preorder(root); printf("\n");    // 1 2 4 5 3 6 7
    printf("In-order: "); inorder(root); printf("\n");      // 4 2 5 1 6 3 7
    printf("Post-order: "); postorder(root); printf("\n");  // 4 5 2 6 7 3 1
    
    destroy(root);
    
    // Тест 2: Маленькое дерево
    int vals2[] = {10, 20, 30};
    int* ptr2 = vals2;
    Tree_Node* root2 = build_from_array(&ptr2, 3);
    
    printf("\nТест 2: Дерево из 3 элементов\n");
    printf("Pre-order: "); preorder(root2); printf("\n");   // 10 20 30
    
    destroy(root2);
    
    // Тест 3: Один узел
    int vals3[] = {42};
    int* ptr3 = vals3;
    Tree_Node* root3 = build_from_array(&ptr3, 1);
    
    printf("\nТест 3: Дерево из 1 элемента\n");
    printf("Pre-order: "); preorder(root3); printf("\n");   // 42
    
    destroy(root3);
    
    return 0;
}
*/
