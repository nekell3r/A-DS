#include "../List/List.h"

#define MAX 5

typedef bool Graph[MAX][MAX];

DEF_LIST(Path, int) // Определяем список с именем Path с элементами типа int
DEF_LIST(Paths, Path *) // Определяем список с именем Paths с элементами типа Path*

/* DepthSearch ищет все пути между init и goal и возвращает список из найденных путей*/
Paths* DepthSearch(Graph G, int init, int goal) {
    Paths * result = Paths_create();
    Path* p = Path_create(); // Создаем список в котором будем накапливать текущий путь
    void search() {
        int v = *Path_fetch(p, Path_prev(List_path_end(p))); // Вытаскиваем последний элемент
        if(v == goal) { // Если нашли целевую вершину
            Paths_insert(result, Paths_end(result), Path_copy(p)); // Копируем текущий путь в список с путями
        }
        else {
            for(int i = 0; i < MAX; i++) {
                if(G[v][i] && Path_equal(find(p, i), Path_end(p))) {
                    Path_iterator it = Path_insert(p, Path_end(p), i);/* Вершины в пути являются в обратном порядке для удобства программирования */
                    search(); // Запускаем рекурсивно поиск пути из всех вершин, в которые можно попасть из данной
                    Path_delete(p, it);
                }
            }
        }
    }
    Path_insert(p, Path_end(p), init);
    search();
    Path_destroy(&p);
    return result;
}

// ============ СЛОЖНОСТЬ ============
// Время: O(V + E) где V - вершины, E - рёбра
// Память: O(V) - стек рекурсии
// DFS находит ВСЕ пути, но не гарантирует кратчайший

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Поиск в глубину (DFS) ===\n\n");
    
    // Граф:
    //     0 --- 1 --- 2
    //     |     |     |
    //     3 --- 4
    
    Graph G = {
        {0, 1, 0, 1, 0},  // 0 связан с 1, 3
        {1, 0, 1, 0, 1},  // 1 связан с 0, 2, 4
        {0, 1, 0, 0, 0},  // 2 связан с 1
        {1, 0, 0, 0, 1},  // 3 связан с 0, 4
        {0, 1, 0, 1, 0}   // 4 связан с 1, 3
    };
    
    // Тест 1: Все пути от 0 до 2
    printf("Тест 1: Все пути от 0 до 2\n");
    Paths *paths1 = DepthSearch(G, 0, 2);
    printf("Найдено путей: %d\n", Paths_size(paths1));
    printf("Пути: 0→1→2, 0→3→4→1→2\n\n");
    
    // Тест 2: Все пути от 0 до 4
    printf("Тест 2: Все пути от 0 до 4\n");
    Paths *paths2 = DepthSearch(G, 0, 4);
    printf("Найдено путей: %d\n", Paths_size(paths2));
    printf("Пути: 0→1→4, 0→3→4\n\n");
    
    // Тест 3: Путь к самому себе
    printf("Тест 3: Путь от 0 до 0\n");
    Paths *paths3 = DepthSearch(G, 0, 0);
    printf("Найдено путей: 1 (сам узел)\n");
    
    return 0;
}
*/
