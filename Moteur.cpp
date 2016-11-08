#include "Moteur.h"

using namespace std;

Moteur::Moteur()
{}

Moteur::Moteur(Graphe _Graph)
:Graph(_Graph)
{}

void Moteur::Glouton()
{
  int nb_color = 0;
  int color;
  Graphe G(Graph);
  std::vector<Noeud*> edges = G.get_edges();
  G.init_edges();
  for (unsigned int i=0; i<edges.size(); ++i)
  {
    color = edges[i]->find_color();
    if (color >= nb_color)
      ++nb_color;
  }
  G.set_nb_colors(nb_color);
  cout << "Algorithme Glouton simple : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void Moteur::Glouton_degre()
{
  int nb_color = 0;
  int color;
  Graphe G(Graph);
  G.tri_degre();
  std::vector<Noeud*> edges = G.get_edges();
  G.init_edges();
  for (unsigned int i=0; i<edges.size(); ++i)
  {
    color = edges[i]->find_color();
    if (color >= nb_color)
      ++nb_color;
  }
  G.set_nb_colors(nb_color);
  edges = Graph.get_edges();
  cout << "Algorithme Glouton trié selon l'arité des noeuds : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void Moteur::Glouton_largeur()
{
  int nb_color=0, color;
  Graphe G(Graph);
  G.init_edges();
  vector<Noeud*> trait;
  list<Noeud*> intrait;
  vector<Noeud*> edges = G.get_edges();
  vector<Noeud*> next;
  Noeud* v, *v_test;
  intrait.push_back(edges[0]);
  unsigned int t = edges.size();
  unsigned int j;
  while(trait.size() != t)
  {
    if (!intrait.empty())
    {
      v = intrait.front();
      v->set_visit(true);
      color = v->find_color();
      if (color >= nb_color)
	nb_color++;
      intrait.pop_front();
      trait.push_back(v);
      next = v->get_next();
      for (unsigned int i=0; i<next.size(); ++i)
      {
	v_test = next[i];
	if ((v_test->get_visit()==false) && ((find(intrait.begin(), intrait.end(), v_test))==(intrait.end())))
	  intrait.push_back(v_test);
      }  
    }
    else
    {
      j=0;
      while (intrait.empty())
      {
	if ((edges[j]->get_visit() == false) && ((find(intrait.begin(), intrait.end(), edges[j]))==(intrait.end())))
	  intrait.push_back(edges[j]);
	else
	  ++j;
      }
    }
  }
  G.set_nb_colors(nb_color);
  edges = Graph.get_edges();
  cout << "Algorithme Glouton avec parcours en largeur : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void Moteur::Glouton_profondeur()
{
  int nb_color=0, color;
  Graphe G(Graph);
  G.init_edges();
  vector<Noeud*> trait;
  vector<Noeud*> intrait;
  vector<Noeud*> edges = G.get_edges();
  vector<Noeud*> next;
  Noeud* v, *v_test;
  intrait.push_back(edges[0]);
  unsigned int t = edges.size();
  unsigned int j;
  while(trait.size() != t)
  {
    if (!intrait.empty())
    {
      v = intrait.back();
      v->set_visit(true);
      color = v->find_color();
      if (color >= nb_color)
	nb_color++;
      intrait.pop_back();
      trait.push_back(v);
      next = v->get_next();
      for (unsigned int i=0; i<next.size(); ++i)
      {
	v_test = next[i];
	if ((v_test->get_visit()==false) && ((find(intrait.begin(), intrait.end(), v_test))==(intrait.end())))
	  intrait.push_back(v_test);
      }  
    }
    else
    {
      j=0;
      while (intrait.empty())
      {
	if ((edges[j]->get_visit() == false) && ((find(intrait.begin(), intrait.end(), edges[j]))==(intrait.end())))
	  intrait.push_back(edges[j]);
	else
	  ++j;
      }
    }
  }
  G.set_nb_colors(nb_color);
  edges = Graph.get_edges();
  cout << "Algorithme Glouton avec parcours en profondeur : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void Moteur::Welsh_Powell()
{
  int color=0;
  Noeud* v, *v_test;
  Graphe G(Graph);
  G.tri_degre();
  std::vector<Noeud*> edges = G.get_edges();
  std::vector<unsigned int> un_edges;
  std::vector<Noeud*> next;
  bool exist;
  G.init_edges();
  for (unsigned int i=0; i<edges.size(); ++i)
    un_edges.push_back(i);
  while(!(un_edges.empty()))
  {
    v = edges[un_edges[0]];
    v->set_color(color);
    un_edges.erase(un_edges.begin());
    for (unsigned int i=1; i<un_edges.size(); ++i)
    {
      v_test = edges[un_edges[i]];
      next = v_test->get_next();
      if ((find(next.begin(),next.end(),v))==next.end())
      {
	exist = false;
	for (unsigned int j=0; j<next.size(); ++j)
	{
	  if (next[j]->get_color() == color)
	  {
	    exist = true;
	    j = next.size();
	  }
	}
	if (exist == false)
	{
	  v_test->set_color(color);
	  un_edges.erase(un_edges.begin()+i);
	}
      }
    }
    ++color;
  }
  G.set_nb_colors(color);
  edges = Graph.get_edges();
  cout << "Algorithme Welsh et Powell : " << endl << "Graphe colorié avec : " << color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void Moteur::DSATUR()
{
  int nb_color = 0;
  int color;
  Graphe G(Graph);
  G.tri_degre();
  std::vector<Noeud*> edges = G.get_edges();
  G.init_edges();
  edges[0]->find_color();
  nb_color++;
  edges.erase(edges.begin());
  while(!edges.empty())
  {
    tri_dsat(edges);
    color = edges[0]->find_color();
    if (color>=nb_color)
      nb_color++;
    edges.erase(edges.begin());
  }
  G.set_nb_colors(nb_color);
  edges = Graph.get_edges();
  cout << "Algorithme DSATUR : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void Moteur::NoN()
{
  int color=0;
  Graphe G(Graph);
  vector<Noeud*> edges = G.get_edges(), edges_c, soluc;
  vector<Noeud*> s, vois_2, cross, next;
  vector<vector<Noeud*>> s_edges;
  Noeud* n,* np, *test;
  bool cont = true;
  while(!(edges.empty()))
  {
    s_edges.clear();
    for (unsigned int i=0; i<edges.size(); ++i)
    {
      s.clear();
      n = edges[i];
	s.push_back(n);
	Graphe Gc(G);
	np = n;
	cont = true;
	edges_c = Gc.get_edges();
	for (unsigned int i=0; i<edges_c.size(); ++i)
	  edges_c[i]->init_g_f();
	while (cont == true)
	{
	  vois_2 = Gc.vois_2(np);
	  for (unsigned int i=0; i<vois_2.size(); ++i)
	  {
	    test=vois_2[i];
	    cross = test->cross(np);
	    test->set_f(test->get_f()+cross.size());
	    test->set_g(cross);
	  }
	  next = np->get_next();
	  next.push_back(np);
	  Gc.take_off(next);
	  if (!(Gc.get_edges().empty()))
	  {
	    np = Gc.max();
	    s.push_back(np);
	  }
	  else
	    cont = false;
	}
      s_edges.push_back(s);
    }
    s = max_s(s_edges);
    G.take_off(s);
    for (unsigned int i=0; i<s.size(); ++i)
    {
      soluc.push_back(new Noeud(s[i], color));
      s[i]->set_visit(true);
      s[i]->set_color(color);
    }
    ++color;
    edges = G.get_edges();
  }
  G.set_nb_colors(color);
  edges = Graph.get_edges();
  cout << "Algorithme Non : " << endl << "Graphe colorié avec : " << color << " couleurs" << endl;
  for (unsigned int i=0; i<edges.size(); ++i)
    cout << *edges[i] << endl;
}

void tri_dsat(std::vector< Noeud* >& edges)
{
  sort(edges.begin(),edges.end(),dsat);
}

bool dsat(Noeud* n1, Noeud* n2)
{
  if (n1->DSAT() == n2->DSAT())
  {
    if (n1->get_next().size() == n2->get_next().size())
      return (n1->get_num() < n2->get_num());
    else
      return (n1->get_next().size() > n2->get_next().size());
  }
  else
    return (n1->DSAT() > n2->DSAT()); 
}

std::vector< Noeud* > max_s(vector< std::vector< Noeud* > > s_edges)
{
  std::vector<Noeud*> sol = s_edges[0];
  unsigned int ar = compt_ar(sol);
  unsigned int ar_test;
  unsigned int ed = sol.size();
  for (unsigned int i=1; i<s_edges.size(); ++i)
  {
    ar_test = compt_ar(s_edges[i]);
    if (ar_test > ar)
    {
      sol = s_edges[i];
      ar = ar_test;
      ed = sol.size();
    }
    else
    {
      if (ar_test == ar)
      {
	if(s_edges[i].size() > ed)
	{
	  sol = s_edges[i];
	  ar = ar_test;
	  ed = sol.size();
	}
      }
    }
  }
  return sol;
}

unsigned int compt_ar(std::vector< Noeud* > edges)
{
  unsigned int c=0;
  for (unsigned int i=0; i<edges.size(); ++i)
    c+=edges[i]->get_nb_vois();
  return c;
}
