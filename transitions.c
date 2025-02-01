#include "unistd.h" 

#include "transitions.h"
#include "common.h"


Transition transitionsPool[MAX_TRANSITIONS];  
int poolIndex = 0;  
Transition* hashTable[TABLE_SIZE] = {0};


void insertTransition(const char* currentState, char currentSymbol, const char* nextState, char writeSymbol, char direction) {  
    unsigned int index = hash(currentState, currentSymbol);  
    //выделяем место под новый переход
    Transition* newTransition = &transitionsPool[poolIndex++];
    stringCopy(newTransition->currentState, currentState);  
    newTransition->currentSymbol = currentSymbol;  
    stringCopy(newTransition->nextState, nextState);  
    newTransition->writeSymbol = writeSymbol;  
    newTransition->direction = direction;  
    newTransition->next = NULL;  
    //если по этому хэшу ничего нет то это первый элемент 
    if (hashTable[index] == NULL) {  
        hashTable[index] = newTransition;  
    } else {  
        //иначе добавляется в конец связного списка
        Transition* current = hashTable[index];  
        while (current->next) current = current->next;  
        current->next = newTransition; 
    }  
} 

Transition* findTransition(const char* currentState, char currentSymbol) {  
    unsigned int index = hash(currentState, currentSymbol);  

    Transition* current = hashTable[index]; 
    while (current) { 
        if (stringCompare(current->currentState, currentState) && current->currentSymbol == currentSymbol) {  
            return current;  
        } 
        current = current->next;  
    }  
    return NULL;  
} 

unsigned int hash(const char* state, char symbol) {  
    unsigned int hashValue = 0;  
    int i = 0;  
    while (state[i] != '\0') {  
        //добавляю аски символ
        hashValue = (hashValue * 31 + state[i]) % TABLE_SIZE;  
        i++;
    } 
    hashValue = (hashValue * 31 + symbol) % TABLE_SIZE;  
    return hashValue;  
}