#ifndef ORBITALSPACES_H
#define ORBITALSPACES_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

using namespace std;

class OrbitalSpaces 
{
    /**  \brief
        Use this class to help organize the orbitals into spaces 
        **/
        
    private:
        int _n_orbs;  
        int _n_blocks; 
        vector< vector<int> > _orb_block_a; ///< orbital_blocks[block][orb1, orb2, ....] alpha
        vector< vector<int> > _orb_block_b; ///< orbital_blocks[block][orb1, orb2, ....] beta 
        vector<int> _block_size_a; ///< size of each alpha orbital block
        vector<int> _block_size_b; ///< size of each beta orbital block
    public:
        OrbitalSpaces(){};
        OrbitalSpaces(const vector<int>&); //!< Take vector of orbital sizes (assume orbitals are already ordered)
        OrbitalSpaces(const vector<int>&, const vector<int>&); //!< Take 2 vectors of orbital sizes (assume orbitals are already ordered), (alpha,beta)

        /// Get number of orbital blocks defined
        int n_blocks(){return _n_blocks;}; 
        /// Get number of total orbitals
        int n_orbs(){return _n_orbs;}; 

        /// Get size of each alpha orbital block
        int block_size_a(const int& i){return _block_size_a.at(i);};

        /// Get size of each beta orbital block
        int block_size_b(const int& i){return _block_size_a.at(i);}; 

        /// Get vector of orbitals defined for block i:  orbital_blocks[block][orb1, orb2, ....] alpha
        vector<int> orb_block_a(const int& i){return _orb_block_a.at(i);};
       
        /// Get vector of orbitals defined for block i:  orbital_blocks[block][orb1, orb2, ....] beta 
        vector<int> orb_block_b(const int& i){return _orb_block_a.at(i);}; 
        
        void print(); ///< pretty print
};

#endif


