#ifndef _Q1Q2_H
#define _Q1Q2_H

#include <stdint.h>
#include "list.h"
#include "list_sort.h"

struct item {
    uint16_t i;
    struct list_head list;
};

int cmpint(void *priv, const struct list_head *a, const struct list_head *b);
int list_size(struct list_head *head);
void list_shuffle(struct list_head *head);

void q1_sort(void *priv, struct list_head *head, list_cmp_func_t cmp);
void q2_sort(void *priv, struct list_head *head, list_cmp_func_t cmp);
void q2_sort_v1(void *priv, struct list_head *head, list_cmp_func_t cmp);

#endif
