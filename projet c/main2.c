#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int max_length = 100;

int main() {

    char buffer[max_length];
    //t_d_cell *mycell = createCell(2, 6);
    //t_d_cell *newcell = createCell(5, 5);

    //insertList(mylist, mycell);
    //insertList(mylist, newcell);
    int N = 7;
    int var=100000;
    int len = (1<<N) - 1; // 2^N - 1
    t_d_list *mylist = createList(N);
    int tabval[len];

    for (int i=0; i< len; i++){
        tabval[i]= rand() % len;
    }



    dichotomie(mylist, tabval);

    printAllList(*mylist);
    int recherche ;
    printf("mesure temps rechercheplus N=%d , nombre d'iteration %d\n",N,var);
    startTimer();
    for (int i=0;i<var;i++) {
        int n = rand() % len;
        recherche +=rechercheplus (n,*mylist);
        //printf("%d\n",recherche);
    }
    stopTimer();
    displayTime();
    printf("mesure temps recherche classique N=%d , nombre d'iteration %d\n",N,var);
    startTimer();
    for (int i=0;i<var;i++) {
        int n = rand() % len;
        recherche +=rechercheclassique(n,*mylist);
        //printf("%d\n",recherche);
    }
    stopTimer();
    displayTime();

    return 0;
}




