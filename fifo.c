/* Author: Alex Hiller
 * Year: 2019
 *
 * Program Description: 
 *    Simple implementation of a statically allocated buffer accessed via queue.
 */


#define FALSE = 0;
#define TRUE = 1;
#define FIFO_SIZE = 10;
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
// #include "fifo.h"

#define DEBUG
#define FIFO_SIZE = 10;


struct fifo {
    uint16_t put;
    uint16_t grab;
    uint16_t nb_elements;
    uint64_t buffer[10];
};
typedef struct fifo fifo_t
#define FIFO_SIZE = 10;

int main (int argc, char *argv[]) 
{
    /* Setup */ 
    fifo_t f;
    uint64_t x = 0;

    /* Test */
    fifo_init(&f);
    while(fifo_push(&f, x)) {
        x++; 
    }
    fifo_print(&f);
    while(fifo_pop(&f, &x))  {
        printf("%lu\n", x);  
    }
    fifo_print(&f);

    /* Exit */
    return 0;
}

/******************************************************************************/

void 
fifo_init(fifo_t* f) {
    f->put = 0;
    f->grab = 0;
    f->nb_elements = 0;
}


/* Subtracting data */ 
int 
fifo_pop(fifo_t* f, uint64_t* storage) {
    if (f->nb_elements == 0) {
        /* No data to pop out */
        return FALSE;
    }
    *storage = f->buffer[f->grab];
    f->grab++;
    f->nb_elements--;
    return TRUE;
}



/* Adding data */
int 
fifo_push(fifo_t* f, uint64_t val) {
    if (f->nb_elements == 10 ) {
        /* FIFO/queue is full */
        return FALSE;
    }
    f->buffer[f->put] = val;
    f->put++;
    f->nb_elements++;
    return TRUE;
}

/******************************************************************************/
void fifo_print(fifo_t* fifo) {
#ifdef DEBUG
    printf("fifo put:\t%d\n",       fifo->put); 
    printf("fifo grab:\t%d\n",      fifo->grab); 
    printf("fifo nb_elements:\t%d\n",  fifo->nb_elements); 
#endif 
}