#ifndef COMBINATORIALINDEX_H
#define COMBINATORIALINDEX_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
//#include <algorithm>
//#include <sstream>
//#include <string>
//#include <map>

using namespace std;

class CombinatorialIndex 
{
    private:
        int n_orbs;  
        int n_elec;  
        vector<int> config;
        void increment_comb(std::vector<int>& list, const int& Mstart, const int& Mend);
        long int calc_nchk(const int&, const int&) const;    // n choose k 
        long int max;

    public:
        CombinatorialIndex();
        CombinatorialIndex(const int&, const int&); // (NOrb,NElec)
        void print();

        //  transformations
        //void operator++(){};
        void incr();

        //  computing data
        long int calc_linear_index(){};
        
        //  accessing data
        long int get_max();
        vector<int> get_unoccupied(){};
        vector<int> get_occupied(){};
};

#endif

