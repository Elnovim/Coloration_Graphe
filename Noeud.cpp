#include "Noeud.h"

using namespace std;

Noeud::Noeud()
:color(-1), visit(false), g(0), f(0)
{}

Noeud::Noeud(unsigned int _num)
:num(_num), color(-1), visit(false), g(0), f(0)
{}

Noeud::Noeud(unsigned int _num, vector< Noeud* >& _next)
:num(_num), color(-1), visit(false), next(_next), g(0), f(0)
{}

Noeud::Noeud(const Noeud* n, int col)
:num(n->num), color(col), visit(false), next(n->next), g(0), f(0)
{}

Noeud::~Noeud()
{

}

unsigned int Noeud::get_num() const
{
  return num;
}

int Noeud::get_color() const
{
  return color;
}

vector< Noeud* > Noeud::get_next() const
{
  return next;
}

bool Noeud::get_visit() const
{
  return visit;
}

unsigned int Noeud::get_g() const
{
  return g;
}

unsigned int Noeud::get_f() const
{
  return f;
}

unsigned int Noeud::get_nb_vois() const
{
  unsigned int k=0;
  for (unsigned int i=0; i<next.size(); ++i)
  {
    if (next[i]->get_visit()==false)
      ++k;
  }
  return k;
}

void Noeud::set_num(unsigned int _num)
{
  num = _num;
}

void Noeud::set_color(int _color)
{
  color = _color;
}

void Noeud::set_visit(bool _visit)
{
  visit = _visit;
}

void Noeud::set_next(vector< Noeud* >& _next)
{
  next = _next;
}

void Noeud::add_next(Noeud* _noeud)
{
  next.push_back(_noeud);
}

void Noeud::set_g(unsigned int _g)
{
  g = _g;
}

void Noeud::set_g(vector< Noeud* > n)
{
  int k=g;
  for (unsigned int i=0; i<n.size(); ++i)
  {
    k+=n[i]->get_f();
  }
  g=k;
}

void Noeud::set_f(unsigned int _f)
{
  f = _f;
}

void Noeud::init_g_f()
{
  g = 0;
  f=0;
  for (unsigned int i=0; i<next.size(); ++i)
  {
    if (next[i]->get_visit() == false)
      ++f;
  }
}

int Noeud::find_color()
{
  int maxi;
  int color_test;
  vector<int> colors;
  bool already = true;
  color = 0;
  for (unsigned int i=0; i<next.size(); ++i)
  {
    color_test = next[i]->get_color();
    if (color_test == color)
    {
      already = true;
      while(already)
      {
	color++;
	if ((find(colors.begin(), colors.end(), color)) == colors.end())
	  already = false;
      }
    }
    else
    {
      if (color_test > -1)
      {
	if ((find(colors.begin(), colors.end(), color_test)) == colors.end())
	  colors.push_back(color_test);
      }
    }
  }
  return color;
}

int Noeud::DSAT()
{
  int c;
  int i=0;
  vector<int> color;
  for (unsigned int j=0; j<next.size(); ++j)
  {
    c = next[j]->get_color();
    if ((c > -1) && (find(color.begin(),color.end(),c)==color.end()))
    {
      color.push_back(c);
      ++i;
    }
  }
  if (color.size()==0)
    i = next.size();
  return i;
}

vector< Noeud* > Noeud::cross(Noeud* n)
{
  vector<Noeud*> n_next = n->get_next();
  vector<Noeud*> result;
  for (unsigned int i=0; i<n_next.size(); ++i)
  {
    if((n_next[i]->get_visit() == false) && (find(next.begin(),next.end(),n_next[i]))!=next.end())
      result.push_back(n_next[i]);
  }
  return result;
}

void Noeud::print(ostream& out) const
{
  out << "Noeud n° : " << num << " couleur : " << color;
}

