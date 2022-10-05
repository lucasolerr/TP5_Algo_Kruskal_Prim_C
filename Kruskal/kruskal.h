#ifndef TP5_ALGO_KRUSKAL_PRIM_KRUSKAL_H
#define TP5_ALGO_KRUSKAL_PRIM_KRUSKAL_H

#include "../Graphe/Graphe.h"

void kruskal(pSommet *graphe, Arrete *liste, int ordre, int *poidsTotal);

void afficherACPM(Arrete* liste, int poidsTotal);

#endif
