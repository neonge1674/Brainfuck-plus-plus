#ifndef HASH
#define HASH

#define HASH_SIZE 1000

typedef struct {
    char* key;
    int data;
} hash_node;

typedef struct {
    hash_node *table[HASH_SIZE];
} hash_table;

unsigned int hash(char* key); 
int get_hash(hash_table* table, char* key);
hash_table* new_table();
hash_node* new_hash_node(char* key, int value);
void set_hash(hash_table* table, char* key, int value);






#endif 