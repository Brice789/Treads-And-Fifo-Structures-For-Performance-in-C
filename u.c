#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define SIZE_FIFO 8
#define NB_PROD 1
#define NB_CONSO 1




// Structure Fifo communication entre consommateurs et producteurs
struct fifo {
    int tab[SIZE_FIFO]; // Tab d'éléments stockés
    int ptr_lecteur;    // Prochaine case à lire
    int ptr_ecrivain;   // ______ à écrire
    int nb_elem;        // Nombre d'éléments présents dans la fifo
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

// Fonction permettant de récupérer une valeur depuis la fifo
int get(struct fifo *f) {
    int varReturn;
    if(f->nb_elem == 0){
        printf("La structure est vide");
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

// prod
void *prod(void* arg) {
    int nRand = rand() % 100 + 1;
    sleep(1);
    printf("[Producteur], j'envoie %d\n", nRand);
    put(&f, nRand);
    pthread_exit((void*)NULL);
}

// Conso
void *conso(void* arg) {
    int valProd = get(&f);
    sleep(1);
    printf("[Consommateur], j'ai reçu %d\n", valProd);
    pthread_exit((void*)NULL);
}




// Fonction principale
int main() {
    long i;
    pthread_t pidProd[NB_PROD];
    pthread_t pidConso[NB_CONSO];

    init_fifo(&f);

    for (i = 0; i < NB_PROD; i++) {
        pthread_create(&pidProd[i], NULL, prod, NULL);
    }
    sleep(5);
    for (i = 0; i < NB_CONSO; i++) {
        pthread_create(&pidConso[i], NULL, conso, NULL);
    }
    sleep(5);
    printf("Fin du thread principal\n");
    return EXIT_SUCCESS;
}
