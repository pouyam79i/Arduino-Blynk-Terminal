#include "../include/terminal.h"

int pin(char type, char func, char order = 'r')
{
    if (type == 'd')
    {
        if (func == 'i')
        {
            if (order == 'r')
                return 1; // read value from digital pin
            else
                return -3; // wrong order
        }
        else if (func == 'o')
        {
            if (order == 'h')
                return 2; // set digital pin to high level
            else if (order == 'l')
                return 3; // set digital pin to low level
            else
                return -3; // wrong order
        }
        else
        {
            return -2; // wrong function of input
        }
    }
    else if (type == 'a')
    {
    }
    else
    {
        return -1; // wrong type
    }
    return 0; // nothing happend
}
