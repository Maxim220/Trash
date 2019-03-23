#include "allias.h"

using namespace std;

void Allias(char *source_name, char * output_name) {
    if ( !strncmp( source_name, "Allias_tmp.txt", 14) || source_name[0] == '\0' ) {
        cout << "Incorrect name of source file for Allias";
        return;
    }
    read( source_name, "Allias_tmp.txt", {'0', '1'} );
    ifstream fin( "Allias_tmp.txt");
    ofstream fout(output_name);
    char curr_s = fin.get();
    Byte buff = new char[1024];
    int saved_bl = byte_len;
    byte_len = 1; // for correct input_length()
    int end = input_length( fin );
    while ( fin.tellg() < end ) {
        byte_len = 0;
        do {
            fin.get( buff[0] );
            ++byte_len;
        } while ( buff[0] == '0' && !fin.eof() );
        if ( fin.eof() )
            break;
        read( fin, buff, fin.tellg() - 1 );
        int count = translate( buff );
        for ( int i = 0; i < count; ++i )
            fout << curr_s;
        curr_s = (curr_s == '0' ? '1' : '0');
    }
    fin.close();
    fout.close();
    byte_len = saved_bl;
    fout << endl << "Data decompression completed successfully";
    cout << "Data decompression completed successfully" << endl;
}
