#include "unistd.h"  


#include "tape.h"
#include "main.h"
#include "transitions.h"
#include "turing_machine.h"
#include "utils.h"

char *tape = NULL;
int tape_size = 0;
int head = 0;


void init_tape(const char *input) { 
    int input_length = my_strlen(input);
 
    tape_size = input_length * 3; 
 
    tape = (char *)my_malloc(tape_size);
    if (!tape) { 
        return;
    } 
 
    my_memset(tape, '_', tape_size); 
 
    // начало данных 
    head = tape_size / 2 - input_length / 2; 

    for (int i = 0; i < input_length; i++) { 
        if (input[i] == ' ') {
            tape[head + i] = '_';  // заменяем пробелы
        } else {
            tape[head + i] = input[i]; 
        }
    } 
}

void expand_tape(int new_size, int grow_left) {
    if (new_size <= tape_size) {
        return;
    }

    char *new_tape = (char *)my_malloc(new_size);
    if (!new_tape) {
        // если память не выделилась, выходим
        return;
    }
    my_memset(new_tape, '_', new_size);

    if (grow_left) {
        //данные сдвигаются вправо
        int shift = new_size - tape_size;
        for (int i = 0; i < tape_size; i++) {
            new_tape[shift + i] = tape[i];
        }
        head += shift;
    } else {
        for (int i = 0; i < tape_size; i++) {
            new_tape[i] = tape[i];
        }
    }
    tape = new_tape;
    tape_size = new_size;
}

void remove_underscores_and_print(char tape[]) {
    char result[tape_size + 1];
    int j = 0;

    for (int i = 0; i < tape_size; i++) {
        if (tape[i] != '_') {
            result[j++] = tape[i];
        }
    }
    result[j] = '\0';
    write_string(result);
}

char *read_all_input() {
    // выделяем начальный буфер
    int buffer_size = INITIAL_BUFFER_SIZE;
    char *buffer = (char *)my_malloc(buffer_size);
    if (!buffer) {
        return NULL;  // ошибка выделения памяти
    }

    int total_read = 0;
    while (1) {
        if (total_read + READ_CHUNK_SIZE > buffer_size) {
            int new_size = buffer_size + READ_CHUNK_SIZE;
            char *new_buffer = (char *)my_malloc(new_size);
            if (!new_buffer) {
                return NULL;  // ошибка выделения памяти
            }
            for (int i = 0; i < total_read; i++) {
                new_buffer[i] = buffer[i];
            }
            buffer = new_buffer;
            buffer_size = new_size;
        }
        // читаем из консоли
        int bytes_read = read(0, buffer + total_read, READ_CHUNK_SIZE);
        if (bytes_read <= 0) {
            break;
        }
        // конец при новой строке 
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[total_read + i] == '\n') {
                buffer[total_read + i] = '\0';
                return buffer;
            }
        }

        total_read += bytes_read;
    }

    // если в конце ввода нет '\n', добавляем '\0'
    if (total_read < buffer_size) {
        buffer[total_read] = '\0';
    } else {
        // расширяем для добавления '\0'
        char *new_buffer = (char *)my_malloc(buffer_size + 1);
        if (!new_buffer) {
            return NULL;
        }
        for (int i = 0; i < total_read; i++) {
            new_buffer[i] = buffer[i];
        }
        new_buffer[total_read] = '\0';
        buffer = new_buffer;
    }

    return buffer; // указатель на данные
}
