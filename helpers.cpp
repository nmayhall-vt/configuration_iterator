#include "helpers.h"

void helpers::print(const vector<int> &k) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size()-1; ++i){
        cout<< k[i] << " " ;
    };
    {
        cout<< k[k.size()-1];
    };
    cout << "]" << endl;
};/*}}}*/

void helpers::print(vector<int> &k) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size()-1; ++i){
        cout<< k[i] << " " ;
    };
    {
        cout<< k[k.size()-1];
    };
    cout << "]" << endl;
};/*}}}*/

