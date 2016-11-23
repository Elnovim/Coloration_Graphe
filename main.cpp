#include "Moteur.h"
#include "ctime"

using namespace std;

int main(int argc, char **argv) {
  string sg = "/home/etudiant/projects/Coloration_Graphe/Graphe/r250_5.txt";
  
  Graphe G;
  G.set_graphe(sg);
  
  Moteur M(G);
//   M.Glouton();
//   M.Glouton_degre();
//   M.Glouton_largeur();
//   M.Glouton_profondeur();
//   M.Welsh_Powell();
//   M.DSATUR();
   double duration;
   clock_t start;
   start = clock();
   M.NoN();
   duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
   cout << "temps pour exécution : " << duration << endl;
}
