// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CombinatorialIndex.h"
#include "DeterminantSpace.h"
#include "Determinant.h"
#include "OrbitalSpaces.h"
#include <armadillo>

using namespace arma;

int main ()
{
#ifdef DEBUG
    printf(" Debug mode\n");
#endif

    printf(" +Test OrbitalSpaces Class\n");
    vector<int> orbital_blocks;
    orbital_blocks.push_back(10);
    orbital_blocks.push_back(10);
    orbital_blocks.push_back(4);
    orbital_blocks.push_back(40);
    orbital_blocks.push_back(40);
    OrbitalSpaces spaces(orbital_blocks);
    spaces.print();
    printf("\n");

    printf(" +Test DeterminantSpace Class\n");
    vector<int> electron_blocks;
    electron_blocks.push_back(10);
    electron_blocks.push_back(10);
    electron_blocks.push_back(2);
    electron_blocks.push_back(0);
    electron_blocks.push_back(0);
    DeterminantSpace cas_space(spaces, electron_blocks, electron_blocks);
    cas_space.print();
    printf("\n");

    Determinant D0(cas_space);
    CombinatorialIndex& a_str = D0.get_block_index_a(2);
    CombinatorialIndex& b_str = D0.get_block_index_b(2);
    a_str.print();
    b_str.print();

    int p=2;
    int q=2;
    int r=2;
    int s=2;
    CombinatorialIndex& Ia = D0.get_block_index_a(p);
    CombinatorialIndex& Ib = D0.get_block_index_b(p);
   
    // In CASCI, all excitations occur within one block 
    size_t index = 0;
    int sign = 1;
    for(size_t I=0; I<D0.size(); I++)
    {
        D0.print();
        // alpha-alpha
        for(int p=0; p<Ia.config().size(); p++)
        {
            for(int q=0; q<Ia.empty().size(); q++)
            {
                Ia.single_excitation2(p,q,index,sign);
                printf("    %4i -> %-4i : %5li  : %2i\n",Ia.occ(p),Ia.vir(q), index, sign);

            };
        };

        D0.incr();
    };

    return 0;
}

