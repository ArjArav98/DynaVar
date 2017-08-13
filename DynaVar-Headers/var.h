#include<iostream>
#include"functions.h"
#include"templates.h"
using namespace std;

class var{
public:	
	int type, allocated;
	int number;
	float floating;
	long longint;
	double longfloat;
	char* string;
	
	var(const char* input){
		initValues();
		
		allocated=0;
		int length=stringlen(input), i;
		string=new char[length];
		
		if(length>1) type=1;
		else type=2;
		
		for(i=0; i<length; i++) string[i]=input[i];
		string[length]='\0';
		
		allocated=1;
	}
	var(char c){
		initValues();
		
		type=2;
		string=new char[1];
		
		string[0]=c;
		string[1]='\0';
		
		allocated=1;
	}
	var(float f){
		initValues();
		
		allocated=0;
		type=3;
		floating=f;
	}
	var(double d){
		initValues();
		
		allocated=0;
		type=4;
		longfloat=d;
	}
	var(int num){
		initValues();
		
		allocated=0;
		type=5;
		number=num;
	}
	var(long l){
		initValues();
		
		allocated=0;
		type=6;
		longint=l;
	}
	var(){
		initValues();
		allocated=0;
	}
	
	void destroy(){
		if(allocated==1){
			delete string;
			allocated=0;
		}
	}
	void input(const char* input){
		int gType=getType(input);
		
		switch(gType){
			case 2: type=2;
			
					if(allocated==1){
						delete string;
						allocated=0;
					}
			
					string=new char[1];
					string[0]=input[0];
					string[1]='\0';
			
					allocated=1;
					break;
					
			case 3: type=3;
					floating=toFloat(input);
					break;
					
			case 4: type=4;
					longfloat=toDouble(input);
					break;
			
			case 5: type=5;
					number=toInt(input);
					break;
			
			case 6: type=6;
					longint=toLong(input);
					break;
		}
	}
	void toString(){
		try{
			switch(type){
				case 1:  throw "var is already of type string!"; break;
				case 2:  throw "var is already of type char!"; break;
				case 3:
					type=1;
					if(allocated==1){
						delete string;
						allocated=0;
					}
					string=::toString(string, floating);
					break;
					
				case 4:
					type=1;
					if(allocated==1){
						delete string;
						allocated=0;
					}
					string=::toString(string, longfloat);
					break;
					
				case 5:
					type=1;
					if(allocated==1){
						delete string;
						allocated=0;
					}
					string=::toString(string, number);
					break;
					
				case 6:
					type=1;
					if(allocated==1){
						delete string;
						allocated=0;
					}
					string=::toString(string, longint);
					break;
				
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void initValues(){
		number=0;
		floating=0;
		longint=0;
		longfloat=0;
	}
	
	void operator=(var var1){
		if(var1.type==1){
			type=var1.type;
			int length=stringlen(var1.string), i;
			
			destroy();
			string=new char[length];

			for(i=0; i<length; i++){
				string[i]=var1.string[i];
			}
		}
		else if(var1.type==2){
			type=2;
			if(allocated==1){
				delete string;
				allocated=0;
			}
			string=new char[1];
			string[0]=var1.string[0];
			string[1]='\0';
		}
		else if(var1.type==3){
			type=3;
			floating=var1.floating;
		}
		else if(var1.type==4){
			type=4;
			longfloat=var1.longfloat;
		}
		else if(var1.type==5){
			type=5;
			number=var1.number;
		}
		else if(var1.type==6){
			type=6;
			longint=var1.longint;
		}
	}
	void operator=(float f){
		type=3;
		floating=f;
	}
	void operator=(const char* input){
		if(allocated==1){
			delete string;
			allocated=0;
		}
		int length=stringlen(input);
		string=new char[length];
		
		if(length==1) type=2;
		else type=1;
		
		int i;
		for(i=0; i<length; i++){
			string[i]=input[i];
		}
		
		i++;
		string[i]='\0';
		
		allocated=1;
	}
	void operator=(char c){
		if(allocated==1){
			delete string;
			allocated=0;
		}
		
		string=new char[1];
		string[0]=c;
		allocated=1;
		
		type=2;
	}
	void operator=(int num){
		type=5;
		number=num;
	}
	void operator=(double d){
		type=4;
		longfloat=d;
	}
	void operator=(long l){
		type=6;
		longint=l;
	}
	
	var operator+(var var2){
		var var3;
		try{
			if(type==var2.type){
				switch(type){
					case 1:
						if(var3.allocated==1){
							delete var3.string;
							var3.allocated=0;
						}
						var3.string=stringcat(string, var2.string);
						var3.type=1;
						break;
					case 2: throw "[cannot add variable of type 'char' with char. Only one character can be stored at a time]";
							break;
					case 3: var3.type=3;
							var3.floating=floating+var2.floating; break;
					case 4: var3.type=4;
							var3.longfloat=longfloat+var2.longfloat; break;
					case 5: var3.type=5;
							var3.number=number+var2.number; break;
					case 6: var3.type=6;
							var3.longint=longint+var2.longint; break;	
				}
			}
			else{
				if((type==3)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=floating+var2.longfloat;
				}
				else if((type==3)&&(var2.type==5)){
					var3.type=3;
					var3.floating=floating+var2.number;
				}
				else if((type==3)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=floating+var2.longint;
				}
				
				else if((type==4)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longfloat+var2.floating;
				}
				else if((type==4)&&(var2.type==5)){
					var3.type=4;
					var3.longfloat=longfloat+var2.number;
				}
				else if((type==4)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=longfloat+var2.longint;
				}
				
				else if((type==5)&&(var2.type==3)){
					var3.type=3;
					var3.floating=number+var2.floating;
				}
				else if((type==5)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=number+var2.longfloat;
				}
				else if((type==5)&&(var2.type==6)){
					var3.type=6;
					var3.longint=number+var2.longint;
				}
				
				else if((type==6)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longint+var2.floating;
				}
				else if((type==6)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=longint+var2.longfloat;
				}
				else if((type==6)&&(var2.type==5)){
					var3.type=6;
					var3.longint=longint+var2.number;
				}
				
				else throw "[Incompatibles Types] These types cannot be added";
			}
		}catch(const char* exception){
			cout<<"Cannot add --> "<<exception<<endl;
		}
		return var3;
	}
	var operator+(int num){
		var var1;
		try{
			switch(type){
				case 1: throw "[Incompatible Types] Cannot add String and Int values!"; break;
				case 2: throw "[Incompatible Types] Cannot add String and Int values!"; break;
				case 3: var1.type=3;
						var1.floating=floating+num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat+num; break;
				case 5: var1.type=5;
						var1.number=number+num; break; 
				case 6: var1.type=6;
						var1.longint=longint+num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator+(float num){
		var var1;
		try{
			switch(type){
				case 1: throw "Cannot add String and Float values! [Incompatible Types]"; break;
				case 2: throw "Cannot add Char and Float values! [Incompatible Types]"; break;
				case 3: var1.type=3; 
						var1.floating=floating+num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat+num; break;
				case 5: var1.type=3;
						var1.floating=number+num; break;
				case 6: var1.type=4;
						var1.longfloat=longint+num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator+(double num){
		var var1;
		try{
			switch(type){
				case 1: throw "Cannot add String and Double values! [Incompatible Types]"; break; 
				case 2: throw "Cannot add Char and Double values! [Incompatible Types]"; break; 
				case 3: var1.type=4;
						var1.longfloat=floating+num; break; 
				case 4: var1.type=4;
						var1.longfloat=longfloat+num; break; 
				case 5: var1.type=4;
						var1.longfloat=number+num; break; 
				case 6: var1.type=4;
						var1.longfloat=longint+num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator+(long num){
		var var1;
		try{
			switch(type){
				case 1: throw "Cannot add String and Long values! [Incompatible Types]"; break;
				case 2: throw "Cannot add Char and Long values! [Incompatible Types]"; break;
				case 3: var1.type=4;
						var1.longfloat=floating+num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat+num; break;
				case 5: var1.type=6;
						var1.longint=number+num; break; 
				case 6: var1.type=6;
						var1.longint=longint+num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	
	void operator+=(var var2){
		char* stringcopy;
		if(type==var2.type){
			switch(type){
				case 1:
					if(allocated==1){
						stringcopy=new char[stringlen(string)];
						stringcopy=stringcpy(stringcopy, string);
						delete string;
					
						string=stringcat(stringcopy, var2.string);
						delete stringcopy;
					
						allocated=1;
					}
					else{
						string=stringcpy(string, var2.string);
						allocated=1;
					}
					break;
				case 2: throw "[Cannot add var of type 'char' to char. Can only store one char at a time.]"; break;
				case 3: floating+=var2.floating; break; 
				case 4: longfloat+=var2.longfloat; break; 
				case 5: number+=var2.number; break; 
				case 6: longint+=var2.longint; break;
			}
		}
		else{
			try{
				switch(type){
				case 1:
					if(var2.type==2){
			
						if(allocated==1){
							stringcopy=new char[stringlen(string)];
							stringcopy=stringcpy(stringcopy, string);
							delete string;
				
							string=stringcat(stringcopy, var2.string);
							delete stringcopy;
				
							allocated=1;
						}
						else{
							string=stringcpy(string, var2.string);
							allocated=1;
						}
						break;
					}
					else{
						throw "[Incompatible Types] You cannot add these two types together!";
					}
					break;
				
				case 2: throw "[Cannot add var of type 'char' to char. Can only store one char at a time.]"; break;
					
				case 3:
					if(var2.type==4){
						type=4;
						longfloat=floating+var2.longfloat;
						break;
					}
					else if(var2.type==5){
						type=3;
						floating=floating+var2.number;
						break;
					}
					else if(var2.type==6){
						type=4;
						longfloat=floating+var2.longint;
						break;
					}
				
				case 4:
					if(var2.type==3){
						type=4;
						longfloat=longfloat+var2.floating;
						break;
					}
					else if(var2.type==5){
						type=4;
						longfloat=longfloat+var2.number;
						break;
					}
					else if(var2.type==6){
						type=4;
						longfloat=longfloat+var2.longint;
						break;
					}
				
				case 5:
					if(var2.type==3){
						type=3;
						floating=number+var2.floating;
						break;
					}
					else if(var2.type==4){
						type=4;
						longfloat=number+var2.longfloat;
						break;
					}
					else if(var2.type==6){
						type=6;
						longint=number+var2.longint;
						break;
					}
					
				case 6:
					if(var2.type==3){
						type=4;
						longfloat=longint+var2.floating;
						break;
					}
					else if(var2.type==4){
						type=4;
						longfloat=longint+var2.longfloat;
						break;
					}
					else if(var2.type==5){
						type=5;
						longint=longint+var2.number;
						break;
					}
				default:
					throw "[Incompatible types] You cannot add these two types together!";
				}
			}
			catch(const char* exception){
				cout<<exception<<endl;
			}
		}
	}
	void operator+=(int num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be added"; break;
			case 2: string[0]+=num; break;
			case 3: floating+=num; break;
			case 4: longfloat+=num; break;
			case 5: number+=num; break;
			case 6: longint+=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator+=(long num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be added"; break; 
			case 2: string[0]+=num; break; 
			case 3: type=4;
					longfloat=floating;
					longfloat+=num; break; 
			case 4: longfloat+=num; break; 
			case 5: type=6;
					longint=number;
					longint+=num; break; 
			case 6: longint+=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator+=(float num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be added"; break;
			case 2: num1=num; 
					string[0]+=num1; break;
			case 3: floating+=num; break;
			case 4: longfloat+=num; break;
			case 5: type=3;
					floating=number;
					floating+=num;
					cout<<"floating is "<<floating<<endl; break;
			case 6: type=4;
					longfloat=longint;
					longfloat+=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator+=(double num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be added"; break;
			case 2: num1=num;
					string[0]+=num1; break;
			case 3: type=4;
					longfloat=floating;
					longfloat+=num; break; 
			case 4: longfloat+=num; break; 
			case 5: type=4;
					longfloat=number;
					longfloat+=num; break;
					cout<<"longfloat is "<<longfloat<<endl; break;
			case 6: type=4;
					longfloat=longint;
					longint+=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator+=(const char* input){
		char* stringcopy;
		try{
			if(type==1){
				if(allocated==1){
					stringcopy=new char[stringlen(input)];
					stringcpy(stringcopy, string);
					
					delete string;
					allocated=0;
					
					string=stringcat(stringcopy, input);
					delete stringcopy;
					allocated=1;
				}
				else{
					string=new char[stringlen(input)];
					stringcpy(string, input);
					allocated=1;
				}
			}
			else throw "[Incompatibles Types] These types cannot be added";
			
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	
	var operator-(var var2){
		var var3;
		try{
			if(type==var2.type){
				switch(type){
					case 1: throw "[Invalid operation] Subtraction cannot be performed on a variable of type 'string'"; break;
					case 2: var3.type=2;
						var3.string=new char[1];
						
						var3.string[0]=string[0]-var2.string[0];
						allocated=1;
						break;
					case 3: var3.type=3;
							var3.floating=floating-var2.floating; break;
					case 4: var3.type=4;
							var3.longfloat=longfloat-var2.longfloat; break;
					case 5: var3.type=5;
							var3.number=number-var2.number; break;
					case 6: var3.type=6;
							var3.longint=longint-var2.longint; break;	
				}
			}
			else{
				if((type==3)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=floating-var2.longfloat;
				}
				else if((type==3)&&(var2.type==5)){
					var3.type=3;
					var3.floating=floating-var2.number;
				}
				else if((type==3)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=floating-var2.longint;
				}
				
				else if((type==4)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longfloat-var2.floating;
				}
				else if((type==4)&&(var2.type==5)){
					var3.type=4;
					var3.longfloat=longfloat-var2.number;
				}
				else if((type==4)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=longfloat-var2.longint;
				}
				
				else if((type==5)&&(var2.type==3)){
					var3.type=3;
					var3.floating=number-var2.floating;
				}
				else if((type==5)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=number-var2.longfloat;
				}
				else if((type==5)&&(var2.type==6)){
					var3.type=6;
					var3.longint=number-var2.longint;
				}
				
				else if((type==6)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longint-var2.floating;
				}
				else if((type==6)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=longint-var2.longfloat;
				}
				else if((type==6)&&(var2.type==5)){
					var3.type=6;
					var3.longint=longint-var2.number;
				}
				
				else throw "[Incompatibles Types] These types cannot be added";
			}
		}catch(const char* exception){
			cout<<"Cannot add --> "<<exception<<endl;
		}
		return var3;
	}
	var operator-(int num){
		var var1;
		try{
			switch(type){
				case 1: throw "[Incompatible Types] Cannot subtrat 'string' and 'int' values!"; break;
				case 2:
					var1.type=2;
					var1.string=new char[1];
				
					var1.string[0]=string[0]-num;
					allocated=1;
					break;
				case 3: var1.type=3; 
					var1.floating=floating-num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat-num; break;
				case 5: var1.type=5;
						var1.number=number-num; break;
				case 6: var1.type=6;
						var1.longint=longint-num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator-(float num){
		var var1;
		long num1;
		try{
			switch(type){
				case 1: throw "Cannot add String and Float values! [Incompatible Types]"; break;
				case 2: var1.type=2;
					var1.string=new char[1];
					
					num1=num;
					var1.string[0]=string[0]-num1;
					allocated=1;
					break;
				case 3: var1.type=3;
						var1.floating=floating-num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat-num; break;
				case 5: var1.type=3;
						var1.floating=number-num; break;
				case 6: var1.type=4;
						var1.longfloat=longint-num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator-(double num){
		var var1;
		long num1;
		try{
			switch(type){
				case 1: throw "Cannot subtract String and Double values! [Incompatible Types]"; break;
				case 2:
					var1.type=2;
					var1.string=new char[1];
				
					num1=num;
					var1.string[0]=string[0]-num1;
					allocated=1;
					break; 
				case 3: var1.type=4;
						var1.longfloat=floating-num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat-num; break;
				case 5: var1.type=4;
						var1.longfloat=number-num; break;
				case 6: var1.type=4;
						var1.longfloat=longint-num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator-(long num){
		var var1;
		try{
			switch(type){
				case 1: throw "Cannot add String and Long values! [Incompatible Types]"; break;
				case 2:
					var1.type=2;
					var1.string=new char[1];
				
					var1.string[0]=string[0]-num;
					allocated=1;
					break; 
				case 3: var1.type=4;
						var1.longfloat=floating-num; break;
				case 4: var1.type=4; 
					var1.longfloat=longfloat-num; break;
				case 5: var1.type=6;
						var1.longint=number-num; break;
				case 6: var1.type=6;
						var1.longint=longint-num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	
	void operator-=(var var2){
		char* stringcopy;
		if(type==var2.type){
			switch(type){
				case 1: throw "[Invalid operation] Subtraction cannot be performed on a variable of type 'string'"; break;
				case 2: string[0]=string[0]-var2.string[0]; break;
				case 3: floating-=var2.floating; break; 
				case 4: longfloat-=var2.longfloat; break;
				case 5: number-=var2.number; break;
				case 6: longint-=var2.longint; break;
			}
		}
		else{
			try{
				long num1;
				switch(type){
					case 1: throw "[Invalid operation] Subtraction cannot be performed on a variable of type 'string'";	break;
				
					case 2:
						if(var2.type==3){
							type=2;
							num1=var2.floating;
							string[0]=string[0]-num1;
							break;
						}
						else if(var2.type==4){
							type=2;
							num1=var2.longfloat;
							string[0]=string[0]-num1;
							break;
						}
						else if(var2.type==5){
							type=2;
							string[0]=string[0]-var2.number;
							break;
						}
						else if(var2.type==6){
							type=2;
							string[0]=string[0]-var2.longint;
							break;
						}
						break;
					
					case 3:
						if(var2.type==4){
							type=4;
							longfloat=floating-var2.longfloat;
							break;
						}
						else if(var2.type==5){
							type=3;
							floating=floating-var2.number;
							break;
						}
						else if(var2.type==6){
							type=4;
							longfloat=floating-var2.longint;
							break;
						}
				
					case 4:
						if(var2.type==3){
							type=4;
							longfloat=longfloat-var2.floating;
							break;
						}
						else if(var2.type==5){
							type=4;
							longfloat=longfloat-var2.number;
							break;
						}
						else if(var2.type==6){
							type=4;
							longfloat=longfloat-var2.longint;
							break;
						}
				
					case 5:
						if(var2.type==3){
							type=3;
							floating=number-var2.floating;
							break;
						}
						else if(var2.type==4){
							type=4;
							longfloat=number-var2.longfloat;
							break;
						}
						else if(var2.type==6){
							type=6;
							longint=number-var2.longint;
							break;
						}
					
					case 6:
						if(var2.type==3){
							type=4;
							longfloat=longint-var2.floating;
							break;
						}
						else if(var2.type==4){
							type=4;
							longfloat=longint-var2.longfloat;
							break;
						}
						else if(var2.type==5){
							type=5;
							longint=longint-var2.number;
							break;
						}
					default:
						throw "[Incompatible types] You cannot add these two types together!";
				}
			}
			catch(const char* exception){
				cout<<exception<<endl;
			}
		}
	}
	void operator-=(int num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be subtracted"; break;
			case 2: string[0]-=num; break; 
			case 3: floating-=num; break; 
			case 4: longfloat-=num; break; 
			case 5: number-=num; break; 
			case 6: longint-=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator-=(long num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be subtracted"; break;
			case 2: string[0]-=num; break;
			case 3: type=4;
					longfloat=floating-num; break;
			case 4: longfloat-=num; break;
			case 5: type=6;
					longint=number-num; break;
			case 6: longint-=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator-=(float num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be subtracted"; break;
			case 2: num1=num;
					string[0]-=num1; break;
			case 3: floating-=num; break;
			case 4: longfloat-=num; break;
			case 5: type=4;
					longfloat=number-num; break;
			case 6: type=4;
					longfloat=longint-num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator-=(double num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be subtracted"; break;
			case 2: num1=num;
					string[0]-=num1; break;
			case 3: type=4;
					longfloat=floating-num; break;
			case 4: longfloat-=num; break;
			case 5: type=4;
					longfloat=number-num; break;
			case 6: type=4;
					longfloat=longint-num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	
	var operator*(var var2){
		var var3;
		try{
			if(type==var2.type){
				switch(type){
					case 1: throw "[Invalid operation] Multiplication cannot be performed on a variable of type 'string'";break;
					case 2:
						var3.type=2;
						var3.string=new char[1];
						
						var3.string[0]=string[0]*var2.string[0];
						allocated=1;
						break;
					case 3: var3.type=3;
							var3.floating=floating*var2.floating; break;
					case 4: var3.type=4;
							var3.longfloat=longfloat*var2.longfloat; break;
					case 5: var3.type=5;
							var3.number=number*var2.number; break;
					case 6: var3.type=6;
							var3.longint=longint*var2.longint; break;	
				}
			}
			else{
				if((type==3)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=floating*var2.longfloat;
				}
				else if((type==3)&&(var2.type==5)){
					var3.type=3;
					var3.floating=floating*var2.number;
				}
				else if((type==3)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=floating*var2.longint;
				}
				
				else if((type==4)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longfloat*var2.floating;
				}
				else if((type==4)&&(var2.type==5)){
					var3.type=4;
					var3.longfloat=longfloat*var2.number;
				}
				else if((type==4)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=longfloat*var2.longint;
				}
				
				else if((type==5)&&(var2.type==3)){
					var3.type=3;
					var3.floating=number*var2.floating;
				}
				else if((type==5)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=number*var2.longfloat;
				}
				else if((type==5)&&(var2.type==6)){
					var3.type=6;
					var3.longint=number*var2.longint;
				}
				
				else if((type==6)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longint*var2.floating;
				}
				else if((type==6)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=longint*var2.longfloat;
				}
				else if((type==6)&&(var2.type==5)){
					var3.type=6;
					var3.longint=longint*var2.number;
				}
				
				else throw "[Incompatibles Types] These types cannot be added";
			}
		}catch(const char* exception){
			cout<<"Cannot add --> "<<exception<<endl;
		}
		return var3;
	}
	var operator*(int num){
		var var1;
		try{
			switch(type){
				case 1: throw "[Incompatible Types] Cannot multiply 'string' and 'int' values!"; break;
				case 2:
					var1.type=2;
					var1.string=new char[1];
				
					var1.string[0]=string[0]*num;
					allocated=1;
					break;
				case 3: var1.type=3;
						var1.floating=floating*num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat*num; break;
				case 5: var1.type=5;
						var1.number=number*num; break;
				case 6: var1.type=6;
						var1.longint=longint*num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator*(float num){
		var var1;
		long num1;
		try{
			switch(type){
				case 1: throw "Cannot multiply String and Float values! [Incompatible Types]"; break;
				case 2:
					var1.type=2;
					var1.string=new char[1];
					
					num1=num;
					var1.string[0]=string[0]*num1;
					allocated=1;
					break;
				case 3: var1.type=3;
						var1.floating=floating*num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat*num; break;
				case 5: var1.type=3;
						var1.floating=number*num; break;
				case 6: var1.type=4;
						var1.longfloat=longint*num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator*(double num){
		var var1;
		long num1;
		try{
			switch(type){
				case 1: throw "Cannot subtract String and Double values! [Incompatible Types]"; break;
				case 2: 
					var1.type=2;
					var1.string=new char[1];
				
					num1=num;
					var1.string[0]=string[0]*num1;
					allocated=1;
					break;
				case 3: var1.type=4;
						var1.longfloat=floating*num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat*num; break;
				case 5: var1.type=4;
						var1.longfloat=number*num; break;
				case 6: var1.type=4;
						var1.longfloat=longint*num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator*(long num){
		var var1;
		try{
			switch(type){
				case 1: throw "Cannot multiply String and Long values! [Incompatible Types]"; break;
				case 2: var1.type=2;
					var1.string=new char[1];
				
					var1.string[0]=string[0]*num;
					allocated=1;
					break;
				case 3: var1.type=4;
						var1.longfloat=floating*num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat*num; break;
				case 5: var1.type=6;
						var1.longint=number*num; break;
				case 6: var1.type=6;
						var1.longint=longint*num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	
	void operator*=(var var2){
		char* stringcopy;
		if(type==var2.type){
			switch(type){
				case 1: throw "[Invalid operation] Subtraction cannot be performed on a variable of type 'string'"; break;
				case 2: string[0]=string[0]*var2.string[0]; break;
				case 3: floating*=var2.floating; break;
				case 4: longfloat*=var2.longfloat; break;
				case 5: number*=var2.number; break;
				case 6: longint*=var2.longint; break;
			}
		}
		else{
			try{
				long num1;
				switch(type){
					case 1:
						throw "[Invalid operation] Multiplication cannot be performed on a variable of type 'string'";
						break;
				
					case 2:
						if(var2.type==3){
							type=2;
							num1=var2.floating;
							string[0]=string[0]*num1;
							break;
						}
						else if(var2.type==4){
							type=2;
							num1=var2.longfloat;
							string[0]=string[0]*num1;
							break;
						}
						else if(var2.type==5){
							type=2;
							string[0]=string[0]*var2.number;
							break;
						}
						else if(var2.type==6){
							type=2;
							string[0]=string[0]*var2.longint;
							break;
						}
						break;
					
					case 3:
						if(var2.type==4){
							type=4;
							longfloat=floating*var2.longfloat;
							break;
						}
						else if(var2.type==5){
							type=3;
							floating=floating*var2.number;
							break;
						}
						else if(var2.type==6){
							type=4;
							longfloat=floating*var2.longint;
							break;
						}
				
					case 4:
						if(var2.type==3){
							type=4;
							longfloat=longfloat*var2.floating;
							break;
						}
						else if(var2.type==5){
							type=4;
							longfloat=longfloat*var2.number;
							break;
						}
						else if(var2.type==6){
							type=4;
							longfloat=longfloat*var2.longint;
							break;
						}
				
					case 5:
						if(var2.type==3){
							type=3;
							floating=number*var2.floating;
							break;
						}
						else if(var2.type==4){
							type=4;
							longfloat=number*var2.longfloat;
							break;
						}
						else if(var2.type==6){
							type=6;
							longint=number*var2.longint;
							break;
						}
					
					case 6:
						if(var2.type==3){
							type=4;
							longfloat=longint*var2.floating;
							break;
						}
						else if(var2.type==4){
							type=4;
							longfloat=longint*var2.longfloat;
							break;
						}
						else if(var2.type==5){
							type=5;
							longint=longint*var2.number;
							break;
						}
					default:
						throw "[Incompatible types] You cannot add these two types together!";
				}
			}
			catch(const char* exception){
				cout<<exception<<endl;
			}
		}
	}
	void operator*=(int num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be multiplied"; break;
			case 2: string[0]*=num; break;
			case 3: floating*=num; break;
			case 4: longfloat*=num; break;
			case 5: number*=num; break;
			case 6: longint*=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator*=(long num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be multiplied"; break;
			case 2: string[0]*=num; break;
			case 3: type=4;
					longfloat=floating*num; break;
			case 4: longfloat*=num; break;
			case 5: type=6;
					longint=number*num; break;
			case 6: longint*=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator*=(float num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be subtracted"; break;
			case 2: num1=num;
					string[0]*=num1; break;
			case 3: floating*=num; break;
			case 4: longfloat*=num; break;
			case 5: type=4;
					longfloat=number*num; break;
			case 6: type=4;
					longfloat=longint*num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator*=(double num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be multiplied"; break;
			case 2: num1=num;
					string[0]*=num1; break;
			case 3: type=4;
					longfloat=floating*num; break;
			case 4: longfloat*=num; break;
			case 5: type=4;
					longfloat=number*num; break;
			case 6: type=4;
					longfloat=longint*num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	
	var operator/(var var2){
		var var3;
		try{
			if(type==var2.type){
				switch(type){
					case 1: throw "[Invalid operation] Division cannot be performed on a variable of type 'string'"; break;
					case 2: throw "[Invalid operation] Division cannot be performed on a variable of type 'char'"; break;
					case 3: var3.type=3;
							var3.floating=floating/var2.floating; break;
					case 4: var3.type=4;
							var3.longfloat=longfloat/var2.longfloat; break;
					case 5: var3.type=5;
							var3.number=number/var2.number; break;
					case 6: var3.type=6;
							var3.longint=longint/var2.longint; break;	
				}
			}
			else{
				if((type==3)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=floating/var2.longfloat;
				}
				else if((type==3)&&(var2.type==5)){
					var3.type=3;
					var3.floating=floating/var2.number;
				}
				else if((type==3)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=floating/var2.longint;
				}
				
				else if((type==4)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longfloat/var2.floating;
				}
				else if((type==4)&&(var2.type==5)){
					var3.type=4;
					var3.longfloat=longfloat/var2.number;
				}
				else if((type==4)&&(var2.type==6)){
					var3.type=4;
					var3.longfloat=longfloat/var2.longint;
				}
				
				else if((type==5)&&(var2.type==3)){
					var3.type=3;
					var3.floating=number/var2.floating;
				}
				else if((type==5)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=number/var2.longfloat;
				}
				else if((type==5)&&(var2.type==6)){
					var3.type=6;
					var3.longint=number/var2.longint;
				}
				
				else if((type==6)&&(var2.type==3)){
					var3.type=4;
					var3.longfloat=longint/var2.floating;
				}
				else if((type==6)&&(var2.type==4)){
					var3.type=4;
					var3.longfloat=longint/var2.longfloat;
				}
				else if((type==6)&&(var2.type==5)){
					var3.type=6;
					var3.longint=longint/var2.number;
				}
				
				else throw "[Incompatibles Types] These types cannot be divided";
			}
		}catch(const char* exception){
			cout<<"Cannot add --> "<<exception<<endl;
		}
		return var3;
	}
	var operator/(int num){
		var var1;
		try{
			switch(type){
				case 1: throw "[Incompatible Types] Cannot divide 'string' and 'int' values!"; break;
				case 2: throw "[Invalid operation] Division cannot be performed on a variable of type 'char'"; break;
				case 3: var1.type=3;
						var1.floating=floating/num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat/num; break;
				case 5: var1.type=5;
						var1.number=number/num; break;
				case 6: var1.type=6;
						var1.longint=longint/num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator/(float num){
		var var1;
		long num1;
		try{
			switch(type){
				case 1: throw "Cannot divide String and Float values! [Incompatible Types]"; break;
				case 2: throw "Cannot divide Char and Float values! [Incompatible Types]"; break;
				case 3: var1.type=3;
						var1.floating=floating/num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat/num; break;
				case 5: var1.type=3;
						var1.floating=number/num; break;
				case 6: var1.type=4;
						var1.longfloat=longint/num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator/(double num){
		var var1;
		long num1;
		try{
			switch(type){
				case 1: throw "Cannot divide String and Double values! [Incompatible Types]"; break;
				case 2: throw "Cannot divide Char and Double values! [Incompatible Types]"; break;
				case 3: var1.type=4;
						var1.longfloat=floating/num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat/num; break;
				case 5: var1.type=4;
						var1.longfloat=number/num; break;
				case 6: var1.type=4;
						var1.longfloat=longint/num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	var operator/(long num){
		var var1;
		try{
			switch(type){
				case 1: throw "Cannot divide String and Long values! [Incompatible Types]"; break;
				case 2: throw "Cannot divide Char and Float values! [Incompatible Types]"; break;
				case 3: var1.type=4;
						var1.longfloat=floating/num; break;
				case 4: var1.type=4;
						var1.longfloat=longfloat/num; break;
				case 5: var1.type=6;
						var1.longint=number/num; break;
				case 6: var1.type=6;
						var1.longint=longint/num; break;
			}
			return var1;
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return NULL;
	}
	
	void operator/=(var var2){
		char* stringcopy;
		if(type==var2.type){
			switch(type){
				case 1: throw "[Invalid operation] Division cannot be performed on a variable of type 'string'"; break;
				case 2: throw "Cannot divide a 'char' value [Incompatible Types]"; break;
				case 3: floating/=var2.floating; break;
				case 4: longfloat/=var2.longfloat; break;
				case 5: number/=var2.number; break;
				case 6: longint/=var2.longint; break;
			}
		}
		else{
			try{
				long num1;
				switch(type){
					case 1: throw "[Invalid operation] Division cannot be performed on a variable of type 'string'"; break;
					case 2: throw "Cannot divide a 'char' value [Incompatible Types]"; break;
					case 3:
						if(var2.type==4){
							type=4;
							longfloat=floating/var2.longfloat;
							break;
						}
						else if(var2.type==5){
							type=3;
							floating=floating/var2.number;
							break;
						}
						else if(var2.type==6){
							type=4;
							longfloat=floating/var2.longint;
							break;
						}
				
					case 4:
						if(var2.type==3){
							type=4;
							longfloat=longfloat/var2.floating;
							break;
						}
						else if(var2.type==5){
							type=4;
							longfloat=longfloat/var2.number;
							break;
						}
						else if(var2.type==6){
							type=4;
							longfloat=longfloat/var2.longint;
							break;
						}
				
					case 5:
						if(var2.type==3){
							type=3;
							floating=number/var2.floating;
							break;
						}
						else if(var2.type==4){
							type=4;
							longfloat=number/var2.longfloat;
							break;
						}
						else if(var2.type==6){
							type=6;
							longint=number/var2.longint;
							break;
						}
					
					case 6:
						if(var2.type==3){
							type=4;
							longfloat=longint/var2.floating;
							break;
						}
						else if(var2.type==4){
							type=4;
							longfloat=longint/var2.longfloat;
							break;
						}
						else if(var2.type==5){
							type=5;
							longint=longint/var2.number;
							break;
						}
					default: throw "[Incompatible types] You cannot divide these two types together!";
				}
			}
			catch(const char* exception){
				cout<<exception<<endl;
			}
		}
	}
	void operator/=(int num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be divided"; break;
			case 2: throw "Cannot divide a 'char' value [Incompatible Types]"; break;
			case 3: floating/=num; break;
			case 4: longfloat/=num; break;
			case 5: number/=num; break;
			case 6: longint/=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator/=(long num){
		try{
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be multiplied"; break;
			case 2: throw "Cannot divide a 'char' value [Incompatible Types]"; break;
			case 3: type=4;
					longfloat=floating/num; break;
			case 4: longfloat/=num;	break;
			case 5: type=6;
					longint=number/num; break;
			case 6: longint/=num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator/=(float num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be subtracted"; break;
			case 2: num1=num;
					string[0]/=num1; break;
			case 3: floating/=num; break;
			case 4: longfloat/=num; break;
			case 5: type=4;
					longfloat=number/num; break;
			case 6: type=4;
					longfloat=longint/num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator/=(double num){
		try{
			long num1;
			switch(type){
			case 1: throw "[Incompatibles Types] These types cannot be divided"; break;
			case 2: throw "Cannot divide a 'char' value [Incompatible Types]"; break;
			case 3: type=4;
					longfloat=floating/num; break;
			case 4: longfloat/=num; break;
			case 5: type=4;
					longfloat=number/num; break;
			case 6: type=4;
					longfloat=longint/num; break;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	
	int operator>(var var2){
		if(type==var2.type){
			int res;
			switch(type){
				case 1:
					res=stringcmp(string, var2.string);
					
					if(res==1) return 1;
					else return 0;
				case 2: return greaterThan<char>(string[0], var2.string[0]);
				case 3: return greaterThan<long>(floating, var2.floating);
				case 4: return greaterThan<long>(longfloat, var2.longfloat);
				case 5: return greaterThan<long>(number, var2.number);
				case 6: return greaterThan<long>(longint, var2.longint);
			}
		}
		else{
			try{
				switch(type){
					case 1:
						throw "[Invalid operation] '>' is an operation that cannot be performed on these types";
						break;
					case 2:
						if(var2.type==3) return greaterThan<char, float>(string[0], var2.floating);
						else if(var2.type==4) return greaterThan<char, double>(string[0], var2.longfloat);
						else if(var2.type==5) return greaterThan<char, int>(string[0], var2.number);
						else if(var2.type==6) return greaterThan<char, long>(string[0], var2.longint);
						else throw "[Invalid operation] '>' is an operation that cannot be performed on these types";
					case 3:
						if(var2.type==2) return greaterThan<float, char>(floating, var2.string[0]);
						else if(var2.type==4) return greaterThan<float, double>(floating, var2.longfloat);
						else if(var2.type==5) return greaterThan<float, int>(floating, var2.number);
						else if(var2.type==6) return greaterThan<float, long>(floating, var2.longint);
						else throw "[Invalid operation] '>' is an operation that cannot be performed on these types";
					case 4:
						if(var2.type==2) return greaterThan<double, char>(longfloat, var2.string[0]);
						else if(var2.type==3) return greaterThan<double, float>(longfloat, var2.floating);
						else if(var2.type==5) return greaterThan<double, int>(longfloat, var2.number);
						else if(var2.type==6) return greaterThan<double, long>(longfloat, var2.longint);
						else throw "[Invalid operation] '>' is an operation that cannot be performed on these types";
					case 5:
						if(var2.type==2) return greaterThan<int, char>(number, var2.string[0]);
						else if(var2.type==3) return greaterThan<int, float>(number, var2.floating);
						else if(var2.type==4) return greaterThan<int, double>(number, var2.longfloat);
						else if(var2.type==6) return greaterThan<int, long>(number, var2.longint);
						else throw "[Invalid operation] '>' is an operation that cannot be performed on these types";
					case 6:
						if(var2.type==2) return greaterThan<long, char>(longint, var2.string[0]);
						else if(var2.type==3) return greaterThan<long, float>(longint, var2.floating);
						else if(var2.type==4) return greaterThan<long, double>(longint, var2.longfloat);
						else if(var2.type==5) return greaterThan<long, int>(longint, var2.number);
						else throw "[Invalid operation] '>' is an operation that cannot be performed on these types";
				}
			}catch(const char* exception){
				cout<<exception<<endl;
			}	
		}
		return 0;
	}
	int operator>(int num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThan<char, int>(string[0], num);
				case 3: return greaterThan<float, int>(floating, num);
				case 4: return greaterThan<double, int>(longfloat, num);
				case 5: return greaterThan<int>(number, num);
				case 6: return greaterThan<long, int>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>(long num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThan<char, long>(string[0], num);
				case 3: return greaterThan<float, long>(floating, num);
				case 4: return greaterThan<double, long>(longfloat, num);
				case 5: return greaterThan<int, long>(number, num);
				case 6: return greaterThan<long>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>(float num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThan<char, float>(string[0], num);
				case 3: return greaterThan<float>(floating, num);
				case 4: return greaterThan<double, float>(longfloat, num);
				case 5: return greaterThan<int, float>(number, num);
				case 6: return greaterThan<long, float>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>(double num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThan<char, double>(string[0], num);
				case 3: return greaterThan<float, double>(floating, num);
				case 4: return greaterThan<double>(longfloat, num);
				case 5: return greaterThan<int, double>(number, num);
				case 6: return greaterThan<long, double>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>(char num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'char'"; break;
				case 2: return greaterThan<char>(string[0], num);
				case 3: return greaterThan<float, char>(floating, num);
				case 4: return greaterThan<double, char>(longfloat, num);
				case 5: return greaterThan<int, char>(number, num);
				case 6: return greaterThan<long, char>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	
	int operator>=(var var2){
		if(type==var2.type){
			int res;
			switch(type){
				case 1:
					res=stringcmp(string, var2.string);
					
					if(res==1||res==0) return 1;
					else return 0;
				case 2: return greaterThanEqual<char>(string[0], var2.string[0]);
				case 3: return greaterThanEqual<long>(floating, var2.floating);
				case 4: return greaterThanEqual<long>(longfloat, var2.longfloat);
				case 5: return greaterThanEqual<long>(number, var2.number);
				case 6: return greaterThanEqual<long>(longint, var2.longint);
			}
		}
		else{
			try{
				switch(type){
					case 1:
						throw "[Invalid operation] '>=' is an operation that cannot be performed on these types";
						break;
					case 2:
						if(var2.type==3) return greaterThanEqual<char, float>(string[0], var2.floating);
						else if(var2.type==4) return greaterThanEqual<char, double>(string[0], var2.longfloat);
						else if(var2.type==5) return greaterThanEqual<char, int>(string[0], var2.number);
						else if(var2.type==6) return greaterThanEqual<char, long>(string[0], var2.longint);
						else throw "[Invalid operation] '>=' is an operation that cannot be performed on these types";
					case 3:
						if(var2.type==2) return greaterThanEqual<float, char>(floating, var2.string[0]);
						else if(var2.type==4) return greaterThanEqual<float, double>(floating, var2.longfloat);
						else if(var2.type==5) return greaterThanEqual<float, int>(floating, var2.number);
						else if(var2.type==6) return greaterThanEqual<float, long>(floating, var2.longint);
						else throw "[Invalid operation] '>=' is an operation that cannot be performed on these types";
					case 4:
						if(var2.type==2) return greaterThanEqual<double, char>(longfloat, var2.string[0]);
						else if(var2.type==3) return greaterThanEqual<double, float>(longfloat, var2.floating);
						else if(var2.type==5) return greaterThanEqual<double, int>(longfloat, var2.number);
						else if(var2.type==6) return greaterThanEqual<double, long>(longfloat, var2.longint);
						else throw "[Invalid operation] '>=' is an operation that cannot be performed on these types";
					case 5:
						if(var2.type==2) return greaterThanEqual<int, char>(number, var2.string[0]);
						else if(var2.type==3) return greaterThanEqual<int, float>(number, var2.floating);
						else if(var2.type==4) return greaterThanEqual<int, double>(number, var2.longfloat);
						else if(var2.type==6) return greaterThanEqual<int, long>(number, var2.longint);
						else throw "[Invalid operation] '>=' is an operation that cannot be performed on these types";
					case 6:
						if(var2.type==2) return greaterThanEqual<long, char>(longint, var2.string[0]);
						else if(var2.type==3) return greaterThanEqual<long, float>(longint, var2.floating);
						else if(var2.type==4) return greaterThanEqual<long, double>(longint, var2.longfloat);
						else if(var2.type==5) return greaterThanEqual<long, int>(longint, var2.number);
						else throw "[Invalid operation] '>=' is an operation that cannot be performed on these types";
				}
			}catch(const char* exception){
				cout<<exception<<endl;
			}	
		}
		return 0;
	}
	int operator>=(int num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThanEqual<char, int>(string[0], num);
				case 3: return greaterThanEqual<float, int>(floating, num);
				case 4: return greaterThanEqual<double, int>(longfloat, num);
				case 5: return greaterThanEqual<int>(number, num);
				case 6: return greaterThanEqual<long, int>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>=(long num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThanEqual<char, long>(string[0], num);
				case 3: return greaterThanEqual<float, long>(floating, num);
				case 4: return greaterThanEqual<double, long>(longfloat, num);
				case 5: return greaterThanEqual<int, long>(number, num);
				case 6: return greaterThanEqual<long>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>=(float num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThanEqual<char, float>(string[0], num);
				case 3: return greaterThanEqual<float>(floating, num);
				case 4: return greaterThanEqual<double, float>(longfloat, num);
				case 5: return greaterThanEqual<int, float>(number, num);
				case 6: return greaterThanEqual<long, float>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>=(double num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return greaterThanEqual<char, double>(string[0], num);
				case 3: return greaterThanEqual<float, double>(floating, num);
				case 4: return greaterThanEqual<double>(longfloat, num);
				case 5: return greaterThanEqual<int, double>(number, num);
				case 6: return greaterThanEqual<long, double>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator>=(char num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'char'"; break;
				case 2: return greaterThanEqual<char>(string[0], num);
				case 3: return greaterThanEqual<float, char>(floating, num);
				case 4: return greaterThanEqual<double, char>(longfloat, num);
				case 5: return greaterThanEqual<int, char>(number, num);
				case 6: return greaterThanEqual<long, char>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	
	int operator<(var var2){
		if(type==var2.type){
			int res;
			switch(type){
				case 1:
					res=stringcmp(string, var2.string);
					
					if(res==(-1)) return 1;
					else return 0;
				case 2: return !greaterThanEqual<char>(string[0], var2.string[0]);
				case 3: return !greaterThanEqual<long>(floating, var2.floating);
				case 4: return !greaterThanEqual<long>(longfloat, var2.longfloat);
				case 5: return !greaterThanEqual<long>(number, var2.number);
				case 6: return !greaterThanEqual<long>(longint, var2.longint);
			}
		}
		else{
			try{
				switch(type){
					case 1:
						throw "[Invalid operation] '<' is an operation that cannot be performed on these types";
						break;
					case 2:
						if(var2.type==3) return !greaterThanEqual<char, float>(string[0], var2.floating);
						else if(var2.type==4) return !greaterThanEqual<char, double>(string[0], var2.longfloat);
						else if(var2.type==5) return !greaterThanEqual<char, int>(string[0], var2.number);
						else if(var2.type==6) return !greaterThanEqual<char, long>(string[0], var2.longint);
						else throw "[Invalid operation] '<' is an operation that cannot be performed on these types";
					case 3:
						if(var2.type==2) return !greaterThanEqual<float, char>(floating, var2.string[0]);
						else if(var2.type==4) return !greaterThanEqual<float, double>(floating, var2.longfloat);
						else if(var2.type==5) return !greaterThanEqual<float, int>(floating, var2.number);
						else if(var2.type==6) return !greaterThanEqual<float, long>(floating, var2.longint);
						else throw "[Invalid operation] '<' is an operation that cannot be performed on these types";
					case 4:
						if(var2.type==2) return !greaterThanEqual<double, char>(longfloat, var2.string[0]);
						else if(var2.type==3) return !greaterThanEqual<double, float>(longfloat, var2.floating);
						else if(var2.type==5) return !greaterThanEqual<double, int>(longfloat, var2.number);
						else if(var2.type==6) return !greaterThanEqual<double, long>(longfloat, var2.longint);
						else throw "[Invalid operation] '<' is an operation that cannot be performed on these types";
					case 5:
						if(var2.type==2) return !greaterThanEqual<int, char>(number, var2.string[0]);
						else if(var2.type==3) return !greaterThanEqual<int, float>(number, var2.floating);
						else if(var2.type==4) return !greaterThanEqual<int, double>(number, var2.longfloat);
						else if(var2.type==6) return !greaterThanEqual<int, long>(number, var2.longint);
						else throw "[Invalid operation] '<' is an operation that cannot be performed on these types";
					case 6:
						if(var2.type==2) return !greaterThanEqual<long, char>(longint, var2.string[0]);
						else if(var2.type==3) return !greaterThanEqual<long, float>(longint, var2.floating);
						else if(var2.type==4) return !greaterThanEqual<long, double>(longint, var2.longfloat);
						else if(var2.type==5) return !greaterThanEqual<long, int>(longint, var2.number);
						else throw "[Invalid operation] '<' is an operation that cannot be performed on these types";
				}
			}catch(const char* exception){
				cout<<exception<<endl;
			}	
		}
		return 0;
	}
	int operator<(int num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThanEqual<char, int>(string[0], num);
				case 3: return !greaterThanEqual<float, int>(floating, num);
				case 4: return !greaterThanEqual<double, int>(longfloat, num);
				case 5: return !greaterThanEqual<int>(number, num);
				case 6: return !greaterThanEqual<long, int>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<(long num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThanEqual<char, long>(string[0], num);
				case 3: return !greaterThanEqual<float, long>(floating, num);
				case 4: return !greaterThanEqual<double, long>(longfloat, num);
				case 5: return !greaterThanEqual<int, long>(number, num);
				case 6: return !greaterThanEqual<long>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<(float num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThanEqual<char, float>(string[0], num);
				case 3: return !greaterThanEqual<float>(floating, num);
				case 4: return !greaterThanEqual<double, float>(longfloat, num);
				case 5: return !greaterThanEqual<int, float>(number, num);
				case 6: return !greaterThanEqual<long, float>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<(double num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThanEqual<char, double>(string[0], num);
				case 3: return !greaterThanEqual<float, double>(floating, num);
				case 4: return !greaterThanEqual<double>(longfloat, num);
				case 5: return !greaterThanEqual<int, double>(number, num);
				case 6: return !greaterThanEqual<long, double>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<(char num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'char'"; break;
				case 2: return !greaterThanEqual<char>(string[0], num);
				case 3: return !greaterThanEqual<float, char>(floating, num);
				case 4: return !greaterThanEqual<double, char>(longfloat, num);
				case 5: return !greaterThanEqual<int, char>(number, num);
				case 6: return !greaterThanEqual<long, char>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	
	int operator<=(var var2){
		if(type==var2.type){
			int res;
			switch(type){
				case 1:
					res=stringcmp(string, var2.string);
					
					if(res==(-1)||res==0) return 1;
					else return 0;
				case 2: return !greaterThan<char>(string[0], var2.string[0]);
				case 3: return !greaterThan<long>(floating, var2.floating);
				case 4: return !greaterThan<long>(longfloat, var2.longfloat);
				case 5: return !greaterThan<long>(number, var2.number);
				case 6: return !greaterThan<long>(longint, var2.longint);
			}
		}
		else{
			try{
				switch(type){
					case 1:
						throw "[Invalid operation] '<=' is an operation that cannot be performed on these types";
						break;
					case 2:
						if(var2.type==3) return !greaterThan<char, float>(string[0], var2.floating);
						else if(var2.type==4) return !greaterThan<char, double>(string[0], var2.longfloat);
						else if(var2.type==5) return !greaterThan<char, int>(string[0], var2.number);
						else if(var2.type==6) return !greaterThan<char, long>(string[0], var2.longint);
						else throw "[Invalid operation] '<=' is an operation that cannot be performed on these types";
					case 3:
						if(var2.type==2) return !greaterThan<float, char>(floating, var2.string[0]);
						else if(var2.type==4) return !greaterThan<float, double>(floating, var2.longfloat);
						else if(var2.type==5) return !greaterThan<float, int>(floating, var2.number);
						else if(var2.type==6) return !greaterThan<float, long>(floating, var2.longint);
						else throw "[Invalid operation] '<=' is an operation that cannot be performed on these types";
					case 4:
						if(var2.type==2) return !greaterThan<double, char>(longfloat, var2.string[0]);
						else if(var2.type==3) return !greaterThan<double, float>(longfloat, var2.floating);
						else if(var2.type==5) return !greaterThan<double, int>(longfloat, var2.number);
						else if(var2.type==6) return !greaterThan<double, long>(longfloat, var2.longint);
						else throw "[Invalid operation] '<=' is an operation that cannot be performed on these types";
					case 5:
						if(var2.type==2) return !greaterThan<int, char>(number, var2.string[0]);
						else if(var2.type==3) return !greaterThan<int, float>(number, var2.floating);
						else if(var2.type==4) return !greaterThan<int, double>(number, var2.longfloat);
						else if(var2.type==6) return !greaterThan<int, long>(number, var2.longint);
						else throw "[Invalid operation] '<=' is an operation that cannot be performed on these types";
					case 6:
						if(var2.type==2) return !greaterThan<long, char>(longint, var2.string[0]);
						else if(var2.type==3) return !greaterThan<long, float>(longint, var2.floating);
						else if(var2.type==4) return !greaterThan<long, double>(longint, var2.longfloat);
						else if(var2.type==5) return !greaterThan<long, int>(longint, var2.number);
						else throw "[Invalid operation] '<=' is an operation that cannot be performed on these types";
				}
			}catch(const char* exception){
				cout<<exception<<endl;
			}	
		}
		return 0;
	}
	int operator<=(int num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThan<char, int>(string[0], num);
				case 3: return !greaterThan<float, int>(floating, num);
				case 4: return !greaterThan<double, int>(longfloat, num);
				case 5: return !greaterThan<int>(number, num);
				case 6: return !greaterThan<long, int>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<=(long num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThan<char, long>(string[0], num);
				case 3: return !greaterThan<float, long>(floating, num);
				case 4: return !greaterThan<double, long>(longfloat, num);
				case 5: return !greaterThan<int, long>(number, num);
				case 6: return !greaterThan<long>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<=(float num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThan<char, float>(string[0], num);
				case 3: return !greaterThan<float>(floating, num);
				case 4: return !greaterThan<double, float>(longfloat, num);
				case 5: return !greaterThan<int, float>(number, num);
				case 6: return !greaterThan<long, float>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<=(double num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !greaterThan<char, double>(string[0], num);
				case 3: return !greaterThan<float, double>(floating, num);
				case 4: return !greaterThan<double>(longfloat, num);
				case 5: return !greaterThan<int, double>(number, num);
				case 6: return !greaterThan<long, double>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator<=(char num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'char'"; break;
				case 2: return !greaterThan<char>(string[0], num);
				case 3: return !greaterThan<float, char>(floating, num);
				case 4: return !greaterThan<double, char>(longfloat, num);
				case 5: return !greaterThan<int, char>(number, num);
				case 6: return !greaterThan<long, char>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	
	int operator==(var var2){
		if(type==var2.type){
			int res;
			switch(type){
				case 1:
					res=stringcmp(string, var2.string);
					
					if(res==0) return 1;
					else return 0;
				case 2: return Equal<char>(string[0], var2.string[0]);
				case 3: return Equal<long>(floating, var2.floating);
				case 4: return Equal<long>(longfloat, var2.longfloat);
				case 5: return Equal<long>(number, var2.number);
				case 6: return Equal<long>(longint, var2.longint);
			}
		}
		else{
			try{
				switch(type){
					case 1:
						throw "[Invalid operation] '==' is an operation that cannot be performed on these types";
						break;
					case 2:
						if(var2.type==3) return Equal<char, float>(string[0], var2.floating);
						else if(var2.type==4) return Equal<char, double>(string[0], var2.longfloat);
						else if(var2.type==5) return Equal<char, int>(string[0], var2.number);
						else if(var2.type==6) return Equal<char, long>(string[0], var2.longint);
						else throw "[Invalid operation] '==' is an operation that cannot be performed on these types";
					case 3:
						if(var2.type==2) return Equal<float, char>(floating, var2.string[0]);
						else if(var2.type==4) return Equal<float, double>(floating, var2.longfloat);
						else if(var2.type==5) return Equal<float, int>(floating, var2.number);
						else if(var2.type==6) return Equal<float, long>(floating, var2.longint);
						else throw "[Invalid operation] '==' is an operation that cannot be performed on these types";
					case 4:
						if(var2.type==2) return Equal<double, char>(longfloat, var2.string[0]);
						else if(var2.type==3) return Equal<double, float>(longfloat, var2.floating);
						else if(var2.type==5) return Equal<double, int>(longfloat, var2.number);
						else if(var2.type==6) return Equal<double, long>(longfloat, var2.longint);
						else throw "[Invalid operation] '==' is an operation that cannot be performed on these types";
					case 5:
						if(var2.type==2) return Equal<int, char>(number, var2.string[0]);
						else if(var2.type==3) return Equal<int, float>(number, var2.floating);
						else if(var2.type==4) return Equal<int, double>(number, var2.longfloat);
						else if(var2.type==6) return Equal<int, long>(number, var2.longint);
						else throw "[Invalid operation] '==' is an operation that cannot be performed on these types";
					case 6:
						if(var2.type==2) return Equal<long, char>(longint, var2.string[0]);
						else if(var2.type==3) return Equal<long, float>(longint, var2.floating);
						else if(var2.type==4) return Equal<long, double>(longint, var2.longfloat);
						else if(var2.type==5) return Equal<long, int>(longint, var2.number);
						else throw "[Invalid operation] '==' is an operation that cannot be performed on these types";
				}
			}catch(const char* exception){
				cout<<exception<<endl;
			}	
		}
		return 0;
	}
	int operator==(int num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return Equal<char, int>(string[0], num);
				case 3: return Equal<float, int>(floating, num);
				case 4: return Equal<double, int>(longfloat, num);
				case 5: return Equal<int>(number, num);
				case 6: return Equal<long, int>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator==(long num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return Equal<char, long>(string[0], num);
				case 3: return Equal<float, long>(floating, num);
				case 4: return Equal<double, long>(longfloat, num);
				case 5: return Equal<int, long>(number, num);
				case 6: return Equal<long>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator==(float num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return Equal<char, float>(string[0], num);
				case 3: return Equal<float>(floating, num);
				case 4: return Equal<double, float>(longfloat, num);
				case 5: return Equal<int, float>(number, num);
				case 6: return Equal<long, float>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator==(double num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return Equal<char, double>(string[0], num);
				case 3: return Equal<float, double>(floating, num);
				case 4: return Equal<double>(longfloat, num);
				case 5: return Equal<int, double>(number, num);
				case 6: return Equal<long, double>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator==(char num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'char'"; break;
				case 2: return Equal<char>(string[0], num);
				case 3: return Equal<float, char>(floating, num);
				case 4: return Equal<double, char>(longfloat, num);
				case 5: return Equal<int, char>(number, num);
				case 6: return Equal<long, char>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	
	int operator!=(var var2){
		if(type==var2.type){
			int res;
			switch(type){
				case 1:
					res=stringcmp(string, var2.string);
					
					if(res!=0) return 1;
					else return 0;
				case 2: return !Equal<char>(string[0], var2.string[0]);
				case 3: return !Equal<long>(floating, var2.floating);
				case 4: return !Equal<long>(longfloat, var2.longfloat);
				case 5: return !Equal<long>(number, var2.number);
				case 6: return !Equal<long>(longint, var2.longint);
			}
		}
		else{
			try{
				switch(type){
					case 1:
						throw "[Invalid operation] '!=' is an operation that cannot be performed on these types";
						break;
					case 2:
						if(var2.type==3) return !Equal<char, float>(string[0], var2.floating);
						else if(var2.type==4) return !Equal<char, double>(string[0], var2.longfloat);
						else if(var2.type==5) return !Equal<char, int>(string[0], var2.number);
						else if(var2.type==6) return !Equal<char, long>(string[0], var2.longint);
						else throw "[Invalid operation] '!=' is an operation that cannot be performed on these types";
					case 3:
						if(var2.type==2) return !Equal<float, char>(floating, var2.string[0]);
						else if(var2.type==4) return !Equal<float, double>(floating, var2.longfloat);
						else if(var2.type==5) return !Equal<float, int>(floating, var2.number);
						else if(var2.type==6) return !Equal<float, long>(floating, var2.longint);
						else throw "[Invalid operation] '!=' is an operation that cannot be performed on these types";
					case 4:
						if(var2.type==2) return !Equal<double, char>(longfloat, var2.string[0]);
						else if(var2.type==3) return !Equal<double, float>(longfloat, var2.floating);
						else if(var2.type==5) return !Equal<double, int>(longfloat, var2.number);
						else if(var2.type==6) return !Equal<double, long>(longfloat, var2.longint);
						else throw "[Invalid operation] '!=' is an operation that cannot be performed on these types";
					case 5:
						if(var2.type==2) return !Equal<int, char>(number, var2.string[0]);
						else if(var2.type==3) return !Equal<int, float>(number, var2.floating);
						else if(var2.type==4) return !Equal<int, double>(number, var2.longfloat);
						else if(var2.type==6) return !Equal<int, long>(number, var2.longint);
						else throw "[Invalid operation] '!=' is an operation that cannot be performed on these types";
					case 6:
						if(var2.type==2) return !Equal<long, char>(longint, var2.string[0]);
						else if(var2.type==3) return !Equal<long, float>(longint, var2.floating);
						else if(var2.type==4) return !Equal<long, double>(longint, var2.longfloat);
						else if(var2.type==5) return !Equal<long, int>(longint, var2.number);
						else throw "[Invalid operation] '!=' is an operation that cannot be performed on these types";
				}
			}catch(const char* exception){
				cout<<exception<<endl;
			}	
		}
		return 0;
	}
	int operator!=(int num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !Equal<char, int>(string[0], num);
				case 3: return !Equal<float, int>(floating, num);
				case 4: return !Equal<double, int>(longfloat, num);
				case 5: return !Equal<int>(number, num);
				case 6: return !Equal<long, int>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator!=(long num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !Equal<char, long>(string[0], num);
				case 3: return !Equal<float, long>(floating, num);
				case 4: return !Equal<double, long>(longfloat, num);
				case 5: return !Equal<int, long>(number, num);
				case 6: return !Equal<long>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator!=(float num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !Equal<char, float>(string[0], num);
				case 3: return !Equal<float>(floating, num);
				case 4: return !Equal<double, float>(longfloat, num);
				case 5: return !Equal<int, float>(number, num);
				case 6: return !Equal<long, float>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator!=(double num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'int'"; break;
				case 2: return !Equal<char, double>(string[0], num);
				case 3: return !Equal<float, double>(floating, num);
				case 4: return !Equal<double>(longfloat, num);
				case 5: return !Equal<int, double>(number, num);
				case 6: return !Equal<long, double>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	int operator!=(char num){
		try{
			switch(type){
				case 1: throw "[Invalid comparison] 'string cannot be compared to 'char'"; break;
				case 2: return !Equal<char>(string[0], num);
				case 3: return !Equal<float, char>(floating, num);
				case 4: return !Equal<double, char>(longfloat, num);
				case 5: return !Equal<int, char>(number, num);
				case 6: return !Equal<long, char>(longint, num);
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return 0;
	}
	
	void operator++(int a){
		try{
			switch(type){
				case 1: throw "[Invalid operation] '++' cannot be performed on var of type 'string'"; break;
				case 2: string[0]+=1; break;
				case 3: floating++;
				case 4: longfloat++;
				case 5: number++;
				case 6: longint++;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	void operator--(int a){
		try{
			switch(type){
				case 1: throw "[Invalid operation] '--' cannot be performed on var of type 'string'"; break;
				case 2: string[0]-=1; break;
				case 3: floating--;
				case 4: longfloat--;
				case 5: number--;
				case 6: longint--;
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
	}
	
	var operator%(var var1){
		var var3;
		try{
			long num1;
			if(type==var1.type){
				switch(type){
					case 5: var3.type=5;
							var3.number=number%var1.number; break;
					case 6: var3.type=6;
							var3.longint=longint%var1.longint; break;
					default: throw "[invalid operation] '%' cannot be used on this type";
				}
			}
			else{
				long num1;
				switch(type){
					case 1: throw "[Invalid operation] '%' cannot be used on this type"; break;
					case 2:
							if(var1.type==5){
								var3.type=2;
								var3.string=new char[1];
								var3.string[0]=string[0]%var1.number;
								break;
							}
							else if(var1.type==6){ 
								var3.type=2;
								var3.string=new char[1];
								var3.string[0]=string[0]%var1.longint;
								break;
							}
							else throw "[Invalid operation] '%' cannot be used on these types";
					case 5:
							if(var1.type==2){ 
								var3.type=5;
								var3.number=number%var1.string[0];
								break;
							}
							else if(var1.type==6){ 
								var3.type=6;
								var3.longint=number;
								var3.longint%=var1.longint;
								break;
							}
							else throw "[Invalid operation] '%' cannot be used on these types";
					case 6:
							if(var1.type==2){
								var3.type=6;
								var3.longint=longint%var1.string[0];
								break;
							}
							else if(var1.type==5){
								var3.type=6;
								var3.longint=longint%var1.number; 
								break;
							}
							else throw "[Invalid operation] '%' cannot be used on these types";
					default: throw "[Invalid operation] '%' cannot be used on these types"; break;
				}
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return var3;
	}
	var operator%(int num){
		var var3;
		try{
			switch(type){
				case 5: var3.type=5;
						var3.number=number%num;
						break;
				case 6: var3.type=6;
						var3.longint=longint%num;
						break;
				default: throw "[Invalid operation] '%' cannot be performed on this type";
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return var3;
	}
	var operator%(long num){
		var var3;
		try{
			switch(type){
				case 5: var3.type=6;
						var3.longint=number;
						var3.longint%=num;
						break;
				case 6: var3.type=6;
						var3.longint=longint%num; break;
				default: throw "[Invalid operation] '%' cannot be performed on this type";
			}
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return var3;
	}
	
	char operator[](int num){
		try{
			if(allocated==1) return string[num];
			else throw "[String not found] String has not been allocated";
		}catch(const char* exception){
			cout<<exception<<endl;
		}
		return '?';
	}
	
	friend ostream &operator<<(ostream &o, var var1);
	friend istream &operator>>(istream &i, var &var1);
};

ostream &operator<<(ostream &o, var var1){
	if(var1.type==1||var1.type==2){
		o<<var1.string;
		return o;
	}
	else if(var1.type==3){
		o<<var1.floating;
		return o;
	}
	else if(var1.type==4){
		o<<var1.longfloat;
		return o;
	}
	else if(var1.type==5){
		o<<var1.number;
		return o;
	}
	else if(var1.type==6){
		o<<var1.longint;
		return o;
	}
	else return o;
}
istream &operator>>(istream &i, var &var1){
	var1.type=1;
	if(var1.allocated==1){
		delete var1.string;
		var1.allocated=0;
	}
	var1.allocated=1;
	var1.string=new char[50];
	
	i>>var1.string;
	
	var1.input(var1.string);
	
	return i;
}
