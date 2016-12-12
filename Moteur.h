#ifndef MOTEUR_H
#define MOTEUR_H

#include "Graphe.h"

#include <list>
#include <ostream>

class Moteur{
private:
  Graphe Graph; // Graphe sur lequel est effectué le traitement des différents algorithmes de coloration
public:
  Moteur(); // Constructeur par défaut
  Moteur(Graphe _Graph); // Constructeur par recopie
  void Glouton(); // Algorithme Glouton, coloration du graphe noeud après noeud sans retour en arrière selon l'ordre du graphe initial (coloration noeud 1, noeud 2, noeud 3...)
  void Glouton_degre(); // Algorithme Glouton où le graphe est trié selon le degré des noeuds en ordre décroissant
  void Glouton_largeur(); // Algorithme Glouton par parcours en largeur du graphe
  void Glouton_profondeur(); // Algorithme Glouton par parcours en profondeur du graphe
  void Welsh_Powell(); // Algorithme Glouton Welsh et Powell
  void DSATUR(); // Algorithme Glouton DSATUR
  void NoN(); // Algorithme constructif NoN (Neighbours of Neighbours)
};

  void tri_dsat(std::vector<Noeud*> & edges); // Tri de vecteur selon DSAT
  bool dsat(Noeud* n1, Noeud* n2); // Fonction de comparaison de DSAT pour la fonction tri_dsat
  std::vector<Noeud*> max_s(std::vector<std::vector<Noeud*>> s_edges); // Fonction qui retourner la clique la plus intéressante parmis un ensemble de clique i.e. celle qui a le plus d'arrête, en cas d'égalité, celle qui contient le plus de noeud
  unsigned int compt_ar(std::vector<Noeud*> edges); // Fonction pour compter le nombre d'arrêtes d'un noeud

#endif