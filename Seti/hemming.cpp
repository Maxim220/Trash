#include "hemming.h"

using namespace std;

void Hemming( char * source_name, char * output_file ) {
    if ( !strncmp( source_name, "Hemming_tmp.txt", 15) || source_name[0] == '\0' ) {
        cout << "Incorrect name of source file for Hemming";
        return;
    }
    int saved_bl = byte_len;
    byte_len = 15;
    read( source_name, "Hemming_tmp.txt", {'0', '1'} );
    ifstream input("Hemming_tmp.txt");
    ofstream fout( output_file );
    int i, j, length = input_length( input );
    Byte curr = new char[byte_len];
    for ( i = 0; i < length; ++i ) {
        read( input, curr );
        int chngd_bit = checksum( curr ) - 1;
        if ( chngd_bit >= 0 )
            curr[chngd_bit] = (curr[chngd_bit] == '0' ? '1' : '0');
        for ( j = 0; j < byte_len; ++j )
            if ( find_degree( j + 1 ) == -1 )
                fout << curr[j];
    }
    byte_len = saved_bl;
    fout << endl << "Recovery of data completed successfull";
    cout << "Recovery of data completed successfull" << endl;
}


int checksum( Byte byte ) {
    int i, j, res = 0, length = 1;
    bool xor_res;
    for ( length = 1; length < byte_len; length *= 2 ) {
        xor_res = false;
        for ( i = length - 1; i < byte_len; i += length * 2 )
            for ( j = 0; j < length; ++j )
                if ( byte[i + j] == '1' )
                    xor_res = !xor_res;
        if ( xor_res )
            res += length;
    }
    return res;
}
