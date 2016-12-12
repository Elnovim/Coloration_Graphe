#include "Moteur.h"
#include "ctime"

using namespace std;

int main(int argc, char **argv) {
  string sg = "/home/etudiant/projects/Coloration_Graphe/Graphe/dsjc250_1.txt";
  
  Graphe G;
  G.set_graphe(sg);
  double duration;
  clock_t start;
  Moteur M(G);
  M.Glouton();
  cout << G.verif_color() << endl;
  M.Glouton_degre();
  cout << G.verif_color() << endl;
  M.Glouton_largeur();
  cout << G.verif_color() << endl;
  M.Glouton_profondeur();
  cout << G.verif_color() << endl;
  M.Welsh_Powell();
  cout << G.verif_color() << endl;
  M.DSATUR();
  cout << G.verif_color() << endl;
  start = clock();
  M.NoN();
  cout << G.verif_color() << endl;
  duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
  cout << "temps pour exécution : " << duration << endl;
}
