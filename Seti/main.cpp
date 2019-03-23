#include "functions.h"
#include "hemming.h"
#include "allias.h"

using namespace std;

int main() {
    Allias( "Allias.txt" );
    decode( "Allias_res.txt", "Allias_resault.txt" );
    Hemming( "Hemming.txt" );
    decode( "Hemming_res.txt", "Hemming_resault.txt" );
    /*
    read( "input.txt", "result.txt"  );
    ifstream fin("resault.txt");
    Byte current = new char[byte_len];
    while ( !fin.eof() ) {
        byte_len = 9;
        current = read( fin );
        byte_len = 8;
        cout << decode( current );
        cout << "1";
        delete [] current;
    }
    */
    return 0;
}
