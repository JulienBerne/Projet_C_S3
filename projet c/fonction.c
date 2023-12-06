#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>





int rechercheplus(int val, t_d_list mylist) {
    if (mylist.head[0] == NULL) {
        return 0;
    } else {
        int i = mylist.lvlmax - 1;

        while (i >= 0) {
            t_d_cell* mycell = mylist.head[i];

            while (mycell != NULL) {
                if (mycell->value == val) {
                    return 1; // Valeur trouvée
                } else if (mycell->value < val) {
                    mycell = mycell->next[i]; // Avancer dans le niveau actuel
                } else {
                    break; // Arrêter la recherche si la valeur actuelle est supérieure à la valeur recherchée
                }
            }

            i--; // Descendre au niveau inférieur
        }

        return 0; // Valeur non trouvée
    }
}

int rechercheclassique(int val, t_d_list mylist) {
    if (mylist.head[0] == NULL) {
        return 0;
    } else {
        int trouver = 0;
        t_d_cell* mycell = mylist.head[0];
        while (mycell != NULL && mycell->value <= val && trouver != 1) {
            if (mycell->value == val) {
                trouver = 1;
            } else {
                mycell = mycell->next[0];
            }
        }
        return trouver;
    }
}



t_d_cell* createCell(int val, int lvl) {
    t_d_cell* newcell = (t_d_cell*)malloc(sizeof(t_d_cell));
    newcell->value = val;
    newcell->lvl = lvl;
    newcell->next = (t_d_cell**)malloc(sizeof(t_d_cell*) * lvl);
    int i;
    for (int i=0;i<lvl;i++)
        newcell->next[i]=NULL;
    return newcell;
}

t_d_list* createList(int val) {
    t_d_list* newlist = (t_d_list*)malloc(sizeof(t_d_list));

    newlist->lvlmax = val;
    newlist->head = (t_d_cell**)malloc(sizeof(t_d_cell*) * val);

    for (int i = 0; i < val; i++) {
        newlist->head[i] = NULL;
    }
    return newlist;
}

void insertList(t_d_list* mylist, t_d_cell* newcell) {
    for (int i = 0; i < newcell->lvl; i++) {
        newcell->next[i] = NULL;
    }

    if (mylist->head[0] == NULL) {
        for (int i = 0; i < newcell->lvl; i++) {
            mylist->head[i] = newcell;
        }
    } else {
        for (int i = 0; i < newcell->lvl; i++) {
            newcell->next[i] = mylist->head[i];
            mylist->head[i] = newcell;
        }
    }
}



void printList (t_d_list mylist , int lvl) {
    t_d_cell* next= mylist.head[lvl] ;
    while (next != NULL) {
        printf("--> [ %d |@ ] ", next->value);
        next = next->next[lvl];
    }
    printf("-->NULL\n");

    return;
}

void printAllList(t_d_list mylist) {
    for (int i = 0 ; i<mylist.lvlmax; i++){
        printf("[list head_%d @-]",i);
        printList(mylist,i);
    }
    return;
}

void insertListOrdre(t_d_list* mylist, t_d_cell* newcell) {
    t_d_cell * myCell;
    t_d_cell * prev;
    int i;
    for (i=0;i<newcell->lvl;i++) {
        if (mylist->head[i] == NULL) {
            // la liste est vide pour ce niveau
            mylist->head[i]=newcell;
        } else {
            myCell = mylist->head[i];
            prev = mylist->head[i];
            // on recherche la premiere cellule qui a une valeur superieure a la nouvelle cellule
            // on arrete la recherche en fin liste pour ce niveau
            while((myCell->value <= newcell->value) && (myCell->next[i] != NULL)) {
                prev = myCell;
                myCell = myCell->next[i];
            }
            if (myCell->value > newcell->value) {
                // inserer avant la cellule
                // on verifie si on sur la premiere cellule de la liste
                if (myCell == mylist->head[i]) {
                    newcell->next[i]= myCell;
                    mylist->head[i] = newcell;
                } else {
                    newcell->next[i]= prev->next[i];
                    prev->next[i] = newcell;
                }
            } else if (myCell->next[i] == NULL) {
                // on est a la fin de la liste pour ce niveau
                // inserer apres la cellule
                myCell->next[i] = newcell;
            }
        }
    }
}

void dichotomie(t_d_list * myListHead , int * tabval){
    int i,j;
    int lvl = myListHead->lvlmax;
    int len = (1<<lvl)-1;
    int tab[len];
    // Creation du tableau de profondeur de cellule
    for (i=0;i<len;i++)
        tab[i] = 0;

    for (i=1;i<lvl;i++) {
      for (j=(1<<i);j<len;j=j+(1<<i)) {
          tab[j-1]++;
      }
    }

    for (i=0;i<len;i++) {
        printf("[dichotomie] createCell val=%d, lvl = %d\n", len-i, tab[i]+1);
        t_d_cell * mycell = createCell(tabval[i], tab[i] + 1);
        insertListOrdre(myListHead,mycell);

    }

}