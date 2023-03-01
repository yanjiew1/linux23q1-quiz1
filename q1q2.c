#include "q1q2.h"
#include "list_sort.h"
#include "list.h"
#include <stdlib.h>

int cmpint(void *priv, const struct list_head *a, const struct list_head *b)
{
    const struct item *ia = list_entry(a, struct item, list);
    const struct item *ib = list_entry(b, struct item, list);
    return ia->i - ib->i;
}

int list_size(struct list_head *head)
{
    int count = 0;
    struct list_head *pos;
    list_for_each(pos, head) {
        count++;
    }
    return count;
}

void list_shuffle(struct list_head *head)
{
    int size = list_size(head);
    struct list_head **entries = malloc(sizeof(struct list_head *) * size);
    struct list_head *itm;
    int i = 0;

    list_for_each (itm, head)
        entries[i++] = itm;

    for (i = size - 1; i > 0; i--) {
        int n = rand() % i;
        struct list_head *tmp = entries[i];
        entries[i] = entries[n];
        entries[n] = tmp;
    }

    INIT_LIST_HEAD(head);
    for (i = 0; i < size; i++)
        list_add_tail(entries[i], head);

    free(entries);
}
