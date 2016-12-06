// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CombinatorialIndex.h"
#include "DeterminantClass.h"
#include "OrbitalSpaces.h"
#include <armadillo>

using namespace arma;

int main ()
{
    
    printf(" Test basic indexing\n");
    CombinatorialIndex Ik(6,3);
    for(size_t i=0; i<Ik.get_max(); i++)
    {
        Ik.print();
        cout << Ik.calc_linear_index() << endl;
        Ik.incr();
    }
    
    printf(" Test set_config\n");
    vector<int> b;
    b.push_back(1);
    b.push_back(3);
    b.push_back(5);
    Ik.set_config(b);
    cout << Ik.calc_linear_index() << endl;

    {
        printf(" Test OrbitalSpaces Class\n");
        vector<int> orbital_blocks;
        orbital_blocks.push_back(10);
        orbital_blocks.push_back(10);
        orbital_blocks.push_back(6);
        orbital_blocks.push_back(6);
        orbital_blocks.push_back(20);
        OrbitalSpaces spaces(orbital_blocks);
        spaces.print();
        printf("\n");

        printf(" Test Determinant Class\n");
        vector<int> electron_blocks;
        electron_blocks.push_back(10);
        electron_blocks.push_back(10);
        electron_blocks.push_back(3);
        electron_blocks.push_back(0);
        electron_blocks.push_back(0);
        DeterminantClass cas_space(spaces, electron_blocks, electron_blocks);
        cas_space.print();
        printf("\n");

        printf("   Add one electron to alpha block 3 and remove one electron from beta block 2\n");
        cas_space.elec_per_block_a(3) += 1;
        cas_space.elec_per_block_b(2) -= 1;
        cas_space.print();
        printf("\n");
    };

    printf(" Test armadillo linking\n");
    arma::mat a = arma::zeros(4,4);
    cout << a << endl;
    return 0;
}

