#ifndef INCOREINTEGRALS_H
#define INCOREINTEGRALS_H

//#include "casman.h" 
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
using namespace std;

class InCoreIntegrals
{
    //
    //  Simple class for organizing data for Integral arrays completely stored in core memory,
    //  whose main use will be for direct access
    //
    //  Access integrals with actual orbital indices, regardless of dimensions of tensor
    //
    private:
        int _seed;
        size_t _size;                                   // Length of data array
        int _rank;                                        // Rank of Integral Tensor
        int _allocated;                                   // Flag to keep ensure allocation only gets called once
        vector<int> _dim_first;                           // Vector of first orbital for each dimension
        vector<int> _dim_last;                            // Vector of last orbital for each dimension
        vector<int> _dim_len;                             // Vector of dimension lengths
        vector<double> _array;                            // Data array
    public:
        InCoreIntegrals();                                // Constructor for Rank-0 tensor
        InCoreIntegrals(int,int);                         // Constructor for Rank-1 tensor
        InCoreIntegrals(int,int,int,int);                 // Constructor for Rank-2 tensor
        InCoreIntegrals(int,int,int,int,int,int);         // Constructor for Rank-3 tensor
        InCoreIntegrals(int,int,int,int,int,int,int,int); // Constructor for Rank-4 tensor
        ~InCoreIntegrals();    
        void allocate();                                  // Allocate and initialize array

        int dim_len(const int&i) const {return _dim_len.at(i);}; // Return length of each dimension
        int dim_first(const int&i) const {return _dim_first.at(i);}; // Return first orbital indexof each dimension
        int dim_last(const int&i) const {return _dim_last.at(i);}; // Return last orbital index of each dimension
        size_t size() const {return _array.size();};
        int rank() const {return _rank;};
        double* ptr() {return &_array[0];};              // Return pointer to data array
        //
        //  Element access. Access integrals by calling with actual orbital index.
        double& operator()(const int&); 
        double& operator()(const int&, const int&); 
        double& operator()(const int&, const int&, const int&); 
        double& operator()(const int&, const int&, const int&, const int&); 

        //
        //  Range check functions
        bool range_check(const int&);                                   // Debugging tool
        bool range_check(const int&,const int&);                        // Debugging tool
        bool range_check(const int&,const int&,const int&);             // Debugging tool
        bool range_check(const int&,const int&,const int&,const int&);  // Debugging tool
        static long int mem_used;                         // Total memory used by all InCoreIntegrals objects

        //
        void fill_rand(); //    Fill tensor with random numbers for testing.
};

#endif

