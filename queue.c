/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* initialize the queue */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *tmp;
    while (q->head != NULL) {  // next element
        tmp = q->head;
        q->head = tmp->next;
        free(tmp->value);  // strdup()
        free(tmp);
    }
    /* nodes all freed */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    /* set the element */
    newh->value = strdup(s);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    newh->next = q->head;
    /* maintain the queue */
    q->head = newh;
    if (q->tail == NULL)  // same element
        q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    /* set the element */
    newt->value = strdup(s);
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    newt->next = NULL;
    /* maintain the queue */
    if (q->head == NULL)  // same element
        q->head = newt;
    else
        q->tail->next = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q->head == NULL)
        return false;
    /* pop the element */
    memset(sp, (int) '\0', bufsize);
    strncpy(sp, q->head->value, bufsize - 1);
    free(q->head->value);
    /* maintain the queue */
    list_ele_t *tmp = q->head;
    q->head = tmp->next;
    free(tmp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue.
  No effect if q is NULL or empty.
  This function should not allocate or free any list elements.
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL)
        return;
    /*
    start from head to tail
    link current(head) and prev then jump to next
    */
    list_ele_t *newt = q->head;
    list_ele_t *prev = NULL;
    while (q->head != NULL) {
        list_ele_t *next = q->head->next;
        q->head->next = prev;
        prev = q->head;
        q->head = next;
    }
    q->head = prev;  // prevent NULL
    q->tail = newt;  // origin head

    /* start from tail to head */
    /*
    list_ele_t *newh = q->tail;
    while (q->tail != q->head) {
        list_ele_t *tmp = q->head;
        while (tmp->next != q->tail)
            tmp = tmp->next;
        q->tail->next = tmp;    // reverse the link of tail
        q->tail = tmp;
    }
    q->head->next = NULL;
    q->head = newh; // origin tail
    */
}
