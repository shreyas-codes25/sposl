#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Define some keywords
const char* keywords[] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue", "char", "double",
};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// Function to check if a string is a keyword
int isKeyword(const char* str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    char operators[] = "+-*/%=<>";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a punctuator
int isPunctuator(char ch) {
    char punctuators[] = ".,;(){}[]";
    for (int i = 0; i < strlen(punctuators); i++) {
        if (ch == punctuators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to print the lexical analyzer table
void lexicalAnalyzer(const char* str) {
    int i = 0;
    int serialNo = 1;  // Initialize serial number
    char token[100];

    printf("S.No\tToken\t\tType\n");
    printf("----------------------------\n");

    while (str[i] != '\0') {
        if (isalpha(str[i])) {  // Start of a keyword or identifier
            int j = 0;
            while (isalnum(str[i])) {
                token[j++] = str[i++];
            }
            token[j] = '\0';
            if (isKeyword(token)) {
                printf("%d\t%s\t\tKeyword\n", serialNo++, token);
            } else {
                printf("%d\t%s\t\tIdentifier\n", serialNo++, token);
            }
        } else if (isdigit(str[i])) {  // Start of a number
            int j = 0;
            while (isdigit(str[i])) {
                token[j++] = str[i++];
            }
            token[j] = '\0';
            printf("%d\t%s\t\tNumber\n", serialNo++, token);
        } else if (isOperator(str[i])) {  // Operator
            printf("%d\t%c\t\tOperator\n", serialNo++, str[i]);
            i++;
        } else if (isPunctuator(str[i])) {  // Punctuator
            printf("%d\t%c\t\tPunctuator\n", serialNo++, str[i]);
            i++;
        } else {  // Any other character (skip whitespaces)
            i++;
        }
    }
}

int main() {
    //const char* input = "int x = 10; float y = x + 3.14;";
    const char* input = " sum = count + rate* 50 ; ";
    lexicalAnalyzer(input);
    return 0;
}