#ifndef UTILS_H
#define UTILS_H

int my_strlen(const char *str);
void my_memset(char *array, char value, int size);
void *my_malloc(int size);
void write_string(const char *str);
void write_num(int num);
void stringCopy(char* dest, const char* src);
int stringCompare(const char* str1, const char* str2);
void write_character(char c);


#endif // UTILS_H