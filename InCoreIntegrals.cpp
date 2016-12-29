#include "InCoreIntegrals.h"



// 
// InCoreIntegrals class stuff...
InCoreIntegrals::InCoreIntegrals()
{/*{{{*/
    // 
    // Constructor for matrix 
    //
    
    _rank = 0; 
    _allocated = 0; 
   //allocate();
};/*}}}*/


InCoreIntegrals::InCoreIntegrals(int i1_first, int i1_last)
{/*{{{*/
    // 
    // Constructor for matrix 
    //
    
    _rank = 1; 
    _dim_first.push_back(i1_first);
    _dim_last.push_back(i1_last);
    _allocated = 0; 
    
    //allocate();
};/*}}}*/


InCoreIntegrals::InCoreIntegrals(int i1_first, int i1_last, int i2_first, int i2_last)
{/*{{{*/
    // 
    // Constructor for matrix 
    //
    
    _rank = 2; 
    _dim_first.push_back(i1_first);
    _dim_first.push_back(i2_first);
    _dim_last.push_back(i1_last);
    _dim_last.push_back(i2_last);
    _allocated = 0; 
    
    //allocate();
};/*}}}*/


InCoreIntegrals::InCoreIntegrals(int i1_first, int i1_last, int i2_first, int i2_last, int i3_first, int i3_last)
{/*{{{*/
    // 
    // Constructor for matrix 
    //
    
    _rank = 3; 
    _dim_first.push_back(i1_first);
    _dim_first.push_back(i2_first);
    _dim_first.push_back(i3_first);
    _dim_last.push_back(i1_last);
    _dim_last.push_back(i2_last);
    _dim_last.push_back(i3_last);
    _allocated = 0; 
    
    //allocate();
};/*}}}*/


InCoreIntegrals::InCoreIntegrals(int i1_first, int i1_last, int i2_first, int i2_last, int i3_first, int i3_last, int i4_first, int i4_last)
{/*{{{*/
    // 
    // Constructor for matrix 
    //
   
    _rank = 4; 
    _dim_first.push_back(i1_first);
    _dim_first.push_back(i2_first);
    _dim_first.push_back(i3_first);
    _dim_first.push_back(i4_first);
    _dim_last.push_back(i1_last);
    _dim_last.push_back(i2_last);
    _dim_last.push_back(i3_last);
    _dim_last.push_back(i4_last);
    _allocated = 0; 

    //allocate();
};/*}}}*/


InCoreIntegrals::~InCoreIntegrals()
{/*{{{*/
    _allocated = 0; 
    //delete[] _array;
    mem_used -= _size*sizeof(double);
};/*}}}*/


double& InCoreIntegrals::operator()(const int&p)
{/*{{{*/
    assert(_rank == 1);
    assert(p >= dim_first(0)  &&  p <= dim_last(0));
    assert(_allocated == 1);

    return _array[
            (p-_dim_first[0]) 
          ];
};/*}}}*/


double& InCoreIntegrals::operator()(const int&p, const int&q)
{/*{{{*/
    assert(_rank == 2);
    assert(p >= dim_first(0)  &&  p <= dim_last(0));
    assert(q >= dim_first(1)  &&  q <= dim_last(1));
    assert(_allocated == 1);

    return _array[
            (p-_dim_first[0]) 
          + (q-_dim_first[1])*_dim_len[0]
          ];
};/*}}}*/


double& InCoreIntegrals::operator()(const int&p, const int&q, const int&r)
{/*{{{*/
    assert(_rank == 3);
    assert(p >= dim_first(0)  &&  p <= dim_last(0));
    assert(q >= dim_first(1)  &&  q <= dim_last(1));
    assert(r >= dim_first(2)  &&  r <= dim_last(2));
    assert(_allocated == 1);

    return _array[
            (p - _dim_first[0]) 
          + (q - _dim_first[1])*_dim_len[0]
          + (r - _dim_first[2])*_dim_len[0]*_dim_len[1]
          ];
};/*}}}*/


double& InCoreIntegrals::operator()(const int&p, const int&q, const int&r, const int&s)
{/*{{{*/
    assert(_rank == 4);
    assert(p >= dim_first(0)  &&  p <= dim_last(0));
    assert(q >= dim_first(1)  &&  q <= dim_last(1));
    assert(r >= dim_first(2)  &&  r <= dim_last(2));
    assert(s >= dim_first(3)  &&  s <= dim_last(3));
    assert(_allocated == 1);

    return _array[
            (p - _dim_first[0]) 
          + (q - _dim_first[1])*_dim_len[0]
          + (r - _dim_first[2])*_dim_len[0]*_dim_len[1]
          + (s - _dim_first[3])*_dim_len[0]*_dim_len[1]*_dim_len[2]
          ];
};/*}}}*/


bool InCoreIntegrals::range_check(const int&p)
{/*{{{*/
    //
    // Return true iff all indices are within the orbital ranges of the respective indices
    //
    bool in_range = true;
    in_range = in_range && _rank == 1;
    in_range = in_range && p >= dim_first(0);
    in_range = in_range && p <= dim_last(0);

    return in_range;
};/*}}}*/


bool InCoreIntegrals::range_check(const int&p, const int&q)
{/*{{{*/
    //
    // Return true iff all indices are within the orbital ranges of the respective indices
    //
    bool in_range = true;
    in_range = in_range && _rank == 2;
    in_range = in_range && p >= dim_first(0);
    in_range = in_range && p <= dim_last(0);
    in_range = in_range && q >= dim_first(1);
    in_range = in_range && q <= dim_last(1);

    return in_range;
};/*}}}*/


bool InCoreIntegrals::range_check(const int&p, const int&q, const int&r)
{/*{{{*/
    //
    // Return true iff all indices are within the orbital ranges of the respective indices
    //
    bool in_range = true;
    in_range = in_range && _rank == 3;
    in_range = in_range && p >= dim_first(0);
    in_range = in_range && p <= dim_last(0);
    in_range = in_range && q >= dim_first(1);
    in_range = in_range && q <= dim_last(1);
    in_range = in_range && r >= dim_first(2);
    in_range = in_range && r <= dim_last(2);

    return in_range;
};/*}}}*/


bool InCoreIntegrals::range_check(const int&p, const int&q, const int&r, const int&s)
{/*{{{*/
    //
    // Return true iff all indices are within the orbital ranges of the respective indices
    //
    bool in_range = true;
    in_range = in_range && _rank == 4;
    in_range = in_range && p >= dim_first(0);
    in_range = in_range && p <= dim_last(0);
    in_range = in_range && q >= dim_first(1);
    in_range = in_range && q <= dim_last(1);
    in_range = in_range && r >= dim_first(2);
    in_range = in_range && r <= dim_last(2);
    in_range = in_range && s >= dim_first(3);
    in_range = in_range && s <= dim_last(3);

    return in_range;
};/*}}}*/


void InCoreIntegrals::allocate()
{/*{{{*/
    //
    //  Allocate and initialize data _array via QAllocDouble
    //
    _size = 1;
    _dim_len.clear();
    for(int i=0; i<rank(); i++){
        _dim_len.push_back( _dim_last[i] - _dim_first[i] + 1);
        _size = _size * size_t(_dim_len[i]);
    };
    
    printf(" Allocating _array with %li elements\n",size());
    //_array = new double[_size];
    _array.resize(_size);
    /*
    try
    {
        _array = new double[_size];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught in InCoreIntegrals: size attempted: " << _size << '\n';
    };
    */
    printf(" done.\n");
    
    for(size_t i=0; i<size(); i++) _array[i]=0.0;

    if(!mem_used) mem_used = 0;

    mem_used += _size*sizeof(double);
    //cout << " InCoreIntegrals memory usage increased to: " << mem_used/1000000 << endl;
    _allocated = 1;
};/*}}}*/


void InCoreIntegrals::fill_rand()
{/*{{{*/
    //
    // Set all elements to a random number between -1 and 1 
    //
   
    if(_allocated == 1) for(size_t i=0; i<size(); i++) _array[i]= ((double) rand() / (RAND_MAX))- .5;

};/*}}}*/



