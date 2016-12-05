#ifndef COMBINATORIALINDEX_H
#define COMBINATORIALINDEX_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include <algorithm>
//#include <sstream>
//#include <string>
//#include <map>

using namespace std;

class CombinatorialIndex 
{
    private:
        int n;  // n choose k
        int k;  // n choose k
    public:
        CombinatorialIndex();
        void print();
        void operator++(){};
        vector<int> get_unoccupied(){};
        vector<int> get_occupied(){};
        long int calc_linear_index(){};
};

#endif

