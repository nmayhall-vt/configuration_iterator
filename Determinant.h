#ifndef DETERMINANT_H
#define DETERMINANT_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "CombinatorialIndex.h"
#include "OrbitalSpaces.h"
#include "DeterminantSpace.h"
#include "helpers.h"
#include <algorithm>
//#include <sstream>
//#include <string>
//#include <map>

using namespace std;

class Determinant 
{
    /*!
    
      This is essentially a collection of Indices corresponding to the different orbitals spaces. 

        Ik = [I0, I1, I2, I3, ...]
        where I0,  I1, etc,
            are the linear indices of each individual orbitals space.

     */
    
    private:
        vector<CombinatorialIndex> _block_indices;
        DeterminantSpace _space;
        size_t _lin_index;
        size_t _size;

    public:
        /// Default constructor
        Determinant();
        Determinant(DeterminantSpace&);
       
        void print(); //!< Formatted print

        //  transformations
        void incr(); //!< Increment the combinatorial index by one, updating the configuration strings: _config/_vir
        void decr(); //!< Decrement the combinatorial index by one, updating the configuration strings: _config/_vir
        void set_config(const vector<int>&); //!< set the index to specified config
        void reset(); //!< Reset configuration back to first index
        const size_t size(){return _size;}; //!<  Number of configs in space
       

        /// These are used to get access to a specific orbital block index 
        CombinatorialIndex& get_block_index(const int& i){return _block_indices.at(i);}; //!<  Get reference to a specific block index 
        CombinatorialIndex& get_block_index_a(const int& i){return _block_indices.at(i);}; //!<  Get reference to a specific alpha block index 
        CombinatorialIndex& get_block_index_b(const int& i){return _block_indices.at(i+_space.n_blocks());}; //!<  Get reference to a specific beta block index 
        
        //  read data
        //  computing data
        size_t calc_linear_index(); //!< Calculate the linear index
        const int& occ(const int&i) const; ///< Get i'th occupied orbital in config
        const int& vir(const int&a) const; ///< Get a'th unnoccupied orbital in config 
        
        //maybe todo...
        /*
        const int& occ(const int&o, const int&i) const; ///< Get i'th occupied orbital index in config of o'th orbital block
        const int& vir(const int&o, const int&a) const; ///< Get a'th unnoccupied orbital index in config of o'th orbital block
        */
        

};

#endif  

