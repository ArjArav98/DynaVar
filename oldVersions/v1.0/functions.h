#include<iostream>
using namespace std;

int stringlen(const char* word){
	int i;
	for(i=0; word[i]!='\0'; i++);
	return i;
}

char* stringcpy(char* word1, const char* word2){
	int len1=stringlen(word1), len2=stringlen(word2);
	int i;
	for(i=0; word2[i]!='\0'; i++){
		word1[i]=word2[i];
	}
	return word1;
}

char* stringcat(char* word1, const char* word2){
	int length1=stringlen(word1), length2=stringlen(word2), i, j;
	char* word3=new char[length1+length2];
	
	for(i=0; word1[i]!='\0'; i++){
		word3[i]=word1[i];
	}
	for(j=0; word2[j]!='\0'; j++, i++){
		word3[i]=word2[j];
	}
	
	return word3;
}

int stringcmp(const char* word1, const char* word2){
	int length1=stringlen(word1), length2=stringlen(word2), shorterLen, equal=0, i;
	
	shorterLen=(length1<length2)? length1: length2;
	shorterLen=(length1==length2)? length1: length1;
	
	for(i=0; i<shorterLen; i++){
		if(word1[i]<word2[i]) return -1;
		else if(word1[i]>word2[i]) return 1;
		else if(word1[i]==word2[i]) equal++;
	}
	
	if(length1==length2){
		if(equal==length1) return 0;
	}
	
	return -1;
}

int getType(const char* input){
	/*
		Return Values:-
			1 --> String
			2 --> Character
			3 --> Floating-Point
			4 --> Double
			5 --> Integer
			6 --> Long
			7 --> Boolean
	*/
	int length=stringlen(input);
	
	int i, numOfDecimals=0;
	
	for(i=0; i<length; i++){
		if(input[i]<'0'||input[i]>'9'){
			if(input[i]=='.'){
				numOfDecimals++;
				if(numOfDecimals==1){
					if(length==1) return 2;
				}
				else{ 
					return 1;
				}
			}
			else if(length>1) return 1;
			else return 2;
		}
		
	}
	
	//for boolean, use stringcmp
	
	if(numOfDecimals==1){
		if(length<=9) return 3;
		else return 4; 
	}
	else{
		if((length<=5&&input[0]<'3')||(length<=5)) return 5;
		else return 6;
	}
}

char* getTypeInWords(char* type, int num){
	
	if(num==1) stringcpy(type, "string");
	else if(num==2) stringcpy(type, "char");
	else if(num==3) stringcpy(type, "float");
	else if(num==4) stringcpy(type, "double");
	else if(num==5) stringcpy(type, "int");
	else if(num==6) stringcpy(type, "long");
	
	return type;
}

int toInt(const char* input){
	int num=0, i, length=stringlen(input);
	
	for(i=0; i<length; i++){
		num*=10;
		int digit=9-('9'-input[i]);
		num+=digit;
	}
	
	return num;
}

long toLong(const char* input){
	long num=0;
	int i, length=stringlen(input);
	
	for(i=0; i<length; i++){
		num*=10;
		long digit=9-('9'-input[i]);
		num+=digit;
	}
	
	return num;
}

float toFloat(const char* input){
	float num=0;
	int i, length=stringlen(input), placesAfterPoint=0;
	
	for(i=0; input[i]!='.'; i++){
		num*=10;
		float digit=9-('9'-input[i]);
		num+=digit;
	}
	
	i++;
	
	float afterPoint=0;
	for(;i<length; i++){
		afterPoint*=10;
		float digit=9-('9'-input[i]);
		afterPoint+=digit;
		placesAfterPoint++;
	}
	
	for(i=0; i<placesAfterPoint; i++){
		afterPoint/=10;
	}
	
	return (num+afterPoint);
}

double toDouble(const char* input){
	double num=0;
	int i, length=stringlen(input), placesAfterPoint=0;
	
	for(i=0; input[i]!='.'; i++){
		num*=10.0;
		double digit=9-('9'-input[i]);
		num+=digit;
	}
	
	i++;
	double afterPoint=0;
	for(;i<length; i++){
		afterPoint*=10.0;
		double digit=9-('9'-input[i]);
		afterPoint+=digit;
		placesAfterPoint++;
	}
	
	for(i=0; i<placesAfterPoint; i++){
		afterPoint/=10.0;
	}
	
	std::cout<<std::fixed;
	
	return (num+afterPoint);
}

char* toString(char* string, int num){
	int i, cpy=num, length;
	for(length=0; cpy!=0; length++, cpy/=10);
	
	string=new char[length];
	
	for(i=0; i<length; i++){
		string[length-1-i]='9'-(9-(num%10));
		num/=10;
	}
	string[length]='\0';
	return string;
}

char* toString(char* string, long num){
	long i, cpy=num, length;
	for(length=0; cpy!=0; length++, cpy/=10);
	
	string=new char[length];
	
	for(i=0; i<length; i++){
		string[length-1-i]='9'-(9-(num%10));
		num/=10;
	}
	string[length]='\0';
	return string;
}

char* toString(char* string, float num){
	
	long long1=num;
	float num1=long1;
	int length1, length2, i;
	
	for(length1=0; long1!=0; length1++, long1/=10);
	
	float diff=1;
	
	for(length2=0; diff!=0;){
		diff=num-num1;
		if(diff!=0) length2++;
		else break;
		
		num*=10;
		long1=num;
		num1=long1;
	}
	
	string=new char[length1+length2+1];
	long1=num;
	
	for(i=0; i<(length2+length1+1); i++){
		if(i==length2){ 
			string[length2+length1-i]='.';
			i++;
		}
		string[length2+length1-i]='9'-(9-(long1%10));
		long1/=10;
	}
	
	string[length1+length2+1]='\0';
	
	return string;
}

char* toString(char* string, double num){
	
	long long1=num;
	double num1=long1;
	int length1, length2, i;
	
	for(length1=0; long1!=0; length1++, long1/=10);
	
	double diff=1;
	
	for(length2=0; diff!=0;){
		diff=num-num1;
		if(diff!=0) length2++;
		else break;
		
		num*=10;
		long1=num;
		num1=long1;
	}
	
	string=new char[length1+length2+1];
	long1=num;
	
	for(i=0; i<(length2+length1+1); i++){
		if(i==length2){ 
			string[length2+length1-i]='.';
			i++;
		}
		string[length2+length1-i]='9'-(9-(long1%10));
		long1/=10;
	}
	
	string[length1+length2+1]='\0';
	
	return string;
}
