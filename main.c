#include "unistd.h" 

#include "main.h"
#include "tape.h"
#include "transitions.h"
#include "turing_machine.h"
#include "utils.h"
#include "common.h"

int main() {  
    TuringMachine tm; 
    const char* filename = "t.txt"; 

    write(1, "Enter input for tape: ", 22);  

    // данные любого размера
    char *input = read_all_input();
    if (!input) {
        write(2, "Error reading input\n", 20);
        return 1;
    }
    load_turing_machine(filename, &tm);  
    init_tape(input);

    // проверка
    write(1, "Tape: ", 6);
    write(1, tape, tape_size);
    write(1, "\n", 1);

    run_turing_machine(); 

    write_string("Final tape: ");  
    remove_underscores_and_print(tape); 

    return 0;  
}
