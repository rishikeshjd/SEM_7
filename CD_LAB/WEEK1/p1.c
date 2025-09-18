#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200

const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while", "for",
    "return", "void", "switch", "case", "break", "continue", "struct"
};
int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

const char *operators[] = {
    "+", "-", "*", "/", "=", "==", "<", ">", "<=", ">=", "&&", "||", "!", "%",
    "&", "|"
};
int operatorCount = sizeof(operators) / sizeof(operators[0]);

int isKeyword(const char *token) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(token, keywords[i]) == 0) return 1;
    }
    return 0;
}

int isOperator(const char *token) {
    for (int i = 0; i < operatorCount; i++) {
        if (strcmp(token, operators[i]) == 0) return 1;
    }
    return 0;
}

int isNumber(const char *token) {
    if (!token[0]) return 0;
    for (int i = 0; token[i]; i++) {
        if (!isdigit(token[i])) return 0;
    }
    return 1;
}

int isIdentifier(const char *token) {
    if (!(isalpha(token[0]) || token[0] == '_')) return 0;
    for (int i = 1; token[i]; i++) {
        if (!(isalnum(token[i]) || token[i] == '_')) return 0;
    }
    return 1;
}

int main() {
    char input[500];
    int totalTokens = 0, keywordCnt = 0, idCnt = 0, numCnt = 0, opCnt = 0, strCnt = 0, specialCnt = 0;

    printf("Enter a line of code:\n");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i]; i++) {
        if (input[i] == '\"') {
            int j = i + 1;
            while (input[j] && input[j] != '\"') j++;
            if (input[j] == '\"') {
                input[i] = '#';
                input[j] = '#';
                i = j;
            }
        }
    }

    char token[100];
    int pos = 0;

    for (int i = 0; input[i]; i++) {
        char ch = input[i];

        if (ch == '#') {
            pos = 0;
            i++;
            while (input[i] && input[i] != '#') {
                token[pos++] = input[i++];
            }
            token[pos] = '\0';
            printf("\"%s\" --> String literal\n", token);
            strCnt++; totalTokens++;
        }
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',') {
            printf("%c --> Special symbol\n", ch);
            specialCnt++; totalTokens++;
        }
        else if (strchr("+-*/=!<>%&|", ch)) {
            char op[3] = {ch, '\0', '\0'};
            if ((ch == '=' || ch == '&' || ch == '|' || ch == '<' || ch == '>') && input[i+1] == ch) {
                op[1] = ch;
                i++;
            } else if ((ch == '<' || ch == '>') && input[i+1] == '=') {
                op[1] = '=';
                i++;
            }
            if (isOperator(op)) {
                printf("%s --> Operator\n", op);
                opCnt++; totalTokens++;
            }
        }
        else if (isspace(ch)) {
            continue;
        }
        else {
            pos = 0;
            while (input[i] && !isspace(input[i]) &&
                   !strchr("(){};,+-*/=!<>%&|#", input[i])) {
                token[pos++] = input[i++];
            }
            token[pos] = '\0';
            i--;

            if (isKeyword(token)) {
                printf("%s --> Keyword\n", token); keywordCnt++;
            }
            else if (isNumber(token)) {
                printf("%s --> Number\n", token); numCnt++;
            }
            else if (isIdentifier(token)) {
                printf("%s --> Identifier\n", token); idCnt++;
            }
            else {
                printf("%s --> Special symbol\n", token); specialCnt++;
            }
            totalTokens++;
        }
    }

    printf("\nSummary of Tokens:\n");
    printf("Keywords   : %d\n", keywordCnt);
    printf("Identifiers: %d\n", idCnt);
    printf("Numbers    : %d\n", numCnt);
    printf("Operators  : %d\n", opCnt);
    printf("String literalss: %d\n", strCnt);
    printf("Specials   : %d\n", specialCnt);
    printf("Total tokens = %d\n", totalTokens);

    return 0;
}


/** O/P
Enter a line of code:
int sum= a+10;         
int --> Keyword
sum --> Identifier
= --> Operator
a --> Identifier
+ --> Operator
10 --> Number
; --> Special symbol

Summary of Tokens:
Keywords   : 1
Identifiers: 2
Numbers    : 1
Operators  : 2
String lits: 0
Specials   : 1
Total tokens = 7



Enter a line of code:
a(a|b)*a
a --> Identifier
( --> Special symbol
a --> Identifier
| --> Operator
b --> Identifier
) --> Special symbol
* --> Operator
a --> Identifier

Summary of Tokens:
Keywords   : 0
Identifiers: 4
Numbers    : 0
Operators  : 2
String lits: 0
Specials   : 2
Total tokens = 8 **/

