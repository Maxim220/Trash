#include "functions.h"

using namespace std;

int byte_len = 8;

void read(char *source_name, char *target_name, vector<char> corr_symb) {
    if ( !strcmp( source_name, target_name ) )
        return;
    ifstream fin( source_name );
    ofstream fout( target_name );
    char c;
    while ( !fin.eof() ) {
        fin.get( c );
        for ( char correct: corr_symb )
            if ( c == correct ) {
                fout << c;
                break;
            }
    }
    fin.close();
    fout.close();
}

Byte read(ifstream& source, Byte for_res, int position) {
    static int pos = 0;
    static void * last_uses_thread = nullptr;
    if ( &source != last_uses_thread ) {
        last_uses_thread = &source;
        if ( position < 0 )
            pos = 0;
    }
    if ( position >= 0 )
        pos = position;
    if ( for_res == nullptr )
        for_res = new char[byte_len];
    int saved_pos = source.tellg();
    source.seekg( pos, ios::beg );
    for ( int i = 0; i < byte_len; ++i )
        source.get( for_res[i] );
    pos += byte_len;
    source.seekg( (saved_pos - 1 + byte_len), ios::beg );
    return for_res;
}

int translate(Byte byte, unsigned in_base) {
    unsigned degree(1), number = 0;
    for ( int pos = byte_len - 1; pos >= 0; --pos ) {
        number += (byte[pos] - '0') * degree;
        degree *= in_base;
    }
    //ToDo: number from 10 to 'n' basse
    return number;
}


int input_length( ifstream& input ) {
    int saved_pos = input.tellg();
    input.clear();
    input.seekg( 0, ios::end );
    int res = input.tellg() / byte_len;
    input.seekg( saved_pos, ios::beg );
    return res;
}

int find_degree(int num, int base) {
    int degree = 0, bs_in_degr = 1;
    while ( bs_in_degr < num ) {
        ++degree;
        bs_in_degr *= base;
    }
    return bs_in_degr == num ? degree : -1;
}

void decode(char *data_file, char *res_file) {
    if ( !strncmp( data_file, "Decode_tmp.txt", 14) || data_file[0] == '\0' ) {
        cout << "Incorrect name of data file for Decode";
        return;
    }
    read( data_file, "Decode_tmp.txt", {'0', '1'} );
    ifstream fin( data_file );
    ofstream fout( res_file );
    int saved_bl = byte_len;
    byte_len = 8;
    int length = input_length( fin );
    Byte current = new char[byte_len];
    for ( int i = 0; i < length; ++i ) {
        read( fin, current );
        fout << decode( current);
    }
    byte_len = saved_bl;
    fin.close();
    fout.close();
}

unsigned char decode( Byte byte, unsigned base ) {
    int number = translate( byte, base );
    unsigned char res( number );
    return res;
}
