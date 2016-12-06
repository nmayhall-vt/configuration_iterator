#ifndef DETERMINANTCLASS_H
#define DETERMINANTCLASS_H

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

class DeterminantClass
{
    /**  \brief
        Each object of this class defines a unique class of determinants obtained
        by all possible configurations allowed by specified occupations of 
        orbital spaces.

        An arbitrary number of orbital spaces is allowed.
        **/
        
    private:
        int n_orbs_tot;  
        int n_elec_tot; 
        int n_blocks; 
        vector< vector<int> > orbital_blocks_a; //!< orbital_blocks[block][orb1, orb2, ....] alpha
        vector< vector<int> > orbital_blocks_b; //!< orbital_blocks[block][orb1, orb2, ....] beta 
        vector<int> block_size_a; //!< size of each alpha orbital block
        vector<int> block_size_b; //!< size of each beta orbital block
        vector<int> block_occ_a; //!< Number of electrons in each alpha orbital block
        vector<int> block_occ_b; //!< Number of electrons in each beta orbital block
    public:
        DeterminantClass(){};
        DeterminantClass(const vector<int>&, const vector<int>&, const vector<int>&);
        void print();
};

#endif


