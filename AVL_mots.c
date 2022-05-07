#include "AVL_mots.h"

static unsigned int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

static void maj_hauteur(Arbre a){
    if(NULL == a)
        return;
    if(NULL != a->fg && NULL != a->fd)
        a->hauteur = 1 + max(a->fg->hauteur, a->fd->hauteur);
    else if(NULL != a->fd)
        a->hauteur = 1 + a->fd->hauteur;
    else if(NULL != a->fg)
        a->hauteur = 1 + a->fg->hauteur;
    else
        a->hauteur = 0;
}

static int calcul_balance(Arbre a){
    int bal;

    bal = 0;
    if(NULL != a->fg)
        bal -= a->fg->hauteur;
    else
        ++bal;
    if(NULL != a->fd)
        bal += a->fd->hauteur;
    else
        --bal;
    return bal;
}

Noeud *alloue_noeud(const char* mot){
    Noeud *tmp;
    assert(NULL != mot);
    tmp = (Noeud *)malloc(sizeof(Noeud));
    if (NULL == tmp){
        fprintf(stderr, "Erreur de l'allocation de la mémoire.\n");
        return NULL;
    }
    tmp->mot = alloue_mot(mot);
    if (NULL == tmp->mot){
        fprintf(stderr, "Erreur d'allocation du mot.\n");
        free(tmp);
        return NULL;
    }
    tmp->fg = NULL;
    tmp->fd = NULL;
    tmp->hauteur = 0;
    return tmp;
}

static void rotation_D(Arbre *r){
    Arbre g;

    assert(NULL != r);
    assert(NULL != *r);

    g = (*r)->fg;
    --(*r)->hauteur;
    ++g->hauteur;
    (*r)->fg = g->fd;
    g->fd = *r;
    *r = g;
}

static void rotation_G(Arbre *r){
    Arbre d;

    assert(NULL != r);
    assert(NULL != *r);

    d = (*r)->fd;
    --(*r)->hauteur;
    ++d->hauteur;
    (*r)->fd = d->fg;
    d->fg = *r;
    *r = d;
}

static void rotation_DG(Arbre *a){
    assert(NULL != a);
    assert(NULL != *a);

    rotation_D(&(*a)->fd);
    rotation_G(a);
}

static void rotation_GD(Arbre *a){
    assert(NULL != a);
    assert(NULL != *a);

    rotation_G(&(*a)->fg);
    rotation_D(a);
}

static void equilibrer(Arbre *a){
    int balance;

    assert(NULL != a);
    assert(NULL != *a);

    balance = calcul_balance(*a);
    if(balance == 2){
        if(calcul_balance((*a)->fd) >= 0)
            rotation_G(a);
        else
            rotation_DG(a);
    }
    else if(balance == -2){
        if(calcul_balance((*a)->fg) <= 0)
            rotation_D(a);
        else
            rotation_GD(a);
    }
}

int ajouter_noeud(Arbre *a, const char *mot){
    int comparaison, res;

    assert(NULL != a);
    assert(NULL != mot);

    if(NULL == *a){
        *a = alloue_noeud(mot);
        if(NULL == *a){
            fprintf(stderr, "Erreur d'allocation.\n");
            return 0;
        }
        return 1;
    }
    comparaison = strcmp(mot, (*a)->mot->str);
    if(comparaison < 0)
        res = ajouter_noeud(&(*a)->fg, mot);
    else if(comparaison > 0)
        res = ajouter_noeud(&(*a)->fd, mot);
    else{
        ++(*a)->mot->nb_occurrences;
        return 0;
    }
    equilibrer(a);
    maj_hauteur(*a);
    return res;
}

Noeud *recherche(const Arbre a, const char *s){
    int comparaison;

    assert(NULL != s);

    if(NULL == a)
        return NULL;
    comparaison = strcmp(s, a->mot->str);
    if(comparaison < 0)
        return recherche(a->fg, s);
    if(comparaison > 0)
        return recherche(a->fd, s);
    return a;
}

int est_dans_arbre(const Arbre a, const char *s){
    return NULL != recherche(a, s);
}

void liberer_arbre(Arbre a){
    if(NULL == a)
        return;
    liberer_arbre(a->fg);
    liberer_arbre(a->fd);
    liberer_mot(a->mot);
    free(a);
}

unsigned int longueur_max_arbre(const Arbre a){
    if(NULL == a)
        return 0;
    return max(strlen(a->mot->str), max(longueur_max_arbre(a->fg), longueur_max_arbre(a->fd)));
}

void afficher_arbre_ordre_lexi(Arbre a, unsigned int longueur_max){
    if(NULL == a)
        return;
    afficher_arbre_ordre_lexi(a->fg, longueur_max);
    printf("%-*s %d\n", longueur_max, a->mot->str, a->mot->nb_occurrences);
    afficher_arbre_ordre_lexi(a->fd, longueur_max);
}
