#include "prim.h"

Arrete* prim(pSommet* graphe, Arrete* liste, int ordre, int* poidsTotal){

    int nbMarques = 0;
    int sommetAnterieur = 0;

    //Tous les sommets sont non marqués
    for (int i = 0; i < ordre; i++) {
        graphe[i]->couleur = 0;
    }

    //On choisit un sommet ici 0 et on le marque
    graphe[0]->couleur = 1;
    //Le nombre de sommets marqués += 1
    nbMarques++;

    //Initialisation d'un parcoursSuccesseursoraire pour parcourir tous les arcs suivants d'un sommet marqué
    struct Arc* parcours = NULL;
    //Initialisation d'un parcoursSuccesseursoraire pour stocker l'arête de poids minimum parmi les sommets marqués
    struct Arc* poidsMinimum = graphe[0]->arc;

    //Création d'une liste d'arête vide
    liste = calloc(1, sizeof(Arrete));
    Arrete* dernierListe = liste;

    //Tant que le nombre d'arêtes marquées est différent de l'ordre
    while (nbMarques != ordre){
        //On parcourt tous les sommets
        for (int i = 0; i < ordre; i++) {
            //Pour les sommets marqués (si le sommet est marqué)
            if ((int) graphe[i]->couleur) {
                //Le parcoursSuccesseursoraire prend la valeur du premier arc du sommet
                parcours = graphe[i]->arc;

                //Parcours de toutes ses arêtes
                while (parcours != NULL) {
                    //Le prédécesseur est le sommet marqué ici i
                    if(poidsMinimum->couleur == 1 && parcours->couleur == 0){
                        poidsMinimum = parcours;
                    }
                    //Si l'arête parcoursSuccesseursoraire parcours a un poids < au parcoursSuccesseursoraire poidsMinimum
                    if (parcours->valeur < poidsMinimum->valeur && parcours->couleur != 1 && graphe[parcours->sommet]->couleur != 1) {
                        //On modifie poidsMinimum
                        sommetAnterieur = i;
                        poidsMinimum = parcours;
                    }
                    //On relance sur l'arête suivante
                    parcours = parcours->arc_suivant;
                }
            }
        }

        //Pour l'ACPM on met cette arête comme 'sélectionnée'
        dernierListe->couleur = 1;
        //Le sommet s1 de cette arête est 'i' = 'sommetAntérieur'
        dernierListe->s1 = sommetAnterieur;
        //Le sommet s2 de cette arête est le sommet de l'arc de poids minimum
        dernierListe->s2 = poidsMinimum->sommet;
        //Le poids de l'arête est égal au poids de l'arc
        dernierListe->poids = poidsMinimum->valeur;
        //L'arc est désormais sélectionné
        poidsMinimum->couleur = 1;

        //Temporaire pour parcourir les arcs des sommets dans les 2 sens
        struct Arc* parcoursSuccesseurs = graphe[poidsMinimum->sommet]->arc;
        //Marquage des arcs dans les 2 sens (graphe orienté)
        while (parcoursSuccesseurs != NULL){

            if(parcoursSuccesseurs->sommet == sommetAnterieur){
                //L'arc est désormais sélectionné dans les 2 sens
                parcoursSuccesseurs->couleur = 1;
            }

            parcoursSuccesseurs = parcoursSuccesseurs->arc_suivant;
        }


        //Le poids total est incrémenté du poids de l'arc
        *poidsTotal += poidsMinimum->valeur;

        //Le sommet s2 est sélectionné
        graphe[poidsMinimum->sommet]->couleur = 1;

        //On alloue dynamiquement la fin de liste
        dernierListe->next = calloc(1, sizeof(Arrete));
        //On réactualise le dernier de la liste
        dernierListe = dernierListe->next;
        //Le nombre marqué est incrémenté de 1
        nbMarques++;
    }

    return liste;
}
