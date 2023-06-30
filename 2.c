#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NBR = 20;



long varGlobal = 0;

void* tache(void* arg){
    long i = (long)arg;
    sleep(1);

    printf("arg : %1d\n", i);
    varGlobal += i;

    //long * tmp = malloc(sizeof(long));
    //*tmp = i*10

    pthread_exit((void*)NULL);


}


int main(){
    long i;
    pthread_t pid[NBR];
    for (i = 0; i < NBR ; i++){
        pthread_create(&pid[i], NULL, tache, (void*)i);
    }
    for( i = 0; i<NBRRR; i++)
    {
        //long* val;
        pthread_join(pid[i], NULL);
        //printf("tache %id renvoyer %1d\n, i , *val")
    }
    print("valeur est %1d\n", varGlobal);
    return EXIT_SUCCESS;
}