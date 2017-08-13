#include<iostream>
using namespace std;

template <class Var1> int greaterThan(Var1 num1, Var1 num2){
	return (num1>num2)? 1 : 0;
}

template <class Var1, class Var2> int greaterThan(Var1 num1, Var2 num2){
	return (num1>num2)? 1: 0; 
}

template <class Var1> int greaterThanEqual(Var1 num1, Var1 num2){
	return (num1>=num2)? 1 : 0;
}

template <class Var1, class Var2> int greaterThanEqual(Var1 num1, Var2 num2){
	return (num1>=num2)? 1: 0; 
}

template <class Var1> int Equal(Var1 num1, Var1 num2){
	return (num1==num2)? 1 : 0;
}

template <class Var1, class Var2> int Equal(Var1 num1, Var2 num2){
	return (num1==num2)? 1: 0; 
}