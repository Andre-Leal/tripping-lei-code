#include "list.h"
#include "list-private.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Cria uma nova lista. Em caso de erro, retorna NULL.
*/
struct list_t *list_create() {

    struct list_t *list = (struct list_t *) malloc(sizeof(struct list_t));
    list->size = 0;
    list->header = NULL;

    if( !list) {
        perror("Error malloc\n");
        return NULL;
    }

    return list;

}

/* Elimina uma lista, libertando *toda* a memoria utilizada pela
 * lista.
 * Retorna 0 (OK) ou -1 (erro)
 */
int list_destroy(struct list_t *list) {

    erase_all_memory(list->header);
    free(list);
}

/*
   Method that recursively frees all the memory space reserved.
   */
void erase_all_memory (struct node_t *node) {

    if (node != NULL) {
        erase_all_memory(node->next);
        entry_destroy(node->entry);
        free(node);
    }
}

/* Adiciona uma entry na lista. Como a lista deve ser ordenada, 
 * a nova entry deve ser colocada no local correto.
 * Retorna 0 (OK) ou -1 (erro)
 */
int list_add(struct list_t *list, struct entry_t *entry) {

    struct node_t *new_node = (struct node_t *) malloc(sizeof(struct node_t));
    new_node->entry = entry;
    new_node->next = NULL;

    //Add if list is empty
    if (list->size == 0) {
        list->header = new_node;
        list->size++;
        return 0;
    }

    // the new element goes to the header
    if(strcmp(new_node->entry->key, list->header->entry->key) < 0) {
        new_node->next = list->header;
        list->header = new_node;

        list->size++;
        return 0;
    }

    struct node_t *curr_node;
    curr_node = list->header;

    while (1) {
        if (curr_node->next == NULL) {
            curr_node->next = new_node;
            break;
        }

        if (strcmp(new_node->entry->key , curr_node->next->entry->key) < 0) {
            new_node->next = curr_node->next;
            curr_node->next = new_node;
            break;
        }

        curr_node = curr_node->next;
    }

    list->size++;
    return 0;
}


/* Elimina da lista um elemento com a chave key. 
 * Retorna 0 (OK) ou -1 (erro)
 */
int list_remove(struct list_t *list, char *key) {

    struct node_t *curr_node = list->header;

    if (list->size == 0) {return -1;}

    while (curr_node != NULL) {
        if(strcmp(key , curr_node->entry->key)==0) {
            curr_node = curr_node->next;
            list->size--;
            return 0;
        }
        curr_node = curr_node->next;
    }

    return -1;
}


/* Obtem um elemento da lista com a chave key. 
 * Retorna a referencia do elemento na lista (ou seja, uma alteração
 * implica alterar o elemento na lista).
 * Nota: a função list_remove ou list_destroy deve ser 
 * a responsável por libertar a memoria ocupada pelo elemento.
 */
struct entry_t *list_get(struct list_t *list, char *key) {

    struct node_t *node = list->header;

    while(node != NULL) {
        if(strcmp(key , node->entry->key)==0) {
            return node->entry;
        }
        node = node->next;
    }
}

/* Retorna o tamanho (numero de elementos) da lista 
 * Retorna -1 em caso de erro)
 */
int list_size(struct list_t *list) {

    return list->size;

}

/* Devolve um array de char* com a cópia de todas as keys da
 * lista, com um ultimo elemento a NULL.
 */
char **list_get_keys(struct list_t *list) {

    char **array_key = malloc((list->size+1) * sizeof(char *));

    struct node_t *node = list->header;
    int i;
    for(i=0;i<list->size;i++) {
        array_key[i] = strdup(node->entry->key);
        node = node->next;
    }
    array_key[i] = NULL;

    return array_key;
}

/* Liberta a memoria alocada por list_get_keys
*/
void list_free_keys(char **keys) {

    int i = 0;

    while(keys[i] != NULL) {
        free(keys[i]);
        i++;
    }
    free(keys);

}
