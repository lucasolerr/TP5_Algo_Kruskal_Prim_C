#include "stdio.h"
#include "Graphe/Graphe.h"
#include "Kruskal/kruskal.h"



int main() {
    Arrete* liste = NULL;
    int poidsTotal = 0;
    Graphe* g = lire_graphe("../binaries/graphe1_TP3.txt", &liste);

    //afficher le graphe
    //graphe_afficher(g);

    //Appel de la fonction kruskal qui permet de simuler la création d'un arbre couvrant de poids minimum du graphe g
    kruskal(g->pSommet, liste, g->ordre, &poidsTotal);

    //Affichage de cet arbre
    afficherACPM(liste, poidsTotal);

    return 0;
}