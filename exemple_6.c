#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_TRAVAILLEUR 4

int travail;
pthread_mutex_t mutex;

void* travailleur(void* arg) {
    printf("hello you \n");
    for (int i=0; i<5; i++) {
        
        if (pthread_mutex_trylock(&mutex)) {
            if (travail > 0) {
                travail += travail*10;
                printf("Variable Global : %d\n", travail);
            }
            else {
                printf("Ma Variable Global Est 1948718200 ");
                exit(NULL);
            }
            pthread_mutex_unlock(&mutex);
        }
        sleep(1);
    }
    pthread_exit(NULL);
         
}

void* patron(void* arg) {
    printf("Hey Him \n");
      if (travail < 1948717100)
    {
    for (int i=0; i<5; i++) {
        pthread_mutex_lock(&mutex);
        travail += 100;
        printf("work produce from him: %d\n", travail);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
    }
}

int main() {
    if (travail < 1900)
    {

   
    pthread_t patron_id;
    pthread_t travailleur_id[NB_TRAVAILLEUR];
    
    travail = 0;

    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&patron_id, NULL, patron, NULL);
    for (int i = 0; i < NB_TRAVAILLEUR; i++) {
        pthread_create(&travailleur_id[i], NULL, travailleur, NULL);
    }
    for(;;);
    }
    else{
        printf("variable global est 1964823300 ");
    }
}



// Write the following program: The main task creates N tasks and passes the order of its creation as a parameter 
// to each task (the first task will have the number 0, the next 1, etc.). 

// The N tasks display the number passed as an argument then return this value multiplied by 10 to the main task. 
// The main task waits for the completion of the N tasks and displays the N returned values.