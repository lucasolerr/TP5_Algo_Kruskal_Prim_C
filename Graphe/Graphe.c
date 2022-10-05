#include "Graphe.h"

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet* sommet, int num) {

    printf(" sommet %d :\n", num);

    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("%d poids : %d/ ", arc->sommet, arc->valeur);
        arc = arc->arc_suivant;
    }

}

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet *CreerArete(pSommet* sommet, int s1, int s2, int poids) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->arc_suivant = NULL;
        Newarc->valeur = poids;
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->arc_suivant = NULL;
        Newarc->valeur = poids;

        if (temp->sommet > s2) {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            temp->sommet = s2;
            temp->valeur = poids;
            temp->arc_suivant = Newarc;
            return sommet;
        }

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

// creer le graphe
Graphe* CreerGraphe(int ordre) {
    Graphe* Newgraphe = (Graphe*) malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*) malloc(ordre * sizeof(pSommet));

    for (int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}

Arrete* triArrete(Arrete* liste, int s1, int s2, int poids){
    Arrete* temp = malloc(sizeof(Arrete));

    temp->s1 = s1;
    temp->s2 = s2;
    temp->poids = poids;
    temp->couleur = -1;
    temp->next = NULL;

    Arrete* parcours = liste;

    if(liste == NULL){
        liste = temp;
        return liste;
    } else if(liste->next == NULL){
        if(liste->poids < temp->poids){
            liste->next = temp;
            return liste;
        } else {
            Arrete* tempListe = liste;
            liste = temp;
            temp->next = tempListe;
            return liste;
        }
    } else {
        while (parcours->next != NULL){
            //Ajout en tête (et comparaison pour le 1er)
            if(liste->poids > temp->poids){
                Arrete* tempParcours = liste;
                liste = temp;
                temp->next = tempParcours;
                return liste;
            }
            if(parcours->next->poids < temp->poids){
                parcours = parcours->next;
            } else {
                temp->next = parcours->next;
                parcours->next = temp;
                return liste;
            }
        }

        parcours->next = temp;
        return liste;
    }
}

void afficherListe(Arrete* liste){
    Arrete* temp = liste;

    while (temp != NULL){
        printf("%d %d %d\n", temp->s1, temp->s2, temp->poids);

        temp = temp->next;
    }

}


/* La construction du reseau peut se faire a partir d'un fichier dont le nom est passe en parametre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe* lire_graphe(char *nomFichier, Arrete** liste) {
    *liste = NULL;
    Graphe* graphe;
    FILE* ifs = fopen(nomFichier, "r");
    int taille, orientation, ordre, s1, s2, poids;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);

    graphe = CreerGraphe(ordre); // creer le graphe d'ordre sommets

    fscanf(ifs, "%d", &taille);
    fscanf(ifs, "%d", &orientation);

    graphe->orientation = orientation;
    graphe->ordre = ordre;

    // creer les aretes du graphe
    for (int i = 0; i < taille; ++i) {
        fscanf(ifs, "%d%d%d", &s1, &s2, &poids);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poids);
        *liste = triArrete(*liste, s1, s2, poids);
        if (!orientation)
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, poids);
    }

    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe *graphe) {
    printf("graphe\n");

    if (graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n", graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}



