#include "utilitaire.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include "etat.h"

bool SaisieSecurisee(int &n, int b, int a)
{
    using namespace std;

    while(!(cin >> n) || n < b || n > a)
    {
        if(cin.eof())
        {
            return false;
        }
        else if(cin.fail())
        {
            cerr << "Saisie incorrecte : veuillez entré un nombre ";
            cin.clear();
            cin.ignore(numeric_limits < streamsize >::max(), '\n');
        }
        else
        {
            cerr << "La saisie n'est pas entre : " << b << " et " << a << endl;
        }
    }
    return true;
}

bool vectorSort(const State & e1, const State & e2)
{
    return e1.s_etat[0] < e2.s_etat[0];
}
bool transSort(const transition & t1, const transition & t2)
{
    return t1.alpha < t2.alpha;
}

void removeTwinVect(std::vector < std::string > &doub)
{
    for(unsigned int i = 0; i < doub.size(); i++)
    {
        for(unsigned int j = 0; j < doub.size(); j++)
        {
            if(i != j && doub[i] == doub[j])
            {
                doub.erase(doub.begin() + i);
            }
        }
    }
}
void removeTwinVect(std::vector < int >&doub)
{
    for(unsigned int i = 0; i < doub.size(); i++)
    {
        for(unsigned int j = 0; j < doub.size(); j++)
        {
            if(i != j && doub[i] == doub[j])
            {
                doub.erase(doub.begin() + i);
            }
        }
    }
}
void removeTwinTrans(std::vector < transition > &doub)
{
    for(unsigned int i = 0; i < doub.size(); i++)
    {
        for(unsigned int j = 0; j < doub.size(); j++)
        {
            if(i != j && doub[i].alpha == doub[j].alpha && doub[i].end == doub[j].end
                    && doub[i].begin == doub[j].begin)
            {
                doub.erase(doub.begin() + i);

            }
        }
    }
}
void removeTwinState(std::vector < State > &doub)
{
    for(unsigned int i = 0; i < doub.size(); i++)
    {
        for(unsigned int j = 0; j < doub.size(); j++)
        {
            if(i != j && doub[i].returnState() == doub[j].returnState())
            {
                doub.erase(doub.begin() + i);
            }
        }
    }
}

void reinitState(State & e)
{
    e.changeState(e.returnState() + 1);   // incrémente l'etat.
    e.changeStateTerminal(false);
    e.changeStateInitial(false);
    e.s_etat.clear();
    e.s_trans.clear();
}

bool cmpState(State & e, std::vector < State > &v, int &statefind)      // return true si on le trouve
{

    // plus rapide si les etats etait dans l'ordre
    unsigned int m = 0;

    // pour chaque etat du vecteur
    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(v[i].s_etat.size() == e.s_etat.size())
        {
            // pour chaque etat de l'etat
            for(unsigned int j = 0; j < e.s_etat.size(); j++)
            {
                // pour chaque etat de l'etat du vecteur
                for(unsigned int k = 0; k < v[i].s_etat.size(); k++)
                {
                    if(e.s_etat[j] == v[i].s_etat[k])
                    {
                        m++;
                    }
                }
            }
            // si on a trouver l'etat
            if(m == e.s_etat.size())
            {
                statefind = v[i].returnState();
                return true;
            }
            else
            {
                m = 0;
            }
        }
    }

    // si on n'a pas trouver

    return false;

}

std::string intToRomain(int tmp)
{

    std::string romain;
    switch (tmp)
    {
    case 1:
        romain = "I";
        break;
    case 2:
        romain = "II";
        break;
    case 3:
        romain = "III";
        break;
    case 4:
        romain = "IV";
        break;
    case 5:
        romain = "V";
        break;
    case 6:
        romain = "VI";
        break;
    case 7:
        romain = "VII";
        break;
    case 8:
        romain = "VIII";
        break;
    case 9:
        romain = "IX";
        break;
    case 10:
        romain = "X";
        break;
    case 11:
        romain = "XI";
        break;
    case 12:
        romain = "XII";
        break;
    }

    return romain;
}
