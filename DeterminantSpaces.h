#ifndef DETERMINANTSPACES_H
#define DETERMINANTSPACES_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "OrbitalSpaces.h"
#include "helpers.h"
//#include <algorithm>
//#include <sstream>
//#include <string>
//#include <map>

using namespace std;

class DeterminantSpaces
{
    /**  \brief
        Each object of this class defines a unique class of determinants obtained
        by all possible configurations allowed by specified occupations of 
        orbital spaces.

        An arbitrary number of orbital spaces is allowed.
        **/
        
    private:
        int _n_orbs;  
        int _n_elec;
        int _n_alpha;
        int _n_beta; 
        int _n_blocks; 
        vector<int> _elec_per_block_a; //!< Number of electrons in each alpha orbital block
        vector<int> _elec_per_block_b; //!< Number of electrons in each beta orbital block
        OrbitalSpaces _spaces;
    public:
        /// Default Constructor
        DeterminantSpaces(){};

        /// Constructor taking OrbitalSpaces object, and two vectors indicating number of alpha and beta electrons per block
        DeterminantSpaces(OrbitalSpaces, const vector<int>& alpha, const vector<int>& beta);
        
        /// Get access to the number of electrons in each alpha orbital block
        int& elec_per_block_a(const int& i){return _elec_per_block_a.at(i);}; 
        /// Get access to the number of electrons in each beta orbital block
        int& elec_per_block_b(const int& i){return _elec_per_block_b.at(i);}; 
        
        void print(); ///< Pretty print
};

#endif


