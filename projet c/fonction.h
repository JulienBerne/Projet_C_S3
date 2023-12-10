#ifndef PROJET_C_S3_FONCTION_H
#define PROJET_C_S3_FONCTION_H

typedef struct s_d_cell {
    int value ;
    int lvl ;
    struct  s_d_cell** next;

}t_d_cell;

typedef struct s_d_list {
    t_d_cell** head;
    int lvlmax ;

}t_d_list;







int rechercheplus (int ,t_d_list  );
int rechercheclassique(int , t_d_list );
t_d_cell* createCell (int,int);
t_d_list* createList (int);
void insertList (t_d_list* , t_d_cell* );
void printList (t_d_list , int );
void printAllList(t_d_list);
void insertListOrdre(t_d_list*, t_d_cell*);
void dichotomie();

#endif //PROJET_C_S3_FONCTION_H
