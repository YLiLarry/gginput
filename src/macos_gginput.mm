#include "gginput.h"
#include <iostream>
#include <cassert>

using namespace gginput;
using namespace std;

void GGInput::stop()
{
}

void GGInput::start()
{
    string input;
    cout << "press any key to exit" << endl;
    std::getline(std::cin, input);
}

