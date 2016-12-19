#ifndef DETERMINANTSPACE_H
#define DETERMINANTSPACE_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "OrbitalSpaces.h"
#include "CombinatorialIndex.h"
#include "helpers.h"
//#include <algorithm>
//#include <sstream>
//#include <string>
//#include <map>

using namespace std;

class DeterminantSpace
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
        size_t _global_offset;  ///< Determinants in this class will start at this linear index
        size_t _size;
        vector<int> _elec_per_block_a; //!< Number of electrons in each alpha orbital block
        vector<int> _elec_per_block_b; //!< Number of electrons in each beta orbital block
        OrbitalSpaces _spaces;
        void calc_size();
    public:
        /// Default Constructor
        DeterminantSpace(){};

        /// Constructor taking OrbitalSpaces object, and two vectors indicating number of alpha and beta electrons per block
        DeterminantSpace(OrbitalSpaces, const vector<int>& alpha, const vector<int>& beta);
        /// Where do these determinants in this space start? (i.e. CAS determinants are typically first)
        void global_offset(const size_t& o){_global_offset = o;}; 
        /// Where do these determinants in this space start? (i.e. CAS determinants are typically first)
        size_t global_offset(){return _global_offset;}; 
        
        /// Get access to the number of electrons in each alpha orbital block
        int& elec_per_block_a(const int& i){return _elec_per_block_a.at(i);}; 
        /// Get access to the number of electrons in each beta orbital block
        int& elec_per_block_b(const int& i){return _elec_per_block_b.at(i);}; 
        
        /// Return number of orbital blocks (alpha and beta are separate) 
        int& n_blocks(){return _n_blocks;}; 

        vector<CombinatorialIndex> get_iterators(); ///< Return vector of combinatorial indices for iterating through this determinantspace        
        void print(); ///< Pretty print

        /// Return number of determinants in this space
        size_t size(){calc_size();return _size;};
        
        /// Return to OrbitalSpaces object 
        OrbitalSpaces& orb_spaces(){return _spaces;};
};

#endif


