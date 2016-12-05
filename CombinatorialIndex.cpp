#include "CombinatorialIndex.h" 

CombinatorialIndex::CombinatorialIndex()
{
    max = -1;
    n_orbs = 0;
    n_elec = 0;
    printf(" Hi, from constructor\n");
};

CombinatorialIndex::CombinatorialIndex(const int& n_, const int& k_)
{
    max = -1;
    n_orbs = n_;
    n_elec = k_;
    printf(" Hi, from constructor2\n");
    
    // Start with initial configuration
    //config.resize(n_elec);
    for(int i=0; i<n_elec; i++) config.push_back(i); 
};

void CombinatorialIndex::incr()
{
    /* Increment index */
    increment_comb(config,0,n_orbs);
};

void CombinatorialIndex::print()
{
    helpers::print(config);
};


long int CombinatorialIndex::get_max()
{/*{{{*/
    //  
    //  Return n choose k
    if (max == -1) // this is the uninitialized value
    {
        max = calc_nchk(n_orbs,n_elec);
    }
    return max;
};/*}}}*/

long int CombinatorialIndex::calc_nchk(const int& n,const int& k) const
{/*{{{*/
    //  
    //  Return m choose n
    long int accum = 1;
    for(long int i=1; i<=k; i++){
        accum = accum * (n-k+i)/i;
    };
    return accum;
};/*}}}*/

void CombinatorialIndex::increment_comb(std::vector<int>& list, const int& Mstart, const int& Mend)
{/*{{{*/
    /*
    Form the next combination of M choose N
    for (Mstart, Mstart+1, Mstart+2,.., Mend) of 
    length N
    Returns: 0  if not at final combination
             1  if at final combination
    */
    int N = list.size();
    for(int i=N-1; i>=0; i--){
        if(list[i] < Mend-N+i+1){
            list[i]++;
            for(int j=i+1; j<N; j++){
                list[j] = list[j-1]+1;
            };
        };
    };
};/*}}}*/

