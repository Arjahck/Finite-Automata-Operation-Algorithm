#include "transition.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>


transition::transition(int _begin, std::string _alpha, int _end)
{
    begin = _begin;
    alpha = _alpha;
    end = _end;
}
