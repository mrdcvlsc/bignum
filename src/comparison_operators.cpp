#include "bignum.h"
//test
// -------------------- Comparison Operators --------------------

// the == operator is a base operator method used to create other comparison operators
bool bignum::operator==(const bignum& bnum_) const{
	size_t l_size = this->data.size();
	size_t r_size = bnum_.data.size();

	pair<string,string> left  = dec_slice(this->data);
	pair<string,string> right = dec_slice(bnum_.data);

	// check whole number length
	if(left.first.size()!=right.first.size())
		return false; 

	for(size_t i=0; i<l_size && i<r_size; ++i)
		if(this->data[i]!=bnum_.data[i])
			return false;
	return true;
}

// the < operator is another base operator method used to create other comparison operators
bool bignum::operator<(const bignum& bnum_) const{

	// if different signs
	if(this->data[0]=='-' && bnum_.data[0]!='-') return true;
	if(this->data[0]!='-' && bnum_.data[0]=='-') return false;

	// if same sign
	pair<string,string> left  = dec_slice(this->data);
	pair<string,string> right = dec_slice(bnum_.data);

	size_t left_w_size = left.first.size();
	size_t right_w_size = right.first.size();

	size_t left_d_size = left.second.size();

	if(this->data[0]!='-'){ // positive
		     if(left_w_size<right_w_size) return true;
		else if(left_w_size>right_w_size) return false;
		else{
			// check whole
			for(size_t i=0; i<left_w_size; ++i){
				if(left.first[i]<right.first[i]) return true;
				if(left.first[i]>right.first[i]) return false;
			}
			// check decimal
			for(size_t i=0; i<left_d_size; ++i){
				if(left.second[i]<right.second[i]) return true;
				if(left.second[i]>right.second[i]) return false;
			}
			return false;
		}
	}
	else{	// negative
			 if(left_w_size>right_w_size) return true;
		else if(left_w_size<right_w_size) return false;
		else{
			// check whole
			for(size_t i=0; i<left_w_size; ++i){
				if(left.first[i]>right.first[i]) return true;
				if(left.first[i]<right.first[i]) return false;
			}
			// check decimal
			for(size_t i=0; i<left_d_size; ++i){
				if(left.second[i]>right.second[i]) return true;
				if(left.second[i]<right.second[i]) return false;
			}
			return false;
		}
	}
}

bool bignum::operator!=(const bignum& bnum_) const{
	return !(*this==bnum_);
}

bool bignum::operator>(const bignum& bnum_) const{
	if((*this==bnum_))
		return false;
	return !(*this<bnum_);
}

bool bignum::operator<=(const bignum& bnum_) const{
	if(*this==bnum_)
		return true;
	return *this<bnum_;
}

bool bignum::operator>=(const bignum& bnum_) const{	
	if(*this==bnum_)
		return true;
	return *this>bnum_;
}
