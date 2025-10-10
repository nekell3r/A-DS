// Общее дерево (general tree) - представление "первый ребёнок - следующий брат"
// Структура: каждый узел хранит ссылку на первого ребёнка и на следующего брата
// СТРУКТУРЫ:
//   struct node {
//       int val;            - значение узла
//       node* main_bro;     - следующий брат (next sibling)
//       node* first_child;  - первый ребёнок
//   };
// ОСНОВНЫЕ ФУНКЦИИ:
//   void init(node** tree, int root_value)         - инициализировать дерево с корнем
//   node* create_node(int value)                   - создать узел
//   node* build(int value, node** children, int count) - построить из массива детей
//   node* build_from_array(int values[], int n)    - построить из массива (1 уровень)
//   bool is_empty(node* tree)                      - проверка пустоты
//   int root_value(node* tree)                     - значение корня
//   node* first_child(node* tree)                  - первый ребёнок
//   node* next_sibling(node* tree)                 - следующий брат
//   node** get_node(node** t, char* path)          - получить узел по пути ('c'/'b')
//   void destroy(node* tree)                       - удалить дерево
//   void preorder(node* tree)                      - прямой обход (корень->дети->братья)
//   void postorder(node* tree)                     - обратный обход (дети->корень->братья)
//
// ==========================================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node node;

// Структура узла общего дерева
struct node {
    int val;              // Значение узла
    node* main_bro;       // Указатель на следующего брата (next sibling)
    node* first_child;    // Указатель на первого ребёнка
};

// ============ БАЗОВЫЕ ФУНКЦИИ ============

// Инициализация дерева с корнем (деревья общего вида не бывают пустые)
void init(node** tree, int root_value) {
    *tree = (node*)malloc(sizeof(node));
    (*tree)->val = root_value;
    (*tree)->first_child = NULL;
    (*tree)->main_bro = NULL;
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
node* build(int root_value, node** children, int count) {
    node* root = create_node(root_value);
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
bool is_empty(node* tree) {
    return tree == NULL;
}

// Получение значения корня
int root_value(node* tree) {
    if (is_empty(tree)) return -1;
    return tree->val;
}

// Получение первого ребёнка
node* first_child(node* tree) {
    if (is_empty(tree)) return NULL;
    return tree->first_child;
}

// Получение следующего брата
node* next_sibling(node* tree) {
    if (is_empty(tree)) return NULL;
    return tree->main_bro;
}

// Получение узла по пути
// path - строка из символов 'c' (first_child) и 'b' (main_bro)
// Пример: "cb" - первый ребёнок, затем его следующий брат
node** get_node(node** t, char* path) {
    if (path[0] == '\0') {
        return t;
    } else if (path[0] == 'c' && (*t)->first_child != NULL) {
        return get_node(&((*t)->first_child), path + 1);
    } else if (path[0] == 'b' && (*t)->main_bro != NULL) {
        return get_node(&((*t)->main_bro), path + 1);
    } else {
        return NULL;
    }
}

// Удаление дерева
void destroy(node* tree) {
    if (tree == NULL) return;
    destroy(tree->first_child);  // Рекурсивно удаляем детей
    destroy(tree->main_bro);     // Рекурсивно удаляем братьев
    free(tree);
}

// ============ ПОСТРОЕНИЕ ДЕРЕВА ИЗ МАССИВА ============

// Построение дерева из массива (первый элемент - корень, остальные - дети)
// Простой вариант: одноуровневое дерево
node* build_from_array(int values[], int n) {
    if (n <= 0) return NULL;
    
    node* root = create_node(values[0]);
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
// Сначала перебираются сыновья (аналогичен КЛП обходу)
void preorder(node* tree) {
    if (tree == NULL) return;
    printf("%d ", tree->val);           // Берется корень
    preorder(tree->first_child);        // Поиск в глубину от first_child
    preorder(tree->main_bro);           // Поиск в глубину от братьев
}

// Обход в глубину (post-order): дети -> корень -> братья
void postorder(node* tree) {
    if (tree == NULL) return;
    postorder(tree->first_child);       // Сначала дети
    printf("%d ", tree->val);           // Потом корень
    postorder(tree->main_bro);          // Потом братья
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
    
    // Тест 1: Инициализация с корнем
    node* tree1;
    init(&tree1, 1);
    printf("Тест 1: Дерево с корнем\n");
    printf("Корень: %d\n", root_value(tree1));  // 1
    
    // Тест 2: Построение из массива
    node* tree = build_from_array((int[]){1, 2, 3, 4, 5}, 5);
    
    // Структура:
    //       1
    //     / | \ \
    //    2  3  4  5
    
    printf("\nТест 2: Дерево с 4 детьми\n");
    printf("Pre-order: "); preorder(tree); printf("\n");   // 1 2 3 4 5
    printf("Post-order: "); postorder(tree); printf("\n"); // 2 3 4 5 1
    
    // Тест 3: Построение вручную (многоуровневое) как на фото
    node* leaf8 = create_node(8);
    node* leaf9 = create_node(9);
    leaf8->first_child = leaf9;
    
    node* node3 = create_node(3);
    node3->first_child = leaf8;
    
    node* node6 = create_node(6);
    node* node7 = create_node(7);
    node6->main_bro = node7;
    
    node* node5 = create_node(5);
    node5->first_child = node6;
    
    node* node4 = create_node(4);
    node4->main_bro = node5;
    node3->main_bro = node4;
    
    node* node2 = create_node(2);
    node2->main_bro = node3;
    
    node* root = create_node(1);
    root->first_child = node2;
    
    // Структура (как на фото):
    //       1
    //      /|\
    //     2 3 4--5
    //       |    |
    //       8   6--7
    //       |
    //       9
    
    printf("\nТест 3: Многоуровневое дерево (как на фото)\n");
    printf("Pre-order: "); preorder(root); printf("\n");    // 1 2 3 8 9 4 5 6 7
    printf("Post-order: "); postorder(root); printf("\n");  // 2 9 8 3 4 6 7 5 1
    
    // Тест 4: Получение узла по пути
    printf("\nТест 4: Получение узла по пути\n");
    node** found = get_node(&root, "c");     // первый ребёнок (2)
    if (found) printf("Путь 'c': %d\n", (*found)->val);
    
    found = get_node(&root, "cb");             // первый ребёнок, затем брат (3)
    if (found) printf("Путь 'cb': %d\n", (*found)->val);
    
    found = get_node(&root, "cbc");            // 1->2->3->8
    if (found) printf("Путь 'cbc': %d\n", (*found)->val);
    
    found = get_node(&root, "cbcc");           // 1->2->3->8->9
    if (found) printf("Путь 'cbcc': %d\n", (*found)->val);
    
    destroy(tree1);
    destroy(tree);
    destroy(root);
    
    return 0;
}
*/
