#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include "common.h"

#define BUFFER_SIZE 1024 
extern int step_count; 



void load_turing_machine(const char* filename, TuringMachine* tm);
void run_turing_machine();


#endif // TURING_MACHINE_H