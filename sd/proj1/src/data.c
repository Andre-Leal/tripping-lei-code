#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

struct data_t *data_create(int size) {
    void *raw_data = malloc(size);
    return data_create2(size, raw_data);
}

struct data_t *data_create2(int size, void *data) {
    struct data_t *new_data;
    new_data = (struct data_t *) malloc(sizeof(struct data_t));
    new_data->datasize = size;
    new_data->data = data;

    return new_data;
}

void data_destroy(struct data_t *data) {
    free(data->data);
    free(data);
}

struct data_t *data_dup(struct data_t *data) {
    void *new_raw_data = malloc(data->datasize);
    memcpy(new_raw_data, data->data, data->datasize);

    struct data_t *new_data = data_create2(data->datasize, new_raw_data);

    return new_data;
}
