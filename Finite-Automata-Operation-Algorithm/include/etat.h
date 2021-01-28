#ifndef ETAT_H
#define ETAT_H
# include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "transition.h"

class State
{

private:
    bool initial;
    bool terminal;
    int number;
public:

    std::vector < transition > s_trans;  // tableau de structure des transition de l'état.
    std::vector < int >s_etat;   // liste des états de l'etat actuel

    //constructeur
    State(int, bool, bool);
    State();

    //accesseur
    int returnState();
    bool returnInitial();
    bool returnTerminal();

    void changeState(int _number);
    void changeStateInitial(bool _initial);
    void changeStateTerminal(bool _terminal);

};

#endif// ETAT_H
