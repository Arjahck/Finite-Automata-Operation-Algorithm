#ifndef TRANSITION_H
#define TRANSITION_H
#include <string>
#include <iostream>

class transition
{
public:
    transition(int _begin, std::string _alpha, int _end);
    int begin;
    int end;
    std::string alpha;
};
#endif// TRANSITION_H
