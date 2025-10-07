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
 * 1. Создаём структуру для стека:
 *    - Массив для хранения пар границ (left, right)
 *    - Функции push() и pop()
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

// Структура для хранения границ подмассива
typedef struct {
    int left;
    int right;
} Range;

// Структура стека
typedef struct {
    Range* data;
    int top;
    int capacity;
} Stack;

// Создание стека
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (Range*)malloc(capacity * sizeof(Range));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Добавление элемента в стек
void push(Stack* stack, int left, int right) {
    if (stack->top < stack->capacity - 1) {
        stack->top++;
        stack->data[stack->top].left = left;
        stack->data[stack->top].right = right;
    }
}

// Извлечение элемента из стека
Range pop(Stack* stack) {
    Range r = {-1, -1};
    if (stack->top >= 0) {
        r = stack->data[stack->top];
        stack->top--;
    }
    return r;
}

// Проверка пустоты стека
int isEmpty(Stack* stack) {
    return stack->top < 0;
}

// Обмен элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Разделение массива (как в рекурсивной версии)
int partition(int arr[], int left, int right) {
    int pivot = arr[(left + right) / 2];
    
    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        
        if (left <= right) {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    
    return left;
}

// Нерекурсивная быстрая сортировка
void quickSortNonRecursive(int arr[], int n) {
    // Создаём стек для хранения границ подмассивов
    Stack* stack = createStack(n);
    
    // Кладём в стек границы всего массива
    push(stack, 0, n - 1);
    
    // Пока есть подмассивы для сортировки
    while (!isEmpty(stack)) {
        // Берём очередной диапазон
        Range range = pop(stack);
        int left = range.left;
        int right = range.right;
        
        // Если диапазон корректный
        if (left < right) {
            // Разделяем массив
            int pivot = partition(arr, left, right);
            
            // Добавляем в стек границы получившихся подмассивов
            if (pivot - 1 > left) {
                push(stack, left, pivot - 1);
            }
            if (right > pivot) {
                push(stack, pivot, right);
            }
        }
    }
    
    // Освобождаем память
    free(stack->data);
    free(stack);
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n log n) в среднем, O(n²) в худшем случае
// Память: O(n) для стека
// Преимущество перед рекурсией: контроль над использованием памяти

/*
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("До сортировки: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    quickSortNonRecursive(arr, n);
    
    printf("\nПосле сортировки: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    return 0;
}
*/