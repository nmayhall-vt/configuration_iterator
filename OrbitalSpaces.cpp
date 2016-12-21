#include "OrbitalSpaces.h"


OrbitalSpaces::OrbitalSpaces(const vector<int>& orb_blocks)
{/*{{{*/
    /* @Brief
       Constructor taking a vector or orbital block definitions, and a vector of block occupation numbers.

       This Constructor assumes that the orbital blocks are arranged in a linear fasion: ie., | block1 | block2 | block3 | .....
       and that alpha and beta are the same

      */
    
    _n_blocks = orb_blocks.size();
    _block_size_a = orb_blocks;
    _block_size_b = orb_blocks;
    int shift = 0;
    for(int b=0; b<_n_blocks; b++)
    {
        _block_shift_a.push_back(shift);
        _block_shift_b.push_back(shift);
        shift += _block_size_a.at(b);
    };
    _n_orbs = shift;
    /*
    int orb_i =0;
    for(int b=0; b<_n_blocks; b++)
    {
        vector<int> tmp;
        for(int bi=0; bi<orb_blocks.at(b); bi++)
        {
            tmp.push_back(orb_i);
            orb_i += 1;
        };
        _orb_block_a.push_back(tmp);
        _orb_block_b.push_back(tmp);
        _block_size_a.push_back(tmp.size());
        _block_size_b.push_back(tmp.size());
    };
    */
};/*}}}*/

OrbitalSpaces::OrbitalSpaces(const vector<int>& orb_block_a, const vector<int>& orb_blocks_b)
{/*{{{*/
    printf(" NYI\n");
    exit(-1);
};/*}}}*/

void OrbitalSpaces::print()
{/*{{{*/
    printf(" Orbitals  |");
    for(int b=0; b<_n_blocks; b++)
    {
        printf("(%3i,%-3i)",block_size_a(b),block_size_b(b));
    };
    printf("|\n");
    printf(" Block     |");
    for(int b=0; b<_n_blocks; b++)
    {
        printf(" %4i    ",b);
    };
    printf("|\n");
};/*}}}*/

