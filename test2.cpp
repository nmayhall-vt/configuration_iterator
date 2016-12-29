// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CombinatorialIndex.h"
#include "DeterminantSpace.h"
#include "Determinant.h"
#include "OrbitalSpaces.h"
#include "InCoreIntegrals.h"
#include <armadillo>

using namespace arma;
long int InCoreIntegrals::mem_used = 0;

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


    InCoreIntegrals I_aaaa;
    I_aaaa = InCoreIntegrals(
            spaces.block_shift_a(2), spaces.block_shift_a(2)+spaces.block_size_a(2)-1,
            spaces.block_shift_a(2), spaces.block_shift_a(2)+spaces.block_size_a(2)-1,
            spaces.block_shift_a(2), spaces.block_shift_a(2)+spaces.block_size_a(2)-1,
            spaces.block_shift_a(2), spaces.block_shift_a(2)+spaces.block_size_a(2)-1
            );
    I_aaaa.allocate();
    srand(1);
    I_aaaa.fill_rand();

    // symmetrize single bar integrals
    {
        int size = spaces.block_size_a(2);
        int shift = spaces.block_shift_a(2);
        for(int i=shift; i<shift+size; i++)
        {
            for(int j=shift; j<shift+size; j++)
            {
                for(int k=i; k<shift+size; k++)
                {
                    for(int l=j; l<shift+size; l++)
                    {
                        I_aaaa(k,j,i,l) = I_aaaa(i,j,k,l);
                        I_aaaa(i,l,k,j) = I_aaaa(i,j,k,l);
                        I_aaaa(k,l,i,j) = I_aaaa(i,j,k,l);
                    };  
                };  
            };  
        };
        cout << I_aaaa(0+shift,1+shift,2+shift,3+shift) << endl;
        cout << I_aaaa(2+shift,1+shift,0+shift,3+shift) << endl;
        cout << I_aaaa(0+shift,3+shift,2+shift,1+shift) << endl;
        cout << I_aaaa(2+shift,3+shift,0+shift,1+shift) << endl;
    };
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

