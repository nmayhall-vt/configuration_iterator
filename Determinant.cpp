#include "Determinant.h"

Determinant::Determinant(DeterminantSpace& space)
{/*{{{*/
    _space = space;

    _block_indices.clear();
    for(int b=0; b<_space.orb_spaces().n_blocks(); b++)
    {
        CombinatorialIndex alpha(_space.orb_spaces().block_size_a(b), _space.elec_per_block_a(b));
        //alpha.set_orb_shift( _space.orb_spaces().block_shift_a(b) );
        _block_indices.push_back(alpha);
    };
    for(int b=0; b<_space.orb_spaces().n_blocks(); b++)
    {
        CombinatorialIndex beta(_space.orb_spaces().block_size_b(b), _space.elec_per_block_b(b));
        //beta.set_orb_shift( _space.orb_spaces().block_shift_b(b) );
        _block_indices.push_back(beta);
    };
    _size = _space.size();
};/*}}}*/


void Determinant::print()
{/*{{{*/
    printf(" Determinant:  %12li\n",calc_linear_index());
    for(int b=0; b<_space.orb_spaces().n_blocks(); b++)
    {
        printf(" Shift: %4i,%-4i ",_space.orb_spaces().block_shift_a(b),_space.orb_spaces().block_shift_b(b));
        helpers::print(
                    get_block_index_a(b).config(),
                    get_block_index_b(b).config()
                    );
    };
    printf("\n");
};/*}}}*/


size_t Determinant::calc_linear_index()
{/*{{{*/
#ifdef DEBUG
    if(_space.n_blocks()*2 != _block_indices.size()) 
    {
        printf(" %4i \n",_space.n_blocks());
        printf(" %4li \n",_block_indices.size());
        throw std::runtime_error("_space.orb_spaces().n_blocks() != _block_indices.size()"); 
    };
#endif

    _lin_index = 0;

    size_t offset = 1;
    for(int i=_space.n_blocks()*2-1; i>-1; i--)
    {
        //_block_indices.at(i).print();
        _lin_index += _block_indices.at(i).calc_linear_index() * offset;
        offset = offset * _block_indices.at(i).max();
    }; 
    return _lin_index + _space.global_offset();
};/*}}}*/

void Determinant::incr()
{/*{{{*/
    for(int i=_space.n_blocks()*2-1; i>-1; i--)
    {
        //printf("j: %4i %4i %4i\n",i,_block_indices.at(i).linear_index(),_block_indices.at(i).max()-1);
        //_block_indices.at(i).print();
        //printf(" %4i\n",_block_indices.at(i).linear_index());
        //printf(" %4i\n",_block_indices.at(i).max());
        if(_block_indices.at(i).linear_index() == _block_indices.at(i).max()-1)
        {
            _block_indices.at(i).reset();
            //_block_indices.at(i).print();
        }
        else
        {
            _block_indices.at(i).incr();
            _lin_index += 1;
            break;
        };
    }; 
    
};/*}}}*/

        //todo
void Determinant::decr(){};


//  maybe todo
/*
const int& Determinant::occ(const int&o, const int&i) const;
const int& Determinant::vir(const int&o, const int&a) const;
*/

