#include "DeterminantClass.h"

DeterminantClass::DeterminantClass(
        const vector<int>& orb_blocks, 
        const vector<int>& elec_blocks_a,
        const vector<int>& elec_blocks_b)
{
    /* @Brief
       Constructor taking a vector or orbital block definitions, and a vector of block occupation numbers.

       This Constructor assumes that the orbital blocks are arranged in a linear fasion: ie., | block1 | block2 | block3 | .....
       and that alpha and beta are the same

      */
    
    n_blocks = orb_blocks.size();
    int orb_i =0;
    for(int b=0; b<n_blocks; b++)
    {
        vector<int> tmp;
        for(int bi=0; bi<orb_blocks.at(b); bi++)
        {
            tmp.push_back(orb_i);
            orb_i += 1;
        };
        orbital_blocks_a.push_back(tmp);
        orbital_blocks_b.push_back(tmp);
        block_size_a.push_back(tmp.size());
        block_size_b.push_back(tmp.size());
    };
    block_occ_a = elec_blocks_a;
    block_occ_b = elec_blocks_b;
};

void DeterminantClass::print()
{/*{{{*/
    printf(" Orbitals  |");
    for(int b=0; b<n_blocks; b++)
    {
        printf("(%3i,%-3i)",block_size_a.at(b),block_size_b.at(b));
    };
    printf("|\n");
    printf(" Electrons |");
    for(int b=0; b<n_blocks; b++)
    {
        printf("(%3i,%-3i)",block_occ_a.at(b),block_occ_b.at(b));
    };
    printf("|\n");
    printf(" Block     |");
    for(int b=0; b<n_blocks; b++)
    {
        printf(" %4i    ",b+1);
    };
    printf("|\n");
};/*}}}*/
