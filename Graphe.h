#ifndef GRAPHE_H
#define GRAPHE_H

#include "Noeud.h"

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <set>

class Graphe{
private:
  std::vector<Noeud*> edges; // Noeuds du graphe
  unsigned int nb_edges; // Nombre de noeuds du graphe
  unsigned int nb_colors; // Nombre de couleur du graphe
public:
  Graphe(); // Constructeur par défaut
  Graphe(const Graphe& G); // Constructeur par recopie
  
  void init_edges(); // Réinitialisation des noeuds du graphe i.e. remise à zéro des couleurs et noeud non visité
  void set_graphe(const std::string& _namefile); // Initialisation d'un graphe à partir d'un fichier texte
  
  
  std::vector<Noeud*> get_edges() const; // Getter sur les noeuds du graphe
  unsigned int get_nb_egdes()const; // Getter sur le nombre de noeuds du graphe
  unsigned int get_nb_colors() const; // Getter sur le nombre de couleur du graphe
  
  void set_edges(std::vector<Noeud*>& _edges); // Setter sur les noeuds du graphe
  void add_edge(Noeud* _edge); // Setter pour l'ajout d'un noeud au graphe
  void set_nb_edges(unsigned int _nb_edges); // Setter sur le nombre de noeuds d'un graphe
  void set_nb_colors(unsigned int _nb_colors); // Setter sur le nombre de couleur du graphe
  
  
  bool verif_color(); // Vérification de la coloation du graphe
  void inc_nb_colors(); // Incrémentation du nombre de couleur du graphe
  void tri_degre(); // Tri des noeuds du graphe par degré en ordre décroissant
  void take_off(std::vector<Noeud*> n); // Fonction pour retirer plusieurs noeuds du graphe (vérification si les noeuds appartiennent bien au graphe)
  std::vector<Noeud*> vois_2(Noeud* n); // Fonction pour déterminer les voisins de distance deux d'un graphe
  Noeud* max(); // Retourne le noeud ayant un g maximum, en cas d'égalité, un f maximum
  
  
  void print(std::ostream& out) const; // Fonction transformant les informations d'un graphe sous forme de strin
  
  friend std::ostream& operator<<(std::ostream& _out, const Graphe& _g){ // Surcharge de l'opérateur <<
    _g.print(_out);
    return _out;
  };
};

bool degre(Noeud* n1, Noeud* n2); // Fonction de comparaison du degré de deux noeuds
std::vector<std::string> string_tokenizer(std::string str); // Fonction de décomposition d'un string par caractère ' '

#endif