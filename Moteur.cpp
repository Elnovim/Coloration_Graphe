#include "Moteur.h"

using namespace std;

Moteur::Moteur() // Constructeur par défaut
{}

Moteur::Moteur(Graphe _Graph) // Constructeur par recopie
:Graph(_Graph)
{}

void Moteur::Glouton() // Algorithme Glouton, coloration du graphe noeud après noeud sans retour en arrière selon l'ordre du graphe initial (coloration noeud 1, noeud 2, noeud 3...)
{
  int nb_color = 0; // nombre de couleur utilisé
  int color; // La couleur utilisée pour la coloration du graphe en traitement
  Graphe G(Graph); // Copie du graphe à colorier 
  std::vector<Noeud*> edges = G.get_edges(); // Récupération de tous les noeuds du graphe
  
  G.init_edges(); // On initialise les noeuds (on met leur couleur à -1 au cas où l'on aurait déjà coloré le graphe)
  for (unsigned int i=0; i<edges.size(); ++i) // Parcours des noeuds
  {
    color = edges[i]->find_color(); // On regarde quelle couleur minimum peut recevoir le noeud en traitement
    if (color >= nb_color) // Si on vient de d'utiliser une nouvelle couleur
      ++nb_color; // On incrémente le nombre de couleur totale
  }
  G.set_nb_colors(nb_color); // On met le nombre de couleur associé au graphe colorié
  
  cout << "Algorithme Glouton simple : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl; // Affichage de la coloration par algorithme Glouton
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}



void Moteur::Glouton_degre() // Algorithme Glouton où le graphe est trié selon le degré des noeuds en ordre décroissant
{
  int nb_color = 0; // nombre de couleur utilisé
  int color; // La couleur utilisée pour la coloration du graphe en traitement
  Graphe G(Graph); // Copie du graphe à colorier 
  G.init_edges(); // On initialise les noeuds (on met leur couleur à -1 au cas où l'on aurait déjà coloré le graphe)
  G.tri_degre(); // On trie le graphe selon le degré des noeuds en ordre décroissant
  std::vector<Noeud*> edges = G.get_edges(); // Récupération de tous les noeuds du graphe
  
  for (unsigned int i=0; i<edges.size(); ++i) // Parcours des noeuds
  {
    color = edges[i]->find_color(); // On regarde quelle couleur minimum peut recevoir le noeud en traitement
    if (color >= nb_color) // Si on vient de d'utiliser une nouvelle couleur
      ++nb_color; // On incrémente le nombre de couleur totale
  }
  G.set_nb_colors(nb_color); // On met le nombre de couleur associé au graphe colorié
  
  edges = Graph.get_edges(); // On récupère les noeuds du graphe initial pour récupérer l'ordre initiale
  cout << "Algorithme Glouton trié selon le degré des noeuds : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl; // Affichage de la coloration par algorithme Glouton avec graphe trié selon le degré des noeuds
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}



void Moteur::Glouton_largeur() // Algorithme Glouton par parcours en largeur du graphe
{
  Graphe G(Graph); // Copie du graphe à colorier 
  G.init_edges(); // On initialise les noeuds (on met leur couleur à -1 au cas où l'on aurait déjà coloré le graphe)
  list<Noeud*> intrait; // Liste des noeuds à traiter lors du parcours en largeur du graphe
  vector<Noeud*> trait; // Vector des noeuds déjà traités lors du parcours en largeur du graphe
  vector<Noeud*> next; // Vector pour récupérer les successeurs d'un noeud
  vector<Noeud*> edges = G.get_edges(); // Récupération de tous les noeuds du graphe
  Noeud* v; // Noeud en cours de traitement du parcours
  Noeud *v_test; // Noeud successeur de v en traitement
  int nb_color = 0; // nombre de couleur utilisé
  int color; // La couleur utilisée pour la coloration du graphe en traitement
  unsigned int t = edges.size(); // int pour éviter de calculer plusieurs fois edges.size()
  unsigned int j; // int pour le traitement d'une boucle while
  
  intrait.push_back(edges[0]); // Comencement du parcours en largeur par le premier noeud du graphe
  while(trait.size() != t) // Tant que tous les noeuds n'ont pas été traités
  {
    if (!intrait.empty()) // Si la liste des noeuds à traiter n'est pas vide
    {
      v = intrait.front(); // On récupère le premier élément de la liste dans v
      intrait.pop_front(); // On retire ce noeud de la liste
      v->set_visit(true); // On déclare ce noeud comme étant visité
      trait.push_back(v); // On rajoute ce noeud au noeud traité
      color = v->find_color(); // On le colore avec la plus petite couleur petite
      if (color >= nb_color) // Si on a ajouté une nouvelle couleur
	nb_color++; // On incrémente le nombre de couleur total
      next = v->get_next(); // On récupère les noeuds successeur du noeud en traitement.
      for (unsigned int i=0; i<next.size(); ++i) // Pour tous les successeurs
      {
	v_test = next[i]; // On regarde chaque noeud successeur
	if ((v_test->get_visit()==false) && ((find(intrait.begin(), intrait.end(), v_test))==(intrait.end()))) // Si ce noeud n'a pas été visité et ne fais pas déjà parti de la liste des noeuds à traiter
	  intrait.push_back(v_test); // On rajoute le noeud au noeud à traiter
      }  
    }
    else // Si la liste des noeuds à traiter est vide
    {
      j=0;
      while (intrait.empty()) // Tant que la liste des noeuds à traiter est vide
      {
	if ((edges[j]->get_visit() == false)) // On regarde un à un les noeuds du graphe et on récupère celui qui n'a pas encore été visité
	  intrait.push_back(edges[j]); // On met ce noeud dans la liste des noeuds à traiter
	else
	  ++j;
      }
    }
  }
  G.set_nb_colors(nb_color); // On met le nombre de couleur associé au graphe colorié
  
  edges = Graph.get_edges(); // On récupère les noeuds du graphe initial pour récupérer l'ordre initiale
  cout << "Algorithme Glouton avec parcours en largeur : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl; // Affichage de la coloration par algorithme Glouton et parcours en largeur du graphe
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}



void Moteur::Glouton_profondeur() // Algorithme Glouton par parcours en profondeur du graphe
{
  Graphe G(Graph); // Copie du graphe à colorier 
  G.init_edges(); // On initialise les noeuds (on met leur couleur à -1 au cas où l'on aurait déjà coloré le graphe)
  vector<Noeud*> intrait; // Vector des noeuds à traiter lors du parcours en largeur du graphe
  vector<Noeud*> trait; // Vector des noeuds déjà traités lors du parcours en largeur du graphe
  vector<Noeud*> next; // Vector pour récupérer les successeurs d'un noeud
  vector<Noeud*> edges = G.get_edges(); // Récupération de tous les noeuds du graphe
  Noeud* v; // Noeud en cours de traitement du parcours
  Noeud *v_test; // Noeud successeur de v en traitement
  int nb_color = 0; // nombre de couleur utilisé
  int color; // La couleur utilisée pour la coloration du graphe en traitement
  unsigned int t = edges.size(); // int pour éviter de calculer plusieurs fois edges.size()
  unsigned int j; // int pour le traitement d'une boucle while
  
  intrait.push_back(edges[0]); // Comencement du parcours en largeur par le premier noeud du graphe
  while(trait.size() != t) // Tant que tous les noeuds n'ont pas été traités
  {
    if (!intrait.empty()) // Si la liste des noeuds à traiter n'est pas vide
    {
      v = intrait.back(); // On récupère le premier élément du vecteur dans v
      intrait.pop_back(); // On retire ce noeud du vecteur
      v->set_visit(true); // On déclare ce noeud comme étant visité
      trait.push_back(v); // On rajoute ce noeud au noeud traité
      color = v->find_color(); // On le colore avec la plus petite couleur petite
      if (color >= nb_color) // Si on a ajouté une nouvelle couleur
	nb_color++; // On incrémente le nombre de couleur total
      next = v->get_next(); // On récupère les noeuds successeur du noeud en traitement.
      for (unsigned int i=0; i<next.size(); ++i) // Pour tous les successeurs
      {
	v_test = next[i]; // On regarde chaque noeud successeur
	if ((v_test->get_visit()==false) && ((find(intrait.begin(), intrait.end(), v_test))==(intrait.end()))) // Si ce noeud n'a pas été visité et ne fais pas déjà parti de la liste des noeuds à traiter
	  intrait.push_back(v_test); // On rajoute le noeud au noeud à traiter
      }  
    }
    else // Si la liste des noeuds à traiter est vide
    {
      j=0;
      while (intrait.empty()) // Tant que le vector des noeuds à traiter est vide
      {
	if ((edges[j]->get_visit() == false)) // On regarde un à un les noeuds du graphe et on récupère celui qui n'a pas encore été visité
	  intrait.push_back(edges[j]); // On met ce noeud dans le vecteur des noeuds à traiter
	else
	  ++j;
      }
    }
  }
  G.set_nb_colors(nb_color); // On met le nombre de couleur associé au graphe colorié
  
  edges = Graph.get_edges(); // On récupère les noeuds du graphe initial pour récupérer l'ordre initiale
  cout << "Algorithme Glouton avec parcours en profondeur : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl; // Affichage de la coloration par algorithme Glouton et parcours en profondeur du graphe
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}



void Moteur::Welsh_Powell() // Algorithme Glouton Welsh et Powell
{
  Graphe G(Graph); // Copie du graphe à colorier 
  G.init_edges(); // On initialise les noeuds (on met leur couleur à -1 au cas où l'on aurait déjà coloré le graphe)
  G.tri_degre(); // On trie le graphe selon le degré des noeuds en ordre décroissant
  int color=0; // La couleur utilisée pour la coloration du graphe, pour l'algorithme Welsh et Powell, on colorie tous les noeuds possibles avec la première couleur, puis avec la suivante...
  Noeud* v; // Noeud en cours de traitement de l'algorithme
  Noeud *v_test; // Noeud successeur de v en traitement
  std::vector<Noeud*> next; // Vector permettant de récupérer les successeurs d'un noeud
  std::vector<Noeud*> edges = G.get_edges(); // Vector contenant tous les noeuds du graphe
  bool exist; // bool permettant de savoir si le voisin d'un noeud est déjà colorié avec la couleur que l'on souhaite attriver à ce noeud
  
  while(!(edges.empty())) // Tant que tous les noeuds n'ont pas été coloriés
  {
    v = edges[0]; // On récupère le premier noeuds du vecteur des noeuds encore à traiter 
    v->set_color(color); // On lui attribue la couleur à laquelle le traitement est rendu
    edges.erase(edges.begin()); // On l'enlève du vecteur des noeuds à traiter
    for (unsigned int i=0; i<edges.size(); ++i) // On regarde un à un les autres noeuds, toujours dans l'ordre après tri de le degré
    {
      v_test = edges[i]; // On récupère ces noeuds
      next = v_test->get_next(); // On récupère leurs successeurs
      if ((find(next.begin(),next.end(),v))==next.end()) // Si le noeud initial v en traitement ne fait pas partie de ses voisins
      {
	exist = false; // On initialise exist à false
	for (unsigned int j=0; j<next.size(); ++j) // Pour tous les noeuds successeurs
	{
	  if (next[j]->get_color() == color) // On regarde s'il en existe un qui aurait déjà la couleur du moment attribuée
	  {
	    exist = true; // Si oui, on instancie exist à true
	    j = next.size(); // et on fini de regarder les successeurs
	  }
	}
	if (exist == false) // Si exist est à false i.e. le noeud v_test n'a pas v comme successeurs, ni de successeurs ayant déjà la couleur du moment attribuée
	{
	  v_test->set_color(color); // Alors on colorie ce noeud avec la couleur du moment
	  edges.erase(edges.begin()+i); // On retire ce noeud du vecteur des noeuds à traiter
	}
      }
    }
    if (!(edges.empty())) // Si il reste des noeuds à traiter
      ++color; // On incrémente le nombre de couleur à utiliser
  }
  G.set_nb_colors(color); // On met le nombre de couleur associé au graphe colorié
  
  edges = Graph.get_edges(); // On récupère les noeuds du graphe initial pour récupérer l'ordre initial
  cout << "Algorithme Welsh et Powell : " << endl << "Graphe colorié avec : " << color << " couleurs" << endl; // Affichage de la coloration par l'algorithme Glouton Welsh et Powell
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}

void Moteur::DSATUR() // Algorithme Glouton DSATUR
{
  int nb_color = 0; // nombre de couleur utilisé
  int color; // La couleur utilisée pour la coloration du graphe en traitement
  Graphe G(Graph); // Copie du graphe à colorier 
  G.init_edges(); // On initialise les noeuds (on met leur couleur à -1 au cas où l'on aurait déjà coloré le graphe)
  G.tri_degre(); // On trie le graphe selon le degré des noeuds en ordre décroissant
  std::vector<Noeud*> edges = G.get_edges(); // Vector contenant tous les noeuds du graphe
  
  edges[0]->find_color(); // On attribue la première couleur au premier noeud
  nb_color++;	// On augmente ainsi le nombre de couleur maximum utilisée
  edges.erase(edges.begin()); // On supprime ce noeud du vecteur des noeuds à traiter
  while(!edges.empty()) // Tant que tous les noeuds n'ont pas été coloriés
  {
    tri_dsat(edges); // On tri le vecteur selon DSAT par ordre décroissant
    color = edges[0]->find_color(); // On colorie le noeud ayant le plus grand DSAT
    if (color>=nb_color) // Si on a attribuée une nouvelle couleur
      nb_color++; // On augmente le nombre de couleur maximum
    edges.erase(edges.begin());	// On enlève ce noeud des noeuds à traiter
  }
  G.set_nb_colors(nb_color); // On met le nombre de couleur associé au graphe colorié
  
  edges = Graph.get_edges(); // On récupère les noeuds du graphe initial pour récupréer l'ordre initial
  cout << "Algorithme DSATUR : " << endl << "Graphe colorié avec : " << nb_color << " couleurs" << endl; // Affichage de la coloration par l'algorithme Glouton DSATUR
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}

void Moteur::NoN() // Algorithme constructif NoN (Neighbours of Neighbours)
{
  int color=0; // La couleur utilisée pour la coloration du graphe, pour l'algorithme NoN, on calcule les cliques à partir de chaque noeuds et on colorie la meilleur avec la première couleur puis on recomence...
  Graphe G(Graph); // Copie du graphe à colorier
  Noeud* n; // Noeud courant d'où l'on commence pour l'élaboration de clique
  Noeud* np; // Noeud que l'on traite pour savoir si l'on peut le rajouter à la clique de noeud initial n
  Noeud* test; // Noeud successeur de successeur de np
  vector<Noeud*> edges = G.get_edges(); // Vector contenant tous les noeuds du graphe général
  vector<Noeud*> edges_c; // Vector contenant tous les noeuds du graphe lors de la recherche de clique
  vector<Noeud*> vois_2; // Vector contenant les successeurs de successeurs dans le graphe courant par rapport au noeud np
  vector<Noeud*> cross; // Vector contenant l'intersection des successeurs de np avec les successeurs de test
  vector<Noeud*> next; // Vector contenant les successeurs de np ainsi que np, nécessaire à leur retrait dans edges_c
  vector<Noeud*> s; // Vector contenant une clique élaborée à partir de n
  vector<vector<Noeud*>> s_edges; // Vector contenant toute les cliques élaborées à partir de tous les noeuds de edges
  bool cont = true; // bool permettant de savoir si la construction d'une clique est fini ou non
  
  while(!(edges.empty())) // Tant que le graphe n'est pas vide
  {
    s_edges.clear(); // On vide les cliques précédemment créées
    
    for (unsigned int i=0; i<edges.size(); ++i) // Pour tous les noeuds du graphe courant edges
    {
      Graphe Gc(G); // On récupère une copie du graphe courant
      
      n = edges[i]; // On récupère le noeud initial de la clique à construire
      np = n; // On commence le traitement à partir du noeud initial n
      cont = true; // On instancie cont à true
      edges_c = Gc.get_edges(); // On récupère le noeud du graphe
      
      s.clear(); // On vide la clique précédemment créée
      s.push_back(n); // On initialise la nouvelle clique avec le noeud initial n
      
      for (unsigned int j=0; j<edges_c.size(); ++j) //Pour tous les noeuds du graphe
	edges_c[j]->init_g_f(); // On initialise leurs valeurs g et f
      
      while (cont == true) // Tant que cont est à true
      {
	vois_2 = Gc.vois_2(np); // On calcule les successeurs de successeurs du noeud en traitement actuel np
	
	for (unsigned int j=0; j<vois_2.size(); ++j) // Pour tous les noeuds successeurs de successeurs de np
	{
	  test=vois_2[j]; // On les récupère un à un
	  cross = test->cross(np); // On récupère l'intersection avec le noeud en traitement np
	  test->set_f(test->get_f()+cross.size()); // On met à jour sa valeur f
	  test->set_g(cross); // On met à jour sa valeur g
	}
	
	next = np->get_next(); // On récupère les successeurs de np
	next.push_back(np); // On y ajoute np
	Gc.take_off(next); // On les enlève du graphe
	
	if (!(Gc.get_edges().empty())) // Si le graphe n'est pas vide
	{
	  np = Gc.max(); // On récupère le prochain noeud à traiter
	  s.push_back(np); // Et on le rajoute à la clique en construction
	}
	else // Sinon
	  cont = false; // La construction de la clique de noeud initial n est terminée, on passe à la construction de clique suivante
      } // La clique courante est fini d'être construite
      s_edges.push_back(s); // On ajoute la clique nouvellement construite à toutes les cliques construitent pour le graphe actuel
    } // Toutes les cliques du graphe actuel ont été construitent
    
    s = max_s(s_edges); // On récupère la clique la plus intéressante
    G.take_off(s); // On supprime les noeuds de cette clique du graphe initial G
    
    for (unsigned int i=0; i<s.size(); ++i) // Pour tous les noeuds de la clique choisie
    {
      s[i]->set_visit(true); // On met ses noeuds comme étant visité
      s[i]->set_color(color); // On colorie les noeuds avec la couleur actuelle
    }
    ++color; // On incrémente la couleur
    edges = G.get_edges(); // On récupère les noeuds du graphe mise à jour après suppression de la clique
  } // Traitement de l'algorithme terminé
  G.set_nb_colors(color); // On met le nombre de couleur associé au graphe colorié
  
  edges = Graph.get_edges(); // On récupère les noeuds du graphe initial pour récupréer l'ordre initial
  cout << "Algorithme NoN : " << endl << "Graphe colorié avec : " << color << " couleurs" << endl; // Affichage de la coloration par l'algorithme constructif NoN (Neighbours of Neighbours)
//   for (unsigned int i=0; i<edges.size(); ++i)
//     cout << *edges[i] << endl;
}

void tri_dsat(std::vector< Noeud* >& edges) // Tri de vecteur selon DSAT
{
  sort(edges.begin(),edges.end(),dsat);
}

bool dsat(Noeud* n1, Noeud* n2) // Fonction de comparaison de DSAT pour la fonction tri_dsat
{
  if (n1->DSAT() == n2->DSAT()) // Si le DSAT des deux noeuds est égal
  {
    if (n1->get_next().size() == n2->get_next().size()) // Et si leur nombre de successeurs est égal
      return (n1->get_num() < n2->get_num()); // On retourne si le numéro de n1 est plus petit que celui de n2
    else // Sinon
      return (n1->get_next().size() > n2->get_next().size()); // On retourne si n1 à plus de successeurs que n2
  }
  else // Sinon
    return (n1->DSAT() > n2->DSAT()); // On retourne si n1 à un DSAT plus grand que n2
}

std::vector< Noeud* > max_s(vector< std::vector< Noeud* > > s_edges) // Fonction qui retourner la clique la plus intéressante parmis un ensemble de clique i.e. celle qui a le plus d'arrête, en cas d'égalité, celle qui contient le plus de noeud
{
  std::vector<Noeud*> sol = s_edges[0]; // On récupère la première clique
  unsigned int ed = sol.size(); // On enregistre le nombre de noeud de la clique
  unsigned int ar = compt_ar(sol); // On enregistre son nombre d'arrête
  unsigned int ar_test; // Contiendra le nombre d'arrête de la clique à comparer
  
  for (unsigned int i=1; i<s_edges.size(); ++i) // Pour toutes les autres cliques
  {
    ar_test = compt_ar(s_edges[i]); // On récupère le nombre d'arrêtes de la clique à comparer
    if (ar_test > ar) // Si la clique testée a plus d'arrête que la clique enregistrée
    {
      sol = s_edges[i]; // On enregistre la clique testée
      ar = ar_test;
      ed = sol.size();
    }
    else // Sinon
    {
      if (ar_test == ar) // Si le nombre d'arrêtes est égal
      {
	if(s_edges[i].size() > ed) // Si la clique testée a plus de noeuds que la clique enregistrée
	{
	  sol = s_edges[i]; // On enregistre la clique testée
	  ar = ar_test;
	  ed = sol.size();
	}
      }
    }
  }
  return sol; // On retourne la meilleur clique
}

unsigned int compt_ar(std::vector< Noeud* > edges) // Fonction pour compter le nombre d'arrêtes d'un noeud
{
  unsigned int c=0;
  for (unsigned int i=0; i<edges.size(); ++i)
    c+=edges[i]->get_nb_vois();
  return c;
}
