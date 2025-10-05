// Алгоритм Рабина-Карпа (Rabin-Karp)
// Поиск подстроки с использованием хэш-функции
#include <stdio.h>
#include <string.h>

#define d 256  // Размер алфавита (ASCII)

// Поиск всех вхождений pattern в text
void rabinKarp(char* text, char* pattern) {
    int M = strlen(pattern);
    int N = strlen(text);
    long long q = 101;  // Простое число для модуля
    
    long long h = 1;  // h = d^(M-1) % q
    long long p = 0;  // Хэш паттерна
    long long t = 0;  // Хэш текущего окна текста
    
    // Вычисляем h = d^(M-1) % q
    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }
    
    // Вычисляем хэш паттерна и первого окна текста
    for (int i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    
    // Сдвигаем окно по тексту
    for (int i = 0; i <= N - M; i++) {
        // Если хэши совпали - проверяем посимвольно
        if (p == t) {
            int j;
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            
            if (j == M) {
                printf("Найдено на позиции %d\n", i);
            }
        }
        
        // Вычисляем хэш следующего окна
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            
            // Если получилось отрицательное - делаем положительным
            if (t < 0) {
                t = t + q;
            }
        }
    }
}

// ============ СЛОЖНОСТЬ ============
// Время: O(n + m) в среднем случае
//        O(n*m) в худшем (много коллизий)
// Память: O(1)
// Хорошо работает для поиска нескольких паттернов одновременно

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Алгоритм Рабина-Карпа ===\n\n");
    
    // Тест 1: Простой поиск
    char text1[] = "AABAACAADAABAABA";
    char pattern1[] = "AABA";
    
    printf("Тест 1: Ищем \"%s\" в \"%s\"\n", pattern1, text1);
    rabinKarp(text1, pattern1);
    printf("\n");
    
    // Тест 2: Поиск в тексте
    char text2[] = "this is a test text for testing";
    char pattern2[] = "test";
    
    printf("Тест 2: Ищем \"%s\" в \"%s\"\n", pattern2, text2);
    rabinKarp(text2, pattern2);
    printf("\n");
    
    // Тест 3: Паттерн не найден
    char text3[] = "abcdefghijk";
    char pattern3[] = "xyz";
    
    printf("Тест 3: Ищем \"%s\" в \"%s\"\n", pattern3, text3);
    rabinKarp(text3, pattern3);
    printf("(не найдено)\n\n");
    
    // Тест 4: Повторяющийся паттерн
    char text4[] = "ababababab";
    char pattern4[] = "abab";
    
    printf("Тест 4: Ищем \"%s\" в \"%s\"\n", pattern4, text4);
    rabinKarp(text4, pattern4);
    printf("\n");
    
    return 0;
}
*/
