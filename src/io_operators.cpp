#include "bignum.h"

// ---------- input and output stream operators ---------- 
ostream& operator<<(ostream &out, const bignum &value){
    out << value.data;
    return out;
}

istream& operator>>(istream &in, bignum &value) {
	in >> value.data;
	return in;
}
