#include "unistd.h" 

#include "turing_machine.h"
#include "common.h"
#include "utils.h"
#include "transitions.h"
#include "tape.h"


int step_count = 0; 

void load_turing_machine(const char* filename, TuringMachine* tm) { 
    int fd = open(filename, 0);
    if (fd < 0) { 
        write_string("Error: Cannot open file\n"); 
        return; 
    } 
    char buffer[BUFFER_SIZE]; 
    int bytes_read = read(fd, buffer, BUFFER_SIZE - 1); 
    if (bytes_read <= 0) { 
        write_string("Error: Cannot read file\n"); 
        close(fd); 
        return; 
    } 
    buffer[bytes_read] = '\0';
    close(fd); 
    //ptr указатель на начао строки буффера
    char* ptr = buffer; 
    // количество состояний 
    tm->num_states = 0; 
    while (*ptr >= '0' && *ptr <= '9') { 
        tm->num_states = tm->num_states * 10 + (*ptr - '0'); 
        ptr++; 
    } 
    ptr++; // пропускаем '\n' 

    //состояния 
    for (int i = 0; i < tm->num_states; i++) { 
        char* state_start = ptr; 
        while (*ptr != ' ' && *ptr != '\n') { 
            ptr++; 
        } 
        int state_len = ptr - state_start; 
        strncpy(tm->states[i], state_start, state_len); 
        tm->states[i][state_len] = '\0'; 
        if (*ptr == ' ') ptr++; 
    } 
    ptr++; // пропускаем '\n' 

    // переходы
    tm->num_transitions = 0; 
    while (*ptr >= '0' && *ptr <= '9') { 
        tm->num_transitions = tm->num_transitions * 10 + (*ptr - '0'); 
        ptr++; 
    } 
    ptr++; // пропускаем '\n'
    // таблица переходов 
    for (int i = 0; i < tm->num_transitions; i++) { 
        Transition* t = &tm->transitions[i]; 

        // Текущее состояние 
        char* t_start = ptr; 
        while (*ptr != ',') ptr++; 
        strncpy(t->currentState, t_start, ptr - t_start); 
        t->currentState[ptr - t_start] = '\0'; 
        ptr++; // Пропускаем ',' 

        t->currentSymbol = *ptr; 
        ptr += 4; // пропускаем  -> 

        while (*ptr == ' ') ptr++;
        t_start = ptr; 
        while (*ptr != ',') ptr++; 
        strncpy(t->nextState, t_start, ptr - t_start); 
        t->nextState[ptr - t_start] = '\0'; 
        ptr++; // пропускаем ',' 

        t->writeSymbol = *ptr; 
        ptr += 2; // пропускаем символ и ',' 
 
        t->direction = *ptr; 
        ptr += 2; // пропускаем символ и '\n' 
        insertTransition(t->currentState, t->currentSymbol, t->nextState, t->writeSymbol, t->direction);
    } 
}

void run_turing_machine() { 
    char currentState[MAX_STATE_LEN] = "start";
    while (strcmp(currentState, "stop") != 0) { 
        if (step_count>=100000){
            write_string("Step limit reached \n");
            break;
        }

        char currentSymbol = tape[head]; 
        Transition* t = findTransition(currentState, currentSymbol); 
        if (!t) { 
            write_string("No valid transition found!\n"); 
            break;
        } 
        // запись символа и смена состояния
        tape[head] = t->writeSymbol;
        stringCopy(currentState, t->nextState); 

        if (t->direction == '>') {
            head++;
        } else if (t->direction == '<') {
            head--;
        } else if (t->direction == '.') {
        } else { 
            break; 
        }

        // разширение влево
        if (head < 0) {
        int new_size = tape_size * 2;
        expand_tape(new_size, 1);
        }

        // расширение вправо
        if (head >= tape_size) {
            int new_size = tape_size * 2;
            expand_tape(new_size, 0);
        }
        step_count++;
    }
    write_string("the end\n");
}