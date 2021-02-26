#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>  
#include <time.h>

typedef struct __node {                   
    int value;
    struct __node *next;
    struct __node *prev;
} node_t;

static inline void list_make_node_t(node_t **head, node_t **tail, int value) {
    node_t *tmp;

    tmp = (node_t*)malloc(sizeof(node_t));

    if(!tmp)
        return;

    tmp->value = value;
    tmp->next = NULL;
    
    if(!*head) {
        tmp->prev = NULL;
        *head = tmp;
        *tail = tmp;
    } else {
        tmp->prev = *tail;
        (*tail)->next = tmp;
        *tail = tmp;
    }
}


static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

void quicksort(node_t *head, node_t *tail, int length)
{
    if (!head)
        return;
    
    node_t *beg[length];
    node_t *end[length], *L, *R;
    int i=0, piv;

    beg[0] = head;
    end[0] = tail;

    while (i >= 0) {
        L = beg[i];
        R = end[i];

        if( L != R && L && R) {
            piv = beg[i]->value;
            while (L != R) {
                while ( R->value >= piv && L != R )
                    R = R->prev;
                if (L != R) {
                    L->value = R->value;
                    L = L->next;
                } 
                while ( L->value <= piv && L != R )
                    L = L->next;
                if (L != R) {
                    R->value = L->value;
                    R->prev;
                }
            }
            L->value = piv;
            beg[i+1] = L->next;
            end[i+1] = end[i];
            end[i++] = L;
        } else {
            i--;
        }
    }
}

void list_free(node_t **list) {
    node_t *tmp;
    while(*list) {
        tmp = (*list)->next;
        free(*list);
        *list = tmp;
    }
}

int main(int argc, char **argv) {
    size_t count = 20;

    node_t *head = NULL, *tail = NULL;

    srand((unsigned int) time(NULL));
    while (count--)
        list_make_node_t(&head, &tail, rand() % 1024);

    list_display(head);
    quicksort(head, tail, 20);
    list_display(head);

    if (!list_is_ordered(head))
        return EXIT_FAILURE;

    list_free(&head);
    return EXIT_SUCCESS;
}