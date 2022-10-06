#include "kruskal.h"

void afficherACPM(Arrete* liste, int poidsTotal){
    Arrete* temp = liste;
    while (temp != NULL){
        if(temp->couleur == 1){
            printf("%d--%d, poids : %d\n", temp->s1, temp->s2, temp->poids);
        }
        temp = temp->next;
    }

    printf("Poids total %d\n", poidsTotal);
}

void kruskal(pSommet *graphe, Arrete *liste, int ordre, int *poidsTotal) {

    int nbArretes = 0;

    for (int i = 0; i < ordre; i++) {
        graphe[i]->couleur = (char) i;
    }

    //Connaître le numéro d'arrête où on en est
    int compteur = 0;

    //Temp pour parcourir la liste jusqu'à une arrête
    Arrete *temp = liste;


    while (nbArretes < ordre - 1) {
        if (graphe[temp->s1]->couleur != graphe[temp->s2]->couleur) {
            *poidsTotal += temp->poids;
            //Problème de couleur
            temp->couleur = 1;
            for (int i = 0; i < ordre; i++) {
                if (graphe[i]->couleur == graphe[temp->s1]->couleur) {

                    graphe[i]->couleur = graphe[temp->s2]->couleur;
                }

            }
            graphe[temp->s1]->couleur = graphe[temp->s2]->couleur;
            nbArretes++;

        } else {
            temp->couleur = 0;
        }
        compteur++;
        temp = temp->next;
    }


}
