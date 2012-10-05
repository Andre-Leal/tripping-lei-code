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

	free(list);

}

/* Adiciona uma entry na lista. Como a lista deve ser ordenada, 
 * a nova entry deve ser colocada no local correto.
 * Retorna 0 (OK) ou -1 (erro)
 */
int list_add(struct list_t *list, struct entry_t *entry) {

	struct node_t *new_node = (struct node_t *) malloc(sizeof(struct node_t));
	new_node->entry = entry;	

    if (list->size == 0) {
        list->header = new_node;
        list->size++;
        return 0;
    }

	if(list->size == 1) {
		if (strcmp(new_node->entry->key , list->header->entry->key) < 0) {
			new_node = list->header;
			list->header = new_node;		
		}
		else {
        	new_node->next = list->header->next;
			list->header->next = new_node;
		}
		list->size++;
		return 0;
	}

    struct node_t *curr_node = list->header;

	if (strcmp(new_node->entry->key , curr_node->entry->key) < 0) {
        new_node->next = curr_node->next;
		curr_node->next = new_node;
	}

    while (curr_node->next != NULL) {
    	if (strcmp(new_node->entry->key , curr_node->next->entry->key) < 0) {
			printf("second chance %s\n" , new_node->entry->key);
            new_node->next = curr_node->next;
            curr_node->next = new_node;
            list->size++;
            return 0;
        }
		curr_node = curr_node->next;
    }

	curr_node->next = new_node;

}


/* Elimina da lista um elemento com a chave key. 
 * Retorna 0 (OK) ou -1 (erro)
 */
int list_remove(struct list_t *list, char *key) {



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


}

/* Liberta a memoria alocada por list_get_keys
 */
void list_free_keys(char **keys) {


}
