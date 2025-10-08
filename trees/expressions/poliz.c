// Обратная Польская Запись (ПОЛИЗ / Postfix / RPN)
// Формат: операнды перед оператором
// Пример: "3 4 +" = 3 + 4 = 7
// Пример: "5 1 2 + 4 * + 3 -" = 5 + (1+2)*4 - 3 = 14
//
// ============ КРАТКАЯ СПРАВКА ============
//
// ОСНОВНАЯ ФУНКЦИЯ:
//   int Poliz(char* expression)  - вычислить выражение в RPN
//
// АЛГОРИТМ:
//   1. Читаем строку слева направо
//   2. Цифра → кладём в стек
//   3. Оператор → вытаскиваем 2 числа, вычисляем, кладём результат
//   4. Результат = вершина стека
//
// ОПЕРАТОРЫ: +, -, *, /
// ОГРАНИЧЕНИЕ: работает только с однозначными числами (0-9)
//
// ==========================================

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK 100

// ============ СТЕК (импортированный интерфейс) ============

typedef struct {
    int data[MAX_STACK];
    int top;
} Stack;

void Stack_Init(Stack *s);
void Stack_Push(Stack *s, long long value);
int Stack_Pop(Stack *s);
int Stack_IsEmpty(Stack *s);
int Stack_Size(Stack *s);

// ============ ОСНОВНАЯ ФУНКЦИЯ ============

// Вычисление выражения в обратной польской записи
long long Poliz(char *expression) {
    Stack stack;
    Stack_Init(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char symbol = expression[i];

        // Пробелы и разделители - пропускаем
        if (symbol == ' ' || symbol == '\t' || symbol == '\n') {
            continue;
        }
        // Если цифра - кладём в стек
        else if (isdigit(symbol)) {
            int number = symbol - '0';
            Stack_Push(&stack, number);
        }
        // Оператор - достаём 2 числа, вычисляем, кладём результат
        else {
            int b = Stack_Pop(&stack);  // Второй операнд
            int a = Stack_Pop(&stack);  // Первый операнд

            int result;
            if (symbol == '+') {
                result = a + b;
            }
            else if (symbol == '-') {
                result = a - b;
            }
            else if (symbol == '*') {
                result = a * b;
            }
            else if (symbol == '/') {
                if (b == 0) {
                    printf("Ошибка: деление на ноль\n");
                    exit(1);
                }
                result = a / b;
            }
            else {
                printf("Ошибка: неизвестный оператор '%c'\n", symbol);
                exit(1);
            }

            Stack_Push(&stack, result);
        }
    }
    
    return Stack_Pop(&stack);
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n) - один проход по строке
// Память: O(n) - в худшем случае весь стек заполнен

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Обратная Польская Запись (Postfix) ===\n\n");
    
    // Тест 1: Простое сложение
    char expr1[] = "3 4 +";
    printf("Тест 1: \"%s\" = %lld (ожидается 7)\n", expr1, Poliz(expr1));
    
    // Тест 2: Сложное выражение: 5 + (1+2)*4 - 3 = 14
    char expr2[] = "5 1 2 + 4 * + 3 -";
    printf("Тест 2: \"%s\" = %lld (ожидается 14)\n", expr2, Poliz(expr2));
    
    // Тест 3: Умножение разности: (9-5)*2 = 8
    char expr3[] = "9 5 - 2 *";
    printf("Тест 3: \"%s\" = %lld (ожидается 8)\n", expr3, Poliz(expr3));
    
    // Тест 4: Деление: 8/2 = 4
    char expr4[] = "8 2 /";
    printf("Тест 4: \"%s\" = %lld (ожидается 4)\n", expr4, Poliz(expr4));
    
    // Тест 5: Только число
    char expr5[] = "7";
    printf("Тест 5: \"%s\" = %lld (ожидается 7)\n", expr5, Poliz(expr5));
    
    return 0;
}
*/

