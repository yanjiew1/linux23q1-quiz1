#include <stdio.h>
#include <stdlib.h>
#include "cpucycles.h"
#include "list.h"
#include "q1q2.h"

static void insert_test_data(struct list_head *head)
{
    struct item *itm = NULL;
    for (int i = 0; i < 100000; i++) {
        itm = malloc(sizeof(struct item));
        itm->i = rand();
        list_add_tail(&itm->list, head);
    }
}

int cmp(void *priv, const struct list_head *a, const struct list_head *b)
{
    const struct item *ia = list_entry(a, struct item, list);
    const struct item *ib = list_entry(b, struct item, list);
    return ia->i - ib->i;
}

uint64_t q1_sort_time()
{
    LIST_HEAD(list);
    insert_test_data(&list);
    uint64_t start = cpucycles();
    q1_sort(&list);
    uint64_t end = cpucycles();
    return end - start;
}

uint64_t q2_sort_time()
{
    LIST_HEAD(list);
    insert_test_data(&list);
    uint64_t start = cpucycles();
    q2_sort(&list);
    uint64_t end = cpucycles();
    return end - start;
}

uint64_t q2_sort_v1_time()
{
    LIST_HEAD(list);
    insert_test_data(&list);
    uint64_t start = cpucycles();
    q2_sort_v1(NULL, &list, cmp);
    uint64_t end = cpucycles();
    return end - start;
}

#define NUM_TESTS 100

int main(void)
{
    double q1 = 0, q2 = 0, q2_v1 = 0;

    for (int i = 0; i < NUM_TESTS; i++) {
        q1 += q1_sort_time();
        q2 += q2_sort_time();
        q2_v1 += q2_sort_v1_time();
    }

    q1 /= NUM_TESTS;
    q2 /= NUM_TESTS;
    q2_v1 /= NUM_TESTS;

    printf("Average Time for q1: %.2f\n", q1);
    printf("Average Time for q2: %.2f\n", q2);
    printf("Average Time for q2_v1: %.2f\n", q2_v1);

    return 0;
}
