#include "Graphe.h"

using namespace std;

Graphe::Graphe()
:nb_edges(0), nb_colors(0)
{}

Graphe::Graphe(const Graphe& G)
:edges(G.edges), nb_edges(G.nb_edges), nb_colors(G.nb_colors)
{}

void Graphe::init_edges()
{
  for (unsigned int i=0; i<edges.size(); ++i)
  {
    edges[i]->set_color(-1);
    edges[i]->set_visit(false);
  }
}

void Graphe::set_graphe(const string& _namefile)
{
  int num1, num2;
  ifstream file (_namefile.c_str(), ios::in);
  if (file)
  {
    string line;
    vector<string> link;
    while(getline(file, line) && line[0] == 'c')
    {
    }
    link = string_tokenizer(line);
    nb_edges = atoi(link[2].c_str());
    for (unsigned int i=0; i<nb_edges; ++i)
    {
      Noeud* n = new Noeud(i+1);
      edges.push_back(n);
    }
    while(getline(file, line))
    {
      link = string_tokenizer(line);
      num1 = atoi(link[1].c_str());
      num2 = atoi(link[2].c_str());
      edges[num1-1]->add_next(edges[num2-1]);
      edges[num2-1]->add_next(edges[num1-1]);
    }
  }
}

std::vector< Noeud* > Graphe::get_edges() const
{
  return edges;
}

unsigned int Graphe::get_nb_egdes() const
{
  return nb_edges;
}

unsigned int Graphe::get_nb_colors() const
{
  return nb_colors;
}

void Graphe::set_edges(std::vector< Noeud* >& _edges)
{
  edges = _edges;
}

void Graphe::add_edge(Noeud* _edge)
{
  edges.push_back(_edge);
}

void Graphe::set_nb_edges(unsigned int _nb_edges)
{
  nb_edges = _nb_edges;
}

void Graphe::set_nb_colors(unsigned int _nb_colors)
{
  nb_colors = _nb_colors;
}

void Graphe::inc_nb_colors()
{
  ++nb_colors;
}

void Graphe::tri_degre()
{
  sort(edges.begin(),edges.end(),degre);
}

void Graphe::take_off(std::vector< Noeud* > n)
{
  vector<Noeud*>::iterator it;
  for (unsigned int i=0; i<n.size(); ++i)
  {
    it = find(edges.begin(), edges.end(), n[i]);
    if (it != edges.end())
      edges.erase(it);
  }
}

vector< Noeud* > Graphe::vois_2(Noeud* n)
{
  set<Noeud*> vois2;
  vector<Noeud*> vois;
  vector<Noeud*> result;
  vois = n->get_next();
  set<Noeud*>::iterator it;
  for (unsigned int i=0; i<vois.size(); ++i)
  {
    if (vois[i]->get_visit() == false)
    {
      result = vois[i]->get_next();
      for (unsigned int j=0; j<result.size(); ++j)
      {
	if ((find(edges.begin(),edges.end(),result[j]))!=edges.end())
	  vois2.insert(result[j]);
      }
    }
  }
  result.clear();
  for(it = vois2.begin(); it!=vois2.end(); ++it)
  {
    result.push_back(*it);
  }
  return result;
}

Noeud* Graphe::max()
{
  Noeud* sol = edges[0];
  for (unsigned int i=1; i<edges.size(); ++i)
  {
    if (edges[i]->get_g() > sol->get_g())
      sol = edges[i];
    else
    {
      if(edges[i]->get_g() == sol->get_g())
      {
	if (edges[i]->get_f() > sol->get_f())
	  sol = edges[i];
      }
    }
  }
  return sol;
}

void Graphe::print(ostream& out) const
{
  out << "Graphe de taille : " << edges.size() << " nombre de couleurs : " << nb_colors << '\n';
  for (unsigned int i=0; i<edges.size(); ++i)
    out << *edges[i] << endl;
}

bool degre(Noeud* n1, Noeud* n2)
{
  return (n1->get_next().size() > n2->get_next().size());
}

vector<string> string_tokenizer(string str)
{
  istringstream ss(str);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}
