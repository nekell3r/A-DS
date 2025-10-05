// Сортировка выбором (Selection Sort)
// На каждой итерации находим минимальный элемент и ставим на своё место

// Сортировка выбором
void selectionSort(int arr[], int n) {
    int i, j, min, temp;
    
    // Проходим по всем элементам кроме последнего
    for (i = 0; i < n - 1; i++) {
        // Предполагаем, что минимум - текущий элемент
        min = i;
        
        // Ищем минимальный элемент в оставшейся части
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;  // Нашли элемент меньше текущего минимума
            }
        }
        
        // Если нашли элемент меньше - меняем местами
        if (min != i) {
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n²) всегда - во всех случаях (худший, средний, лучший)
// Память: O(1) - сортировка на месте
// Стабильная: Нет (может изменить порядок равных элементов)
// Количество обменов: O(n) - минимально возможное!

// Особенности:
// - Всегда делает одинаковое количество сравнений
// - Хорош, когда запись в память дорогая (мало обменов)
// - Проще пузырьковой, но медленнее

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("=== Сортировка выбором ===\n\n");
    
    // Тест 1: Обычный массив
    int arr1[] = {64, 25, 12, 22, 11};
    int n1 = 5;
    
    printf("Тест 1: Базовая сортировка\n");
    printf("До:    ");
    printArray(arr1, n1);
    
    selectionSort(arr1, n1);
    
    printf("После: ");
    printArray(arr1, n1);
    printf("\n");
    
    // Тест 2: Обратный порядок
    int arr2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n2 = 10;
    
    printf("Тест 2: Обратный порядок\n");
    printf("До:    ");
    printArray(arr2, n2);
    
    selectionSort(arr2, n2);
    
    printf("После: ");
    printArray(arr2, n2);
    printf("\n");
    
    // Тест 3: Уже отсортирован
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = 5;
    
    printf("Тест 3: Уже отсортирован (всё равно O(n²))\n");
    printf("До:    ");
    printArray(arr3, n3);
    
    selectionSort(arr3, n3);
    
    printf("После: ");
    printArray(arr3, n3);
    printf("\n");
    
    // Тест 4: Повторяющиеся элементы
    int arr4[] = {3, 5, 1, 5, 3, 2, 5, 1};
    int n4 = 8;
    
    printf("Тест 4: Повторяющиеся элементы\n");
    printf("До:    ");
    printArray(arr4, n4);
    
    selectionSort(arr4, n4);
    
    printf("После: ");
    printArray(arr4, n4);
    printf("\n");
    
    // Визуализация работы алгоритма
    printf("=== Визуализация работы (массив [29, 10, 14, 37, 13]) ===\n");
    int demo[] = {29, 10, 14, 37, 13};
    int nd = 5;
    
    printf("Начало:     "); printArray(demo, nd);
    
    for (int i = 0; i < nd - 1; i++) {
        int min = i;
        for (int j = i + 1; j < nd; j++) {
            if (demo[j] < demo[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = demo[i];
            demo[i] = demo[min];
            demo[min] = temp;
        }
        printf("Итерация %d: ", i + 1);
        printArray(demo, nd);
        printf("  (поставили %d на позицию %d)\n", demo[i], i);
    }
    
    printf("\n=== Сравнение с другими алгоритмами ===\n");
    printf("Selection Sort:\n");
    printf("  + Минимум обменов O(n)\n");
    printf("  + Простая реализация\n");
    printf("  - Всегда O(n²) - даже для отсортированных\n");
    printf("  - Нестабильная\n\n");
    
    printf("Bubble Sort:\n");
    printf("  + Стабильная\n");
    printf("  + O(n) для отсортированных (с оптимизацией)\n");
    printf("  - Много обменов O(n²)\n");
    
    return 0;
}
*/

