#include "bignum.h"

bignum::bignum(const char* value){
		string temp(value);
		check(temp);	
		temp = removeFrontZeros(temp);
		this->data = temp;
}
bignum::bignum(string value){
		check(value);
		string value2 = removeFrontZeros(value);
		this->data=value2;
}
