#include "kruskal.h"

void afficherACPM(Arrete *liste, int poidsTotal) {
    Arrete *temp = liste;
    //Parcours de toutes les arêtes
    while (temp != NULL) {
        //Si l'arête est marquée de la bonne couleur
        if (temp->couleur == 1) {
            //On l'affiche de la forme s1--s2, poids : p
            printf("%d--%d, poids : %d\n", temp->s1, temp->s2, temp->poids);
        }
        //On passe à l'arête suivante
        temp = temp->next;
    }

    //On affiche ici le poids total
    printf("Poids total %d\n", poidsTotal);
}


void kruskal(pSommet *graphe, Arrete *liste, int ordre, int *poidsTotal) {

    //Le nombre d'arêtes de l'arbre est initialement à 0
    int nbArretes = 0;

    //On initialise tous les sommets comme composantes connexes isolées
    for (int i = 0; i < ordre; i++) {
        graphe[i]->couleur = (char) i;
    }

    //Temp pour parcourir la liste jusqu'aux arêtes suivantes
    Arrete *temp = liste;

    //Un graphe est arbre ssi il est sans cycle et possède n-1 arêtes
    //Tant que le nbArêtes < ordre - 1
    while (nbArretes < ordre - 1) {
        //Si l'arête ne créé pas de cycle
        if (graphe[temp->s1]->couleur != graphe[temp->s2]->couleur) {
            //Le poids total est incrémenté du poids de l'arête
            *poidsTotal += temp->poids;
            //L'arête est marquée (utile pour afficher un l'arbre couvrant de poids minimum
            temp->couleur = 1;

            //Pour tous les sommets
            for (int i = 0; i < ordre; i++) {
                //Si un sommet si est connexe à s1
                if (graphe[i]->couleur == graphe[temp->s1]->couleur) {
                    //si est désormais connexe à s2
                    graphe[i]->couleur = graphe[temp->s2]->couleur;
                }
            }
            //s1 est désormais connexe avec s2
            graphe[temp->s1]->couleur = graphe[temp->s2]->couleur;

            //Le nombre d'arêtes sélectionné est incrémenté
            nbArretes++;
        } else {
            //Sinon cette arête créée un cycle, elle est marquée de la mauvaise couleur
            temp->couleur = 0;
        }
        //On passe à l'arête suivante
        temp = temp->next;
    }
}
