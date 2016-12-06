#include "helpers.h"

void helpers::print(const vector<int> &k) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size()-1; ++i)
    {
        cout<< k[i] << " " ;
    };
    if (k.size() > 0)
    {
        cout<< k[k.size()-1];
    };
    cout << "]" << endl;
};/*}}}*/

void helpers::print(vector<int> &k) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size()-1; ++i)
    {
        cout<< k[i] << " " ;
    };
    if (k.size() > 0)
    {
        cout<< k[k.size()-1];
    };
    cout << "]" << endl;
};/*}}}*/

void helpers::print(const vector<int> &k, const vector<int> &l) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size()-1; ++i)
    {
        cout<< k[i] << " " ;
    };
    if (k.size() > 0)
    {
        cout<< k[k.size()-1];
    };
    cout << "],[";
    for (int i = 0; i < (int)l.size()-1; ++i)
    {
        cout<< l[i] << " " ;
    };
    if (l.size() > 0)
    {
        cout<< l[l.size()-1];
    };
    cout << "]" << endl;
};/*}}}*/

size_t helpers::nchk(const int& n,const int& k)
{/*{{{*/
    //  
    //  Return m choose n
    long int accum = 1;
    for(long int i=1; i<=k; i++){
        accum = accum * (n-k+i)/i;
    };
    return accum;
};/*}}}*/

