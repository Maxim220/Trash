#include <iostream>
#include <cstring>

using namespace std;

typedef long long int hash_t;
typedef char* key_t;

// c е templat'ом компилится слииишком
// долго я так до релиза не доживу
// шаблон с 2 параметрами просто трэш
// час пытлся написать шаблонный класс
// в итоге просто удалил этот ужас
// ...

struct node {
    node* right;
    node* left;
    int value;
    node( value ) {
        this->value = value;
        right = nullptr;
        left  = nullptr;
    }
};

class AVL_tree {

};

struct ceil {
    hash_t hash;
    int value;
};

class AssocArray {
        int size;
        int count;
        ceil * data;
        key_t * keys;
        void add( key_t key, int value = 0 );
        void resize( int new_size );
        int find( key_t key );
        hash_t get_hash( key_t key );
    public:
        void set( key_t key, int value );
        void change( key_t key, int delta );
        int get( key_t key );
        int &operator[] (const key_t key);
        AssocArray( int init_size, ceil * init_arr );
        ~AssocArray();
};

int main() {
    Array<char*,int> arr;
    arr.read();
    int pos, end;
    cin >> pos >> end;
    cout << (end - pos - 1) << endl;
    for ( pos = pos + 1; pos < end; ++pos ) {
        cout << arr[pos] << " ";
    }
    return 0;
}


void AssocArray::add(key_t key, int value) {
    int pos = find( key );
    if ( count >= size )
        resize( size * 2 );
    for ( int i = count; i > pos; --i )
        data[i] = data[i-1];
    data[pos] = ceil( get_hash(key), value );
}

void AssocArray::resize(int new_size) {
    key_t * new_data = new ceil[new_size];
    for ( int i = 0; i < count; ++i )
        new_data[i] = data[i];
    delete [] data;
    data = new_data;
    size = new_size;
}

int AssocArray::find(key_t key) {
    hash_t hash_v = get_hash( key );
    hash_t left = 0, pos, right = count;
    while ( right - left > 1 ) {
        pos = (right - left) / 2;
        if ( data[pos].hash >= hash_v ) {
            right = pos;
        } else
            left  = pos;
    }
    if ( right < count && data[right].hash == hash_v ) {
        return right;
    } else
        return -1;
}

hash_t AssocArray::get_hash( key_t key ) {
    hash_t res = 0, pos = 0, incr, pos_degr = 1;
    char c;
    while ( key[pos] != '\0' ) {
        if ( c >= '0' && c <= '9' ) {
            incr = c - '0';
        }
        else if ( c == '_' ) {
            incr = 10;
        }
        else if ( c >= 'a' && c <= 'z' ) {
            incr = c - 'a' + 11;
        }
        else if ( c >= 'A' && c <= 'Z' ) {
            incr = c - 'A' + 37;
        } else
            cout << "WTF <" << c << "> doing here ???" << endl;
        res += incr * pos_degr;
        pos_degr *= (10 + 1 + 26 + 26);
    }
    return res;
}

void AssocArray::set(key_t key, int value) {
    int pos = find( key );
    if ( pos == -1 ) {
        add( pos)
    }
}

T &AssocArray::operator [](int index) {
    if ( index >= 0 )
        return data[index % count];
    //cout << (index + 1) << '|' << ((index + 1) % count) << '|' << ((index + 1) % count - 1) << endl << ( count - ((index + 1) % count - 1) ) << endl;
    return data[ count + ((index + 1) % count - 1) ];
}

AssocArray::AssocArray(int init_size, ceil *init_arr) {
    size = 10;
    count = 0;
    data = new T[size];
    if ( init_arr != nullptr ) {
        push_back( init_arr, init_size );
        count = init_size;
    }
}

AssocArray::~AssocArray() {
    delete [] data;
    delete [] keys;
}
