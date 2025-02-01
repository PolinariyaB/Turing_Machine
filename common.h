#ifndef COMMON_H
#define COMMON_H

#define MAX_STATE_LEN 32
#define MAX_TRANSITIONS 1024

typedef struct Transition { 
    char currentState[MAX_STATE_LEN];
    char currentSymbol;
    char nextState[MAX_STATE_LEN];
    char writeSymbol;
    char direction;
    struct Transition* next;
} Transition; 

typedef struct { 
    int num_states; 
    char states[128][MAX_STATE_LEN];
    int num_transitions; 
    Transition transitions[MAX_TRANSITIONS];
} TuringMachine;

extern Transition transitionsPool[MAX_TRANSITIONS];  

#endif // COMMON_H