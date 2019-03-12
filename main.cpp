#include <iostream>
#include <cstring>
#include <ctype>

using namespace std;

class String {
    protected:
        int length;
        int size;
        char * data;
    public:

        int get_len();
        int operator /(int) ();
        int find ( const String& token );
        void resize( int new_size);
        bool is_number();

        bool operator >  ( const String& second );
        bool operator <  ( const String& second );
        bool operator <= ( const String& second );
        bool operator >= ( const String& second );
        bool operator != ( const String& second );
        bool operator == ( const String& second );

        String operator ()  ( int num );
        String& operator [] ( int pos );
        String& operator =  ( const String& source );

        friend istream& operator >> ( istream& input, String& str );
        friend ostream& operator << ( ostream& output, String& str );
        friend String operator * ( const String& str, int count );
        friend String operator + ( const String& first, const String& second );

        String();
        String( const String& source );
        String( char * def_str, int def_len = -1 );
        ~String();
};

int main() {
    String obj;
    obj.data[1] = 'x';
    cout << obj << endl;
    return 0;
}



int String::get_len() {
    return length;
}

int String::operator /(int) () {
    if ( !is_number() )
        throw "Can't convert string to number. Incorrect symb.";
    int res = 0;
    bool negative = (data[0] == '-');
    // std::func( -- ).
}

int String::find(const String &token) {
    int pos = 0;
    while ( pos < length) {
        while ( pos < length && data[pos] != token.data[0] )
            ++pos;
        if ( pos < length ) {
            int saved_v = pos;
            do {
                ++pos;
            } while ( (pos - saved_v) < token.length && data[pos] == token.data[pos - saved_v] && pos < length );
            if ( (pos - saved_v) == token.length )
                return saved_v;
            pos = saved_v + 1;
        }
    }
    return -1;
}

void String::resize(int new_size) {
    char * new_data = new char[new_size];
    length = min( length, new_size );
    for ( int i = 0; i < length; ++i )
        new_data[i] = data[i];
}

bool String::is_number() {
    bool is_negative(false), is_fract(false);
    if ( data[0] == '-' ) {
        is_negative = true;
        ++data;
        --length;
    }
    for ( int i = 0; i < length; ++i ) {
        if ( data[i] == '.' ) {
            if ( is_fract )
                return false;
            is_fract = true;
        }
        else if ( data[i] < '0' || data[i] > '9' ) {
            return false;
        }
    }
    if ( is_negative ) {
        --data;
        ++length;
    }
    return true;
}

bool String::operator >(const String &second) {
    for ( int pos = 0; pos < min( this->length, second.length ); ++pos )
        if ( data[pos] > second.data[pos] ) {
            return true;
        }
        else if ( data[pos] < second.data[pos] ) {
            return false;
        }
    return ( this->length > second.length );
}

bool String::operator <(const String &second) {
    for ( int pos = 0; pos < min( this->length, second.length ); ++pos )
        if ( data[pos] < second.data[pos] ) {
            return true;
        }
        else if ( data[pos] > second.data[pos] ) {
            return false;
        }
    return ( this->length < second.length );
}

bool String::operator <=(const String &second) {
    return !( (this*) > second );
}

bool String::operator >=(const String &second) {
    return !( (this*) < second );
}

bool String::operator !=(const String &second) {
    return !( (this*) == second );
}

bool String::operator ==(const String &second) {
    if ( this->length != second.length )
        return false;
    for ( int i = 0;i < length; ++i )
        if ( data[i] != second.data[i] )
            return false;
    return true;
}

String String::operator ()(int num) {
    int count = 0, pos = 0;
    while ( pos < length && count < num ) {
        while ( pos < length && isspace( data[pos] ) )
            ++pos;
        while ( pos < length && !isspace( data[pos] ) )
            ++pos;
        if ( !isspace( data[pos - 1] ) )
            ++count;
    }
    if ( count == num ) {
        int str_len = 0, last_pos = pos;
        while ( pos >= 0 && isspace( data[pos] ) )
            --pos;
        while ( pos >= 0 && !isspace( data[pos--] ) )
            ++str_len;
        return String( &(data[pos + 1]), str_len );
    }
    return String( "!", 0 );
}

String &String::operator [](int index) {
    if ( index >= 0 )
        return data[index % length];
    return data[ length + ((index + 1) % length - 1) ];
}

String &String::operator =(const String &source) {
    this->length = source.length;
    this->size = maks( source.size, length );
    delete [] data;
    data = new char[size];
    for ( int i = 0; i < length; ++i )
        data[i] = source.data[i];
    return (this*);
}

istream &operator >>(istream &input, String &str) {
    char c;
    while ( input.get( c ) && c != '\n' ) {
        if ( str.length >= str.size)
            str.resize( str.size * 2 );
        str.data[ str.length++ ] = c;
    }
    str.data[ str.length++ ] = '\0';
    return input;
}

ostream &operator <<(ostream &output, String &str) {
    for ( int i =0; i < str.length; ++i )
        output << str.data[i];
    return output;
}

String operator *(const String &str, int count) {
    if ( count < 0 )
        throw("Cannot multiply string by negative number");
    String res( str );
    int new_size = ( (res.length * count + 1) / 10) * 10;
    res.resize( new_size );
    int i, j, m;
    for ( i = 1; i < count; ++i )
        for ( m = res.length * i, j = 0; j < res.length; ++j )
            res.data[m + j] = res.data[j];
    res.length *= count;
    return res;
}

String operator +(const String &first, const String &second) {
    String res;
    res.resize( first.size + second.size );
    int i;
    while ( i < first.length )
        res.data[i] = first[i];
    while ( i < (first.length + second.length) )
        res.data[i] = second[i - first.size];
    return res;
}

String::String() {
    size = 10;
    length = 0;
    data = new char[size];
}

String::String(const String &source): String( source.data, source.length ) {
    // всё
}

String::String(char *def_str, int def_len) {
    if ( def_str == nullptr )
        throw("nullptr in parametr Ctor of String");
    if ( def_len >= 0 ) {
        size = ((def_len + 1) / 10 + 1) * 10;
        data = new char[size];
        for ( length = 0 ; length < def_len; ++length )
            data[length] = def_str[length];
    }
    else {
        length = 0;
        do {
            ++length;
        } while ( def_str[length] != '\0' );

        size = (length / 10 + 1) * 10;
        data = new char[size];

        for ( int i = 0; i < length; ++i )
            data[i] = def_str[i];
    }
    data[length++] = '\0';
}

String::~String() {
    delete [] data;
}
