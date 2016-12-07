// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CombinatorialIndex.h"
#include "DeterminantSpaces.h"
#include "OrbitalSpaces.h"
#include <armadillo>

using namespace arma;

int main ()
{
   
    /* 
    printf(" +Test CombinatorialIndex\n");
    CombinatorialIndex Ik(6,3);
    for(size_t i=0; i<Ik.get_max(); i++)
    {
        Ik.print();
        cout << Ik.calc_linear_index() << endl;
        Ik.incr();
    }
    
    printf(" +Test set_config\n");
    vector<int> b;
    b.push_back(1);
    b.push_back(3);
    b.push_back(5);
    Ik.set_config(b);
    cout << Ik.calc_linear_index() << endl;
    */

    {
        printf(" +Test OrbitalSpaces Class\n");
        vector<int> orbital_blocks;
        orbital_blocks.push_back(10);
        orbital_blocks.push_back(10);
        orbital_blocks.push_back(6);
        orbital_blocks.push_back(8);
        orbital_blocks.push_back(20);
        OrbitalSpaces spaces(orbital_blocks);
        spaces.print();
        printf("\n");

        printf(" +Test DeterminantSpaces Class\n");
        vector<int> electron_blocks;
        electron_blocks.push_back(10);
        electron_blocks.push_back(10);
        electron_blocks.push_back(3);
        electron_blocks.push_back(0);
        electron_blocks.push_back(0);
        DeterminantSpaces cas_space(spaces, electron_blocks, electron_blocks);
        cas_space.print();
        printf("\n");

        printf("   get alpha particle space\n");
        DeterminantSpaces p_a_space;
        p_a_space = cas_space;
        p_a_space.elec_per_block_a(3) += 1;
        p_a_space.elec_per_block_a(2) -= 1;
        p_a_space.elec_per_block_b(3) += 1;
        p_a_space.elec_per_block_b(1) -= 1;
        p_a_space.print();
        printf("\n");

        vector<CombinatorialIndex> t_index = p_a_space.get_iterators();
        t_index.at(2).incr();
        t_index.at(7).incr();
        //t_index.at(7).incr();
        //t_index.at(3).incr();
        for(int s=0; s<spaces.n_blocks(); s++)
        {
            int n_blocks = spaces.n_blocks();
            helpers::print( t_index.at(s).config(), t_index.at(s+spaces.n_blocks()).config() );
            //cout << t_index.at(s).calc_linear_index() << "," << t_index.at(s+n_blocks).calc_linear_index() << endl;
        };

        printf(" +Test calc_single_excitation_sign\n");
        t_index.at(7).print();
        cout << t_index.at(7).calc_single_excitation_sign(1,2) << endl;
        cout << t_index.at(7).calc_single_excitation_sign2(2,2) << endl;
#ifdef DEBUG
        printf(" Debug mode\n");
#endif
    };

    /*
    printf(" +Test armadillo linking\n");
    arma::mat a = arma::zeros(4,4);
    cout << a << endl;
    */
    return 0;
}

