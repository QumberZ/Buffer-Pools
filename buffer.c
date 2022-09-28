#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
void check_error(FILE* fp){
    if(!fp){
        fprintf(stderr, "can not open the file for reading \n");
        exit(1);
    }
}

char skip_comments(FILE* fp){
    char current_char = getc(fp);
    while(current_char == '#'){
        current_char = getc(fp); //get char = get current char
        while (current_char != '\n') {
            current_char = getc(fp);
        }
        current_char = getc(fp);
    }
    return current_char;
}

int count_row(const char* filename){
    FILE* fp = fopen(filename, "r");
    check_error(fp);
    int row = 0;
    char  current_char = skip_comments(fp);
    while(current_char != EOF){
        if (current_char == '\n') {
            row++;
        }
        current_char = getc(fp);
    }
    
    return row;
}

int* count_cols(const char* filename, int row){
    int* cols = (int*)calloc(row, sizeof(int));
    FILE* fp = fopen(filename, "r");
    char current_char = skip_comments(fp);
    int col_char_sum = 0, row_index = 0;
    while (current_char != EOF) {
        if (current_char == '\n') {
            cols[row_index] = col_char_sum;
            col_char_sum = 0;
            row_index++;
        }
        col_char_sum++;
        current_char = getc(fp);
    }
    
    fclose(fp);
    return cols;
}


char** buffer(int row, int* cols, const char* filename){
    FILE* fp = fopen(filename, "r");
    char** buffer_pool = (char**)malloc(row*sizeof(char*));
    for (int index = 0; index < row; index++) {
        buffer_pool[index] = (char*)malloc(cols[index] * sizeof(char));
    }
    char current_char = skip_comments(fp);
    int row_index = 0, col_index = 0;
    while (current_char != EOF) {
        if (current_char == '\n') {
            buffer_pool[row_index][col_index] = current_char;
            col_index = 0;
            row_index++;
        }
        else{
            buffer_pool[row_index][col_index] = current_char;
            col_index++;
        }
        current_char = getc(fp);
    }
    return buffer_pool;
    
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Please pass two arguments\n");
        exit(1);
    }
    const char* filename = argv[1];
    int row = count_row(filename);
    int* cols = count_cols(filename, row);
    char** buffer_pool = buffer(row,cols,filename);
    printf("Number of rows: %d\n", row);
    for (int index = 0; index < row; index++) {
        printf("%s\n", buffer_pool[index]);
    }
    return 0;
}
