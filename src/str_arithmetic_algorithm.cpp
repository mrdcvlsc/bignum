#include "bignum.h"

string bignum::internal_addition(string a, string b) const{
	
	vector<long long int> upper_adden = str_part_by(18,a);
	vector<long long int> lower_adden = str_part_by(18,b);

	size_t adden_size = upper_adden.size();
	size_t n = adden_size+1ll;
	long long int *index_sums = new long long int[n];
	index_sums[0] = 0ll;									

	for(size_t i=0ll ;i<adden_size; ++i)
		index_sums[i+1]=upper_adden[i]+lower_adden[i];

	for(size_t i=n-1ll; i>0ll; --i)
		if(index_sums[i]>999999999999999999ll){
			index_sums[i]=index_sums[i]-1000000000000000000ll;
			++index_sums[i-1];
		}

	string carried_answer="", current_index;
	for(size_t i=0ll;i<n;++i) {

		index_sums[i] = abs(index_sums[i]);
		current_index = to_string(index_sums[i]);
		string front_zeros(18-current_index.size(),'0');
		carried_answer+=(front_zeros+current_index);
	}
	
	delete [] index_sums;
	return removeFrontZeros(carried_answer);
}

string bignum::internal_subtraction(string a, string b) const{

	vector<long long int>    minuend = str_part_by(18,a);
	vector<long long int> subtrahend = str_part_by(18,b);

	size_t minuend_size = minuend.size();
	size_t n = minuend_size+1ll;
	long long int *index_diff = new long long int[n];
	index_diff[0] = 0ll; 

	for(size_t i=0ll; i<minuend_size; ++i)
		index_diff[i+1]=minuend[i]-subtrahend[i];

	for(size_t i=n-1ll; i>0ll; --i)
		if(index_diff[i]<0ll) {

			index_diff[i]=index_diff[i]+1000000000000000000ll;
			--index_diff[i-1];
		}

	string carried_answer="", current_index;
	for(size_t i=0ll;i<n;++i) {

		index_diff[i] = abs(index_diff[i]);
		current_index = to_string(index_diff[i]);
		string front_zeros(18-current_index.size(),'0');
		carried_answer+=(front_zeros+current_index);
	}
	delete [] index_diff;
	return removeFrontZeros(carried_answer);
}

string bignum::internal_multiplication(string upperNumber, string bottomNumber) const{
	
	vector<long long int> multiplicand = str_part_by(8,upperNumber);
	vector<long long int> multiplier   = str_part_by(8,bottomNumber);

	// set all values of product to zero
	size_t product_length = multiplicand.size()+multiplier.size(); 
	long long int *index_product = new long long int[product_length];
	
	for(size_t i=0ll; i<product_length; ++i){ index_product[i] = 0ll; }

	// add the answer of the multiplicand and multiplier to the answer array
	size_t multiplier_size = multiplier.size();
	size_t multiplicand_size = multiplicand.size();

	for(size_t i=0ul; i<multiplier_size; ++i){
		for(size_t j=0ul;j<multiplicand_size;++j) {
			index_product[product_length-1-i-j] = index_product[product_length-1-i-j]+(multiplicand[multiplicand_size-1-j]*multiplier[multiplier_size-1-i]);
		}
	}

	for(size_t i=0ul;i<product_length;++i) {
		if(index_product[product_length-1-i]>=100000000ll) {
			long long int ten = ten_thsd(index_product[product_length-1-i]);
			long long int one = one_thsd(index_product[product_length-1-i],ten);
			index_product[product_length-1-i]=one;
			index_product[product_length-1-i-1]=index_product[product_length-1-i-1]+ten;
		}
	}

	string carried_answer, current_index;
	for(size_t i=0;i<product_length;++i) {
		current_index = to_string(index_product[product_length-1-i]);
		string front_zeros(8-current_index.size(),'0');
		carried_answer= front_zeros+current_index+carried_answer;
	}
	delete [] index_product;
	return removeFrontZeros(carried_answer);
}
                      
string bignum::internal_division(string dividen, string divisor) const
{
	if(dividen==divisor) return "1";
	if(dividen=="0")     return "0";
	if(divisor=="1")     return dividen;

	bignum BIGDIVISOR = divisor;

	size_t DIVIDEN_LENGTH = dividen.size();

	string p_answer = "";
	string remainders = "";

	for(size_t i=0; i<DIVIDEN_LENGTH; ++i)
	{
		string digitChar(1,dividen[i]);
		bignum p_dividen = remainders + digitChar;

		int p_count = 0;

		while(true){
			if(BIGDIVISOR<=p_dividen){
				p_count++;
				p_dividen = p_dividen - BIGDIVISOR;
			}
			else{
				break;
			}
		}
		remainders = p_dividen.data;
		if(remainders=="0") remainders = "";

		p_answer = p_answer + to_string(p_count);
	}
	return p_answer;
}