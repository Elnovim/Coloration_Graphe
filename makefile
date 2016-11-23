CFLAGS = -Wall -std=c++11
OFLAGS = -O2

main.exe: main.cpp Noeud.o Graphe.o Moteur.o
	g++ -o $@ main.cpp Noeud.o Graphe.o Moteur.o $(CFLAGS) $(CFLAGS)

Noeud.o: Noeud.cpp
	g++ -c -o $@ $< $(CFLAGS) $(OFLAGS)

Graphe.o: Graphe.cpp
	g++ -c -o $@ $< $(CFLAGS) $(OFLAGS)

Moteur.o: Moteur.cpp
	g++ -c -o $@ $< $(CFLAGS) $(OFLAGS)

