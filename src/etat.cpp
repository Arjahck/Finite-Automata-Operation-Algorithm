# include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "transition.h"
#include "etat.h"
State::State(int _number, bool _initial, bool _terminal)
{
    number = _number;
    initial = _initial;
    terminal = _terminal;
    s_etat.push_back(_number);
}

State::State()
{
    initial = false;
    terminal = false;
}

int State::returnState()
{
    return number;
}
bool State::returnInitial()
{
    return initial;
}
bool State::returnTerminal()
{
    return terminal;
}

void State::changeStateInitial(bool _initial)
{
    initial = _initial;
}
void State::changeStateTerminal(bool _terminal)
{
    terminal = _terminal;
}
void State::changeState(int _number)
{
    number = _number;
}
