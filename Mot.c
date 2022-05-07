#include "Mot.h"

/* function : alloue_mot(mot)    Alloue un Mot contenant la chaine de caractères pointée par mot, renvoie son adresse (ou NULL si échec).

 * param : const char *mot Mot à copier dans le mot
 * return : Mot *   adresse du Mot, ou NULL
*/
Mot *alloue_mot(const char *mot) {
    Mot *tmp;
    tmp = (Mot *)malloc(sizeof(Mot));
    if (NULL == tmp){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire.\n");
        return NULL;
    }
    tmp->str = (char *)malloc(sizeof(char) * strlen(mot) + 1);
    if(NULL == tmp->str){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire.\n");
        free(tmp);
        return NULL;
    }
    tmp->nb_occurrences = 1;
    strcpy(tmp->str, mot);
    return tmp;
}

/* function : mot_valide(mot)    Renvoie 1 si le mot est valide, 0 sinon

 * param : const char *mot      mot à tester
 * return : int     0 ou 1
*/
int mot_valide(const char *mot) {
    for(; *mot; ++ mot) {
        if(!isalpha(*mot) && *mot != ' ')
            return 0;
    }
    return 1;
}

void passer_en_minuscules(char *s){
    for(; *s; ++s)
        *s = tolower(*s);
}

void liberer_mot(Mot *mot){
    free(mot->str);
    free(mot);
    mot = NULL;
}
