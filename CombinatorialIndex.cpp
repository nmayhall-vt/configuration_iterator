#include "CombinatorialIndex.h" 

CombinatorialIndex::CombinatorialIndex()
{/*{{{*/
    _max = -1;
    _n_orbs = 0;
    _n_elec = 0;
};/*}}}*/

CombinatorialIndex::CombinatorialIndex(const int& n_, const int& k_)
{/*{{{*/
    _max = -1;
    _n_orbs = n_;
    _n_elec = k_;
    
    // Start with initial _configuration
    //_config.resize(_n_elec);
    for(int i=0; i<_n_elec; i++) _config.push_back(i); 
    _scr.resize(_config.size());
};/*}}}*/

void CombinatorialIndex::incr()
{/*{{{*/
    /* Increment index */
    increment_comb(_config,0,_n_orbs-1);
};/*}}}*/

void CombinatorialIndex::print()
{/*{{{*/
    helpers::print(_config);
};/*}}}*/

long int CombinatorialIndex::get_max()
{/*{{{*/
    //  
    //  Return n choose k
    if (_max == -1) // this is the uninitialized value
    {
        _max = calc_nchk(_n_orbs,_n_elec);
    }
    return _max;
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
            return;
        };
    };
    return;
};/*}}}*/

long int CombinatorialIndex::calc_linear_index()
{/*{{{*/
   /* 
      Return linear index for lexically ordered _config string
      */
    

    int lin_index = 0;

    int v_prev = -1;

    for(int i=0; i<_config.size(); i++){
        int v = _config[i];
        int M = _n_orbs - v;
        int N = _config.size() - i - 1;
        int w = v - v_prev - 1;
        //todo: change mchn from function call to data lookup!
        for(int j=0; j<w; j++){
            lin_index += calc_nchk(M+j,N);
        };
        v_prev = v;
    };
    return lin_index;
};/*}}}*/

void CombinatorialIndex::set_config(const vector<int>& config)
{/*{{{*/
    if(config.size() == _config.size())
    {
        _config = config;
    }
    else
    { 
        cout << " Changing size in set_config NYI" << endl;
        exit(-1);
    };
};/*}}}*/


int CombinatorialIndex::calc_single_excitation_sign(const int& n, const int& a)
{/*{{{*/
    //  
    //  Compute sign required to bring an "excited" active space configuration,
    //  obtained by replacing assigning a to n (config[n] = a) into canonical (sorted)
    //  order.
    //
    //  Input:  
    //    config    list of orbitals occupied for a given configuration
    //    n         index for electron to be replaced
    //    a         value of orbital index to occupy with n, i.e.,
    //              
    //
    //  Return: 
    //    sign      +1/-1 sign depending on number of orbital swaps required to sort
    //
    //  
    //  Complexity: logarithmic in length of config
    //
    
    
    int sign = 1;
    vector<int>::const_iterator pos_a_sorted;     // electron index for a in canonical ordering
    
    pos_a_sorted = lower_bound(_config.begin(), _config.end(),a);

    int ub = pos_a_sorted-_config.begin();   // upper_bound index
    int dest;                               // destination index for a

#ifdef DEBUG
    if( n >= _config.size()) throw std::range_error( "out of range: n" );
    if( a >= _n_orbs) throw std::range_error( "out of range: a");
#endif


    if(ub>n){ 
        dest = ub-1;
    }else{ 
        dest = ub;
    };
    
    if( (dest-n) % 2 == 0){ 
        sign = 1;
    }else{
        sign = -1;
    };
    
    return sign;
};/*}}}*/

int CombinatorialIndex::calc_single_excitation_sign2(const int& i, const int& a)
{/*{{{*/
    //  
    //  Compute sign required to bring an "excited" active space configuration,
    //  obtained by finding the index corresponding to orbital i and replacing that
    //  with a replacing assigning    
    //
    //  Input:  
    //    config    list of orbitals occupied for a given configuration
    //    i         value of orbital index occupied to replace
    //    a         value of orbital index to occupy with n, i.e.,
    //              
    //
    //  Return: 
    //    sign      +1/-1 sign depending on number of orbital swaps required to sort
    //
    //  
    //  Complexity: logarithmic in length of config
    //
    
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _n_orbs) throw std::range_error( "a >= _n_orbs");
    int present = 0;
    for(int j=0; j<_config.size(); j++)
    {
        if(_config.at(j) == i) present +=1;
        if(_config.at(j) == a) throw std::range_error( "out of range: i");
    };
    if(present == 0) throw std::range_error(" i not found");
    if(i >= _n_orbs) throw std::range_error(" i > _n_orbs");
#endif
    
    vector<int>::const_iterator pos_i_sorted;     // electron index for i in canonical ordering
    vector<int>::const_iterator pos_a_sorted;     // electron index for a in canonical ordering
    
    pos_i_sorted = lower_bound(_config.begin(), _config.end(),i);
    pos_a_sorted = lower_bound(_config.begin(), _config.end(),a);

    int sign = 1;
    if(pos_a_sorted > pos_i_sorted){ 
        if( (pos_a_sorted-pos_i_sorted-1) % 2 != 0) sign = -1;
    }else{ 
        if( (pos_a_sorted-pos_i_sorted) % 2 != 0) sign = -1;
    };

    return sign;
};/*}}}*/

void CombinatorialIndex::apply_single_excitation(const int& i, const int& a)
{/*{{{*/
    /// 
    ///
    ///  Modify index so as to create the configuration generated by an E_i^a excitation.
    ///  This uses a sort algorithm to bring the substituted configuration back into 
    ///  canonical order. However, this function should be combined with 
    ///      "calc_single_excitation_sign" to minimize duplicate work.
    ///
    ///  Input:  
    ///
    ///    i         value of orbital index occupied to replace
    ///
    ///    a         value of orbital index to occupy with n, i.e
    ///              
    ///
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _n_orbs) throw std::range_error( "a >= _n_orbs");
    if(i >= _n_orbs) throw std::range_error(" i > _n_orbs");
#endif
    
    int i_loc = -1;
    for(int j=0; j<_config.size(); j++)
    {
        if(_config.at(j) == i)
        {
            i_loc = j;
        };
        if(_config.at(j) == a)
        {
            throw std::range_error(" a already here"); 
        };
        if(_config.at(j) == a)
        {
            throw std::range_error(" a already here"); 
        };
    };
    if(i_loc == -1) throw std::range_error(" i not found");
    
    _config.at(i_loc) = a;                          // make i -> a replacement
    sort(_config.begin(), _config.end());           // sort resulting string

    return ;
};/*}}}*/

void CombinatorialIndex::single_excitation(const int& i, const int& a, size_t& lin_index, int& sign)
{/*{{{*/
    //  
    //  Compute sign required to bring an "excited" active space configuration,
    //  obtained by finding the index corresponding to orbital i and replacing that
    //  with a replacing assigning    
    //
    //  Input:  
    //    config    list of orbitals occupied for a given configuration
    //    i         value of orbital index occupied to replace
    //    a         value of orbital index to occupy with n, i.e.,
    //              
    //
    //  Return: 
    //    sign      +1/-1 sign depending on number of orbital swaps required to sort
    //
    //  
    //  Complexity: logarithmic in length of config
    //
    
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _n_orbs) throw std::range_error( "a >= _n_orbs");
    int present = 0;
    for(int j=0; j<_config.size(); j++)
    {
        if(_config.at(j) == i) present +=1;
        if(_config.at(j) == a) throw std::range_error( "a already present");
    };
    if(present == 0) throw std::range_error(" i not found");
    if(i >= _n_orbs) throw std::range_error(" i > _n_orbs");
#endif
    
    vector<int>::const_iterator pos_i_sorted;     // electron index for i in canonical ordering
    vector<int>::const_iterator pos_a_sorted;     // electron index for a in canonical ordering
    
    pos_i_sorted = lower_bound(_config.begin(), _config.end(),i);
    pos_a_sorted = lower_bound(_config.begin(), _config.end(),a);
    
    
    //  get sign
    sign = 1;
    if(pos_a_sorted > pos_i_sorted){ 
        if( (pos_a_sorted-pos_i_sorted-1) % 2 != 0) sign = -1;
    }else{ 
        if( (pos_a_sorted-pos_i_sorted) % 2 != 0) sign = -1;
    };


    /* 
    //  get linear index 
    int jj = 0; 
    for(int j=0; j<_config.size(); j++)
    {

        if(j!=pos_i_sorted-_config.begin())
        {
            _scr.at(jj) = _config.at(j);
            jj +=1;
        }
        else if(j!=pos_a_sorted-_config.begin())
        {
            _scr.at(jj) = a;
            jj +=1;
        };
    };
    */

    //  copy config to scr to avoid overwriting current data
    if(_config.size() != _scr.size()) throw std::range_error("_config.size() != _scr.size()");
    for(int j=0; j<_config.size(); j++) _scr[j] = _config[j];
    
    //  make substitution on scr
    _scr.at(pos_i_sorted-_config.begin()) = a;

    //  sort this config - should improve this algorithm later
    sort(_scr.begin(), _scr.end());           

    //  taken from calc_linear_index
    lin_index = 0;

    int v_prev = -1;

    for(int i=0; i<_scr.size(); i++){
        int v = _scr[i];
        int M = _n_orbs - v;
        int N = _scr.size() - i - 1;
        int w = v - v_prev - 1;
        //todo: change mchn from function call to data lookup!
        for(int j=0; j<w; j++){
            lin_index += calc_nchk(M+j,N);
        };
        v_prev = v;
    };
    helpers::print(_scr);
    
    return;
};/*}}}*/



