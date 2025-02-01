#include "unistd.h"  

#include "tape.h"
#include "main.h"
#include "transitions.h"
#include "turing_machine.h"
#include "utils.h"

int my_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_memset(char *array, char value, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = value;
    }
}
void *my_malloc(int size) {
    //выделяем память
    static char heap[32 * 1024 * 1024]; 
    static int offset = 0; // конец памяти

    // выравниваем запрашиваемую память до кратности 4
    int aligned_size = (size + 3) & ~3;

    // есть ли место в куче
    if (offset + aligned_size > sizeof(heap)) {
        return 0;
    }

    void *ptr = &heap[offset];
    offset += aligned_size;
    return ptr;//указатель на начало выделенного участка памяти
}

// Печать строки 
void write_string(const char *str) { 
    write(1, str, strlen(str)); 
}

void write_num(int num) {
    char buffer[16];
    int i = 15;
    buffer[i] = '\0';

    if (num == 0) {
        buffer[--i] = '0';
    } else {
        while (num > 0) {
            buffer[--i] = '0' + (num % 10);
            num /= 10;
        }
    }
    write_string(&buffer[i]);
}

void stringCopy(char* dest, const char* src) { 
    while (*src) { 
        *dest++ = *src++; 
    } 
    *dest = '\0'; 
} 
 
int stringCompare(const char* str1, const char* str2) { 
    return strcmp(str1, str2) == 0; 
} 
void write_character(char c) {
    write(1, &c, 1);
}