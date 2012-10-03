#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Funcao que cria um novo par chave-valor (isto e, que inicializa
* a estrutura e aloca a memoria necessaria).
*/
struct entry_t *entry_create(char *key, struct data_t *data) {

    struct entry_t *new_entry = (struct entry_t *) malloc(sizeof(struct entry_t));
    new_entry->timestamp = 0;
    new_entry->key = key;
    new_entry->value = data;

    return new_entry;
}

/* Funcao que destroi um par chave-valor e liberta toda a memoria.
*/
void entry_destroy(struct entry_t *entry) {

    free(entry->key);
    data_destroy(entry->value);
    free(entry);

}

/* Funcao que duplica um par chave-valor. */
struct entry_t *entry_dup(struct entry_t *entry) {

    char *key_copy = malloc(strlen(entry->key)+1);
    strcpy(key_copy , entry->key);

    struct data_t *value_copy = data_dup(entry->value);

    struct entry_t *new_entry = entry_create(key_copy , value_copy);

    return new_entry;
}
