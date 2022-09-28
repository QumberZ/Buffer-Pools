#ifndef buffer_h
#define buffer_h

#include <stdio.h>
#include <stdlib.h>

void check_error(FILE* fp);
char skip_comments(FILE* fp);
int count_row(const char* filename);
int* count_cols(const char* filename, int row);
char** buffer(int row, int* cols, const char* filename);

#endif

