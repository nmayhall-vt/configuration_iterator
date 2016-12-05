#include "helpers.h"

int helpers::increment_comb(std::vector<int>& list, const int& Mstart, const int& Mend)
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
            return 0;
        };
    };
    return 1;
};/*}}}*/

void helpers::print(const vector<int> &k) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size(); ++i){
        cout<< k[i] << " " ;
    };
    cout << "]" << endl;
};/*}}}*/

void helpers::print(vector<int> &k) 
{/*{{{*/
    cout << "[";
    for (int i = 0; i < (int)k.size(); ++i){
        cout<< k[i] << " " ;
    };
    cout << "]" << endl;
};/*}}}*/

void helpers::print(const vector<int> &k, const vector<int> &l) 
{/*{{{*/
    //cout << "[";
    for (int i = 0; i < (int)k.size(); ++i) cout << k[i] << " " ;
    //cout << "] | [";
    cout << "| ";
    for (int i = 0; i < (int)l.size(); ++i) cout << l[i] << " " ;
    //cout << "]" << endl;
    //cout << endl;
};/*}}}*/


