#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "automate.h"
#include "utilitaire.h"
#include "etat.h"


int main()
{

    std::cout << std::endl << "  Projet de Mathematique pour l'Informatique " << std::endl;
    std::cout << std::endl << "  Groupe C " << std::endl;
    std::cout << std::endl << "  Equipe C4 " << std::endl;
    std::cout << std::endl << "  Membres du groupe : Johann Subirats, Adrien Riaux, Giuseppe Porpiglia, Mathieu Cantagrel, Alexandre Vignaud" << std::endl;

    int choice = 0;

    std::string mon_fichier;
    bool rechargeAutomate;

    Automate First;

    do
    {
        rechargeAutomate = false;
        // chargement du fichier contenant l'automate
        std::cout << std::endl << "  Choississez l'automate que vous voulez lire :" << std::endl;
        std::cout << "  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 ; " << std::endl;
        std::cout << "  11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 ; " << std::endl;
        std::cout << "  21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 ; " << std::endl;
        std::cout << "  31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 40 ; " << std::endl;
        std::cout << "  41 | 42 | 44 ; " << std::endl;

        SaisieSecurisee(choice, 0, 45);
        //choice=5;
        switch (choice)
        {
        case 1:
            mon_fichier = "Automates de test/#01.txt";
            break;
        case 2:
            mon_fichier = "Automates de test/#02.txt";
            break;
        case 3:
            mon_fichier = "Automates de test/#03.txt";
            break;
        case 4:
            mon_fichier = "Automates de test/#04.txt";
            break;
        case 5:
            mon_fichier = "Automates de test/#05.txt";
            break;
        case 6:
            mon_fichier = "Automates de test/#06.txt";
            break;
        case 7:
            mon_fichier = "Automates de test/#07.txt";
            break;
        case 8:
            mon_fichier = "Automates de test/#08.txt";
            break;
        case 9:
            mon_fichier = "Automates de test/#09.txt";
            break;
        case 10:
            mon_fichier = "Automates de test/#10.txt";
            break;
        case 11:
            mon_fichier = "Automates de test/#11.txt";
            break;
        case 12:
            mon_fichier = "Automates de test/#12.txt";
            break;
        case 13:
            mon_fichier = "Automates de test/#13.txt";
            break;
        case 14:
            mon_fichier = "Automates de test/#14.txt";
            break;
        case 15:
            mon_fichier = "Automates de test/#15.txt";
            break;
        case 16:
            mon_fichier = "Automates de test/#16.txt";
            break;
        case 17:
            mon_fichier = "Automates de test/#17.txt";
            break;
        case 18:
            mon_fichier = "Automates de test/#18.txt";
            break;
        case 19:
            mon_fichier = "Automates de test/#19.txt";
            break;
        case 20:
            mon_fichier = "Automates de test/#20.txt";
            break;
        case 21:
            mon_fichier = "Automates de test/#21.txt";
            break;
        case 22:
            mon_fichier = "Automates de test/#22.txt";
            break;
        case 23:
            mon_fichier = "Automates de test/#23.txt";
            break;
        case 24:
            mon_fichier = "Automates de test/#24.txt";
            break;
        case 25:
            mon_fichier = "Automates de test/#25.txt";
            break;
        case 26:
            mon_fichier = "Automates de testt/#26.txt";
            break;
        case 27:
            mon_fichier = "Automates de test/#27.txt";
            break;
        case 28:
            mon_fichier = "Automates de test/#28.txt";
            break;
        case 29:
            mon_fichier = "Automates de test/#29.txt";
            break;
        case 30:
            mon_fichier = "Automates de test/#30.txt";
            break;
        case 31:
            mon_fichier = "Automates de test/#31.txt";
            break;
        case 32:
            mon_fichier = "Automates de test/#32.txt";
            break;
        case 33:
            mon_fichier = "Automates de test/#33.txt";
            break;
        case 34:
            mon_fichier = "Automates de test/#34.txt";
            break;
        case 35:
            mon_fichier = "Automates de test/#35.txt";
            break;
        case 36:
            mon_fichier = "Automates de test/#36.txt";
            break;
        case 37:
            mon_fichier = "Automates de test/#37.txt";
            break;
        case 38:
            mon_fichier = "Automates de test/#38.txt";
            break;
        case 39:
            mon_fichier = "Automates de test/#39.txt";
            break;
        case 40:
            mon_fichier = "Automates de test/#40.txt";
            break;
        case 41:
            mon_fichier = "Automates de test/#41.txt";
            break;
        case 42:
            mon_fichier = "Automates de test/#42.txt";
            break;
        case 44:
            mon_fichier = "Automates de test/#44.txt";
            break;
        default:
            std::cerr << " N'est pas cense arriver" << std::endl;
            return EXIT_FAILURE;
            break;
        }
        std::cout << std::endl;

        if(!First.LectureAutomate(mon_fichier))
        {
            std::cerr << " Verifier votre fichier. ";
            std::cout << " Rechager ? (0 : Non | 1 : Oui ) : ";
            SaisieSecurisee(choice, 0, 1);
            if(choice)
            {
                rechargeAutomate = true;
                continue;
            }
            else
            {
                std::cerr << " Aucun automate charge " << std::endl;
                return EXIT_FAILURE;
            }
        }
        // Affichage automate initial
        std::cout << " Automate 1 : " << std::endl;
        First.afficherAutomate(1);
        std::cout << "Appuyer sur entree pour determiniser l'automate  " << std::endl;
        getchar();
        getchar();

        // Determinisation
        Automate Third = First;
        std::cout << " Automate deterministe : " << std::endl;

        if(Third.EstDeterministe())
        {
            std::cout << std::endl << " L'automate est deterministe " << std::endl;
            Third.afficherAutomate(3);
            std::cout << std::endl << "Appuyer sur entree pour charger" << std::endl;
            getchar();
        }
        else
        {
            std::cout << std::endl <<" L'automate est non-deterministe : Determinisation" << std::endl;
            std::cout << "Appuyer sur entree pour continuer; " << std::endl;
            getchar();

            Third.Determinisation();
            Third.afficherAutomate(3);
        }
        std::cout << " Automate deterministe et complet : " << std::endl;

        // Completion
        Automate Fourth = Third;

        if(Fourth.EstComplet())
        {
            std::cout << std::endl << " L'automate est complet ";
            if(Fourth.Completion(true))
            {
                std::cout << "Appuyer sur entree pour continuer " << std::endl;
                getchar();
                std::cout << " Un etat poubelle a ete ajoute " << std::endl;
                Fourth.afficherAutomate(4);

            }
            else
            {
                Fourth.afficherAutomate(3);
            }
        }
        else
        {
            std::
            cout << " L'automate n'est pas complet, on le complete " << std::endl;
            Fourth.Completion(false);
            std::cout << "Appuyer sur entree pour continuer " << std::endl;
            getchar();
            Fourth.afficherAutomate(4);
        }

        // Complementarisation de l'automate déterministe complet
        Automate Six = Fourth;
        Six.Complementaire(6);

        std::cout << "Appuyer sur entree pour continuer " << std::endl;
        getchar();

        Automate Second = First;
        std::cout << "Appuyer sur entree pour continuer " << std::endl;
        getchar();
        std::cout << " Automate deterministe complet et minimal " << std::endl;

        // Minimisation
        std::cout << std::endl << " Minimisation de l'automate " << std::endl;
        Automate Fifth = Fourth;

        Fifth.Minimisation();

        std::cout << "Appuyer sur entree pour continuer " << std::endl;
        getchar();
        Fifth.afficherAutomate(5);
        std::cout << "Appuyer sur entree pour continuer " << std::endl;
        getchar();



        // Standardisation
        std::cout << " Automate standard " << std::endl;
        Second.Standard();     // Vérification ET standardisation a defaut
        Second.afficherAutomate(2);

        std::cout << "Appuyer sur entree pour continuer " << std::endl;
        getchar();

        // Reconnaissance du mot
        do
        {
            std::cout << " Que voulez vous faire ? " << std::endl;
            std::cout << " Lire le mot sur ?  : " << std::endl;
            std::cout << " 1 : Automate deterministe " << std::endl;
            std::cout << " 2 : Automate deterministe et complet " << std::endl;
            std::cout << " 3 : Automate minimal " << std::endl;
            std::cout << " 4 : Automate standard " << std::endl;
            std::cout << " 0 : Quitter : ";


            SaisieSecurisee(choice, 0, 4);
            switch (choice)
            {
            case 1:
                Third.ReconnaissanceMot();
                break;
            case 2:
                Fourth.ReconnaissanceMot();
                break;
            case 3:
                Fifth.ReconnaissanceMot();
                break;
            case 4:
                Second.ReconnaissanceMot();
                break;
            default:
                break;
            }
        }
        while(choice);      // on quitte si 0

        std::cout << " Que voulez vous faire ? " << std::endl;
        std::cout << " 0 : quitter | 1 : Recharger un automate : ";

        SaisieSecurisee(choice, 0, 1);
        if(choice)
        {
            rechargeAutomate = true;

        }

    }
    while(rechargeAutomate);

    return 0;
}
