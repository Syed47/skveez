
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int*  rnumg(int from, int to, int smpl);
int   get_fsize(FILE *f);
void  write_file(const char* fname, const char* data);
char* load_file(const char *path);
char* bin_to_char(const char* bincode);
int   bin_to_decimal(const char* bincode);
void  printcc(char *arr, int len);
void  bin_code(const char *str);
// NOT YET DONE
void  write_bfile(const char* fname, const char* data, unsigned int size);
char* read_bfile(const char* fname);
int* to_set(const int* n, const int size);
#endif