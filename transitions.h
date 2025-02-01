#ifndef TRANSITIONS_H
#define TRANSITIONS_H
#include "common.h"
#include "utils.h"
#define TABLE_SIZE 16  


extern int poolIndex;  
extern Transition* hashTable[TABLE_SIZE];  

void insertTransition(const char* currentState, char currentSymbol, const char* nextState, char writeSymbol, char direction);
Transition* findTransition(const char* currentState, char currentSymbol);
unsigned int hash(const char* state, char symbol);

#endif // TRANSITIONS_H