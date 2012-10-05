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
    else {
        struct node_t *curr_node = list->header;
        while (curr_node != NULL) {
            if (strcmp(new_node->entry->key , curr_node->entry->key) > 0) {
                new_node->next = curr_node->next;
                curr_node->next = new_node;
                list->size++;
                return 0;
            }
        }
        return -1;
    }

    /*if (find_place_to_insert (list->header , new_node) ) {
		list->size++;
		return 0;
	}
	
	return 1;
    */

}

int find_place_to_insert (struct node_t *node , struct node_t *new_node) {
    /* TODO: qual era o problema aqui?
     * o problema eh que nao te esquecas que isto em C eh tudo de muito baixo
     * nivel...
     * O que quero dizer com isto eh a expressao  node = new_node  eh marota!
     * Nao te esquecas que como argumento estamos a receber um ponteiro, nada
     * mais do que isso! E o que eh um ponteiro? Eh simplesmente um tipo
     * primitivo, uma especie de inteiro que aponta para algures na memoria
     * nao eh um objecto em si...
     *
     * Eu percebo o que querias fazer... eh como se passases o objecto do
     * header aqui como argumento *node e depois todo fanfarrao achavas que
     * node=new_node ia actualizar o list->header tambem xD. Mas nao, na verdade
     * este node=new_node que fizeste aqui, ficou-se apenas por este metodo e
     * depois vai com os passarinhos. Tal como todos os argumentos dos metodos
     *
     * Tens sempre de fazer explicitamente list->header = <...>
     * Porque o que queres eh actualizar o ponteiro da estrutura list.
     *
     * Epa, isto funcionava da forma que estavas aqui a pensar se usasses
     * ponteiros que apontam para ponteiros. Ou seja, se o conteudo de list->header
     * fosse um ponteiro para o verdadeiro objecto node
     * Isso assim ja poderias fazer neste metodo:
     *      *node (sim, com o asterisco!) = new_node;
     *
     *  Entendes porque?
     *
     */
	if (node == NULL) {
		node = new_node;
		node->next = NULL;
		return 1;
	}


/*
	int cmp = strcmp(new_node->entry->key , node->entry->key);

	if (cmp == 0) {
		node->entry->value = new_node->entry->value;
		return 1;		
	}

	if (cmp < 0) {
		new_node->next = node;
		node = node;
		return 1;		
	}

	if (cmp > 0) {
		find_place_to_insert (node->next , new_node);
	}
*/

	return 0;
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
	
	int i ;
	for (i=0 ; i <= list->size ; i++) {
		if (strcmp (list->header->entry->key , key) == 0)
			return list->header->entry;
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
