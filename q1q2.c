#include "q1q2.h"
#include "list_sort.h"
#include "list.h"

int cmpint(void *priv, const struct list_head *a, const struct list_head *b)
{
    const struct item *ia = list_entry(a, struct item, list);
    const struct item *ib = list_entry(b, struct item, list);
    return ia->i - ib->i;
}
