// Естественная сортировка слиянием (Natural Merge Sort)
// Использует естественные последовательности в массиве

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура для хранения серии (отсортированной последовательности)
typedef struct {
    int start;  // Начало серии
    int length; // Длина серии
} Series;

// Поиск естественных серий в массиве
int findSeries(int arr[], int n, Series series[]) {
    int seriesCount = 0;
    int i = 0;
    
    while (i < n) {
        series[seriesCount].start = i;
        series[seriesCount].length = 1;
        
        // Ищем конец текущей серии
        while (i + 1 < n && arr[i] <= arr[i + 1]) {
            series[seriesCount].length++;
            i++;
        }
        
        seriesCount++;
        i++;
    }
    
    return seriesCount;
}

// Слияние двух серий
void mergeSeries(int arr[], Series s1, Series s2, int* temp) {
    int i = s1.start;
    int j = s2.start;
    int k = 0;
    int end1 = s1.start + s1.length;
    int end2 = s2.start + s2.length;
    
    // Слияние, пока есть элементы в обеих сериях
    while (i < end1 && j < end2) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    // Копируем оставшиеся элементы первой серии
    while (i < end1) {
        temp[k++] = arr[i++];
    }
    
    // Копируем оставшиеся элементы второй серии
    while (j < end2) {
        temp[k++] = arr[j++];
    }
    
    // Копируем результат обратно в исходный массив
    for (i = 0; i < k; i++) {
        arr[s1.start + i] = temp[i];
    }
}

// Естественная сортировка слиянием
void naturalMergeSort(int arr[], int n) {
    Series* series = (Series*)malloc(n * sizeof(Series));  // Максимум n серий
    int* temp = (int*)malloc(n * sizeof(int));            // Временный массив
    bool sorted = false;
    
    while (!sorted) {
        // Находим естественные серии
        int seriesCount = findSeries(arr, n, series);
        
        // Если осталась только одна серия - массив отсортирован
        if (seriesCount == 1) {
            sorted = true;
            continue;
        }
        
        // Сливаем пары серий
        for (int i = 0; i < seriesCount - 1; i += 2) {
            mergeSeries(arr, series[i], series[i + 1], temp);
        }
    }
    
    free(series);
    free(temp);
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n log n) в среднем и худшем случае
//        O(n) в лучшем случае (уже отсортирован)
// Память: O(n) для временных массивов
// Стабильная: Да

// Особенности:
// - Адаптивный алгоритм (использует существующий порядок)
// - Эффективен для частично отсортированных данных
// - Требует два прохода по данным на каждой итерации
// - Хорошо подходит для внешней сортировки

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Естественная сортировка слиянием ===\n\n");
    
    // Тест 1: Частично отсортированный массив
    int arr1[] = {1, 3, 5, 2, 4, 6, 9, 7, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Тест 1: Частично отсортированный массив\n");
    printf("До:    ");
    for (int i = 0; i < n1; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    
    naturalMergeSort(arr1, n1);
    
    printf("После: ");
    for (int i = 0; i < n1; i++)
        printf("%d ", arr1[i]);
    printf("\n\n");
    
    // Тест 2: Массив с длинными сериями
    int arr2[] = {1, 2, 3, 7, 8, 9, 4, 5, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Тест 2: Массив с длинными сериями\n");
    printf("До:    ");
    for (int i = 0; i < n2; i++)
        printf("%d ", arr2[i]);
    printf("\n");
    
    naturalMergeSort(arr2, n2);
    
    printf("После: ");
    for (int i = 0; i < n2; i++)
        printf("%d ", arr2[i]);
    printf("\n\n");
    
    // Тест 3: Уже отсортированный массив
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Тест 3: Уже отсортированный массив (лучший случай)\n");
    printf("До:    ");
    for (int i = 0; i < n3; i++)
        printf("%d ", arr3[i]);
    printf("\n");
    
    naturalMergeSort(arr3, n3);
    
    printf("После: ");
    for (int i = 0; i < n3; i++)
        printf("%d ", arr3[i]);
    printf("\n(Только один проход - нашлась одна серия!)\n");
    
    return 0;
}
*/
