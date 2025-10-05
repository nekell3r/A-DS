// Алгоритм Кнута-Морриса-Пратта (KMP)
// Поиск подстроки с использованием префикс-функции
#include <stdio.h>
#include <string.h>

// Построение префикс-функции (таблицы сдвигов)
void computeLPSArray(char* pattern, int M, int* lps) {
    int len = 0;  // Длина предыдущего наибольшего префикса-суффикса
    lps[0] = 0;   // lps[0] всегда 0
    int i = 1;
    
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Поиск всех вхождений pattern в text
void KMPSearch(char* text, char* pattern) {
    int M = strlen(pattern);
    int N = strlen(text);
    
    // Создаем массив lps[] (longest proper prefix which is also suffix)
    int lps[M];
    
    // Строим префикс-функцию
    computeLPSArray(pattern, M, lps);
    
    int i = 0;  // Индекс для text[]
    int j = 0;  // Индекс для pattern[]
    
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == M) {
            printf("Найдено на позиции %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            // Несовпадение после j совпадений
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

// ============ СЛОЖНОСТЬ ============
// Построение таблицы: O(m) где m - длина образца
// Поиск: O(n) где n - длина текста
// Общая сложность: O(n + m)
// Память: O(m) - таблица сдвигов
// КМП не возвращается назад в тексте - линейное время!

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Алгоритм Кнута-Морриса-Пратта (KMP) ===\n\n");
    
    // Тест 1: Простой поиск
    char text1[] = "ABABDABACDABABCABAB";
    char pattern1[] = "ABABC";
    
    printf("Тест 1: Ищем \"%s\" в \"%s\"\n", pattern1, text1);
    KMPSearch(text1, pattern1);
    printf("\n");
    
    // Тест 2: Множественные вхождения
    char text2[] = "AABAACAADAABAABA";
    char pattern2[] = "AABA";
    
    printf("Тест 2: Ищем \"%s\" в \"%s\"\n", pattern2, text2);
    KMPSearch(text2, pattern2);
    printf("\n");
    
    // Тест 3: Поиск в тексте
    char text3[] = "this is a pattern matching pattern";
    char pattern3[] = "pattern";
    
    printf("Тест 3: Ищем \"%s\" в \"%s\"\n", pattern3, text3);
    KMPSearch(text3, pattern3);
    printf("\n");
    
    // Тест 4: Паттерн не найден
    char text4[] = "abcdefghijk";
    char pattern4[] = "xyz";
    
    printf("Тест 4: Ищем \"%s\" в \"%s\"\n", pattern4, text4);
    KMPSearch(text4, pattern4);
    printf("(не найдено)\n\n");
    
    // Тест 5: Демонстрация префикс-функции
    printf("=== Префикс-функция для \"ABABC\" ===\n");
    char demo[] = "ABABC";
    int M = strlen(demo);
    int lps[M];
    computeLPSArray(demo, M, lps);
    
    printf("Паттерн: ");
    for (int i = 0; i < M; i++) printf("%c ", demo[i]);
    printf("\nLPS:     ");
    for (int i = 0; i < M; i++) printf("%d ", lps[i]);
    printf("\n");
    
    return 0;
}
*/
