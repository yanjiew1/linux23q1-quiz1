#include <stdint.h>
#include "list.h"
#include "list_sort.h"
#include "q1q2.h"

void q1_sort(void *priv, struct list_head *head, list_cmp_func_t cmp)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    struct list_head list_less, list_greater;
    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    struct list_head *pivot = head->next;
    list_del(pivot);

    struct list_head *itm = NULL, *is = NULL;
    list_for_each_safe (itm, is, head) {
        if (cmp(NULL, itm, pivot) < 0)
            list_move(itm, &list_less);
        else
            list_move(itm, &list_greater);
    }

    q1_sort(NULL, &list_less, cmp);
    q1_sort(NULL, &list_greater, cmp);

    list_add(pivot, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}
