#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <vector>
#include <algorithm>

class Noeud{
private:
  unsigned int num;
  int color;
  bool visit;
  std::vector<Noeud*> next;
  unsigned int g;
  unsigned int f;
public:
  Noeud();
  Noeud(unsigned int _num);
  Noeud(unsigned int _num, std::vector<Noeud*>& _next);
  Noeud(const Noeud* n, int col);
  ~Noeud();
  unsigned int get_num() const;
  int get_color() const;
  std::vector<Noeud*> get_next() const;
  bool get_visit() const;
  unsigned int get_g() const;
  unsigned int get_f() const;
  unsigned int get_nb_vois() const;
  void set_num(unsigned int _num);
  void set_color(int _color);
  void set_visit(bool _visit);
  void set_next(std::vector<Noeud*>& _next);
  void add_next(Noeud* _noeud);
  void set_g(unsigned int _g);
  void set_g(std::vector<Noeud*> n);
  void set_f(unsigned int _f);
  void init_g_f();
  int find_color();
  int DSAT();
  std::vector<Noeud*> cross(Noeud* n);
  void print(std::ostream& out) const;
  friend std::ostream& operator<<(std::ostream& _out, const Noeud& _n){
    _n.print(_out);
    return _out;
  };
};

#endif