#ifndef UTILITAIRE_H
#define UTILITAIRE_H
#  include <iostream>
#  include <limits>
#  include "etat.h"

bool SaisieSecurisee(int &n, int a, int b); // Saisie de nombre securise
bool vectorSort(const State & e1, const State & e2);
bool transSort(const transition & t1, const transition & t2);   // Arrangement des transition

void removeTwinVect(std::vector < std::string > &doub); // Retire les doublons : lettre
void removeTwinTrans(std::vector < transition > &doub); // Retire les doublons : transition
void removeTwinVect(std::vector < int >&doub);  // Retire les doublons : entier
void removeTwinState(std::vector < State > &doub);      // Retire les doublons : Etat

void reinitState(State & e);    // reinitialise un Etat a 0
bool cmpState(State & e, std::vector < State > &v, int &statefind);     // Chercher un etat dans un vecteur d'etat
std::string intToRomain(int tmp);       // Transforme un entier en chiffre Romain



#endif // UTILITAIRE_H
