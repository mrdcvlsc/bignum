#include "bignum.h"

long long int bignum::one_thsd(long long int number, long long int tens) const {
	return number-(tens*100000000ll);
}

long long int bignum::ten_thsd(long long int number) const {
	return (long long int)floor((long double)number/100000000.0);
}

string bignum::removeFrontZeros(string input) const
{	
	long long in_size = input.size();
	size_t substr_to_remove = 0;
	bool negative = false;
	if(input[0]=='-') negative = true;

	for(long long i=0; i<in_size; ++i)
	{	
		if(in_size>=2)
		{
			if(input[i]=='0' && input[i+1]=='.') break;
		}

		if(input[i]=='0' && i<in_size-1)
		{	
			++substr_to_remove;
			continue;
		}
		if(input[i]>='1' && input[i]<='9') break;
	}
	
	if(substr_to_remove and negative)
		input.erase(1,substr_to_remove);
	else if(substr_to_remove and !negative)
		input.erase(0,substr_to_remove);
	return input;
}

string bignum::removeRearZeros(string input) const
{
	size_t in_size = input.size();
	size_t start_erase_index=0;

	for(size_t i=in_size-1; i>=0; --i){
		if(input[i]=='0' or input[i]=='.'){
			start_erase_index=i;
			if(input[i]=='.') break;
			if(i==1 || i==0) break;
		}
		else
			break;
	}
	if(start_erase_index)
		input.erase(input.begin()+start_erase_index,input.end());
	return input;
}

bignum bignum::absolute(const bignum& input) const {

	string number = input.data;
	if(number[0] == '-') {
		
		number[0] = '0';
		number = removeFrontZeros(number);
	}
	return number;
}

vector<long long int> bignum::str_part_by(long long int length, string number) const {
	
	vector<string> str_partition;
	vector<long long int>   long_partition;

	string str_temp(length,'0');
	size_t num_size = number.size();
	for(size_t i=0, str_i; i<num_size;++i) {
		
		if(i==0 or i%length==0){
			str_i = length;
			str_partition.push_back(str_temp);
		}
		str_partition.back()[str_i-1] = number[num_size-1-i];
		--str_i;
	}

	size_t str_size = str_partition.size();
	for(size_t i=0; i<str_size; ++i)	
		long_partition.push_back(stoll(str_partition[str_size-1-i]));

	return long_partition;
}

pair<string,string> bignum::strfront_fill0(string a, string b) const {

	size_t length1 = a.length();
	size_t length2 = b.length();

	string num1 = a,
	       num2 = b;

	if(length1>length2) {
		
		if(num2[0]=='-') {
			
			num2[0]='0';
			string pad(length1-length2,'0');
			num2=pad+num2;
			num2[0]='-';
		}
		else{

			string pad(length1-length2,'0');
			num2=pad+num2;
		}
	}
	else if(length2>length1) {
		
		if(num1[0]=='-') {
			
			num1[0]='0';
			string pad(length2-length1,'0');
			num1=pad+num1;
			num1[0]='-';
		}
		else{

			string pad(length2-length1,'0');
			num1=pad+num1;
		}
	}
	return make_pair(num1,num2);
}

pair<string,string> bignum::strback_fill0(string a, string b) const {

	size_t length1 = a.length();
	size_t length2 = b.length();

	string num1 = a,
	       num2 = b;

	if(length1>length2) {
		
		if(num2[0]=='-') {
			
			num2[0]='0';
			string pad(length1-length2,'0');
			num2=num2+pad;
			num2[0]='-';
		}
		else{

			string pad(length1-length2,'0');
			num2=num2+pad;
		}
	}
	else if(length2>length1) {
		
		if(num1[0]=='-') {
			
			num1[0]='0';
			string pad(length2-length1,'0');
			num1=num1+pad;
			num1[0]='-';
		}
		else{

			string pad(length2-length1,'0');
			num1=num1+pad;
		}
	}
	return make_pair(num1,num2);
}

pair<string,string> bignum::dec_slice(string float_number) const {
	
	size_t point = 0;
	size_t float_size_num = float_number.size();

	for(size_t i=0; i<float_size_num; ++i){
		
		if(float_number[i]=='.') {
			
			point = i;
			break;
		}
	}
	if(!point)
		return make_pair(float_number,"");
	return make_pair(float_number.substr(0,point),float_number.substr(point+1));
}

bool bignum::isPositive() const {
	
	if(this->data[0] == '-')
		return false;
	return true;
}

bool bignum::sameSign(const bignum& a, const bignum& b) const {
	
	if((a.data[0]=='-' && b.data[0]!='-') || (a.data[0]!='-' && b.data[0]=='-'))
		return false;
	return true;
}

bool bignum::isFloat()const
{	
	string temp = this->data;
	size_t tmp_size = temp.size();
	for(size_t i=0; i<(tmp_size/2)+1; ++i)
		if(temp[i] == '.' || temp[tmp_size-1-i] == '.')
			return true;
	return false;
}

string bignum::moveDecimal(string number,long long moveBy) const{
	long long numberLen = number.size();
	long long decimalPlace = 0;
	for(long long i=0; i<numberLen; ++i){
		if(number[i]=='.'){
			decimalPlace = i;
			break;
		}
	}

	if(decimalPlace==0){
		number = number + ".";
		numberLen = number.size();
		decimalPlace = numberLen-1;
	}

	number.erase(decimalPlace,1);

	if(moveBy<0){
		string addZeroes(-moveBy,'0');
		number = number + addZeroes;
		number.insert(decimalPlace+abs(moveBy),".");
	}
	else{
		string addZeroes(moveBy,'0');
		decimalPlace+=moveBy;
		number = addZeroes + number;
		number.insert(decimalPlace-(moveBy),".");
	}
	return number;
}