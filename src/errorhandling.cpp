#include "bignum.h"

// performs a scan if the string is a valid number
void bignum::check(string &value){
	size_t value_size = value.size(); 
	if(value_size<=0){
		cout<<"\n\x1B[31mbignum ERROR\033[0m [check] : NUMBER HAS NO VALUE"<<endl;
		exit(1);
	}

	if(value[value_size-1]=='.')
		value=value+'0';
	if(value[0]=='.')
		value='0'+value;
	if(value[0]=='-' and value[1]=='.'){
		value[0]='0';
		value='-'+value;
	}

	bool decimal  = false;
	bool negative = false;
	size_t prec = 0;

	for(size_t i=0; i<value_size; ++i){
		
		if(decimal) ++prec; // counts the precision value of the big number
		if(value[i]=='.' and !decimal and isdigit(value[i+1])){
			decimal = true;
			continue;
		}
		if(value[i]>='0' and value[i]<='9')
			continue;
		if(value[i]=='-' and !negative and i==0 and value_size>1){
			negative = true;
			continue;
		}
		if(i==value_size)
			break;
		else{
			cout<<"\n\x1B[31mbignum ERROR\033[0m [check] : ASSIGNED INVALID NUMBER DETECTED ("<<value<<")"<<endl;
			exit(1);
		}
	}
}
