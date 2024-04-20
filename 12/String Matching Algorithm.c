#include <stdio.h>
#include <string.h>

void string_matching(char* text, char* pattern) {
    int text_length = strlen(text);
    int pattern_length = strlen(pattern);
    int i, j;

    for (i = 0; i <= text_length - pattern_length; i++) {
        j = 0;
        while (j < pattern_length && text[i + j] == pattern[j])
            j++;
        
        if (j == pattern_length)
            printf("Pattern found at index %d\n", i);
    }
}

int main() {
    char text[1000];
    char pattern[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);

    // Removing newline characters
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);

    string_matching(text, pattern);

    return 0;
}

