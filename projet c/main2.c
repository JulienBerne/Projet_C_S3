#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>

int max_length = 100;

int main() {

    char buffer[max_length];
    //t_d_cell *mycell = createCell(2, 6);
    //t_d_cell *newcell = createCell(5, 5);

    //insertList(mylist, mycell);
    //insertList(mylist, newcell);
    int N = 3;
    t_d_list *mylist = createList(N);
    int tabval[(1<<N) - 1];
    tabval[0]= 6;
    tabval[1]= 0;
    tabval[2]= 1;
    tabval[3]= 4;
    tabval[4]= 3;
    tabval[5]= 2;
    tabval[6]= 5;
    dichotomie(mylist, tabval);

    printAllList(*mylist);
    int recherche = rechercheclassique(5, *mylist);
    printf("%d\n",recherche);

    for (int i=0;i<10;i++) {
        int n = rand() % ((1<<N) - 1);
        recherche =rechercheplus (n,*mylist);
        printf("%d\n",recherche);
    }

    exit(1);
    scanstring(buffer, max_length);
    printf("Chaîne de caractères lue : %s, longeur = %d\n", buffer, strlen(buffer));

    //char chaine1[100];
    //char chaine2[100];
    //strcpy(chaine2, "ewenbernard");
    //strcpy(chaine1, "yoannernard");
    //int val = comparerChaine(chaine1, chaine2);
    //printf("comparaison = %d\n", val);
    //Agenda * myAgenda = createAgenda();
    //AgendaEntry_t * myAgenda1 = createAgendaEntry("yoann", "bernard");
    //AgendaEntry_t * myAgenda2 = createAgendaEntry("ewen", "bernard");
    //AgendaEntry_t * myAgenda3 = createAgendaEntry("pierre", "bernard");
    //printf("first\n");
    //insertAgenda(myAgenda, myAgenda1);
    //printf("first2\n");
    //printAllAgenda(myAgenda);
    //printf("second\n");
    //insertAgenda(myAgenda, myAgenda2);
    //printAllAgenda(myAgenda);
    //printf("third\n");
    //insertAgenda(myAgenda, myAgenda3);
    //printAllAgenda(myAgenda);

    return 0;
}





