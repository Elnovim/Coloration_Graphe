#include "Moteur.h"

using namespace std;

int main(int argc, char **argv) {
  string sg = "/home/theo/projects/Coloration_Graphe/Graphe/dsjc500_5.txt";
  
  Graphe G;
  G.set_graphe(sg);
  
  Moteur M(G);
  M.Glouton();
  M.Glouton_degre();
  M.Glouton_largeur();
  M.Glouton_profondeur();
  M.Welsh_Powell();
  M.DSATUR();
  M.NoN();
}
