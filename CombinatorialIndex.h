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
        /// Default constructor
        CombinatorialIndex();
        CombinatorialIndex(const int&, const int&); //!< (NOrb,NElec)
        
        
        void print(); //!< Formatted print

        //  transformations
        //void operator++(){};
        void incr(); //!< Increment the combinatorial index by one, updating the configuration string
        void set_config(const vector<int>&); //!< set the index to specified config

        //  computing data
        long int calc_linear_index(); //!< Calculate the linear index
        
        //  accessing data
        long int get_max(); ///< Get max of linear index
        vector<int> get_occupied(); ///< Return vector of occupied orbitals for this current value of the index
        vector<int> get_unoccupied(); ///< Return vector of unoccupied orbitals for this current value of the index

};

#endif  

