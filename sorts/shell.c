// Сортировка Шелла с динамическими шагами
void ShellSort(int arr[], int size) {
    // Проходы с уменьшающимся шагом: size/2, size/4, ..., 1
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Сортировка вставками для элементов, отстоящих на gap позиций
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            
            // Сдвигаем элементы, пока не найдём позицию для temp
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = temp;
        }
    }
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n^(3/2)) в среднем, зависит от последовательности шагов
// Память: O(1) - сортировка на месте

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
#include <stdio.h>

int main() {
    printf("=== Сортировка Шелла ===\n\n");
    
    // Тест 1: Обычный массив
    int arr1[] = {5, 2, 9, 1, 7, 6, 3, 8, 4, 0};
    int n1 = 10;
    printf("Тест 1: До сортировки: ");
    for(int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    printf("\n");
    
    ShellSort(arr1, n1);
    
    printf("После сортировки: ");
    for(int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    printf("\n\n");
    
    // Тест 2: Уже отсортированный
    int arr2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n2 = 10;
    printf("Тест 2: Отсортированный → ");
    ShellSort(arr2, n2);
    for(int i = 0; i < n2; i++) printf("%d ", arr2[i]);
    printf("\n\n");
    
    // Тест 3: Обратный порядок
    int arr3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n3 = 10;
    printf("Тест 3: Обратный → ");
    ShellSort(arr3, n3);
    for(int i = 0; i < n3; i++) printf("%d ", arr3[i]);
    printf("\n\n");
    
    // Тест 4: Большой массив
    int arr4[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50, 13, 5, 77, 1};
    int n4 = 14;
    printf("Тест 4: Массив из 14 элементов\n");
    printf("До:    ");
    for(int i = 0; i < n4; i++) printf("%d ", arr4[i]);
    printf("\n");
    
    ShellSort(arr4, n4);
    
    printf("После: ");
    for(int i = 0; i < n4; i++) printf("%d ", arr4[i]);
    printf("\n");
    
    return 0;
}
*/
