#include "CombinatorialIndex.h" 

CombinatorialIndex::CombinatorialIndex()
{/*{{{*/
    _max = -1;
    _n_orbs = 0;
    _n_elec = 0;
    _orb_shift = 0;
};/*}}}*/

CombinatorialIndex::CombinatorialIndex(const int& n_, const int& k_)
{/*{{{*/
    _max = -1;
    _n_orbs = n_;
    _n_elec = k_;
    _orb_shift = 0;
    
    // Start with initial _configuration
    //_config.resize(_n_elec);
    for(int i=0; i<_n_elec; i++) _config.push_back(i); 
    for(int i=_n_elec; i<_n_orbs; i++) _vir.push_back(i); 
    _scr.resize(_config.size());
    _vir_reset = _vir;
    _config_reset = _config;
};/*}}}*/

void CombinatorialIndex::reset()
{/*{{{*/
    /* Increment index */
    //for(int i=0; i<_n_elec; i++) _config.at(i)=i; 
    //for(int i=0; i<_n_orbs-_n_elec; i++) _vir.at(i) = i+_n_elec; 
    _config = _config_reset;
    _vir = _vir_reset;
    _lin_index = 0;
};/*}}}*/

void CombinatorialIndex::incr()
{/*{{{*/
    /* Increment index */
    increment_comb(_config,0,_n_orbs-1);
    decrement_comb(_vir,0,_n_orbs-1);
    _lin_index += 1;
};/*}}}*/

void CombinatorialIndex::decr()
{/*{{{*/
    /* Increment index */
    decrement_comb(_config,0,_n_orbs-1);
    increment_comb(_vir,0,_n_orbs-1);
    _lin_index -= 1;
};/*}}}*/

void CombinatorialIndex::print()
{/*{{{*/
    helpers::print(_config);
    //helpers::print(_config,_orb_shift);
};/*}}}*/

size_t CombinatorialIndex::max()
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
    /*!
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

void CombinatorialIndex::decrement_comb(std::vector<int>& list, const int& Mstart, const int& Mend)
{/*{{{*/
    /*!
    Form the previous combination of M choose N
    for (Mstart, Mstart+1, Mstart+2,.., Mend) of 
    length N
    */
    int N = list.size();
    for(int i=N-1; i>0; i--){
        //helpers::print(list);
        //cout << list[i] << ","<< list[i-1] << endl;
        if(list[i] > list[i-1]+1){
            list[i]--;
            for(int j=N-1; j>i; j--){
                list[j] = Mend-((N-1)-j);
            };
            return;
        };
    };
    if(list[0] > Mstart){
        list[0]--;
        for(int j=N-1; j>0; j--){
            list[j] = Mend-((N-1)-j);
        };
        return;
    };
    return;
};/*}}}*/

const size_t& CombinatorialIndex::calc_linear_index()
{/*{{{*/
   /* 
      Return linear index for lexically ordered _config string
      */
    

    _lin_index = 0;

    int v_prev = -1;

    for(int i=0; i<_config.size(); i++){
        int v = _config[i];
        int M = _n_orbs - v;
        int N = _config.size() - i - 1;
        int w = v - v_prev - 1;
        //todo: change mchn from function call to data lookup!
        for(int j=0; j<w; j++){
            _lin_index += calc_nchk(M+j,N);
        };
        v_prev = v;
    };
    return _lin_index;
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

void CombinatorialIndex::single_excitation2(const int& i, const int& a, size_t& lin_index, int& sign)
{/*{{{*/
    ///  
    ///  Compute sign required to bring an "excited" active space configuration,
    ///  obtained by replacing the orbital index corresponding to electron i and replacing that
    ///  with the orbital index associated with the a'th 'hole'  
    ///
    ///  Input:  
    ///    config    list of orbitals occupied for a given configuration
    ///    i         electron index in configuration to replace
    ///    a         virtual index in configuration to now occupy
    ///              
    ///
    ///  Return: 
    ///    sign      +1/-1 sign depending on number of orbital swaps required to sort
    ///
    ///
    
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _vir.size()) throw std::range_error( "a >= _vir");
    if( i >= _config.size()) throw std::range_error( "a >= _config");
#endif
    _scr = _config;
    _scr[i] = _vir[a];
    
    //printf("      ");
    //helpers::print(_scr); 

    sign = 1;
    for(int i=1; i<_scr.size(); )
    {
        if(_scr[i] < _scr[i-1])
        {
            flip(_scr,i,i-1);
            sign = -sign;
            i = min(i-1,1);
            //i = 1;
            continue;
        };
        i++;
    };
    //printf(" %4i ",sign);
    //helpers::print(_scr); 
    //printf("\n");
    
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
    return;
};/*}}}*/

void CombinatorialIndex::double_excitation2(const int& i, const int& j, const int& a, const int& b, size_t& lin_index, int& sign)
{/*{{{*/
    ///  
    ///  Compute sign required to bring an "excited" active space configuration,
    ///  obtained by replacing the orbital index corresponding to orbitals i and j 
    ///  with the orbital indices corresponding to the a'th and b'th unoccupied sites
    ///
    ///  Input:  
    ///    i         electron index in configuration to replace
    ///    j         electron index in configuration to replace
    ///    a         virtual index in configuration to now occupy
    ///    b         virtual index in configuration to now occupy
    ///              
    ///
    ///  Return: 
    ///    sign      +1/-1 sign depending on number of orbital swaps required to sort
    ///
    ///  
    
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _vir.size()) throw std::range_error( "a >= _vir");
    if( b >= _vir.size()) throw std::range_error( "b >= _vir");
    if( i >= _config.size()) throw std::range_error( "i >= _config");
    if( j >= _config.size()) throw std::range_error( "i >= _config");
    if( j <= i) throw std::range_error( "j <= i");
    if( b <= a) throw std::range_error( "b <= a");
#endif
    _scr = _config;
    _scr[i] = _vir[a];
    _scr[j] = _vir[b];
   
    /* 
    printf("      ");
    helpers::print(_scr); 
    */

    sign = 1;
    for(int i=1; i<_scr.size(); )
    {
        if(_scr[i] < _scr[i-1])
        {
            flip(_scr,i,i-1);
            sign = -sign;
            i = min(i-1,1);
            //i = 1;
            continue;
        };
        i++;
    };

#ifdef DEBUG
    // double check sorting
    for(int i=1; i<_scr.size(); i++) if(_scr[i] < _scr[i-1]) throw std::runtime_error("string not sorted");
#endif
   
    /* 
    printf(" %4i ",sign);
    helpers::print(_scr); 
    printf("\n");
    */
    
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
    return;
};/*}}}*/

const int CombinatorialIndex::occ(const int& i)
{/*{{{*/
#ifdef DEBUG
    if(i >= _config.size()) throw std::range_error("occ: i >= _config.size()");
#endif
    //return _config[i];
    return _config[i] + _orb_shift;
};/*}}}*/

const int CombinatorialIndex::vir(const int& a)
{/*{{{*/
#ifdef DEBUG
    if(a >= _vir.size()) throw std::range_error("occ: i >= _vir.size()");
#endif
    //return _vir[a];
    return _vir[a] + _orb_shift;
};/*}}}*/

void CombinatorialIndex::flip(vector<int>& v, const int& p, const int& q)
{/*{{{*/
#ifdef DEBUG
    if(p >= _vir.size()) throw std::range_error("in flip");
    if(q >= _vir.size()) throw std::range_error("in flip");
    if(p < 0) throw std::range_error("negative in flip");
    if(q < 0) throw std::range_error("negative in flip");
#endif
    int tmp = v[p];
    v[p] = v[q];
    v[q] = tmp;
    return;
};/*}}}*/







/* ================================================== Obsolescent =======================================*/
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
    ///  
    ///  Compute sign required to bring an "excited" active space configuration,
    ///  obtained by finding the index corresponding to orbital i and replacing that
    ///  with a replacing assigning    
    ///
    ///  Input:  
    ///    config    list of orbitals occupied for a given configuration
    ///    i         value of orbital index occupied to replace
    ///    a         value of orbital index to occupy with n, i.e.,
    ///              
    ///
    ///  Return: 
    ///    sign      +1/-1 sign depending on number of orbital swaps required to sort
    ///
    ///  
    ///  Complexity: logarithmic in length of config
    ///
    
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _n_orbs) throw std::range_error( "a >= _n_orbs");
    int present = 0;
    for(int j=0; j<_config.size(); j++)
    {
        if(_config[j] == i) present +=1;
        if(_config[j] == a) throw std::range_error( "out of range: i");
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

CombinatorialIndex CombinatorialIndex::apply_single_excitation(const int& i, const int& a)
{/*{{{*/
    /*! 
    
      Modify index so as to create the configuration generated by an E_i^a excitation.
      This uses a sort algorithm to bring the substituted configuration back into 
      canonical order. However, this function should be combined with 
          "calc_single_excitation_sign" to minimize duplicate work.
    
      Input:  
    
        i         value of orbital index occupied to replace
    
        a         value of orbital index to occupy with n, i.e
                  
    */
#ifdef DEBUG
    //
    //  Check ranges
    if( a >= _n_orbs) throw std::range_error( "a >= _n_orbs");
    if(i >= _n_orbs) throw std::range_error(" i > _n_orbs");
#endif
   
    _scr = _config;

    int i_loc = -1;
    int a_loc = -1;
    for(int j=0; j<_scr.size(); j++)
    {
        if(_scr[j] == i) i_loc = j;
        if(_scr[j] == a) throw std::range_error(" a already here"); 
        if(_scr[j] == a) throw std::range_error(" a already here"); 
    };
    /*
    for(int j=0; j<_vir.size(); j++)
    {
        if(_vir.at(j) == a) a_loc = j;
        if(_vir.at(j) == i) throw std::range_error(" i already here"); 
        if(_vir.at(j) == i) throw std::range_error(" i already here"); 
    };
    */
    if(i_loc == -1) throw std::range_error(" i not found");
    
    _scr[i_loc] = a;                          // make i -> a replacement
    sort(_scr.begin(), _scr.end());           // sort resulting string

    CombinatorialIndex tmp(_n_orbs, _n_elec);
    tmp.set_config(_scr);
    return tmp;
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
    
    return;
};/*}}}*/

