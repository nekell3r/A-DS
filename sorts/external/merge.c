// Сортировка слиянием (Merge Sort)
// Рекурсивный алгоритм "разделяй и властвуй"

#include <stdio.h>
#include <stdlib.h>

// Слияние двух отсортированных подмассивов
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;    // Размер левого подмассива
    int n2 = right - mid;       // Размер правого подмассива
    
    // Создаем временные массивы
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    // Копируем данные во временные массивы
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Слияние временных массивов обратно в arr[left..right]
    i = 0;      // Индекс первого подмассива
    j = 0;      // Индекс второго подмассива
    k = left;   // Индекс объединенного массива
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Копируем оставшиеся элементы L[], если они есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Копируем оставшиеся элементы R[], если они есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Освобождаем память
    free(L);
    free(R);
}

// Рекурсивная сортировка слиянием
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // (left + right) / 2
        
        // Сортируем левую и правую половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Слияние отсортированных половин
        merge(arr, left, mid, right);
    }
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n log n) во всех случаях
// Память: O(n) для временных массивов
// Стабильная: Да (сохраняет порядок равных элементов)

// Особенности:
// - Гарантированная сложность O(n log n)
// - Стабильная сортировка
// - Требует дополнительную память O(n)
// - Хорошо подходит для связных списков
// - Легко распараллеливается

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Сортировка слиянием ===\n\n");
    
    // Тест 1: Обычный массив
    int arr1[] = {12, 11, 13, 5, 6, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Тест 1: Обычный массив\n");
    printf("До:    ");
    for (int i = 0; i < n1; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    
    mergeSort(arr1, 0, n1 - 1);
    
    printf("После: ");
    for (int i = 0; i < n1; i++)
        printf("%d ", arr1[i]);
    printf("\n\n");
    
    // Тест 2: Обратный порядок
    int arr2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Тест 2: Обратный порядок\n");
    printf("До:    ");
    for (int i = 0; i < n2; i++)
        printf("%d ", arr2[i]);
    printf("\n");
    
    mergeSort(arr2, 0, n2 - 1);
    
    printf("После: ");
    for (int i = 0; i < n2; i++)
        printf("%d ", arr2[i]);
    printf("\n\n");
    
    // Тест 3: Повторяющиеся элементы
    int arr3[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Тест 3: Повторяющиеся элементы\n");
    printf("До:    ");
    for (int i = 0; i < n3; i++)
        printf("%d ", arr3[i]);
    printf("\n");
    
    mergeSort(arr3, 0, n3 - 1);
    
    printf("После: ");
    for (int i = 0; i < n3; i++)
        printf("%d ", arr3[i]);
    printf("\n\n");
    
    return 0;
}
*/
