// Прямая Польская Запись (Polish Notation / Prefix)
// Формат: оператор перед операндами
// Пример: "+ 3 4" = 3 + 4 = 7
// Пример: "- + + 5 * + 1 2 4 3" = 5 + (1+2)*4 - 3 = 14

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK 100

// Вычисление выражения в прямой польской записи
// ГЛАВНОЕ ОТЛИЧИЕ: читаем строку СПРАВА НАЛЕВО!
int PolPZ(char *expression) {
    int stack[MAX_STACK];
    int top = -1;
    
    int len = strlen(expression);
    
    // Читаем выражение СПРАВА НАЛЕВО
    for (int i = len - 1; i >= 0; i--) {
        char symbol = expression[i];

        // Если цифра - кладём в стек
        if (isdigit(symbol)) {
            int number = symbol - '0';
            stack[++top] = number;
        }
        // Пробел - пропускаем
        else if (symbol == ' ') {
            continue;
        }
        // Оператор - достаём 2 числа, вычисляем, кладём результат
        // ВАЖНО: порядок операндов ОБРАТНЫЙ (сначала a, потом b)
        else {
            int a = stack[top--];  // Первый операнд
            int b = stack[top--];  // Второй операнд

            int result;
            if (symbol == '+') result = a + b;
            else if (symbol == '-') result = a - b;
            else if (symbol == '*') result = a * b;
            else if (symbol == '/') result = a / b;

            stack[++top] = result;
        }
    }
    
    return stack[top];
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n) - один проход по строке
// Память: O(n) - в худшем случае весь стек заполнен

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Прямая Польская Запись (Prefix) ===\n\n");
    
    // Тест 1: Простое сложение: 3+4 = 7
    char expr1[] = "+ 3 4";
    printf("Тест 1: \"%s\" = %d (ожидается 7)\n", expr1, PolPZ(expr1));
    
    // Тест 2: Сложное выражение: 5 + (1+2)*4 - 3 = 14
    char expr2[] = "- + + 5 * + 1 2 4 3";
    printf("Тест 2: \"%s\" = %d (ожидается 14)\n", expr2, PolPZ(expr2));
    
    // Тест 3: Умножение разности: (9-5)*2 = 8
    char expr3[] = "* - 9 5 2";
    printf("Тест 3: \"%s\" = %d (ожидается 8)\n", expr3, PolPZ(expr3));
    
    // Тест 4: Деление: 8/2 = 4
    char expr4[] = "/ 8 2";
    printf("Тест 4: \"%s\" = %d (ожидается 4)\n", expr4, PolPZ(expr4));
    
    // Тест 5: Вычитание: 9-3 = 6
    char expr5[] = "- 9 3";
    printf("Тест 5: \"%s\" = %d (ожидается 6)\n", expr5, PolPZ(expr5));
    
    return 0;
}
*/

