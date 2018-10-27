#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

static char rwTab[32][20] = {   //　保留字
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
static char oodTab[36][10]　=　{   //　运算符或界符
   "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
   "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
   "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
   "}", "\\", ".", "\?", ":", "!"
};

static  char IDTbab[1000][50] = { "" };//标识符表

void filter(char* sourceCode);  //　过滤掉注释
void printCode(char* code);

int main(void)
{
    char sourceCode[10000];
    int pCode = 0;
    char ch;
    int i = 0;
    FILE* fp;

    if ((fp = fopen("/home/zero/codes/princ2compile/test.c", "r")) == NULL) {
        printf("open file\n");
        exit(-1);
    }
    ch = fgetc(fp);
    while (ch != EOF) {
        sourceCode[pCode++] = ch;
        ch = fgetc(fp);
    }
    sourceCode[pCode] = EOF;
    printf("source code :\n");
    printCode(sourceCode);
    printf("\ncode after filter :\n");
    filter(sourceCode);
    printCode(sourceCode);

    return 0;
}

void printCode(char* code)
{
    int i = 0;
    while (code[i] != EOF) {
        printf("%c", code[i++]);
    }
}

void filter(char* sourceCode)
{
    int i = 0;
    char tempCode[10000];
    int k = 0;

    while (sourceCode[i] != EOF) {
        if (sourceCode[i] == '/' && sourceCode[i+1] == '/') {   // 行注释
            while (sourceCode[i] != '\n') {
                ++i;
            }
            ++i;    // 跳过回车换行
        }
        if (sourceCode[i] == '/' && sourceCode[i+1] == '*') {   // 多行注释
            while (!(sourceCode[i] == '*' && sourceCode[i] == '/')) {
                if (sourceCode[i] == EOF) {
                    printf("format error\n");
                    exit(-1);
                }
                ++i;
            } 
            ++i;
        }    
        if (sourceCode[i] == '\n' || sourceCode[i] == '\t') {
            sourceCode[i] = ' ';
        }
        tempCode[k++] = sourceCode[i++];
    }
    tempCode[k++] = EOF;
    tempCode[k] = '\0';    
    memset(sourceCode, '\0', 10000);
    strcpy(sourceCode, tempCode);
}

int isUnderLine(char ch)
{
    return (ch == '_');
}

int isLetter(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || 
            (ch >= 'A' && ch <= 'Z'));
}