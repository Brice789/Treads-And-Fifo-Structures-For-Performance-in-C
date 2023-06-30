#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE_FIFO 8
#define NB_PROD 1
#define NB_CONSO 1
#define FALSE = 0
#define TRUE = 1

// Structure Fifo communication entre consommateurs et producteurs
struct fifo {
    uint64_t tab[SIZE_FIFO]; // Tableau d'éléments stockés
    int ptr_lecteur;    // Index de la prochaine case à lire
    int ptr_ecrivain;   // Index de la prochaine case à écrire
    int nb_elem;        // Nombre d'éléments présents dans la fifo
} fifo;

// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) 
{
f->ptr_lecteur  = 0;
f->ptr_ecrivain  =0;
f->nb_elem       =0;
}

// Fonction permettant d'insérer une valeur dans la fifo
void put(struct fifo *f, int a) 
{

  if (f->ptr_ecrivain == SIZE_FIFO) {
        /* FIFO/queue is full */
        return FALSE;
    }
    f-> tab[f->ptr_lecteur] = NB_CONSO;
    f->ptr_lecteur++;
    f->nb_elem++;
    return 1;
}



// Fonction permettant de récupérer une valeur depuis la fifo
//can add value from the fifo
int get(struct fifo *f,uint64_t* storage ) 
{
    if (f->nb_elem == 0) {
        /* No data to pop out */
        return 0;
    }
    *storage = f->tab[f->ptr_ecrivain];
    f->ptr_ecrivain++;
    f->nb_elem--;
    return 1;
}


// Fonction de production
void* prod(void* arg) {
    printf("Hello ? \n");
    for (;;) {
        // if (pthread_mutex_trylock(&mutex)) {
            // if (work > 0) {
            //     travail -= 10;
            //     printf("work take : %d\n", travail);
            // }
            // else {
            //     printf("POLLING\n");
            // }
            // pthread_mutex_unlock(&mutex);
        // }   
        sleep(1);
    }
    pthread_exit(NULL);
}




// Fonction of consomation. Each thread take 10 for exemple
void *conso(void* arg) 
{
    printf("Bonjour patron \n");
   // for (;;) 
}


// Fonction principale
//main fonction

int main() {
	init_fifo(&fifo)
    long i;
    pthread_t prod_id;
    pthread_t conso_id[NB_CONSO];
    

    // pthread_mutex_init(&mutex, NULL);
    // pthread_cond_init(&cond, NULL);
    
    pthread_create(&prod_id, NULL, prod, NULL);
    for (int i = 0; i < NB_CONSO; i++) {
        pthread_create(&conso_id[i], NULL, conso, (void*)&fifo);
    }
    
    pthread_exit(NULL);
}