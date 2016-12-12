#include "Graphe.h"

using namespace std;

Graphe::Graphe() // Constructeur par défaut
:nb_edges(0), nb_colors(0)
{}

Graphe::Graphe(const Graphe& G) // Constructeur par recopie
:edges(G.edges), nb_edges(G.nb_edges), nb_colors(G.nb_colors)
{}


void Graphe::init_edges() // Réinitialisation des noeuds du graphe i.e. remise à zéro des couleurs et noeud non visité
{
  for (unsigned int i=0; i<edges.size(); ++i)
  {
    edges[i]->set_color(-1);
    edges[i]->set_visit(false);
  }
}

void Graphe::set_graphe(const string& _namefile) // Initialisation d'un graphe à partir d'un fichier texte
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
      if(line.size() > 0)
      {      
	link = string_tokenizer(line);
	num1 = atoi(link[1].c_str());
	num2 = atoi(link[2].c_str());
	edges[num1-1]->add_next(edges[num2-1]);
	edges[num2-1]->add_next(edges[num1-1]);
      }
    }
  }
}


std::vector< Noeud* > Graphe::get_edges() const // Getter sur les noeuds du graphe
{
  return edges;
}

unsigned int Graphe::get_nb_egdes() const // Getter sur le nombre de noeuds du graphe
{
  return nb_edges;
}

unsigned int Graphe::get_nb_colors() const // Getter sur le nombre de couleur du graphe
{
  return nb_colors;
}

void Graphe::set_edges(std::vector< Noeud* >& _edges) // Setter sur les noeuds du graphe
{
  edges = _edges;
}

void Graphe::add_edge(Noeud* _edge) // Setter pour l'ajout d'un noeud au graphe
{
  edges.push_back(_edge);
}

void Graphe::set_nb_edges(unsigned int _nb_edges) // Setter sur le nombre de noeuds d'un graphe
{
  nb_edges = _nb_edges;
}

void Graphe::set_nb_colors(unsigned int _nb_colors) // Setter sur le nombre de couleur du graphe
{
  nb_colors = _nb_colors;
}


bool Graphe::verif_color() // Vérification de la coloation du graphe
{
  int color;
  Noeud* edge;
  vector<Noeud*> vois;
  for (unsigned i=0; i<edges.size(); ++i)
  {
    edge = edges[i];
    color = edge->get_color();
    if (color == -1) 
      return false;
    vois = edge->get_next();
    for (unsigned int j=0; j<vois.size(); ++j)
    {
      if (vois[j]->get_color() == color)
	return false;
    }
  }
  return true;
}

void Graphe::inc_nb_colors() // Incrémentation du nombre de couleur du graphe
{
  ++nb_colors;
}

void Graphe::tri_degre() // Tri des noeuds du graphe par degré en ordre décroissant
{
  sort(edges.begin(),edges.end(),degre);
}

void Graphe::take_off(std::vector< Noeud* > n) // Tri des noeuds du graphe par degré en ordre décroissant (vérification si les noeuds appartiennent bien au graphe)
{
  vector<Noeud*>::iterator it;
  for (unsigned int i=0; i<n.size(); ++i)
  {
    it = find(edges.begin(), edges.end(), n[i]);
    if (it != edges.end())
      edges.erase(it);
  }
}

vector< Noeud* > Graphe::vois_2(Noeud* n) // Fonction pour déterminer les voisins de distance deux d'un graphe
{
  vector<Noeud*> vois = n->get_next(); // Vecteur contenant les successeurs du noeud n
  set<Noeud*> vois2; // Set contenant les successeurs d'un successeur du noeud n avant vérification
  vector<Noeud*> result; // Vecteur servant à retourner les successeurs de successeurs du noeud n valident, mais aussi d'intermédiaire en récupérant les successeurs d'un successeur du noeud n
  set<Noeud*>::iterator it; // Iterateur de set permettant de parcourir vois2
  
  for (unsigned int i=0; i<vois.size(); ++i) // Pour tous les successeurs de n
  {
    result = vois[i]->get_next(); // On récupère leur successeur
    for (unsigned int j=0; j<result.size(); ++j) // Pour chacun de leurs successeurs
      vois2.insert(result[j]); // On les met dans le set vois2
  }
  result.clear(); // On vide result qui a servi à récupérer les successeurs de successeurs pour l'utiliser pour récupérer le résultat 
  for(it = vois2.begin(); it!=vois2.end(); ++it) // Pour chaque successeurs de successeurs récupérés
  {
    vois = (*it)->get_next(); // On récupère leur successeurs
    if((find(vois.begin(),vois.end(),n)==(vois.end())) && ((*it) != n) && ((find(edges.begin(),edges.end(),(*it)))!=edges.end())) // On regarde s'ils n'ont pas le noeud n comme successeur et s'il appartiennent bien au graphe courant
      result.push_back(*it); // Si oui, on les met dans le résultat à retourner
  }
  return result; // On retourne les successeurs de successeurs valident pour n dans le graphe courant
}

Noeud* Graphe::max() // Retourne le noeud ayant un g maximum, en cas d'égalité, un f maximum
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


void Graphe::print(ostream& out) const // Fonction transformant les informations d'un graphe sous forme de strin
{
  out << "Graphe de taille : " << edges.size() << " nombre de couleurs : " << nb_colors << '\n';
  for (unsigned int i=0; i<edges.size(); ++i)
    out << *edges[i] << endl;
}

bool degre(Noeud* n1, Noeud* n2) // Fonction de comparaison du degré de deux noeuds
{
  return (n1->get_next().size() > n2->get_next().size());
}

vector<string> string_tokenizer(string str) // Fonction de décomposition d'un string par caractère ' '
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
