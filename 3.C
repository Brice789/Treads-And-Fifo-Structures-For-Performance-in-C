#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


// mon ordinateur possede 4 coeurs

#define SIZE_FIFO 8
#define NB_PROD 5 
#define NB_CONSO 7

pthread_mutex_t mutex;

// Structure Fifo 
struct fifo {
    int tab[SIZE_FIFO]; 
    int ptr_lecteur;    
    int ptr_ecrivain;   
    int nb_elem;        
} fifo;

struct fifo f;
// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) {
    for(int i = 0; i < SIZE_FIFO; i++){
        f->tab[i] = 0;
    }
    f->ptr_lecteur=0;
    f->ptr_ecrivain=0;
    f->nb_elem=0;
}

// Fonction permettant d'insérer une valeur dans la fifo
void put(struct fifo *f, int a) {
    if((f->ptr_ecrivain >= SIZE_FIFO)&&(f->tab[f->ptr_ecrivain] == 0)){
        f->tab[0] = a;
        f->ptr_ecrivain=1;
        ++(f->nb_elem);
    }

    else if(f->nb_elem < SIZE_FIFO) {
        f->tab[f->ptr_ecrivain] = a;
        ++(f->ptr_ecrivain);
        ++(f->nb_elem);
    }

    else {
        printf("Memoire saturée");
    }
}

// récupére une valeur depuis la fifo
int get(struct fifo *f) {
    int varReturn;
    if(f->nb_elem == 0){
        printf("La structure est vide\n");
        exit(0);
    }
    else {
        varReturn = f->tab[f->ptr_lecteur];
        f->tab[f->ptr_lecteur] = 0;
        f->ptr_ecrivain = f->ptr_lecteur;
        ++(f->ptr_lecteur);
        --(f->nb_elem);
    }
    if(f->ptr_lecteur >= SIZE_FIFO){
        f->ptr_lecteur = 0;
    }
    return varReturn;
}

// Prod
void *prod(void* arg) {
    pthread_mutex_lock(&mutex);
    int nRand = rand() % 100 + 1;
    printf("Prod, j'envoie %d\n", nRand);
    put(&f, nRand);
    pthread_mutex_unlock(&mutex);
    sleep(5);
    pthread_exit((void*)NULL);
}

// Fonction de consommation
void *conso(void* arg) {
    if (pthread_mutex_trylock(&mutex)) {
        int valProd = get(&f);
        printf("Conso, j'ai reçu %d\n", valProd);
        pthread_mutex_unlock(&mutex);
    }
    sleep(1);
    pthread_exit((void*)NULL);
}



// Fonction principale
int main() {
    srand(time(NULL)); 
    long i;
    pthread_t pidProd[NB_PROD];
    pthread_t pidConso[NB_CONSO];
    
    init_fifo(&f);
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NB_PROD; i++) {
        pthread_create(&pidProd[i], NULL, prod, NULL);
    }
    //sleep(5);
    for (i = 0; i < NB_CONSO; i++) {
        pthread_create(&pidConso[i], NULL, conso, NULL);
    }
    sleep(5);
    printf("Fin du thread principal\n");
    return EXIT_SUCCESS;
}
