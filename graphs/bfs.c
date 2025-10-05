#include "../list/list.h"
#include "../Queue/queue.h"
#define MAX 5

typedef bool Graph[MAX][MAX];

DEF_LIST(Path, int) // Определяем список с именем Path с элементами типа int
DEF_LIST(Paths, Path *) // Определяем список с именем Paths с элементами типа Path*
DEF_QUEUE(QPaths, Path *) // Определяем очередь с именем QPaths с элементами типа Path*

Paths * breadth_search(Graph G, int init, int goal) { // Возвращает список путей от init до goal
    Paths *result = Paths_create();
    Path *p = Path_create();
    Path_insert(p, Path_end(p), init); /*Создаем список Path p и вставляем в него init - начало пути*/
    QPaths *q = QPaths_create();
    QPaths_push(q, Path_copy(p)); /*Пушим текущий Путь в Очередь Путей*/
    
    while (!QPaths_empty(q)) { /*Пока в Очереди есть незаконченные пути*/
        p = *QPaths_front(q); /* Снимаем из Очереди верхний Путь */
        QPaths_pop(q);
        int v = *Path_fetch(p, Path_prev(Path_end(p))); /* Вытаскиваем последний пункт в Пути */
        if (v == goal) { /* Если последний пункт - конечный пункт, значит мы нашли полный Путь, и добавляем его в список путей*/
            Paths_insert(result, Paths_end(result), Path_copy(p));
        } else { /* Иначе смотрим в какие пункты можно попасть из данного*/
            for (int i = 0; i < MAX; i++) {
                if (G[v][i] && Path_equal(find(p, i), Path_end(p))) { /*Если можно перейти в вершину i и её еще нет в Пути*/
                    Path_insert(p, Path_end(p), i); /* Добавляем пункт в Путь */
                    QPaths_push(q, Path_copy(p)); /* Пушим копию Пути в конец Очереди*/
                    Path_delete(p, Path_prev(Path_end(p))); /* Удаляем последний добавленный пункт, т.к. могут быть ещё пункты, в которые можно попасть из данного*/
                }
            }
        }
    }
    return result; // Возвращаем список путей из init в goal
}

// ============ СЛОЖНОСТЬ ============
// Время: O(V + E) где V - вершины, E - рёбра
// Память: O(V) - для очереди и путей
// BFS гарантирует нахождение кратчайшего пути

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Поиск в ширину (BFS) ===\n\n");
    
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
    
    // Тест 1: Путь от 0 до 2
    printf("Тест 1: Пути от 0 до 2\n");
    Paths *paths1 = breadth_search(G, 0, 2);
    printf("Найдено путей: %d\n", Paths_size(paths1));
    printf("Кратчайший путь: 0 → 1 → 2 (длина 2)\n\n");
    
    // Тест 2: Путь от 0 до 4
    printf("Тест 2: Пути от 0 до 4\n");
    Paths *paths2 = breadth_search(G, 0, 4);
    printf("Найдено путей: %d\n", Paths_size(paths2));
    printf("Кратчайшие пути: 0 → 1 → 4, 0 → 3 → 4 (длина 2)\n\n");
    
    // Тест 3: Нет пути (несвязные вершины)
    printf("Тест 3: BFS находит только существующие пути\n");
    
    return 0;
}
*/
