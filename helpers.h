#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace helpers{
    void print(const vector<int> &k);

    void print(vector<int> &k);

    void print(vector<int> &k, const int& shift);

    void print(const vector<int>&, const vector<int>&);
    
    void print(const vector<int>&, const vector<int>&, const int& shift1, const int& shift2);

    size_t nchk(const int&, const int&);
}


#endif


