#include "factorial.h"

int factorial::computeFact(const int factorialNumber)
{

    if (factorialNumber == 0)
    {
        return 1;
    }
    else if (factorialNumber == 1)
    {
        return 1;
    }
    else if (factorialNumber == 2)
    {
        return 2;
    }
    else if (factorialNumber == 3)
    {
        return 6;
    }
    if (factorialNumber == 4)
    {
        return 24;
    }
    if (factorialNumber == 5)
    {
        return 120;
    }
    else
    {
        return factorialNumber * computeFact(factorialNumber - 1);
    }
}
