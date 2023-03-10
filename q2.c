#include "list.h"
#include "list_sort.h"
#include "q1q2.h"
#define MAX_DEPTH 512

void q2_sort(void *priv, struct list_head *head, list_cmp_func_t cmp)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    struct list_head stack[MAX_DEPTH];
    for (int i = 0; i < MAX_DEPTH; i++)
        INIT_LIST_HEAD(&stack[i]);
    int top = -1;
    list_splice_init(head, &stack[++top]);

    struct list_head partition;
    INIT_LIST_HEAD(&partition);

    while (top >= 0) {
        INIT_LIST_HEAD(&partition);
        list_splice_init(&stack[top--], &partition);
        if (!list_empty(&partition) && !list_is_singular(&partition)) {
            struct list_head list_less, list_greater;
            INIT_LIST_HEAD(&list_less);
            INIT_LIST_HEAD(&list_greater);
            struct list_head *pivot = partition.next;
            list_del(pivot);
            INIT_LIST_HEAD(pivot);

            struct list_head *itm = NULL, *is = NULL;
            list_for_each_safe (itm, is, &partition) {
                list_del(itm);
                if (cmp(NULL, itm, pivot) < 0)
                    list_move(itm, &list_less);
                else
                    list_move(itm, &list_greater);
            }

            list_move_tail(pivot, &list_less);
            if (!list_empty(&list_greater))
                list_splice_tail(&list_greater, &stack[++top]);
            if (!list_empty(&list_less))
                list_splice_tail(&list_less, &stack[++top]);
        } else {
            top++;
            list_splice_tail(&partition, &stack[top]);
            while (top >= 0 && list_is_singular(&stack[top])) {
                struct list_head *tmp = stack[top].next;
                list_del(tmp);
                INIT_LIST_HEAD(&stack[top--]);
                list_add_tail(tmp, head);
            }
        }
    }
}

void q2_sort_v1(void *priv, struct list_head *head, list_cmp_func_t cmp)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    /* The stack top */
    struct list_head *top = head->next;
    /* Convert to a null-terminated singly-linked list. */
    head->prev->next = NULL;
    top->prev = NULL;
    INIT_LIST_HEAD(head);

    while (top) {
        /* Pop from the stack */
        struct list_head *pivot = top;
        top = top->prev;
        if (!pivot->next) {
            list_add_tail(pivot, head);
            continue;
        }

        struct list_head *less = NULL, *greater = pivot->next;
        struct list_head **indirect = &greater;
        struct list_head **tail = &less;
        pivot->next = NULL;

        /* Walk through the list and partition */
        while (*indirect) {
            struct list_head *node = *indirect;
            if (cmp(priv, pivot, node) <= 0) {
                indirect = &(*indirect)->next;
                continue;
            }
            /* Move to less list */
            *indirect = node->next;
            *tail = node;
            node->next = NULL;
            tail = &node->next;
        }

        /* Put pivot at the end of less list */
        *tail = pivot;
        /* Push greater and less list into stack */
        if (greater) {
            greater->prev = top;
            less->prev = greater;
            top = less;
        } else {
            less->prev = top;
            top = less;
        }
    }
}
