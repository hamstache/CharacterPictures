#include <iostream>
using namespace std;
#include "Picture.h"
#include <string>

const char* init[] = {"Miami" , "in the" , "Autumn" };

int main() {
    Picture p( init, 3);
    cout << p << endl;
    
    Picture p_framed = frame(p);
    cout << p_framed << endl;
    
    Picture q = frame(p_framed & (p | p_framed) );
    cout << q << endl;
    
    Picture r = (p_framed & p) | q;
    cout << r << endl;
    
    Picture r_framed = frame(r);
    cout << r_framed << endl;
    
    return 0;
}
