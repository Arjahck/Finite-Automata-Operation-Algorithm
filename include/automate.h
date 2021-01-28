#ifndef AUTOMATE_H
#define AUTOMATE_H
#  include <iostream>
#  include <vector>
#  include <algorithm>
#  include <cstdlib>
#  include <fstream>
#  include <string>
#  include "utilitaire.h"
#  include "etat.h"
#  include "transition.h"


class Automate
{
public:
    bool LectureAutomate(std::string mon_fichier);

    void Standard();                 // automate standardisation
    bool EstDeterministe();               // automate deterministe?
    void Determinisation();                //determinisation;
    bool EstComplet();                    // automate apres determinisation complet?
    bool Completion(bool Comp);           // Completion
    void Minimisation();    // Minimisation


    void Complementaire(int elem); //  Complementaire
    void afficherAutomate(int statut);      // Affichage de l'automate
    void ReconnaissanceMot();              // Reconnaissance d'un mot

private:
    std::vector < int >ei;       // etat initiaux
    std::vector < int >ef;       // etat finaux
    std::vector < std::string > alphabet;        // Alphabet lu
    std::vector < transition > a_trans;  // tableau de structure des transition de l'automate complet.
    std::vector < State > Etat;

    void afficherMinimal(std::vector < std::vector < int > >state);

};
#endif// AUTOMATE_H
