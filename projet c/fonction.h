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


// Structure pour le contact
typedef struct  {
    char *nom;
    char *prenom;
}Contact;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Structure pour l'heure
typedef struct {
    int heure;
    int minute;
} Heure;

//Structure pour les rendez-vous
typedef struct RendezVous_s {
    Date date;
    Heure debut;
    Heure duree;
    char *objet;
    struct RendezVous_s * next;
} RendezVous;

//structure pour l'objet du rendez-vous
typedef struct AgendaEntry_s{
    Contact contact;
    RendezVous * rendezVous;
    struct AgendaEntry_s ** suivant;
} AgendaEntry_t;

typedef struct Agenda_s {
    struct AgendaEntry_s ** head;
}Agenda;



int rechercheplus (int ,t_d_list  );
int rechercheclassique(int , t_d_list );
t_d_cell* createCell (int,int);
t_d_list* createList (int);
void insertList (t_d_list* , t_d_cell* );
void printList (t_d_list , int );
void printAllList(t_d_list);
void insertListOrdre(t_d_list*, t_d_cell*);
void dichotomie();
void scanstring(char * input, int max_length);
int comparerChaine(char * str1, char * str2);
AgendaEntry_t * createAgendaEntry(char * nom, char * prenom);
RendezVous * createRdv(Date d, Heure debut, Heure duree, char * objet);
void addRdvToContact(AgendaEntry_t * A, RendezVous * R);
void insertAgenda(Agenda * currentAgenda, AgendaEntry_t * newEntry);
void printAgenda (AgendaEntry_t *  A , int lvl);
void printAllAgenda(AgendaEntry_t * myAgenda);
#endif //PROJET_C_S3_FONCTION_H
