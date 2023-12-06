#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main() {

    //t_d_cell *mycell = createCell(2, 6);
    //t_d_cell *newcell = createCell(5, 5);

    //insertList(mylist, mycell);
    //insertList(mylist, newcell);
    int N = 3;
    t_d_list *mylist = createList(N);
    int tabval[(1<<N) - 1];
    tabval[0]= 6;
    tabval[1]= 3;
    tabval[2]= 5;
    tabval[3]= 2;
    tabval[4]= 3;
    tabval[5]= 0;
    tabval[6]= 1;
    dichotomie(mylist, tabval);

    printAllList(*mylist);
    int recherche = rechercheclassique(5, *mylist);
    printf("%d\n",recherche);

    recherche =rechercheplus (7,*mylist);
    printf("%d\n",recherche);



    return 0;
}





