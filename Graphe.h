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
  std::vector<Noeud*> edges;
  unsigned int nb_edges;
  unsigned int nb_colors;
public:
  Graphe();
  Graphe(const Graphe& G);
  void init_edges();
  void set_graphe(const std::string& _namefile);
  std::vector<Noeud*> get_edges() const;
  unsigned int get_nb_egdes()const;
  unsigned int get_nb_colors() const;
  void set_edges(std::vector<Noeud*>& _edges);
  void add_edge(Noeud* _edge);
  void set_nb_edges(unsigned int _nb_edges);
  void set_nb_colors(unsigned int _nb_colors);
  void inc_nb_colors();
  void tri_degre();
  void take_off(std::vector<Noeud*> n);
  std::vector<Noeud*> vois_2(Noeud* n);
  Noeud* max();
  void print(std::ostream& out) const;
  friend std::ostream& operator<<(std::ostream& _out, const Graphe& _g){
    _g.print(_out);
    return _out;
  };
};

bool degre(Noeud* n1, Noeud* n2);
std::vector<std::string> string_tokenizer(std::string str);

#endif