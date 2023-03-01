#ifndef _Q1Q2_H
#define _Q1Q2_H

#include "list.h"
#include "list_sort.h"
#include <stdint.h>

struct item {
    uint16_t i;
    struct list_head list;
};

static inline int cmpint(const void *p1, const void *p2)
{
    const uint16_t *i1 = (const uint16_t *) p1;
    const uint16_t *i2 = (const uint16_t *) p2;
    return *i1 - *i2;
}

void q1_sort(struct list_head *head);
void q2_sort(struct list_head *head);
void q2_sort_v1(void *priv, struct list_head *head, list_cmp_func_t cmp);

#endif
