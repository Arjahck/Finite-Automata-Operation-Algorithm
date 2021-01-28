#include "automate.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

bool Automate::LectureAutomate(string mon_fichier)
{
    string tmp;
    bool valid = true;            // valid controle le chargement de l'automate,
    unsigned int i = 0, k = 0;

    // On fait le menage en avance au cas ou on recharge un automate
    ef.clear();
    ei.clear();
    alphabet.clear();
    a_trans.clear();
    Etat.clear();

    ifstream VeriFile;       // sert juste a verifier le formatage du fichier

    VeriFile.open(mon_fichier.c_str());
    if(VeriFile)
    {

        VeriFile >> tmp;
        if(tmp != "Etat_initiaux")
        {
            VeriFile.close();
            return false;
        }

        if(valid)
        {
            valid = false;
            while(!((valid ) || (VeriFile.eof())))     // tant qu'on a pas trouver le mot clef ou qu'on est dans le fichier
            {
                VeriFile >> tmp;
                if(tmp == "Etat_terminaux")
                {
                    valid = true;
                }
            }
        }
        if(valid)
        {
            valid = false;
            while(!((valid == true) || (VeriFile.eof())))
            {
                VeriFile >> tmp;
                if(tmp == "Alphabet")
                {
                    valid = true;
                }
            }
        }
        if(valid)
        {
            valid = false;
            while(!((valid == true) || (VeriFile.eof())))
            {
                VeriFile >> tmp;
                if(tmp == "Automate")
                {
                    valid = true;
                }
            }
        }
        if(valid)
        {
            valid = false;
            while(!((valid == true) || (VeriFile.eof())))
            {
                VeriFile >> tmp;
                if(tmp == "FIN")
                {
                    valid = true;
                }
            }
        }
        VeriFile.close();
        if(!valid)
        {
            return false;
        }
    }
    else
    {
        cerr << "Erreur d'ouverture !" << endl;
        return false;
    }

    ifstream File;

    File.open(mon_fichier.c_str());

    if(File)
    {

        // On elimine la premiere ligne
        File >> tmp;

        // Recuppereration des etats initiaux
        File >> tmp;

        if(tmp == "Etat_terminaux")
        {
            cerr << "Pas d'etat Initial. Choisissez un fichier valide" << endl;
            File.close();
            return false;
        }
        while(tmp != "Etat_terminaux")
        {
            ei.push_back(atoi(tmp.c_str()));
            File >> tmp;
        }

        // Recuperation des etats finaux
        File >> tmp;
        while(tmp != "Alphabet")
        {
            ef.push_back(atoi(tmp.c_str()));
            File >> tmp;
        }

        // Rrecuperation de l'alphabet
        File >> tmp;
        while(tmp != "Automate")
        {
            alphabet.push_back(tmp);
            File >> tmp;
        }

        i = 0;
        k = 0;
        bool find = false, init, fin, lect = false;
        int statetmp;               // stock l'etat sous forme d'entier pour eviter de rappeler atoi en boucle
        string firsttmp;            // garde en memoire la premiere etape de la transition
        string scdtmp;              // la deuxiemme,

        while(tmp != "FIN")
        {
            if(tmp == "FIN" || !lect)
            {
                File >> tmp;
                lect = true;
            }
            // a chaque etat rencontre on verifie qu'il existe, sinon on le creer et on trie le tableau
            if(((i % 3) != 1))        // tout les cas sauf l'alphabet de transition
            {

                find = false;
                statetmp = atoi(tmp.c_str());

                if(Etat.size() != 0)
                {
                    for(k = 0; k < Etat.size(); k++)
                    {
                        if(Etat[k].returnState() == statetmp)       // si l'etat existe
                        {
                            find = true;
                        }
                    }
                }
                if(Etat.size() == 0 || find == false)   // si l'etat existait pas.
                {

                    // rechercher ses attribus init / terminal
                    init = fin = false;
                    for(k = 0; k < ei.size() && !init; k++)
                    {
                        if(ei[k] == statetmp)
                        {
                            init = true;
                        }
                    }
                    for(k = 0; k < ef.size() && !fin; k++)
                    {
                        if(ef[k] == statetmp)
                        {
                            fin = true;
                        }
                    }
                    // creation de l'etat
                    Etat.push_back(State(statetmp, init, fin));

                }
            }

            if((i % 3) == 0)          // debut de la transition
            {
                firsttmp = tmp;
            }

            find = false;
            if((i % 3) == 1)          // alphabet utilise
            {
                for(k = 0; k < alphabet.size(); k++)
                {
                    if(alphabet[k] == tmp)        // si la lettre est dans l'alphabet
                    {
                        find = true;
                    }
                }
                // si l'a lettre n'a pas ete trouvee
                if(!find)
                {
                    cerr <<
                         " La lettre de transition n'a pas ete trouvee dans l'alphabet"
                         << endl;
                    File.close();
                    return false;
                }
                scdtmp = tmp;
            }
            if((i % 3) == 2)          // arrivee
            {

                // on rajoute la transition dans l'automate et l'etat
                a_trans.push_back(transition
                                  (atoi(firsttmp.c_str()), scdtmp, atoi(tmp.c_str())));

                for(k = 0; k < Etat.size(); k++)
                {
                    if(Etat[k].returnState() == atoi(firsttmp.c_str()))
                    {
                        Etat[k].s_trans.push_back(transition
                                                  (atoi(firsttmp.c_str()), scdtmp,
                                                   atoi(tmp.c_str())));
                        // initialisation de la structure transition au seins du vector de transition de la classe Etat
                    }
                }
            }
            File >> tmp;
            i++;
        }

        File.close();

    }
    else
    {
        cerr << "Erreur a l'ouverture !" << endl;
        return false;
    }

    // on trie pour que l'affichage soit plus plus beau.
    sort(Etat.begin(), Etat.end(), vectorSort);

    if(Etat.size() == 1)
    {
        Etat[0].changeState(1);
    }
    return true;  // si tout a ete chargee normalement
}

void Automate::Standard()
{
    bool valid = true;
    unsigned int i;

    //s'il y a plus d'un etat initial, l'automate n'est pas standard
    if(ei.size() > 1)
    {
        valid = false;
    }
    ////si une transition revient sur l'etat initial l'automate n'est pas standard
    else
    {
        for(i = 0; i < a_trans.size() && valid; i++)
        {
            if(ei[0] == a_trans[i].end)
            {
                valid = false;
            }
        }
    }
    if(Etat.size() == 1)
    {
        valid = true;
    }


    if(valid)
    {
        cout << endl << " L'automate est standard" << endl;
    }
    else
    {
        cout << endl << " Automate non-standard : Standardisation de l'automate" <<
             endl << endl;

        State tmpState(0, true, false);     // Futur etat initial

        for(i = 0; i < ei.size(); i++)
        {
            // Si il est initial et terminal on le rajoute a  la liste des etat terminaux
            for(unsigned k = 0; k < ef.size() && ei[i] == ef[k]; k++)
            {
                tmpState.changeStateTerminal(true);
                ef.push_back(i);
            }

            for(unsigned int k = 0; k < Etat.size(); k++)
            {
                // Si l'etat est initial on recopie ses transitions
                for(unsigned int j = 0; (j < Etat[k].s_trans.size()) && (Etat[k].returnState() == ei[i]); j++)
                {
                    tmpState.s_trans.push_back(Etat[k].s_trans[j]);
                }
                Etat[k].changeStateInitial(false); // On enleve tout les etat initiaux de l'automate
            }
        }
        ei.clear();

        // On supprime les potentiels doublons
        for(i = 0; i < tmpState.s_trans.size(); i++)
        {
            tmpState.s_trans[i].begin = 0;    // On concidere 0 comme initial
            a_trans.push_back(tmpState.s_trans[i]);
        }
        removeTwinTrans(tmpState.s_trans);

        ei.push_back(i);    // Mise a jour de la table des etat initiaux

        Etat.push_back(tmpState);

        removeTwinState(Etat);
        sort(Etat.begin(), Etat.end(), vectorSort);
    }
}

bool Automate::EstDeterministe()
{

    if(ei.size() > 1)
    {
        return false;       // Si il y a plus d'un etat initial.
    }

    for(unsigned int i = 0; i < Etat.size(); i++)
    {
        for(unsigned int k = 0; k < Etat[i].s_trans.size(); k++)
        {
            for(unsigned int j = 0; j < Etat[i].s_trans.size(); j++)
            {
                if((Etat[i].s_trans[k].alpha == Etat[i].s_trans[j].alpha) && (j != k))
                {
                    // si il y a deux fois la meme lettre dans une transition d'un etat.
                    return false;
                }

            }
        }
    }
    return true;
}

void Automate::Determinisation()
{

    vector < State > vectTmpState;        // contient le futur vecteurr d'etat de l'automate
    State tmpState;               // contient l'etat temporaire a ajouter au tableau d'etat.

    // Creation du premier Etat de l'automate deterministe
    tmpState.changeState(1);
    tmpState.changeStateInitial(true);       // le premier etat est forcement initial

    for(unsigned int i = 0; i < ei.size(); i++)
    {
        for(unsigned int j = 0; j < Etat.size(); j++)
        {
            if(ei[i] == Etat[j].returnState())
            {
                tmpState.s_etat.push_back(ei[i]);
            }
        }
    }
    for(unsigned int i = 0; i < tmpState.s_etat.size(); i++)
    {
        for(unsigned int k = 0; k < ef.size() && tmpState.s_etat[i] == ef[k]; k++)
        {
            tmpState.changeStateTerminal(true);
        }
    }
    vectTmpState.push_back(State(tmpState));
    reinitState(tmpState);

    unsigned int it = 0;

    while(it < vectTmpState.size())       // tant qu'on a pas tester tout les etats de vectTmpState
    {

        // recuperation de l'alphabet lu par l'etat. // evite de devoir tester tous les etats par la suite
        vector < string > alphatmp;
        for(unsigned int i = 0; i < vectTmpState[it].s_etat.size(); i++)
        {
            for(unsigned int j = 0; j < Etat.size(); j++)
            {
                if(vectTmpState[it].s_etat[i] == Etat[j].returnState())
                {
                    for(unsigned int k = 0; k < Etat[j].s_trans.size(); k++)
                    {
                        alphatmp.push_back(Etat[j].s_trans[k].alpha);
                    }
                }
            }
        }
        removeTwinVect(alphatmp);   // supprime les doublons

        sort(alphatmp.begin(), alphatmp.end());


        // pour chaque lettre lu part l'etat en cour
        for(unsigned int i = 0; i < alphatmp.size(); i++)
        {

            // pour chaque etat compris par l'etat en cour
            for(unsigned int j = 0; j < vectTmpState[it].s_etat.size(); j++)
            {

                // recherche des Ã©tats
                for(unsigned int k = 0; k < Etat.size(); k++)
                {
                    if(Etat[k].returnState() == vectTmpState[it].s_etat[j])
                    {
                        for(unsigned int m = 0; m < Etat[k].s_trans.size(); m++)
                        {
                            if(Etat[k].s_trans[m].alpha == alphatmp[i])
                            {
                                tmpState.s_etat.push_back(Etat[k].s_trans[m].end);

                            }
                        }
                    }

                }

            } // fin de parcours des etats de l'etat en cour
            removeTwinVect(tmpState.s_etat);




            int statefind = 0;        // retourne l'etat trouver

            // rechercher si tmpState , n'existe pas deja
            // Si il existe :
            if(cmpState(tmpState, vectTmpState, statefind))
            {
                // on decremente le compteur en prevision de la fonction reinitial.
                tmpState.changeState(tmpState.returnState() - 1);
            }
            else      // si il n'existe pas
            {
                // recherche si le futur etat est Final
                for(unsigned int j = 0; j < tmpState.s_etat.size(); j++)
                {
                    for(unsigned int k = 0; k < ef.size(); k++)
                    {
                        if(tmpState.s_etat[j] == ef[k])
                        {
                            tmpState.changeStateTerminal(true);
                        }
                    }
                }


                // On rajoute l'etat au vecteur d'etat
                vectTmpState.push_back(State(tmpState));
                // on sauvegarde son numero pour ajouter les transitions
                statefind = tmpState.returnState();

            } // Fin si (l'etat existe

            // On met a jour les transitons de it vers le nouvel (ou non) etat
            // numero d'etat contenu dans statefind, soit recuperer, soit incrementation
            vectTmpState[it].s_trans.push_back(transition
                                               (vectTmpState[it].returnState(),
                                                alphatmp[i], statefind));
            removeTwinTrans(vectTmpState[it].s_trans);

            // On reinitialise le vecteur temporaire

            reinitState(tmpState);


        }   // fin de lecture alphabet de l'etat en cour
        alphatmp.clear();



        it++;       // tant qu'on a pas atteint la fin du stack d'etat
    }     // fin de traitement des etats

    // reconstitution de l'automate
    ei.clear();
    ei.push_back(1);      // le premier etat est forcement initial

    ef.clear();
    a_trans.clear();
    Etat.clear();

    for(unsigned int i = 0; i < vectTmpState.size(); i++)
    {
        if(vectTmpState[i].returnTerminal())
        {
            ef.push_back(vectTmpState[i].returnState());
        }
        for(unsigned int j = 0; j < vectTmpState[i].s_trans.size(); j++)
        {
            a_trans.push_back(vectTmpState[i].s_trans[j]);
        }
    }
    Etat = vectTmpState;

}

bool Automate::EstComplet()
{
    // L'automate deterministe est complet si il y a autant de transition que possible
    // nombre d'etat * taille alphabet = taille table de transition

    cout << endl << " Alphabet : " << alphabet.
         size() << " | Etat : " << Etat.size() << endl;
    cout << " Total : " << a_trans.size() << " sur :  " << alphabet.size() *
         Etat.size() << endl;
    if((alphabet.size() * Etat.size() < a_trans.size()))
    {
        cerr << " erreur lors de la determinisation " << endl;
        return EXIT_FAILURE;
    }
    if((alphabet.size() * Etat.size() == a_trans.size()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Automate::Completion(bool Comp)
{
    cout << endl;
    int dustFind = 0;
    bool dust = true;

    // Recherche si un etat est deja une poubelle
    for(unsigned int i = 0; i < Etat.size() && dust; i++)
    {
        dust = true;
        if(Etat[i].s_trans.size() == 0)
        {
            dustFind = i;     // Si il l'etat n'a pas de transition.
        }
        else
        {
            dustFind = i;
            for(unsigned int j = 0; j < Etat[i].s_trans.size() && dustFind; j++)
            {
                dustFind = i;
                if(Etat[i].s_trans[j].end != Etat[i].returnState())
                {
                    dustFind = 0; // Si un etat n'a pas de transition autre que sur lui-meme.
                }
            }
            if(dustFind)
            {
                dust = false;
            }
        }
        // Si on en a trouver un, on verifie qu'il n'est pas final
        if(dustFind)
        {
            for(unsigned int k = 0; k < ef.size(); k++)
            {
                if(Etat[i].returnState() == ef[k])
                {
                    dustFind = 0;
                    dust = true;
                }
            }
        }
    }

    // creation etat poubelle
    State trash(Etat.size() + 1, false, false);

    if(!dustFind)         // si on en a pas trouver d'etat implicite
    {
        if(!Comp)   // Si l'automate n'est pas deja complet
        {
            dustFind = Etat.size();
            for(unsigned int i = 0; i < alphabet.size(); i++)
            {
                // On met a jour les transitions de l'etat poubelle ( de lui-meme vers lui-meme )
                trash.s_trans.push_back(transition
                                        (trash.returnState(), alphabet[i],
                                         trash.returnState()));
            }
            Etat.push_back(State(trash));     // On rajoute l'etat au vecteur d'etat
            for(unsigned int i = 0; i < trash.s_trans.size(); i++)
            {
                a_trans.push_back(transition(trash.s_trans[i]));        // On met a jour les transitions
            }
        }
    }
    else
    {
        trash = Etat[dustFind];     // on recupere l'etat poubelle
        Etat.push_back(State(trash));       // on le rajoute a la fin
        removeTwinState(Etat);      // supprimera la premiere occurence trouver du double

        // On regarde si la transition existe
        for(unsigned int j = 0; j < alphabet.size(); j++)
        {
            bool Cont = true;

            for(unsigned int i = 0; i < Etat[dustFind].s_trans.size() && Cont; i++)
            {
                if(Etat[dustFind].s_trans[i].alpha == alphabet[j])
                {
                    Cont = false;
                }
            }

            // Si il faut on met a jours les tables de transitions
            if(Cont)
            {
                Etat[dustFind].s_trans.push_back(transition
                                                 (Etat[dustFind].returnState(),
                                                  alphabet[j],
                                                  Etat[dustFind].returnState()));
                a_trans.push_back(transition
                                  (Etat[dustFind].returnState(), alphabet[j],
                                   Etat[dustFind].returnState()));
            }

        }

    }


    bool find = false;

    for(unsigned int i = 0; i < Etat.size(); i++)
    {
        for(unsigned int j = 0; j < alphabet.size(); j++)
        {
            for(unsigned int k = 0; k < Etat[i].s_trans.size(); k++)
            {
                if(alphabet[j] == Etat[i].s_trans[k].alpha)
                {
                    find = true;
                }
            }
            if(!find)
            {
                Etat[i].s_trans.push_back(transition
                                          (Etat[i].returnState(), alphabet[j],
                                           Etat[dustFind].returnState()));
                a_trans.push_back(transition
                                  (Etat[i].returnState(), alphabet[j],
                                   Etat[dustFind].returnState()));
            }
            find = false;
        }
        // On trie la liste des transitions.
        sort(Etat[i].s_trans.begin(), Etat[i].s_trans.end(), transSort);
    }
    cout << endl;
    return !dust; // si on n'a rien fait on l'indique
}

void Automate::Minimisation()
{
    cout << endl;

    // Initialisation de la premier partition
    vector < vector < int > >state(Etat.size());
    vector < vector < int > >part(2);      // etat des partitions



    for(unsigned int i = 0; i < Etat.size(); i++)
    {
        state[i].push_back(Etat[i].returnState());

        if(Etat[i].returnTerminal())     // si il est terminal
        {
            state[i].push_back(1);
            part[1].push_back(Etat[i].returnState());
        }
        else
        {
            state[i].push_back(2);
            part[0].push_back(Etat[i].returnState());
        }
    }
    // Fin creation part etat initial/ terminal


    for(unsigned int i = 0; i < Etat.size(); i++)
    {
        for(unsigned int j = 0; j < Etat[i].s_trans.size(); j++)
        {
            for(unsigned int k = 0; k < state.size(); k++)
            {
                if(Etat[i].s_trans[j].end == state[k][0])
                {
                    state[i].push_back(state[k][1]);
                }
            }
        }
    }

    afficherMinimal(state);  // affichage de la premie¨re table de transitions

    bool find = false, partfind1 = false, partfind2 = false;      // si l'etat est encore valid
    unsigned int taillepart = 0;


    // boucle de minimisation, tant qu'on a de nouveau etat, ou qu'on a autant d'etat que de partition.
    while(part.size() > taillepart && part.size() != Etat.size())
    {
        cout << "Appuyer sur une touche pour continuer; " << endl;
        getchar();
        taillepart = part.size();   // Sert a savoir si le nombre de partition a changer

        part.clear();

        // Comparaison des partitions etat par etat
        for(unsigned int i = 0; i < Etat.size(); i++)
        {
            for(unsigned int j = 0; j < Etat.size(); j++)
            {
                find = true;
                for(unsigned int k = 1; k < state[i].size(); k++)
                {
                    if(i != j && i < j && find)   // si on regarde pas le meme etat ou n etat precedant et qu'on doit continuer
                    {
                        if(state[i][k] != state[j][k] && find)
                        {
                            find = false;
                        }
                        else
                        {
                            find = true;
                        }
                    }
                    else          // si i = j ou i > j
                    {
                        find = false;
                    }
                }       // fin de recherche des etat identiques

                // si on a trouver tout les etats de la table actuel || si ils ont la meme partition
                if(find)
                {
                    //  Redefinition de la table des partitions.
                    partfind1 = partfind2 = false;
                    unsigned int k = 0;

                    for(k = 0; k < part.size() && !(partfind1 || partfind2); k++)
                    {
                        if(part[k].size() > 0)
                        {
                            for(unsigned int m = 0; m < part[k].size(); m++)
                            {
                                if(part[k][m] == state[i][0])
                                {
                                    partfind1 = true;
                                }
                                if(part[k][m] == state[j][0])
                                {
                                    partfind2 = true;
                                }
                            }
                        }
                    }
                    k--;  // sorti de boucle k est decrementation
                    if(partfind1 || partfind2)
                    {
                        if(partfind1 && !partfind2)
                        {
                            part[k].push_back(state[j][0]);
                        }
                        else if(!partfind1 && partfind2)
                        {
                            part[k].push_back(state[i][0]);
                        }
                    }
                    else          // les etat n'etait dans aucune partition existante
                    {
                        // nouvelle ligne dans la table
                        part.resize(part.size() + 1);
                        part[part.size() - 1].push_back(state[i][0]);
                        part[part.size() - 1].push_back(state[j][0]);
                    }

                }       // find if


            } // fin comparaison etat
        }   // fin comparaison etat
        // si l'etat n'a aucun equivalent, il est tout seul dans sa partition
        for(unsigned int i = 0; i < state.size(); i++)      // pour chaque etat
        {
            partfind1 = false;
            for(unsigned int j = 0; j < part.size(); j++)     // on le cherche dans la table de partition
            {
                for(unsigned int k = 0; k < part[j].size(); k++)
                {
                    if(part[j][k] == state[i][0])
                    {
                        partfind1 = true;
                    }
                }
            }
            if(!partfind1)    // si on l'a pas trouver
            {
                part.resize(part.size() + 1);
                part[part.size() - 1].push_back(state[i][0]);   // on le rajoute
            }
        }

        cout << " Etat des partitions apres traitement " << endl;
        for(unsigned int i = 0; i < part.size(); i++)
        {
            cout << " " << intToRomain(i + 1) << " : ";
            for(unsigned int j = 0; j < part[i].size(); j++)
            {
                cout << part[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;


        // on met a jour le statut de state par rapport a  la nouvelle table de partition.
        for(unsigned int i = 0; i < part.size(); i++)
        {
            for(unsigned int j = 0; j < part[i].size(); j++)
            {
                for(unsigned int k = 0; k < state.size(); k++)
                {
                    if(part[i][j] == state[k][0])
                    {
                        state[k][1] = i + 1;
                    }
                }
            }
        }

        // on met a jour les partition proprement dite


        for(unsigned int i = 0; i < Etat.size(); i++)
        {
            unsigned int alphacount = 2;

            for(unsigned int j = 0; j < Etat[i].s_trans.size(); j++)
            {
                for(unsigned int k = 0; k < state.size(); k++)
                {
                    if(Etat[i].s_trans[j].end == state[k][0]
                            && alphacount <= alphabet.size() + 2)
                    {
                        state[i][alphacount] = state[k][1];
                        alphacount++;
                    }
                }
            }
        }

        afficherMinimal(state);
    }     // Fin while

    if(part.size() == Etat.size())
    {
        cout << endl << " l'automate etait minimal " << endl;
    }
    else
    {
        cout << endl << " l'automate a ete minimise " << endl;
    }
    cout << endl;


    // Mise a jour de l'etat
    State tmpState;
    int numState = 0;

    Etat.clear();
    a_trans.clear();
    for(unsigned int i = 0; i < part.size(); i++)
    {
        // Recherche du numero de la partition associer
        for(unsigned int j = 0; j < state.size(); j++)
        {
            for(unsigned int k = 0; k < part[i].size(); k++)
            {
                if(part[i][k] == state[j][0])
                {
                    numState = state[j][1];
                }
            }

        }
        tmpState.changeState(numState);
        // rechercher liste des etats de l'etat
        for(unsigned int j = 0; j < part[i].size(); j++)
        {
            tmpState.s_etat.push_back(part[i][j]);

            for(unsigned int k = 0; k < ei.size(); k++)
            {
                if(ei[k] == part[i][j])
                {
                    tmpState.changeStateInitial(true);
                }
            }
            for(unsigned int k = 0; k < ef.size(); k++)
            {
                if(ef[k] == part[i][j])
                {
                    tmpState.changeStateTerminal(true);
                }
            }
        }
        // remplissage table de transition

        for(unsigned int j = 0; j < state.size(); j++)
        {
            find = false;
            if(state[j][1] == numState && !find)      // si on est a l'etat correspondant
            {
                find = true;
                for(unsigned int k = 0; k < alphabet.size(); k++)
                {
                    tmpState.
                    s_trans.push_back(transition
                                      (numState, alphabet[k], state[j][k + 2]));
                    a_trans.push_back(transition(numState, alphabet[k], state[j][k + 2]));
                }
            }
        }
        Etat.push_back(tmpState);
        reinitState(tmpState);
    }

    // On met a jour Etat final / Initial
    ei.clear();
    ef.clear();
    for(unsigned int i = 0; i < Etat.size(); i++)
    {
        if(Etat[i].returnInitial())
        {
            ei.push_back(Etat[i].returnState());
        }
        if(Etat[i].returnTerminal())
        {
            ef.push_back(Etat[i].returnState());
        }

    }
}

void Automate::afficherMinimal(vector < vector < int > >state)
{
    // affichage automate.
    cout << "  E/S   | Etat || Part ||";
    for(unsigned int i = 0; i < alphabet.size(); i++)
    {
        cout << "  " << alphabet[i] << "  |";
    }

    cout << endl << "-------------------------";
    for(unsigned int j = 0; j < alphabet.size(); j++)
    {
        cout << "------";
    }
    string tmp;
    bool findInit, findFin;

    cout << endl;
    for(unsigned int i = 0; i < Etat.size(); i++)
    {
        for(unsigned int j = 0; j < state[i].size(); j++)
        {
            if(j == 0)
            {

                findInit = findFin = false;

                for(unsigned int k = 0; k < ei.size(); k++)
                {
                    if(ei[k] == Etat[i].returnState())
                    {
                        findInit = true;
                    }
                }

                for(unsigned int k = 0; k < ef.size(); k++)
                {
                    if(ef[k] == Etat[i].returnState())
                    {
                        findFin = true;
                    }
                }

                if(findInit)
                {
                    if(findFin)   // initial + final
                    {
                        cout << "  <-->";
                    }
                    else          // juste initial
                    {
                        cout << "  --> ";
                    }
                }
                else
                {
                    if(findFin)   // juste final
                    {
                        cout << "  <-- ";
                    }
                    else          // rien du tout
                    {
                        cout << "      ";
                    }

                }
                cout << "  | ";

                cout << "  " << state[i][j] << "  ||";
            }
            // Affichage des partitions
            if(j == 1)
            {
                tmp = intToRomain(state[i][j]);
                if(tmp.size() == 1)
                {
                    cout << "   " << tmp << "  ||";
                }
                if(tmp.size() == 2)
                {
                    cout << "  " << tmp << "  ||";
                }
                if(tmp.size() == 3)
                {
                    cout << "  " << tmp << " ||";
                }
                if(tmp.size() == 4)
                {
                    cout << " " << tmp << " ||";
                }
            }
            if(j > 1)
            {
                tmp = intToRomain(state[i][j]);
                if(tmp.size() == 1)
                {
                    cout << "  " << tmp << "  |";
                }
                if(tmp.size() == 2)
                {
                    cout << "  " << tmp << " |";
                }
                if(tmp.size() == 3)
                {
                    cout << " " << tmp << " |";
                }
                if(tmp.size() == 4)
                {
                    cout << " " << tmp << "|";
                }
            }
        }
        cout << endl << "-------------------------";
        for(unsigned int j = 0; j < alphabet.size(); j++)
        {
            cout << "------";
        }
        cout << endl;
    }
}
void Automate::Complementaire(int elem)
{
    //     Affichage de l'automate complementaire
    cout << endl << " L'automate complementaire  : " << elem << ""
         << endl << endl;

    //etats initiaux
    std::cout << "etat(s) initial(aux)" << std::endl;
    for (unsigned int p =0; p<ef.size(); p++)
    {
        std::cout<<"(" << ef[p] << ")" << std::endl;
    }
    //etats terminaux
    std::cout << "etat(s) terminal(aux)" << std::endl;
    for (unsigned int p =0; p<ei.size(); p++)
    {
        std::cout<<"(" << ei[p] << ")" << std::endl;
    }
    //table de transition

    bool findInit = false, findFin = false, findAffiche = false;
    unsigned int i = 0;

    if(elem >= 3)
    {
        cout << "  E/S   |" << "    Etat    |   ";
    }
    else
    {
        cout << "  E/S   |" << "  Etat  |   ";
    }

    for(i = 0; i < alphabet.size(); i++)
    {
        cout << alphabet[i] << "   |   ";
    }

    if(elem >= 3)
    {
        cout << endl << "----------------------";
    }
    else
    {
        cout << endl << "------------------";
    }


    for(unsigned int k = 0; k < alphabet.size(); k++)
    {
        cout << "--------";
    }
    cout << endl;

    for(i = 0; i < Etat.size(); i++)
    {
        findInit = findFin = true;
        for(unsigned int k = 0; k < ei.size(); k++)
        {
            if(ei[k] == Etat[i].returnState())
            {
                findInit = false;
            }
        }

        for(unsigned int k = 0; k < ef.size(); k++)
        {
            if(ef[k] == Etat[i].returnState())
            {
                findFin = false;
            }
        }

        if(findInit)
        {
            if(findFin)       // initial + final
            {
                cout << "  ";
            }
            else      // juste initial
            {
                cout << "  --> ";
            }
        }
        else
        {
            if(findFin)       // juste final
            {
                cout << "  <-- ";
            }
            else      // rien du tout
            {
                cout << "      ";
            }

        }
        cout << "  | ";

        // affichage Etat

        // on tient compte du nombre d'etat (jusqu'a 99)
        // affichage des numero d'etat

        if(elem >= 3)
        {
            if(Etat[i].returnState() > 9)
            {
                cout << "" << Etat[i].returnState() << ": ";
                for(unsigned int j = 0; j < Etat[i].s_etat.size(); j++)
                {
                    cout << Etat[i].s_etat[j] << " ";
                }
                for(unsigned int j = (Etat[i].s_etat.size() * 2); j < 7; j++)
                {
                    cout << " ";
                }
            }
            else if(elem == 4 && Etat[i].returnState() == Etat[Etat.size() - 1].returnState())
            {
                cout << " " << "  P     " << "  |";
            }
            else
            {
                cout << "" << Etat[i].returnState() << ": ";
                for(unsigned int j = 0; j < Etat[i].s_etat.size(); j++)
                {
                    cout << Etat[i].s_etat[j] << " ";
                }
                for(unsigned int j = (Etat[i].s_etat.size() * 2); j < 8; j++)
                {
                    cout << " ";
                }
                cout << "|";
            }
        }
        else
        {
            if(Etat[i].returnState() > 9)
            {
                cout << "  " << Etat[i].returnState() << "   |";
            }
            else if(elem == 4 && Etat[i].returnState() == Etat[Etat.size() - 1].returnState())
            {
                cout << " " << "P  " << "  |";
            }
            else
            {
                cout << "   " << Etat[i].returnState() << "   |";
            }
        }

        vector < int >varAffiche;

        // affichage des transition
        for(unsigned int j = 0; j < alphabet.size(); j++)
        {
            for(unsigned int k = 0; k < Etat[i].s_trans.size(); k++)
            {
                if(Etat[i].s_trans[k].alpha == alphabet[j])
                {
                    findAffiche = true;
                    varAffiche.push_back(Etat[i].s_trans[k].end);
                }
            }

            if(findAffiche)
            {
                // affichage des etats poubelle si AFDC
                if(elem == 4 && varAffiche[0] == Etat[Etat.size() - 1].returnState())
                {
                    cout << " " << "P" << "  |";
                }
                else
                {
                    if(elem == 2)
                    {
                        for(unsigned int k = 0; k < varAffiche.size(); k++)
                        {
                            if(varAffiche.size() == 1)
                            {
                                cout << "   " << varAffiche[k] << "   ";
                            }
                            else if(varAffiche.size() == 2)
                            {
                                cout << " " << varAffiche[k] << " ";
                            }
                            else
                            {
                                cout << "" << varAffiche[k] << " ";
                            }
                        }
                        if(varAffiche.size() == 1)
                        {
                            cout << "|";
                        }
                        else if(varAffiche.size() == 2)
                        {
                            cout << " |";
                        }
                        else
                        {
                            cout << "|";
                        }
                    }
                    else
                    {
                        cout << "   " << varAffiche[0] << "   |";
                    }
                }
            }
            else
            {
                cout << "       |";
            }
            findAffiche = false;
            varAffiche.clear();

        }

        if(elem >= 3)
        {
            cout << endl << "----------------------";
        }
        else
        {
            cout << endl << "------------------";
        }
        for(unsigned int k = 0; k < alphabet.size(); k++)
        {
            cout << "--------";
        }
        cout << endl;
    }

    cout << endl;

}


void Automate::afficherAutomate(int statut)
{
//     Affichage de l'automate lu

    cout << endl << " L'automate  : " << statut << ""
         << endl << endl;

    //etats initiaux
    std::cout << "etat(s) initial(aux)" << std::endl;
    for (unsigned int p =0; p<ei.size(); p++)
    {
        std::cout<<"(" << ei[p] << ")" << std::endl;
    }
    //etats terminaux
    std::cout << "etat(s) terminal(aux)" << std::endl;
    for (unsigned int p =0; p<ef.size(); p++)
    {
        std::cout<<"(" << ef[p] << ")" << std::endl;
    }
    //table de transition

    bool findInit = false, findFin = false, findAffiche = false;
    unsigned int i = 0;

    if(statut >= 3)
    {
        cout << "  E/S   |" << "    Etat    |   ";
    }
    else
    {
        cout << "  E/S   |" << "  Etat  |   ";
    }

    for(i = 0; i < alphabet.size(); i++)
    {
        cout << alphabet[i] << "   |   ";
    }

    if(statut >= 3)
    {
        cout << endl << "----------------------";
    }
    else
    {
        cout << endl << "------------------";
    }


    for(unsigned int k = 0; k < alphabet.size(); k++)
    {
        cout << "--------";
    }
    cout << endl;

    for(i = 0; i < Etat.size(); i++)
    {
        findInit = findFin = false;
        for(unsigned int k = 0; k < ei.size(); k++)
        {
            if(ei[k] == Etat[i].returnState())
            {
                findInit = true;
            }
        }

        for(unsigned int k = 0; k < ef.size(); k++)
        {
            if(ef[k] == Etat[i].returnState())
            {
                findFin = true;
            }
        }

        if(findInit)
        {
            if(findFin)       // initial + final
            {
                cout << "  <-->";
            }
            else      // juste initial
            {
                cout << "  --> ";
            }
        }
        else
        {
            if(findFin)       // juste final
            {
                cout << "  <-- ";
            }
            else      // rien du tout
            {
                cout << "      ";
            }

        }
        cout << "  | ";

        // affichage Etat

        // on tient compte du nombre d'etat (jusqu'a 99)
        // affichage des numero d'etat

        if(statut >= 3)
        {
            if(Etat[i].returnState() > 9)
            {
                cout << "" << Etat[i].returnState() << ": ";
                for(unsigned int j = 0; j < Etat[i].s_etat.size(); j++)
                {
                    cout << Etat[i].s_etat[j] << " ";
                }
                for(unsigned int j = (Etat[i].s_etat.size() * 2); j < 7; j++)
                {
                    cout << " ";
                }
            }
            else if(statut == 4 && Etat[i].returnState() == Etat[Etat.size() - 1].returnState())
            {
                cout << " " << "  P     " << "  |";
            }
            else
            {
                cout << "" << Etat[i].returnState() << ": ";
                for(unsigned int j = 0; j < Etat[i].s_etat.size(); j++)
                {
                    cout << Etat[i].s_etat[j] << " ";
                }
                for(unsigned int j = (Etat[i].s_etat.size() * 2); j < 8; j++)
                {
                    cout << " ";
                }
                cout << "|";
            }
        }
        else
        {
            if(Etat[i].returnState() > 9)
            {
                cout << "  " << Etat[i].returnState() << "   |";
            }
            else if(statut == 4 && Etat[i].returnState() == Etat[Etat.size() - 1].returnState())
            {
                cout << " " << "P  " << "  |";
            }
            else
            {
                cout << "   " << Etat[i].returnState() << "   |";
            }
        }

        vector < int >varAffiche;

        // affichage des transition
        for(unsigned int j = 0; j < alphabet.size(); j++)
        {
            for(unsigned int k = 0; k < Etat[i].s_trans.size(); k++)
            {
                if(Etat[i].s_trans[k].alpha == alphabet[j])
                {
                    findAffiche = true;
                    varAffiche.push_back(Etat[i].s_trans[k].end);
                }
            }

            if(findAffiche)
            {
                // affichage des etats poubelle si AFDC
                if(statut == 4 && varAffiche[0] == Etat[Etat.size() - 1].returnState())
                {
                    cout << " " << "P" << "  |";
                }
                else
                {
                    if(statut == 2)
                    {
                        for(unsigned int k = 0; k < varAffiche.size(); k++)
                        {
                            if(varAffiche.size() == 1)
                            {
                                cout << "   " << varAffiche[k] << "   ";
                            }
                            else if(varAffiche.size() == 2)
                            {
                                cout << " " << varAffiche[k] << " ";
                            }
                            else
                            {
                                cout << "" << varAffiche[k] << " ";
                            }
                        }
                        if(varAffiche.size() == 1)
                        {
                            cout << "|";
                        }
                        else if(varAffiche.size() == 2)
                        {
                            cout << " |";
                        }
                        else
                        {
                            cout << "|";
                        }
                    }
                    else
                    {
                        cout << "   " << varAffiche[0] << "   |";
                    }
                }
            }
            else
            {
                cout << "       |";
            }
            findAffiche = false;
            varAffiche.clear();

        }

        if(statut >= 3)
        {
            cout << endl << "----------------------";
        }
        else
        {
            cout << endl << "------------------";
        }
        for(unsigned int k = 0; k < alphabet.size(); k++)
        {
            cout << "--------";
        }
        cout << endl;
    }

    cout << endl;

}

void Automate::ReconnaissanceMot()
{

    string word;
    bool empty = false;
    int choice;

    cout << endl << " Que voulez vous faire ? " << endl;
    cout << " 1 : Lire un mot " << endl;
    cout << " 0 : Lire le mot vide " << endl;

    SaisieSecurisee(choice, 0, 1);
    if(choice)
    {
        cout << " Veuillez entrer le mot que vous voulez lire " << endl;
        cin >> word;
        cout << " Mot lu : " << word << "." << endl;
    }
    else
    {
        empty = true;
    }

    if(empty)     // pour un mot vide , il faut qu'un etat initial soit terminal
    {
        empty = false;
        for(unsigned int i = 0; i < ei.size(); i++)
        {
            for(unsigned int j = 0; j < ef.size() && !empty; j++)
            {
                if(ei[i] == ef[j])
                {
                    empty = true;
                }
            }
        }
        if(empty)
        {
            cout << endl << "Le mot vide est reconnu" << endl;
        }
        else
        {
            cout << "Le mot vide n'est pas reconnu" << endl;
        }

    }
    else
    {

        int etatUsed = ei[0];       // on part de l'etat initial
        bool Cont = false;
        string tmp;

        for(unsigned int i = 0; i < word.size() && !Cont; i++)
        {

            Cont = true;
            for(unsigned int j = 0; j < a_trans.size() && Cont; j++)
            {
                tmp = word[i];
                if((a_trans[j].begin == etatUsed) && (a_trans[j].alpha == tmp))
                {
                    etatUsed = a_trans[j].end;
                    Cont = false;
                }
            }
            if(Cont)
            {
                cout << " Aucune transition trouvee a partir de : " << i << " : " <<
                     word[i] << endl;
            }
        }

        if(!Cont)   // si on a fini de lire le mot
        {
            Cont = true;
            for(unsigned int i = 0; i < ef.size() && Cont; i++)
            {
                if(etatUsed == ef[i])
                {
                    cout << " Le mot est reconnu par l'automate " << endl;
                    Cont = false;
                }
            }
            if(Cont)
            {
                cout << " Le mot n'est pas reconnu par l'automate " << endl;
            }
        }

        cout << endl;
    }

}
