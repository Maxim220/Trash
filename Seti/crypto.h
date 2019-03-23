#ifndef CRYPTO_H
#define CRYPTO_H

#include "functions.h"

class Cipher {
    protected:
        std::ifstream input;
        std::ofstream output;
    public:
        virtual void encrypt() = 0;
        virtual void decrypt() = 0;
        // -_-_-
};

class Syberian: public Cipher {
    public:
        void encrypt() = 0;
        void decrypt() = 0;
        Syberian( char * src_file, char * res_file = "Syberian_res.txt" );
};

class Aes: public Cipher {
    public:
        void encrypt() = 0;
        void decrypt() = 0;
        Aes( char * src_file, char * res_file = "Aes_res.txt" );
};

class My_GPSP {
    int grain;
public:
    int get_number();
    My_GPSP( int grain );
};

class Diffie_Hellman {

};

#endif // CRYPTO_H
