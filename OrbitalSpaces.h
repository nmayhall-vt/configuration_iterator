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
        Use this class to help organize the orbitals into spaces. 
        It is assumed that each orbital block consists of consecutive orbital indices.
        **/
        
    private:
        int _n_orbs;  
        int _n_blocks; 
        //vector< vector<int> > _orb_block_a; ///< orbital_blocks[block][orb1, orb2, ....] alpha
        //vector< vector<int> > _orb_block_b; ///< orbital_blocks[block][orb1, orb2, ....] beta 
        vector<int> _block_size_a; ///< size of each alpha orbital block
        vector<int> _block_size_b; ///< size of each beta orbital block
        vector<int> _block_shift_a; ///< shift for each alpha orbital block. Add this to each orbital to the real orbital index
        vector<int> _block_shift_b; ///< shift for each beta orbital block. Add this to each orbital to the real orbital index
    public:
        OrbitalSpaces(){};
        OrbitalSpaces(const vector<int>&); //!< Take vector of orbital sizes (assume orbitals are already ordered)
        OrbitalSpaces(const vector<int>&, const vector<int>&); //!< Take 2 vectors of orbital sizes (assume orbitals are already ordered), (alpha,beta)

        /// Get number of orbital blocks defined
        int n_blocks(){return _n_blocks;}; 
        /// Get number of total orbitals
        int n_orbs(){return _n_orbs;}; 


        /// Get size of each alpha orbital block
        const int& block_size_a(const int& i){return _block_size_a.at(i);};
        /// Get size of each beta orbital block
        const int& block_size_b(const int& i){return _block_size_a.at(i);}; 

        
        /// Get orbital index shift for each alpha orbital block
        const int& block_shift_a(const int& i) const {return _block_shift_a.at(i);};
        /// Get orbital index shift for each beta orbital block
        const int& block_shift_b(const int& i) const {return _block_shift_b.at(i);};
        /// Set orbital index shift for each alpha block, i, to value of j 
        void set_block_shift_a(const int& i, const int& j){_block_shift_a.at(i) = j;};
        /// Set orbital index shift for each beta block, i, to value of j 
        void set_block_shift_b(const int& i, const int& j){_block_shift_b.at(i) = j;};
        

        void print(); ///< pretty print

        
        /*
        /// Get vector of orbitals defined for block i:  orbital_blocks[block][orb1, orb2, ....] alpha
        vector<int> orb_block_a(const int& i){return _orb_block_a.at(i);};
       
        /// Get vector of orbitals defined for block i:  orbital_blocks[block][orb1, orb2, ....] beta 
        vector<int> orb_block_b(const int& i){return _orb_block_a.at(i);}; 
        */
};

#endif


