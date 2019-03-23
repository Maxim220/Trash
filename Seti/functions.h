#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

typedef char* Byte;

extern int byte_len;

void read( char * source_name, char * target_name, std::vector<char> corr_symb = { '0', '1' } );
Byte read( std::ifstream& source, Byte for_res = nullptr, int position = -1 );
int translate( Byte byte, unsigned base = 2 );
int input_length( std::ifstream& input );
int find_degree( int num, int base = 2 );
void decode( char * data_file, char * res_file );
unsigned char decode( Byte byte, unsigned base = 2 );

#endif // FUNCTIONS_H
