#define _CRT_SECURE_NO_WARNINGS
#include "easyz.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include<stdlib.h>
#include "parser.h"
#include "vm.h"
#include "utils.h"
char* rootDir = NULL;   //¸ùÄ¿Â¼
char* readFile(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        IO_ERROR("Could`t open file \"%s\".\n", path);
    }

    struct stat fileStat;
    stat(path, &fileStat);
    size_t fileSize = fileStat.st_size;
    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        MEM_ERROR("Could`t allocate memory for reading file \"%s\".\n", path);
    }

    size_t numRead = fread(fileContent, sizeof(char), fileSize, file);
    if (numRead < fileSize) {
        IO_ERROR("Could`t read file \"%s\".\n", path);
    }
    fileContent[fileSize] = '\0';

    fclose(file);
    return fileContent;
}
int main() {
	printf("hello,world\n");
	void* p = 1;
    struct parser parser;
    char* path = "";
    const char* sourceCode =readFile("sample.sp");
    VM* vm = newVM();
    initParser(vm, &parser,path , sourceCode);

     #include "token.list"
    while (parser.curToken.type != TOKEN_EOF) {
        getNextToken(&parser);
        printf("%dL: %s [", parser.curToken.lineNo, tokenArray[parser.curToken.type]);
        uint32_t idx = 0;
        while (idx < parser.curToken.length) {
            printf("%c", *(parser.curToken.start + idx++));
        }
        printf("]\n");
    }
	//print_error(p, ERROR_IO, "there have a big error %s", "my god!");
}
