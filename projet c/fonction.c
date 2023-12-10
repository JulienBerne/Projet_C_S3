#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>

int rechercheplus(int val, t_d_list mylist) {
    //printf("Demarrage recherche plus sur valeur = %d\n", val);
    if (mylist.head[0] == NULL) {
        // La liste est vide, on sort
        return 0;
    } else {
        t_d_cell* mycell;
        t_d_cell* prevcell;
        t_d_cell* tmpcell;
        int i = mylist.lvlmax;
        // Au début trouver le premier niveau de liste non vide
        do {
            i--;
            mycell = mylist.head[i];
        } while (mycell == NULL);
        //printf("mycell non null\n");
        prevcell = mycell;
        int sortie=0;
        int trouver = 0;
        while (sortie == 0) {
            //printf("debut boucle curVal = %d\n", mycell->value);
            if (mycell->value == val) {
                trouver = 1; // Valeur trouvée
                sortie = 1; // On sort;
            } else if (mycell->value < val) {
                if (mycell->next[i] == NULL) {
                    if (i == 0) {
                        // on a rien trouvé sur cette ligne et on est sur la dernière ligne => On sort
                        sortie = 1;
                    } else {
                        // on est a la fin de la liste
                        do {
                            // On descend jusqu'a trouver une cellule disponible a un niveau inférieure pour continuer la recherche
                            i--;
                        } while ((mycell->next[i] == NULL)&&(i>0));
                        prevcell = mycell;
                        mycell = mycell->next[i];
                        if (mycell == NULL)
                            // Si la cellule est vide on était a la fin de liste sur tout les niveaux. On sort
                            sortie = 1;
                    }
                } else {
                    // On avance sur la même ligne
                    prevcell = mycell;
                    mycell = mycell->next[i];
                }
            } else if (mycell->value > val) {
                if (i == 0) {
                    // On a pas trouvé dans tout les niveaux de la liste. On sort
                    sortie = 1;
                } else {
                    // on descend au niveau inférieur à partir de la cellule précédente
                    tmpcell = mycell;
                    if (mycell == mylist.head[i]) {
                        // cas particulier de la cellule en tête de la liste
                        i--;
                        mycell = mylist.head[i];
                    }  else {
                        i--;
                        mycell = prevcell->next[i];
                    }
                    prevcell=tmpcell;
                }
            }
        }
        return trouver;
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
        newlist->head[i] = NULL; // Initialisation des pointeurs à NULL
    }
    return newlist;
}

void insertList(t_d_list* mylist, t_d_cell* newcell) {
    for (int i = 0; i < newcell->lvl; i++) {
        newcell->next[i] = NULL; // Initialisation des pointeurs à NULL
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

// Les autres fonctions restent inchangées mais peuvent nécessiter des corrections similaires

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

    // on chaine les cellules par orde croissant de valeurs
    for (i=0;i<len;i++) {
        if ((tabval[i]>len) || (tabval[i] <0)) {
            lvl = 0;
        } else {
            lvl = tab[tabval[i]]+1;
        }
        printf("[dichotomie] createCell val=%d, lvl = %d\n", tabval[i], lvl);
        t_d_cell * mycell = createCell(tabval[i], tab[tabval[i]] + 1);
        insertListOrdre(myListHead,mycell);
    }

}















