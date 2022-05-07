#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
Antoine Bonnier Seïfeddine Brahmi
 Groupe 3
    C TP 6

*/

typedef struct{
    char *str;
    int nb_occurrences;
} Mot;

Mot * alloue_mot(const char *mot);
int mot_valide(const char *mot);
void passer_en_minuscules(char *s);
void ajoute_mot(FILE* fichier, Mot * mots);
void liberer_mot(Mot *mot);
