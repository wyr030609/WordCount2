#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1000

// 定义参数结构体，用于存储用户输入的命令行参数
struct Arguments {
    char* filename; // 文件名
    int mode; // 统计模式：0表示统计字符数，1表示统计单词数
};

// 函数声明
void print_usage();
void parse_arguments(int argc, char* argv[], struct Arguments* args);
int count_chars(char* filename);
int count_words(char* filename);

int main(int argc, char* argv[]) {
    struct Arguments args;
    parse_arguments(argc, argv, &args); // 解析命令行参数
    int count;
    if (args.mode == 0) {
        count = count_chars(args.filename); // 统计字符数
        printf("Char count: %d\n", count);
    }
    else {
        count = count_words(args.filename); // 统计单词数
        printf("Word count: %d\n", count);
    }
    return 0;
}


void print_usage() {
    printf("Usage: WordCount [-c|-w] filename\n");
    printf("\t-c: count characters\n");
    printf("\t-w: count words\n");
}

// 解析命令行参数
void parse_arguments(int argc, char* argv[], struct Arguments* args) {
    if (argc != 3) { // 参数个数不正确
        printf("Invalid arguments.\n");
        print_usage();
        exit(-1);
    }
    if (strcmp(argv[1], "-c") == 0) { // 统计字符数
        args->mode = 0;
    }
    else if (strcmp(argv[1], "-w") == 0) { // 统计单词数
        args->mode = 1;
    }
    else { // 参数不正确
        printf("Invalid arguments.\n");
        print_usage();
        exit(-1);
    }
    args->filename = argv[2];
}

// 统计文件中的字符数
int count_chars(char* filename) {
    FILE* fp;
    char c;
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", filename);
        exit(-1);
    }
    while ((c = fgetc(fp)) != EOF) {
        count++; // 统计字符数
    }
    fclose(fp);

    return count;
}

// 统计文件中的单词数
int count_words(char* filename) {
    FILE* fp;
    char line[MAX_LEN];
    char* token;
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", filename);
        exit(-1);
    }
    while (fgets(line, MAX_LEN, fp) != NULL) {
        token = strtok(line, " \t\n,"); // 以空格、水平制表符、换行符、逗号为分隔符
        while (token != NULL) {
            count++; // 统计单词数
            token = strtok(NULL, " \t\n,");
        }
    }
    fclose(fp);

    return count;
}
