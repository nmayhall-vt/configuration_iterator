#ifndef COMBINATORIALINDEX_H
#define COMBINATORIALINDEX_H

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
#include <algorithm>
//#include <sstream>
//#include <string>
//#include <map>

using namespace std;

class CombinatorialIndex 
{
    /*!
      This implementation of CombinatorialIndex uses a vector<int> as the primary
      object for describing a configuration. 

      @todo{ 
      Reimplement this class using bit operations
      }
     */
    
    private:
        int _n_orbs;  
        //int _orb_shift;  
        int _n_elec;  
        vector<int> _scr; ///< scratch vector
        vector<int> _config_reset; ///< store original config 
        vector<int> _vir_reset; ///< store original config 
        vector<int> _config; ///< vector of orbital indices describing the config
        vector<int> _vir; ///< vector of orbital indices vacant in config
        void increment_comb(std::vector<int>& list, const int& Mstart, const int& Mend);
        void decrement_comb(std::vector<int>& list, const int& Mstart, const int& Mend);
        long int calc_nchk(const int&, const int&) const;    // n choose k 
        size_t _max;
        size_t _lin_index; ///< Current linear index
        void flip(vector<int>& v, const int& p, const int& q); // swap data in p and q

    public:
        /// Default constructor
        CombinatorialIndex();
        CombinatorialIndex(const int&, const int&); //!< (NOrb,NElec)
        
        
        void print(); //!< Formatted print

        //  transformations
        //void operator++(){};
        void incr(); //!< Increment the combinatorial index by one, updating the configuration strings: _config/_vir
        void decr(); //!< Decrement the combinatorial index by one, updating the configuration strings: _config/_vir
        void set_config(const vector<int>&); //!< set the index to specified config
        //void set_orb_shift(const int&i){_orb_shift = i;}; ///< Define the starting orbital index
        void reset(); //!< Reset configuration back to first index
        

        //  computing data
        const size_t& calc_linear_index(); //!< Calculate the linear index
        const size_t& linear_index() {return _lin_index;};      //!< Retrieve the linear index
        
        //  accessing data
        int occ(const int&i) const; ///< Get i'th occupied orbital in config
        int vir(const int&a) const; ///< Get a'th unnoccupied orbital in config 
        size_t max(); ///< Get length of index range
        //const int& get_orb_shift(){return _orb_shift;}; ///< Get the starting orbital index

        /// Get vector of configuration
        vector<int>& config() {return _config;}; 
        /// Get vector of empty configuration 
        vector<int>& empty() {return _vir;}; 


        int calc_single_excitation_sign(const int& n, const int& a); ///< Get sign obtained after creating single excitation (electron -> a) one string search

        int calc_single_excitation_sign2(const int& i, const int& a); ///< Get sign obtained after creating single excitation (i -> a) two string searches
        CombinatorialIndex apply_single_excitation(const int& i, const int& a); ///< Obtain new configuration after applying single substitution (i->a) 
        void single_excitation(const int& i, const int& a, size_t& ind, int& sign); 
        
        // based on flip
        void single_excitation2(const int& i, const int& a, size_t& ind, int& sign);    ///< i,a
        void double_excitation2(const int& i, const int& j, const int& a, const int& b, size_t& ind, int& sign); ///< i,j,a,b
};

#endif  

