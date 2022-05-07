#include "Mot.h"

typedef struct _Noeud{
    Mot *mot;
    unsigned int hauteur;
    struct _Noeud *fg;
    struct _Noeud *fd;
}Noeud, *Arbre;

Noeud *alloue_noeud(const char* mot);
int ajouter_noeud(Arbre *a, const char *mot);
Noeud *recherche(const Arbre a, const char *mot);
void liberer_arbre(Arbre a);
unsigned int longueur_max_arbre(const Arbre a);
void afficher_arbre_ordre_lexi(Arbre a, unsigned int longueur_max);
