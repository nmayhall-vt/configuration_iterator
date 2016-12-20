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
        orbital_blocks.push_back(8);
        orbital_blocks.push_back(40);
        orbital_blocks.push_back(40);
        OrbitalSpaces spaces(orbital_blocks);
        spaces.print();
        printf("\n");

        printf(" +Test DeterminantSpace Class\n");
        vector<int> electron_blocks;
        electron_blocks.push_back(10);
        electron_blocks.push_back(10);
        electron_blocks.push_back(4);
        electron_blocks.push_back(0);
        electron_blocks.push_back(0);
        DeterminantSpace cas_space(spaces, electron_blocks, electron_blocks);
        cas_space.print();
        printf("\n");

        printf("   get alpha particle space\n");
        DeterminantSpace p_a_space;
        p_a_space = cas_space;
        /*
        */
        p_a_space.elec_per_block_a(3) += 1;
        p_a_space.elec_per_block_a(2) -= 1;
        //p_a_space.elec_per_block_b(3) += 1;
        //p_a_space.elec_per_block_b(1) -= 1;
        p_a_space.print();
        printf("\n");

        
        vector<CombinatorialIndex> t_index = p_a_space.get_iterators();
        Determinant p_a(p_a_space);
        printf(" +Test Determinant::incr()/decr()\n");
        {
            p_a.print();
            int a = 0;
            for(size_t i=0; i<p_a.size()-10; i++)
            {
                p_a.incr();
                a = 3;
                //p_a.print();
            };
            p_a.print();
            cout << p_a.calc_linear_index() << endl;
        };

        printf(" +Test incr()/decr()\n");
        if(0)
        {
            t_index.at(2).incr();
            CombinatorialIndex& config = t_index.at(7);
            for(int i=0; i<t_index.at(7).max(); i++)
            {
                config.incr();
                //helpers::print(config.config());
                //helpers::print(config.empty());
                //printf("\n");
            };
            printf("\n");
            for(int i=0; i<t_index.at(7).max(); i++)
            {
                config.decr(); 
            };
            //t_index.at(7).incr();
            //t_index.at(3).incr();
            for(int s=0; s<spaces.n_blocks(); s++)
            {
                int n_blocks = spaces.n_blocks();
                helpers::print( t_index.at(s).config(), t_index.at(s+spaces.n_blocks()).config() );
                //cout << t_index.at(s).calc_linear_index() << "," << t_index.at(s+n_blocks).calc_linear_index() << endl;
            };
        };
        if(0)
        { 
            int sign;
            size_t index; 
            printf(" +Test loop over double excitations\n");
            CombinatorialIndex& Ik = t_index.at(7);
            Ik.print();
            Ik.reset();

            for(size_t I=0; I<Ik.max(); I++)
            {
                Ik.print();
                printf(" %8li -> ",I);
                //helpers::print(Ik.empty());
                for(int i=0; i<Ik.config().size(); i++)
                {
                    for(int a=0; a<Ik.empty().size(); a++)
                    {
                        Ik.single_excitation2(i,a,index,sign);
                        for(int j=i+1; j<Ik.config().size(); j++)
                        {
                            for(int b=a+1; b<Ik.empty().size(); b++)
                            {
                                //Ik.single_excitation(Ij.occ(j),Ij.vir(b),index,sign);
                                //printf(" %4li",index);
                                Ik.double_excitation2(i,j,a,b,index,sign);
                                printf(" %4li",index);
                            };
                        };
                    };
                };
                Ik.incr();
                printf("\n");
            };
        };
        printf(" +Test double excitations in Determinant\n");
        {
            p_a.print();
            int a = 0;
            int p=2;
            int q=2;
            int r=2;
            int s=2;
            CombinatorialIndex& Ip = p_a.get_block_index(p);
            CombinatorialIndex& Iq = p_a.get_block_index(q);
            CombinatorialIndex& Ir = p_a.get_block_index(r);
            CombinatorialIndex& Is = p_a.get_block_index(s);
            //for(size_t I=0; I<p_a.size()-1; I++)
            if(p=r) // p->r is within one block
            {
                for(size_t I=0; I<3; I++)
                {
                    for(int i=0; i<Ip.config().size(); i++)
                    {
                        for(int a=0; a<Ir.empty().size(); a++)
                        {
                            // todo
                            //p_a.single_excitation2(i,a,index,sign);
                        };
                    };

                    p_a.incr();
                    a = 3;

                };
            };
        };
    };

    /*
    printf(" +Test armadillo linking\n");
    arma::mat a = arma::zeros(4,4);
    cout << a << endl;
    */
    return 0;
}

