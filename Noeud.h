#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <vector>
#include <algorithm>

class Noeud{
private:
  unsigned int num; // Numéro du noeud
  int color; // Couleur attribuée au noeud
  bool visit; // Booléen permettant de savoir si un noeud a été visité ou non
  std::vector<Noeud*> next; // Les noeuds successeurs du noeuds
  unsigned int g; // Valeur g utile à l'algorithme de coloration NoN
  unsigned int f; // Valeur f utile à l'algorithme de coloration NoN
public:
  Noeud(); // Constructeur par défaut
  Noeud(unsigned int _num); // Constructeur par numéro
  Noeud(unsigned int _num, std::vector<Noeud*>& _next); // Constructeur par numéro et successeurs
  Noeud(const Noeud* n, int col); // Construction par recopie hors couleur
  
  ~Noeud(); // Destructeur de noeud
  
  
  unsigned int get_num() const; // Getter sur le numéro
  int get_color() const; // Getter sur la couleur
  std::vector<Noeud*> get_next() const; // Getter sur les successeurs
  bool get_visit() const; // Getter sur la valeur booléenne de visite
  unsigned int get_g() const; // Getter sur g
  unsigned int get_f() const; // Getter sur f
  unsigned int get_nb_vois() const; // Getter sur le nombre de successeurs
  
  void set_num(unsigned int _num); // Setter sur le numéro
  void set_color(int _color); // Setter sur la couleur
  void set_visit(bool _visit); // Setter sur la valeur booléenne de visite
  void set_next(std::vector<Noeud*>& _next); // Setter sur les successeurs
  void add_next(Noeud* _noeud); // Ajout d'un successeur
  void set_g(unsigned int _g); // Setter sur g par valeur
  void set_g(std::vector<Noeud*> n); // Setter sur g par ajout de valeur de vector de noeud
  void set_f(unsigned int _f); // Setter sur f par valeur
  
  
  void init_g_f(); // Initialisation des valeurs g et f
  int find_color(); // Fonction pour déterminer simplement une couleur au noeud en fonction des couleurs de ses successeurs
  int DSAT(); // Fonction de calcul de DSAT
  
  std::vector<Noeud*> cross(Noeud* n); // Fonction pour récupérer l'intersection des successeurs entre ce noeud et un autre


  void print(std::ostream& out) const; // Transformation des informations d'un noeud sous forme de string

  friend std::ostream& operator<<(std::ostream& _out, const Noeud& _n){ // Surcharge de l'opérateur <<
    _n.print(_out);
    return _out;
  };
};

#endif