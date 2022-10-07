#include "stdio.h"
#include "Graphe/Graphe.h"
#include "Kruskal/kruskal.h"
#include "Prim/prim.h"



int main() {
    Arrete* liste = NULL;
    int poidsTotal = 0, choix = 0;
    Graphe* g = lire_graphe("../binaries/graphe1_TP3.txt", &liste);

    //afficher le graphe
    //graphe_afficher(g);

    printf("Lancement Kruskal ou Prim ? (0 : Kruskal, 1 : Prim)\n");
    scanf(" %d", &choix);

    if(choix){
        //On choisit de stocker dans une liste d'arête vide
        freeListe(liste);
        //La liste est vide
        liste = NULL;
        //On lance prim
        liste = prim(g->pSommet, liste, g->ordre, &poidsTotal);

        //Affichage de l'arbre
        afficherACPM(liste, poidsTotal);
    } else {
        //Appel de la fonction kruskal qui permet de simuler la création d'un arbre couvrant de poids minimum du graphe g
        kruskal(g->pSommet, liste, g->ordre, &poidsTotal);

        //Affichage de cet arbre
        afficherACPM(liste, poidsTotal);
    }

    //On libère l'arbre alloué dynamiquement
    freeListe(liste);


    return 0;
}