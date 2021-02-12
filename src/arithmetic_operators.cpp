#include "bignum.h"

// ----------------- INCREMENT/DECREMENT OPERATORS ---------------------------

//pre-fix increment/decrementa
bignum bignum::operator++(){ return *this = *this+"1"; }
bignum bignum::operator--(){ return *this = *this-"1"; }

//post-fix increment/decrementa
bignum bignum::operator++(int){
    ++*this;
    return *this-"1"; 
}
bignum bignum::operator--(int){
    --*this;
    return *this+"1";
} 

// -------------------- Arithmetic Operators --------------------

bignum bignum::operator+(const bignum& right_bn) const{

	bignum t_adden1 = *this;
	bignum t_adden2 = right_bn;

	// if there is a float value
	if(t_adden1.isFloat() || t_adden2.isFloat()){

		pair<string,string> adden1_slices = dec_slice(t_adden1.data),
						    adden2_slices = dec_slice(t_adden2.data);

		pair<string,string> newWhl = strfront_fill0(adden1_slices.first,adden2_slices.first);
		pair<string,string> newDec = strback_fill0(adden1_slices.second,adden2_slices.second);

		bignum answerWhole = bignum(newWhl.first + newDec.first) + bignum(newWhl.second + newDec.second);
		return answerWhole.data.insert(answerWhole.data.size()-newDec.first.size(),".");
	}

	/////////// apply rules of addition ///////////
	bool same_sign   = sameSign(t_adden1,t_adden2);
	bool pos_adden1  = t_adden1.isPositive();
	bool pos_adden2  = t_adden2.isPositive();

	t_adden1 = absolute(t_adden1);
	t_adden2 = absolute(t_adden2);

	bool adden1isMax = t_adden1>t_adden2; 

	pair<string,string> add_num = strfront_fill0(t_adden1.data,t_adden2.data);
	
	// different sign
	if(!same_sign and adden1isMax){
		if(pos_adden1)
			return internal_subtraction(add_num.first,add_num.second);
		return "-"+internal_subtraction(add_num.first,add_num.second);
	}
	else if(!same_sign and !adden1isMax){
		if(pos_adden2)
			return internal_subtraction(add_num.second,add_num.first);
		return "-"+internal_subtraction(add_num.second,add_num.first);
	}

	// same sign both negative
	if(same_sign and !pos_adden1 and !pos_adden2)
		return "-"+internal_addition(add_num.first,add_num.second);

	// same sign bot positive
	return internal_addition(add_num.first,add_num.second);
}

bignum bignum::operator-(const bignum& right_bn) const{
	
	bignum t_minuend    = *this,
	       t_subtrahend = right_bn;

	// if there is a float value
	if(t_minuend.isFloat() || t_subtrahend.isFloat()){

		pair<string,string> minuend_slices    = dec_slice(t_minuend.data),
						    subtrahend_slices = dec_slice(t_subtrahend.data);

		pair<string,string> newWhl = strfront_fill0(minuend_slices.first,subtrahend_slices.first);
		pair<string,string> newDec = strback_fill0(minuend_slices.second,subtrahend_slices.second);

		bignum answerWhole = bignum(newWhl.first+newDec.first)-bignum(newWhl.second+newDec.second);

		string padzero(newDec.first.size(),'0');

		bool isNegative = false;
		if(answerWhole<"0"){
			answerWhole = absolute(answerWhole);
			isNegative = true;
		}

		string answer = padzero+answerWhole.data;
		answer = answer.insert(answer.size()-newDec.first.size(),".");

		if(isNegative) answer = "-" + answer;
		return removeRearZeros(removeFrontZeros(answer));
	}
	
	bool same_sign       = sameSign(t_minuend,t_subtrahend);
	bool pos_minuend     = t_minuend.isPositive();

	bool minuendIsMax = t_minuend>t_subtrahend;

	pair<string,string> sub_num = strfront_fill0(absolute(t_minuend).data,absolute(t_subtrahend).data);

	//apply rules of subtraction
	if(same_sign)
	{
		if(t_minuend==t_subtrahend) return "0";

		else if(pos_minuend){

			if(minuendIsMax)
				 return     internal_subtraction(sub_num.first,sub_num.second);
			else return "-"+internal_subtraction(sub_num.second,sub_num.first);
		}
		else if(!pos_minuend){

			if(minuendIsMax)
				 return     internal_subtraction(sub_num.second,sub_num.first);
			else return "-"+internal_subtraction(sub_num.first,sub_num.second);
		}
	}
	else
	{
		if(t_minuend<t_subtrahend)
			 return "-"+internal_addition(sub_num.first,sub_num.second);
		else return     internal_addition(sub_num.first,sub_num.second);
	}
	return "0";
}

bignum bignum::operator*(const bignum& right_bn) const{
	
	// temporary values	
	bignum t_multiplicand = *this,
	       t_multiplier   = right_bn;

	if(t_multiplicand == "0" || t_multiplier == "0")
		return "0";

	// if there is a float value
	if(t_multiplicand.isFloat() || t_multiplier.isFloat()){
		
		bool same_sign_float = sameSign(t_multiplicand,t_multiplier);

		t_multiplicand = absolute(t_multiplicand);
		t_multiplier   = absolute(t_multiplier);

		pair<string,string> multiplicand_slices = dec_slice(t_multiplicand.data),
						    multiplier_slices   = dec_slice(t_multiplier.data);
	    
		pair<string,string> newWhl = strfront_fill0(multiplicand_slices.first,multiplier_slices.first);
		pair<string,string> newDec = make_pair(multiplicand_slices.second,multiplier_slices.second);

		bignum t1 = newWhl.first + newDec.first;
		bignum t2 = newWhl.second + newDec.second;
		bignum answerWhole = (t1*t2);
		
		string finalAnswer = answerWhole.data.insert(answerWhole.data.size()-(multiplicand_slices.second.size()+multiplier_slices.second.size()),".");

		if(same_sign_float) return finalAnswer;
		return "-"+finalAnswer;
	}

	bool same_sign = sameSign(t_multiplicand,t_multiplier);
	pair<string,string> mul_num = strfront_fill0(absolute(t_multiplicand).data,absolute(t_multiplier).data);

	if(!same_sign)
		return "-"+internal_multiplication(mul_num.first,mul_num.second);
	return internal_multiplication(mul_num.first,mul_num.second);
}

bignum bignum::operator/(const bignum& bnum_) const{

	bignum tempDividen = *this,
	       tempDivisor = bnum_.data;

	if(!tempDividen.isFloat()) tempDividen.data = tempDividen.data + ".0";
	if(!tempDivisor.isFloat()) tempDivisor.data = tempDivisor.data + ".0";

	if(tempDividen == "0") return bignum("0");

	if(tempDivisor=="0"){
		cout<<"\x1B[33mDetected in "<<__FILE__<<" : at line - "<<__LINE__<<"\033[0m"<<endl;
		cout<<"\x1B[31mbignum ERROR\033[0m [division] : ("<<tempDividen<<'/'<<tempDivisor<<") dividing by zero is not possible"<<endl;
		exit(1);
	}
	
	bool differentSign = !sameSign(tempDividen,tempDivisor);

	// make the negatives positive
	tempDividen = absolute(tempDividen);
	tempDivisor = absolute(tempDivisor);

	// length fixing
	size_t tempDividenLength = tempDividen.data.size();
	size_t tempDivisorLength = tempDivisor.data.size();

	if(tempDividenLength<=tempDivisorLength){ // add zeroes to the tempDividen
		size_t addLength = (tempDivisorLength+1)-tempDividenLength;
		string addZero(addLength,'0');
		tempDividen.data = tempDividen.data + addZero;
	}

	pair<string,string> slcDividen = dec_slice(tempDividen.data);
	pair<string,string> slcDivisor = dec_slice(tempDivisor.data);

	string strDividen = slcDividen.first + slcDividen.second;
	string strDivisor = slcDivisor.first + slcDivisor.second;

	size_t moveDecimalPlace = slcDividen.second.size() - slcDivisor.second.size();

	int decimalPrecision = 50;

	string precision(decimalPrecision,'0');
	string answer = internal_division(strDividen+precision,strDivisor);

	answer = moveDecimal(answer,moveDecimalPlace+decimalPrecision);
	answer = removeFrontZeros(removeRearZeros(answer));

	if(!differentSign) return answer;
	else               return "-"+answer;
}

// ------------------- SPECIAL OPERATORS -------------------------

bignum bignum::operator%(const bignum& bnum_) const{
	bignum tempDividen = *this,
	       tempDivisor = bnum_;
	cout<<"1: "<<tempDividen<<endl;
	cout<<"2: "<<tempDivisor<<endl;
	bignum answer = tempDividen / tempDivisor;
	cout<<"3: "<<answer<<endl;
	cout<<"4: "<<tempDividen-(tempDivisor*answer)<<endl;
	return tempDividen-tempDivisor*answer;
}

bignum& bignum::operator+=(const bignum a){
	*this = *this + a;
	return *this;
}

bignum& bignum::operator-=(const bignum a){
	*this = *this - a;
	return *this;
}

bignum& bignum::operator*=(const bignum a){
	*this = *this * a;
	return *this;
}

bignum& bignum::operator/=(const bignum a){
	*this = *this / a;
	return *this;
}