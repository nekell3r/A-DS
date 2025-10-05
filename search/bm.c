// Алгоритм Бойера-Мура (Boyer-Moore)
// Поиск подстроки со сравнением справа налево
#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

// Функция для заполнения таблицы плохих символов (bad character heuristic)
void badCharHeuristic(char* pattern, int size, int badchar[NO_OF_CHARS]) {
    // Инициализируем все значения как -1
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badchar[i] = -1;
    }
    
    // Заполняем фактические позиции символов в паттерне
    for (int i = 0; i < size; i++) {
        badchar[(int)pattern[i]] = i;
    }
}

// Поиск всех вхождений pattern в text
void boyerMooreSearch(char* text, char* pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    
    int badchar[NO_OF_CHARS];
    
    // Заполняем таблицу плохих символов
    badCharHeuristic(pattern, m, badchar);
    
    int s = 0;  // s - сдвиг паттерна относительно текста
    
    while (s <= (n - m)) {
        int j = m - 1;
        
        // Сравниваем справа налево
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        
        // Если паттерн найден
        if (j < 0) {
            printf("Найдено на позиции %d\n", s);
            
            // Сдвигаемся, используя таблицу плохих символов
            s += (s + m < n) ? m - badchar[text[s + m]] : 1;
        } else {
            // Сдвигаем паттерн так, чтобы плохой символ в тексте
            // совпал с последним его вхождением в паттерн
            int shift = j - badchar[text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

// ============ СЛОЖНОСТЬ ============
// Построение таблицы: O(m + σ) где m - длина образца, σ - размер алфавита
// Лучший случай: O(n/m) - очень быстро!
// Худший случай: O(n*m)
// Средний случай: O(n) - субхлинейное время
// Память: O(σ) - таблица сдвигов для алфавита (256 для ASCII)
// BM - один из самых быстрых алгоритмов на практике!

// ============ ПРИМЕР ИСПОЛЬЗОВАНИЯ ============

/*
int main() {
    printf("=== Алгоритм Бойера-Мура ===\n\n");
    
    // Тест 1: Простой поиск
    char text1[] = "ABAAABCDABCDABDE";
    char pattern1[] = "ABCD";
    
    printf("Тест 1: Ищем \"%s\" в \"%s\"\n", pattern1, text1);
    boyerMooreSearch(text1, pattern1);
    printf("\n");
    
    // Тест 2: Поиск в английском тексте
    char text2[] = "haystack with needle inside haystack";
    char pattern2[] = "needle";
    
    printf("Тест 2: Ищем \"%s\" в \"%s\"\n", pattern2, text2);
    boyerMooreSearch(text2, pattern2);
    printf("\n");
    
    // Тест 3: Повторяющийся паттерн
    char text3[] = "AABAACAADAABAABA";
    char pattern3[] = "AABA";
    
    printf("Тест 3: Ищем \"%s\" в \"%s\"\n", pattern3, text3);
    boyerMooreSearch(text3, pattern3);
    printf("\n");
    
    // Тест 4: Паттерн не найден
    char text4[] = "abcdefghijk";
    char pattern4[] = "xyz";
    
    printf("Тест 4: Ищем \"%s\" в \"%s\"\n", pattern4, text4);
    boyerMooreSearch(text4, pattern4);
    printf("(не найдено)\n\n");
    
    // Тест 5: Редкий символ (демонстрация скорости)
    char text5[] = "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIZZZZZ";
    char pattern5[] = "ZZZZ";
    
    printf("Тест 5: Ищем \"%s\" (редкий паттерн)\n", pattern5);
    printf("В тексте: \"%s\"\n", text5);
    boyerMooreSearch(text5, pattern5);
    printf("(Быстро нашли благодаря большим сдвигам!)\n");
    
    return 0;
}
*/
