/*
 * БЫСТРАЯ СОРТИРОВКА ХОАРА (НЕРЕКУРСИВНАЯ ВЕРСИЯ)
 * =============================================
 * 
 * ИДЕЯ:
 * Та же быстрая сортировка, но без рекурсии:
 * 1. Используем стек для хранения границ подмассивов
 * 2. Пока стек не пуст:
 *    - Достаём границы очередного подмассива
 *    - Разделяем его (partition)
 *    - Кладём в стек границы получившихся частей
 * 
 * КАК ПИСАТЬ:
 * 1. Используем готовый стек (из structures/stack/)
 *    - Элементы стека: Range (пара границ left, right)
 *    - Функции: Stack_Push(), Stack_Pop(), Stack_IsEmpty()
 * 
 * 2. Основной цикл:
 *    while(стек не пуст) {
 *        - Берём границы из стека
 *        - Разделяем массив
 *        - Добавляем новые границы в стек
 *    }
 */

#include <stdio.h>
#include <stdlib.h>

// ============ ТИП ЭЛЕМЕНТОВ СТЕКА ============

// Структура для хранения границ подмассива
// Это то, что лежит в стеке
typedef struct {
    int left;   // Левая граница
    int right;  // Правая граница
} Range;

// ============ ИСПОЛЬЗУЕМЫЙ СТЕК ============
// 
// Предполагается, что у нас есть готовый стек с функциями:
// 
// Stack stack;                           // Наш стек границ
// Stack_Init(&stack);                    // Инициализация
// Stack_Push(&stack, range);             // Добавить Range в стек
// Range range = Stack_Pop(&stack);       // Извлечь Range из стека
// int empty = Stack_IsEmpty(&stack);     // Проверка пустоты
// 
// Стек хранит элементы типа Range

// Обмен элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Разделение массива на две части относительно опорного элемента
// Возвращает позицию разделения
int partition(int arr[], int left, int right) {
    // Выбираем опорный элемент (средний элемент диапазона)
    int pivot = arr[(left + right) / 2];
    
    // Пока указатели не встретились
    while (left < right) {
        // Двигаем левый указатель вправо, пока элементы меньше опорного
        while (arr[left] < pivot) {
            left++;
        }
        
        // Двигаем правый указатель влево, пока элементы больше опорного
        while (arr[right] > pivot) {
            right--;
        }
        
        // Если указатели встретились или пересеклись - пропускаем swap
        if (left >= right) {
            continue;
        }
        
        // Меняем элементы местами и сдвигаем оба указателя
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
    
    // Возвращаем позицию разделения
    return right;
}

// Нерекурсивная быстрая сортировка
void quickSortNonRecursive(int arr[], int n, Stack* stack) {
    // Предполагается, что стек уже инициализирован: Stack_Init(&stack)
    
    // Создаём начальный диапазон для всего массива
    Range initial_range;
    initial_range.left = 0;
    initial_range.right = n - 1;
    
    // Кладём в стек границы всего массива
    Stack_Push(stack, initial_range);
    
    // Пока есть подмассивы для сортировки
    while (!Stack_IsEmpty(stack)) {
        // Берём очередной диапазон из стека
        Range range = Stack_Pop(stack);
        int left = range.left;
        int right = range.right;
        
        // Если диапазон корректный (больше 1 элемента)
        if (left < right) {
            // Разделяем массив на две части
            int m = partition(arr, left, right);
            
            // Добавляем в стек границы левой части [left, m]
            if (m > left) {
                Range left_range;
                left_range.left = left;
                left_range.right = m;
                Stack_Push(stack, left_range);
            }
            
            // Добавляем в стек границы правой части [m+1, right]
            if (right > m) {
                Range right_range;
                right_range.left = m + 1;
                right_range.right = right;
                Stack_Push(stack, right_range);
            }
        }
    }
    
    // Стек очищается вызывающей стороной
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n log n) в среднем, O(n²) в худшем случае
// Память: O(n) для стека
// Преимущество перед рекурсией: контроль над использованием памяти

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("До сортировки: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    // Создаём и инициализируем стек для хранения Range
    Stack stack;
    Stack_Init(&stack);
    
    // Сортируем массив, передавая стек
    quickSortNonRecursive(arr, n, &stack);
    
    printf("После сортировки: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    // Можно очистить стек если нужно
    // Stack_Destroy(&stack);
    
    return 0;
}
*/