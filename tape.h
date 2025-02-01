#ifndef TAPE_H
#define TAPE_H

#define INITIAL_BUFFER_SIZE 2
#define READ_CHUNK_SIZE 128

extern char *tape;
extern int tape_size;
extern int head;

void init_tape(const char *input);
void expand_tape(int new_size, int grow_left);
void remove_underscores_and_print(char tape[]);
char *read_all_input();

#endif // TAPE_H