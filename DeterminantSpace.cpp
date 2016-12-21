#include "DeterminantSpace.h"

DeterminantSpace::DeterminantSpace(
        OrbitalSpaces spaces, 
        const vector<int>& elec_blocks_a,
        const vector<int>& elec_blocks_b)
{/*{{{*/
    /* @Brief
       Constructor taking a vector or orbital block definitions, and a vector of block occupation numbers.

       This Constructor assumes that the orbital blocks are arranged in a linear fasion: ie., | block1 | block2 | block3 | .....
       and that alpha and beta are the same

      */
    
    _spaces = spaces;
    _n_blocks = _spaces.n_blocks();
    _elec_per_block_a = elec_blocks_a;
    _elec_per_block_b = elec_blocks_b;
    _global_offset = 0;
    
    _n_alpha = 0;
    for(int b=0; b<_elec_per_block_a.size(); b++)
    {
        _n_alpha += _elec_per_block_a.at(b);
    };
    
    _n_beta = 0;
    for(int b=0; b<_elec_per_block_b.size(); b++)
    {
        _n_beta += _elec_per_block_b.at(b);
    };
    _n_elec = _n_alpha + _n_beta;
    _n_orbs = _spaces.n_orbs();
};/*}}}*/

vector<CombinatorialIndex> DeterminantSpace::get_iterators()
{/*{{{*/
    vector<CombinatorialIndex> tensor_index;
    for(int b=0; b<_n_blocks; b++)
    {
        CombinatorialIndex alpha(_spaces.block_size_a(b),elec_per_block_a(b));
        tensor_index.push_back(alpha);
    };
    for(int b=0; b<_n_blocks; b++)
    {
        CombinatorialIndex beta(_spaces.block_size_b(b),elec_per_block_b(b));
        tensor_index.push_back(beta);
    };
    return tensor_index;
};/*}}}*/

void DeterminantSpace::calc_size()
{/*{{{*/
    _size = 1; 
    for(int b=0; b<_n_blocks; b++)
    {
        _size = _size * helpers::nchk(_spaces.block_size_a(b),elec_per_block_a(b)); 
        _size = _size * helpers::nchk(_spaces.block_size_b(b),elec_per_block_b(b)); 
    };
};/*}}}*/

void DeterminantSpace::print()
{/*{{{*/
    printf(" Orbitals  |");
    for(int b=0; b<_n_blocks; b++)
    {
        printf("(%3i,%-3i)",_spaces.block_size_a(b),_spaces.block_size_b(b));
    };
    printf("|\n");
    printf(" Electrons |");
    for(int b=0; b<_n_blocks; b++)
    {
        printf("(%3i,%-3i)",_elec_per_block_a.at(b),_elec_per_block_b.at(b));
    };
    printf("|\n");
    printf(" Block     |");
    for(int b=0; b<_n_blocks; b++)
    {
        printf("%-9i",b);
    };
    printf("|\n");
    printf(" # Configs |");
    for(int b=0; b<_n_blocks; b++)
    {
        size_t block_dim = helpers::nchk(_spaces.block_size_a(b),elec_per_block_a(b)); 
        block_dim = block_dim * helpers::nchk(_spaces.block_size_b(b),elec_per_block_b(b));
        printf("%-9li",block_dim);
    };
    printf("|\n");
    printf(" Total size| %li",size());
    printf("\n");
};/*}}}*/


