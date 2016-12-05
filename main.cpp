// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CombinatorialIndex.h"
#include <armadillo>

using namespace arma;

int main ()
{
    printf(" Hi, from main\n");
    CombinatorialIndex Ik(4,2);
    Ik.print();
    Ik.incr();
    Ik.print();

    arma::mat a = arma::zeros(4,4);
    cout << a << endl;
    return 0;
}

