#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1000

// ��������ṹ�壬���ڴ洢�û�����������в���
struct Arguments {
    char* filename; // �ļ���
    int mode; // ͳ��ģʽ��0��ʾͳ���ַ�����1��ʾͳ�Ƶ�����
};

// ��������
void print_usage();
void parse_arguments(int argc, char* argv[], struct Arguments* args);
int count_chars(char* filename);
int count_words(char* filename);

int main(int argc, char* argv[]) {
    struct Arguments args;
    parse_arguments(argc, argv, &args); // ���������в���
    int count;
    if (args.mode == 0) {
        count = count_chars(args.filename); // ͳ���ַ���
        printf("Char count: %d\n", count);
    }
    else {
        count = count_words(args.filename); // ͳ�Ƶ�����
        printf("Word count: %d\n", count);
    }
    return 0;
}


void print_usage() {
    printf("Usage: WordCount [-c|-w] filename\n");
    printf("\t-c: count characters\n");
    printf("\t-w: count words\n");
}

// ���������в���
void parse_arguments(int argc, char* argv[], struct Arguments* args) {
    if (argc != 3) { // ������������ȷ
        printf("Invalid arguments.\n");
        print_usage();
        exit(-1);
    }
    if (strcmp(argv[1], "-c") == 0) { // ͳ���ַ���
        args->mode = 0;
    }
    else if (strcmp(argv[1], "-w") == 0) { // ͳ�Ƶ�����
        args->mode = 1;
    }
    else { // ��������ȷ
        printf("Invalid arguments.\n");
        print_usage();
        exit(-1);
    }
    args->filename = argv[2];
}

// ͳ���ļ��е��ַ���
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
        count++; // ͳ���ַ���
    }
    fclose(fp);

    return count;
}

// ͳ���ļ��еĵ�����
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
        token = strtok(line, " \t\n,"); // �Կո�ˮƽ�Ʊ�������з�������Ϊ�ָ���
        while (token != NULL) {
            count++; // ͳ�Ƶ�����
            token = strtok(NULL, " \t\n,");
        }
    }
    fclose(fp);

    return count;
}
