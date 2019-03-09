#include <iostream>

using namespace std;

typedef long long int ll_int;

int find_nod(int a, int b);
int find_nok(int a, int b);

class Fraction {
        ll_int dividend;
      //~~~~~~~~~~~~~
        ll_int divider;
    public:
        void reduce();
        void read();
        void show();
        bool operator > (  Fraction& second );
        bool operator < (  Fraction& second );
        bool operator == (  Fraction& second );
        Fraction operator - ();
        Fraction operator + (  int second );
        Fraction operator + (  Fraction second );
        Fraction operator - (  Fraction& second );
        Fraction operator * (  Fraction& second );
        Fraction operator / (  Fraction& second );
        Fraction operator % (  Fraction& second );
        Fraction& operator = (  Fraction& second );
        friend istream& operator >> ( istream& input, Fraction& fract );
        friend ostream& operator << ( ostream& output, const Fraction& fract );
        Fraction( ll_int dividend = 0, ll_int divider = 1 );
};

//___________________________________________________________________________
int main () {
    Fraction a, b;
    int c;
    cin >> a >> b;
    if ( a > b ) {
        cout << ">";
    }
    else if ( a < b ) {
        cout << "<";
    } else
        cout << '=';
    return 0;
}
//___________________________________________________________________________

ll_int find_nod(ll_int a, ll_int b) {
    if ( !a || !b )
        return 0;
    ll_int nod = 1;
    ll_int max = min( a, b ) / 2;
    if ( a % b == 0 )
        return b;
    if ( b % a == 0 )
        return a;
    for ( ll_int i = max; i > 1; --i )
        if ( !( a % i | b % i ) ) {
            a /= i;
            b /= i;
            nod *= i;
            // пересчитываем максимально возможный делитель
            i = min( a, b ) / 2;
        }
   return nod;
}
ll_int find_nok(ll_int a, ll_int b) {
    ll_int nod = find_nod(a, b);
    return nod ? (a * b) / find_nod(a, b) : 0;
}

void Fraction::read() {
    static char trash;
    cin >> dividend >> trash >> divider;
}
void Fraction::show() {
    cout << dividend << '/' << divider;
}


void Fraction::reduce() {
    if ( !dividend || !divider ) {
        dividend = 0;
        divider = 1;
        return;
    }
    ll_int nod = find_nod( dividend, divider );
    dividend /= nod;
    divider /= nod;
}


bool Fraction::operator <( Fraction &second) {
    ll_int nok = find_nok( this->divider, second.divider );
    return ( this->dividend * (nok / this->divider) ) < ( second.dividend * (nok / second.divider) ) ;
}
bool Fraction::operator >( Fraction &second) {
    ll_int nok = find_nok( this->divider, second.divider );
    return ( this->dividend * (nok / this->divider) ) > ( second.dividend * (nok / second.divider) ) ;
}
bool Fraction::operator ==( Fraction &second) {
    this->reduce();
    second.reduce();
    return (this->dividend == second.dividend) && (this->divider == second.divider);
}
Fraction Fraction::operator -(){
    return Fraction( this->dividend * (-1), this->divider );
}

Fraction Fraction::operator +(int second) {
    return Fraction( dividend + divider * second, divider );
}




Fraction Fraction::operator +( Fraction second) {
    ll_int nok = find_nok( this->divider, second.divider );
    return Fraction( ( this->dividend * (nok / this->divider) + second.dividend * (nok / second.divider) ), nok );
}
Fraction Fraction::operator -( Fraction &second) {
    return ( (*this) + (-second)  );
}
Fraction Fraction::operator *( Fraction &second) {
    return Fraction( (this->dividend * second.dividend), (this->divider * second.divider) );
}
Fraction Fraction::operator /( Fraction &second) {
    return Fraction( (this->dividend * second.divider), (this->divider * second.dividend) );
}
Fraction Fraction::operator %( Fraction &second) {
    ll_int nok = find_nok( this->divider, second.divider );
    return Fraction( ( ( this->dividend * (nok / this->divider) ) % ( second.dividend * (nok / second.divider) ) ), nok);
}
Fraction &Fraction::operator =(Fraction &second) {
    second.reduce();
    this->dividend = second.dividend;
    this->divider = second.divider;
    return (*this);
}


istream &operator >>(istream &input, Fraction& fract) {
    static char trash;
    input >> (fract.dividend) >> trash >> (fract.divider);
    return input;
}
ostream &operator <<(ostream &output, const Fraction& fract) {
    output << (fract.dividend) << '/' << (fract.divider);
    return output;
}



Fraction::Fraction(ll_int dividend, ll_int divider) {
    this->dividend = dividend;
    this->divider = divider;
}


