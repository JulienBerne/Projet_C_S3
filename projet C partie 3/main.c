#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions des structures pour un contact et un rendez-vous
//biblio fonction.h
typedef struct {
    int jour;        // Jour du rendez-vous
    int mois;        // Mois du rendez-vous
    int annee;       // Annee du rendez-vous
    int heure;       // Heure du rendez-vous
    int minute;      // Minute du rendez-vous
    int dureeHeures; // Duree du rendez-vous en heures
    int dureeMinutes;// Duree du rendez-vous en minutes
    char *objet;     // Objet ou description du rendez-vous
} RendezVous;
typedef struct RendezVousNode {
    RendezVous rdv;
    struct RendezVousNode *suivant;
} RendezVousNode;

typedef struct Contact {
    char *nom;
    char *prenom;
    RendezVousNode *rendezVous; // Liste des rendez-vous du contact
    struct Contact *suivant;    // Pointeur vers le contact suivant dans la liste chainee
} Contact;

Contact *listeContacts = NULL; // Liste des contacts

char *scanString() { //lit une ligne de texte de, supprime le saut de ligne a la fin et alloue un espace memoire juste assez grand pour stocker la chaine lue
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }
    size_t taille = strlen(buffer);
    if (taille > 0 && buffer[taille - 1] == '\n') {
        buffer[taille - 1] = '\0'; // Supprimer le saut de ligne en marquant avec '/0' la fin de la chaine de caractere(renvoie caractere NULL)
    }
    char *str = malloc(taille);
    if (str != NULL) {
        strcpy(str, buffer);
    }
    return str;
}

void chargerContacts() {
    FILE *fichier = fopen("Contact.txt", "r");
    char ligne[100]; // Pour stocker chaque ligne du fichier

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        Contact *nouveauContact = (Contact *)malloc(sizeof(Contact));
        if (nouveauContact == NULL) {
            perror("Erreur d'allocation memoire");
            return;
        }

        char *nom = strtok(ligne, " \n"); // Separe le nom
        char *prenom = strtok(NULL, " \n"); // Separe le prenom

        if (nom != NULL) {
            nouveauContact->nom = strdup(nom); // Duplique le nom
        } else {
            nouveauContact->nom = NULL;
        }

        if (prenom != NULL) {
            nouveauContact->prenom = strdup(prenom); // Duplique le prenom
        } else {
            nouveauContact->prenom = NULL;
        }

        // Ajouter le nouveau contact a la liste
        nouveauContact->suivant = listeContacts;
        listeContacts = nouveauContact;
    }

    fclose(fichier);
}

void afficherContacts() {
    Contact *actuel = listeContacts;
    while (actuel != NULL) {
        printf("Nom: %s, Prenom: %s\n", actuel->nom, actuel->prenom);
        actuel = actuel->suivant;
    }
}

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

//Biblio fonction.c

void afficherResultatsRecherche(const char *recherche) {
    Contact *actuel = listeContacts;
    int trouve = 0; // Indicateur pour savoir si on a trouve des resultats

    while (actuel != NULL) {
        if (strncmp(actuel->nom, recherche, strlen(recherche)) == 0) {
            printf("Nom: %s, Prenom: %s\n", actuel->nom, actuel->prenom);
            trouve = 1;
        }
        actuel = actuel->suivant;
    }

    if (!trouve) {
        printf("Aucun contact trouve pour '%s'\n", recherche);
    }
}

void rechercherContact() {
    char recherche[100] = {0}; // Tableau pour stocker le nom recherche
    int index = 0; // Index pour le tableau de recherche

    printf("Entrez le nom du contact (caractere par caractere) :\n");

    // Boucle pour la saisie caractere par caractere
    while (index < (sizeof(recherche) - 1)) {
        viderBuffer(); // Vider le buffer d'entree avant de commencer la saisie
        char c = getc(stdin); // Lire un caractere depuis l'entree standard

        // Si l'utilisateur appuie directement sur Entree, terminer la fonction
        if (c == '\n') {
            printf("\n Fin de la recherche \n");
            return;
        }
        // Ignorer les caracteres espace vide ' '
        if (c <= ' ') {
            continue;
        }

        recherche[index++] = c; // Ajouter le caractere a la recherche
        recherche[index] = '\0'; // S'assurer que la chaine est terminee par un caractere nul

        // Completion automatique apras la saisie de 3 caracteres ou plus
        if (index >= 3) {
            printf("\nResultats pour '%s' :\n", recherche);
            afficherResultatsRecherche(recherche);
        }
    }
}
//void afficherRendezVous();

Contact *creerContactPourRendezVous(const char *nom, const char *prenom) {
    Contact *nouveauContact = (Contact *)malloc(sizeof(Contact));
    if (nouveauContact == NULL) {
        perror("Erreur d'allocation memoire");
        return NULL;
    }

    nouveauContact->nom = strdup(nom);
    nouveauContact->prenom = strdup(prenom);
    nouveauContact->suivant = listeContacts;
    nouveauContact->rendezVous = NULL; // Initialiser la liste de rendez-vous a NULL
    listeContacts = nouveauContact;

    printf("Contact '%s %s' ajoute avec succes.\n", nom, prenom);
    return nouveauContact;
}
void creerContact() {
    char nom[50]; // Tableau pour stocker le nom
    char prenom[50]; // Tableau pour stocker le prenom

    // Demander a l'utilisateur de saisir le nom et le prenom du contact
    printf("Entrez le nom du contact : ");
    scanf("%s", nom); // Lire le nom
    printf("Entrez le prenom du contact : ");
    scanf("%s", prenom); // Lire le prenom

    // Creer un nouveau contact
    Contact *nouveauContact = (Contact *)malloc(sizeof(Contact));
    if (nouveauContact == NULL) {
        perror("Erreur d'allocation memoire");
        return;
    }

    nouveauContact->nom = strdup(nom); // Dupliquer le nom
    nouveauContact->prenom = strdup(prenom); // Dupliquer le prenom

    // Ajouter le nouveau contact a la liste
    nouveauContact->suivant = listeContacts;
    listeContacts = nouveauContact;

    printf("Contact '%s %s' ajoute avec succ�s.\n", nom, prenom);
}


Contact *rechercherContactDansListe(const char *nom, const char *prenom) {
    Contact *actuel = listeContacts;
    while (actuel != NULL) {
        if (strcmp(actuel->nom, nom) == 0 && strcmp(actuel->prenom, prenom) == 0) {
            return actuel;
        }
        actuel = actuel->suivant;
    }
    return NULL;
}


void ajouterRendezVousAuContact(Contact *contact, RendezVous rdv)  {
    RendezVousNode *nouveauRdvNode = (RendezVousNode *)malloc(sizeof(RendezVousNode));
    if (nouveauRdvNode == NULL) {
        perror("Erreur d'allocation memoire");
        return;
    }

    nouveauRdvNode->rdv = rdv;
    nouveauRdvNode->suivant = contact->rendezVous;
    contact->rendezVous = nouveauRdvNode;
}

void creerRendezVous() {
    char nom[50], prenom[50];
    RendezVous rdv;

    printf("Nom du contact pour le rendez-vous : ");
    scanf("%s", nom);
    printf("Prenom du contact pour le rendez-vous : ");
    scanf("%s", prenom);

    Contact *contact = rechercherContactDansListe(nom, prenom);
    if (contact == NULL) {
        contact = creerContactPourRendezVous(nom, prenom);
        if (contact == NULL) {
            printf("Erreur de creation du contact.\n");
            return;
        }
    }
    printf("Entrez la date du rendez-vous (JJ MM AAAA) : ");
    scanf("%d %d %d", &rdv.jour, &rdv.mois, &rdv.annee);
    viderBuffer();
    printf("Entrez l'heure du rendez-vous (HH MM) : ");
    scanf("%d %d", &rdv.heure, &rdv.minute);
    viderBuffer();
    printf("Entrez la duree du rendez-vous (HH MM) : ");
    scanf("%d %d", &rdv.dureeHeures, &rdv.dureeMinutes);
    viderBuffer();
    printf("Objet du rendez-vous : ");
    rdv.objet = scanString();
    viderBuffer();

    ajouterRendezVousAuContact(contact, rdv);
    printf("Rendez-vous ajoute.\n");
}

void afficherRendezVousDUnContact() {
    char nom[50], prenom[50];

    printf("Entrez le nom du contact : ");
    scanf("%s", nom);
    printf("Entrez le prenom du contact : ");
    scanf("%s", prenom);

    Contact *contact = rechercherContactDansListe(nom, prenom);
    if (contact == NULL) {
        printf("Contact non trouve.\n");
        return;
    }

    if (contact->rendezVous == NULL) {
        printf("Aucun rendez-vous pour %s %s.\n", nom, prenom);
    } else {
        printf("Rendez-vous pour %s %s :\n", nom, prenom);
        for (RendezVousNode *node = contact->rendezVous; node != NULL; node = node->suivant) {
            printf("Date: %02d/%02d/%04d, Heure: %02d:%02d, Duree: %02d:%02d, Objet: %s\n",
                   node->rdv.jour, node->rdv.mois, node->rdv.annee,
                   node->rdv.heure, node->rdv.minute,
                   node->rdv.dureeHeures, node->rdv.dureeMinutes,
                   node->rdv.objet);
        }
    }
}

RendezVousNode *afficherPropositionRendezVous(Contact *contact, const char *recherche) {
    RendezVousNode *node = contact->rendezVous;
    RendezVousNode *premierRdvCorrespondant = NULL;

    while (node != NULL) {
        if (strstr(node->rdv.objet, recherche) != NULL) {
            printf("Date: %02d/%02d/%04d, Heure: %02d:%02d, Duree: %02d:%02d, Objet: %s\n",
                   node->rdv.jour, node->rdv.mois, node->rdv.annee,
                   node->rdv.heure, node->rdv.minute,
                   node->rdv.dureeHeures, node->rdv.dureeMinutes,
                   node->rdv.objet);
            if (premierRdvCorrespondant == NULL) {
                premierRdvCorrespondant = node;
            }
        }
        node = node->suivant;
    }
    return premierRdvCorrespondant;
}


void supprimerRendezVousSpecifique(Contact *contact, RendezVousNode *rdvASupprimer) {
    if (contact == NULL || rdvASupprimer == NULL) {
        printf("Erreur : contact ou rendez-vous invalide.\n");
        return;
    }

    // Si le rendez-vous a supprimer est le premier de la liste
    if (contact->rendezVous == rdvASupprimer) {
        contact->rendezVous = rdvASupprimer->suivant;
    } else {
        RendezVousNode *courant = contact->rendezVous;
        while (courant != NULL && courant->suivant != rdvASupprimer) {
            courant = courant->suivant;
        }

        // Si le rendez-vous a supprimer a ete trouve dans la liste
        if (courant != NULL) {
            courant->suivant = rdvASupprimer->suivant;
        }
    }

    // Liberer la memoire allouee pour le rendez-vous
    free(rdvASupprimer->rdv.objet);
    free(rdvASupprimer);
}

void supprimerRendezVous() {
    char nom[50], prenom[50];
    char recherche[100] = {0};
    int index = 0;

    printf("Entrez le nom du contact : ");
    scanf("%s", nom);
    printf("Entrez le prenom du contact : ");
    scanf("%s", prenom);

    Contact *contact = rechercherContactDansListe(nom, prenom);
    if (contact == NULL) {
        printf("Contact non trouve.\n");
        return;
    }

    if (contact->rendezVous == NULL) {
        printf("Aucun rendez-vous pour %s %s.\n", nom, prenom);
        return;
    }

    printf("Entrez les details de l'objet du rendez-vous a supprimer (caractere par caractere, '*' pour supprimer le premier de la liste proposee) :\n");
    RendezVousNode *premierRdvCorrespondant = NULL;

    while (index < (sizeof(recherche) - 1)) {
        viderBuffer(); // Vider le buffer d'entree avant de commencer la saisie
        char c = getc(stdin);

        if (c == '\n') {
            printf("\nFin de la recherche.\n");
            return;
        }

        if (c == '*') {
            if (premierRdvCorrespondant != NULL) {
                supprimerRendezVousSpecifique(contact, premierRdvCorrespondant);
                printf("Rendez-vous specifie supprime.\n");
                return;
            } else {
                printf("Aucun rendez-vous correspondant a supprimer.\n");
                return;
            }
        }

        recherche[index++] = c;
        recherche[index] = '\0';

        if (index >= 3) {
            premierRdvCorrespondant = afficherPropositionRendezVous(contact, recherche);
        }
    }
}

void sauvegarderRendezVous() {
    FILE *fichier = fopen("RendezVous.txt", "w");
    if (fichier == NULL)  {
        perror("Erreur lors de l'ouverture du fichier pour sauvegarde");
        return;
    }

    Contact *contactActuel = listeContacts;
    while (contactActuel != NULL) {
        // Verifi si le contact a des rendez-vous
        if (contactActuel->rendezVous != NULL) {
            RendezVousNode *rdvActuel = contactActuel->rendezVous;
            while (rdvActuel != NULL) {
                fprintf(fichier, "%s %s %02d/%02d/%04d %02d:%02d %02d:%02d %s\n",
                        contactActuel->nom, contactActuel->prenom,
                        rdvActuel->rdv.jour, rdvActuel->rdv.mois, rdvActuel->rdv.annee,
                        rdvActuel->rdv.heure, rdvActuel->rdv.minute,
                        rdvActuel->rdv.dureeHeures, rdvActuel->rdv.dureeMinutes,
                        rdvActuel->rdv.objet);
                rdvActuel = rdvActuel->suivant;
            }
        }
        contactActuel = contactActuel->suivant;
    }

    fclose(fichier);
    printf("Rendez-vous sauvegardes dans 'RendezVous.txt'.\n");
}

void chargerRendezVous() {
    FILE *fichier = fopen("RendezVous.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char ligne[200]; // Pour stocker chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char nom[50], prenom[50], objet[100];
        int jour, mois, annee, heure, minute, dureeHeures, dureeMinutes;

        // Analyser la ligne pour obtenir les informations du rendez-vous
        if (sscanf(ligne, "%s %s %d/%d/%d %d:%d %d:%d %[^\n]",
                   nom, prenom, &jour, &mois, &annee, &heure, &minute, &dureeHeures, &dureeMinutes, objet) == 10) {

            // Trouver le contact correspondant
            Contact *contact = rechercherContactDansListe(nom, prenom);
            if (contact == NULL) {
                // Si le contact n'existe pas, le creer
                contact = creerContactPourRendezVous(nom, prenom);
            }

            // Creer le rendez-vous
            RendezVous rdv;
            rdv.jour = jour;
            rdv.mois = mois;
            rdv.annee = annee;
            rdv.heure = heure;
            rdv.minute = minute;
            rdv.dureeHeures = dureeHeures;
            rdv.dureeMinutes = dureeMinutes;
            rdv.objet = strdup(objet);

            // Ajouter le rendez-vous au contact
            ajouterRendezVousAuContact(contact, rdv);
        }
    }

    fclose(fichier);
    printf("Rendez-vous charges depuis 'RendezVous.txt'.\n");
}

//afficherPropositionRendezVous // viderBuffer(); // Vider le buffer d'entree avant de commencer la saisie


// Fonction principale
int main() {
    int choix;
    chargerContacts();//on pre-rempli la liste de contact a partir du fichie contact.txt

    do {
        // Affichage du menu
        printf("////////////////////////////////////////////////////////////////////////////////////\n");
        printf("\nGestion d'Agenda\n");
        printf("1. Rechercher un contact\n");
        printf("2. Afficher les rendez-vous d'un contact\n");
        printf("3. Creer un contact\n");
        printf("4. Creer un rendez-vous pour un contact\n");
        printf("5. Supprimer un rendez-vous\n");
        printf("6. Sauvegarder les rendez-vous dans un fichier\n");
        printf("7. Charger un fichier de rendez-vous et tous les afficher\n");
        printf("8. Temps de calcul pour insertion de nouveau contact\n");
        printf("9. Afficher la liste de tous les contacts\n");
        printf("0. Quitter\n");
        printf("\n////////////////////////////////////////////////////////////////////////////////////\n");
        printf("\nChoisissez une option: ");
               scanf("%d", &choix);

        // Traitement des choix
        switch(choix) {
            case 1:
                printf("\nRechercher un contact\n");
                rechercherContact();//Pour l'instant la saisie de recherche n'est pas securise, et les contacts sont enregistre avec les noms en FULL MAJ donc lors de recherche =>rentrer le nom en MAJ
                break;
            case 2:
                printf("\nAfficher les rendez-vous d'un contact\n");
                afficherRendezVousDUnContact();
                break;
            case 3:
                printf("\nCreer un contact\n");
                creerContact();
                break;
            case 4:
                printf("\nCreer un rendez-vous pour un contact\n");
                creerRendezVous();
                break;
            case 5:
                printf("\nSupprimer un rendez-vous\n");
                supprimerRendezVous();
                break;
            case 6:
                printf("\nSauvegarder les rendez-vous\n");
                sauvegarderRendezVous();
                break;
            case 7:
                printf("\nCharger un fichier de rendez-vous\n");
                chargerRendezVous();
                break;
            case 8:
                printf("\nTemps de calcul pour insertion de nouveau contact\n");
                //calculerTempsInsertion();
                break;
            case 9:
                printf("\nAfficher la liste de tous les contacts\n");
                afficherContacts();
                break;
            case 10:
                printf("\nAfficher la liste de tous les rendez-vous\n");
                afficherContacts();
                break;
            default:
                if (choix != 0) {
                    printf("Option invalide.\n");
                }
        }
    } while (choix != 0);

    return 0;
}


