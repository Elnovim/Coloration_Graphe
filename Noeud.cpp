#include "Noeud.h"

using namespace std;

Noeud::Noeud() // Constructeur par défaut
:color(-1), visit(false), g(0), f(0)
{}

Noeud::Noeud(unsigned int _num) // Constructeur par numéro
:num(_num), color(-1), visit(false), g(0), f(0)
{}

Noeud::Noeud(unsigned int _num, vector< Noeud* >& _next) // Constructeur par numéro et successeurs
:num(_num), color(-1), visit(false), next(_next), g(0), f(0)
{}

Noeud::Noeud(const Noeud* n, int col) // Construction par recopie hors couleur
:num(n->num), color(col), visit(false), next(n->next), g(n->g), f(n->f)
{}

Noeud::~Noeud() // Destructeur de noeud
{}


unsigned int Noeud::get_num() const // Getter sur le numéro
{
  return num;
}

int Noeud::get_color() const // Getter sur la couleur
{
  return color;
}

vector< Noeud* > Noeud::get_next() const // Getter sur les successeurs
{
  return next;
}

bool Noeud::get_visit() const // Getter sur la valeur booléenne de visite
{
  return visit;
}

unsigned int Noeud::get_g() const // Getter sur g
{
  return g;
}

unsigned int Noeud::get_f() const // Getter sur f
{
  return f;
}

unsigned int Noeud::get_nb_vois() const // Getter sur le nombre de successeurs
{
  unsigned int k=0;
  for (unsigned int i=0; i<next.size(); ++i)
  {
    if (next[i]->get_visit()==false)
      ++k;
  }
  return k;
}

void Noeud::set_num(unsigned int _num) // Setter sur le numéro
{
  num = _num;
}

void Noeud::set_color(int _color) // Setter sur la couleur
{
  color = _color;
}

void Noeud::set_visit(bool _visit) // Setter sur la valeur booléenne de visite
{
  visit = _visit;
}

void Noeud::set_next(vector< Noeud* >& _next) // Setter sur les successeurs
{
  next = _next;
}

void Noeud::add_next(Noeud* _noeud) // Ajout d'un successeur
{
  next.push_back(_noeud);
}

void Noeud::set_g(unsigned int _g) // Setter sur g par valeur
{
  g = _g;
}

void Noeud::set_g(vector< Noeud* > n) // Setter sur g par ajout de valeur de vector de noeud
{
  int k=g;
  for (unsigned int i=0; i<n.size(); ++i)
  {
    k+=n[i]->get_f();
  }
  g=k;
}

void Noeud::set_f(unsigned int _f) // Setter sur f par valeur
{
  f = _f;
}


void Noeud::init_g_f() // Initialisation des valeurs g et f
{
  g = 0;
  f=next.size();
}

int Noeud::find_color() // Fonction pour déterminer simplement une couleur au noeud en fonction des couleurs de ses successeurs
{
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

int Noeud::DSAT() // Fonction de calcul de DSAT
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

vector< Noeud* > Noeud::cross(Noeud* n) // Fonction pour récupérer l'intersection des successeurs entre ce noeud et un autre
{
  vector<Noeud*> n_next = n->get_next();
  vector<Noeud*> result;
  for (unsigned int i=0; i<next.size(); ++i)
  {
    if((next[i]->get_visit() == false) && (find(n_next.begin(),n_next.end(),next[i]))!=n_next.end())
      result.push_back(next[i]);
  }
  return result;
}

void Noeud::print(ostream& out) const // Transformation des informations d'un noeud sous forme de string
{
  out << "Noeud n° : " << num << " couleur : " << color;
}

