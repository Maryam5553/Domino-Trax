CPP = g++ --std=c++11 -Wall
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all : go

go : main.o PartieDomino.o PartieTrax.o Partie.o Grille.o Sac.o TuileDomino.o TuileTrax.o Tuile.o
	$(CPP) -o go main.o PartieDomino.o PartieTrax.o Partie.o Grille.o Sac.o TuileDomino.o TuileTrax.o Tuile.o $(SFML)

main.o : main.cpp Partie.hpp
	$(CPP) -c main.cpp

PartieDomino.o : PartieDomino.cpp PartieDomino.hpp Partie.hpp
	$(CPP) -c PartieDomino.cpp

PartieTrax.o : PartieTrax.cpp PartieTrax.hpp Partie.hpp
	$(CPP) -c PartieTrax.cpp

Partie.o : Partie.cpp Partie.hpp
	$(CPP) -c Partie.cpp

Grille.o : Grille.cpp Grille.hpp Tuile.hpp 
	$(CPP) -c Grille.cpp

Sac.o : Sac.cpp Sac.hpp TuileDomino.hpp TuileTrax.hpp Tuile.hpp
	$(CPP) -c Sac.cpp

TuileDomino.o : TuileDomino.cpp TuileDomino.hpp Tuile.hpp
	$(CPP) -c TuileDomino.cpp

TuileTrax.o : TuileTrax.cpp TuileTrax.hpp Tuile.hpp Couleur.hpp
	$(CPP) -c TuileTrax.cpp

Tuile.o : Tuile.cpp Tuile.hpp
	$(CPP) -c Tuile.cpp
	
clean :
	rm *.o