# DynaVar
DynaVar is a project, written wholly in C++, whose main objective is to create a user-defined data structure capable of storing all primitive data-types.  

This project started out as an experimental program which later grew into a full-fledged project aiming to solve a particular problem faced by programmers everywhere. Programmers, especially beginners, always falter when it comes to data-types and type-casting. In languages like C, where there are no built-in data types for Strings and Booleans, the learning-curve can be quite high. Character arrays, enumerated types, type-casting and similar problems could prove to be a significant hindrance to programmers who are learning afresh.

This project could help with these problems by providing a common 'data-type' for all variables. From floats to longs to strings, anything can be stored in the object. By abstracting what goes on in the background, DynaVar could help programmers focus on the more important concepts at hand. 

To paraphrase JRR Tolkien:
> One object to rule them all.

## Getting Started
If you're interested in using DynaVar in your own C++ code, you can follow the instructions below.

### Prerequisites
* Text editor (Sublime, TextMate, Notepad, etc)
* C++ Compiler (Clang, GCC or anything else)
or
* IDE supporting C++ (Dev C++, Xcode, Turbo C++)

### Installation
1. Download or clone this repository onto your computer. There should be a file named ```dynavar.h``` inside the folder.
2. Move this file to the directory in which your C++ file or ```.cpp``` file is located.
3. At the starting of your file, include the ```dynavar.h``` header file. 
```
#include<iostream>
#include"dynavar.h"
.....
````
Like that^.
4. You should now be able to use the ```var``` object in your own programs. The object should satisfy most of your requirements, however, it has a few limitations and there are still some features to be added. To see the full list of available features, how-to and documentation, scroll down below (currently ongoing). 

### Sample Program
#### #1
```
//To check whether a number is even or odd

#include"dynavar.h"

int main(){
	var num;
	
	cout<<"Enter a number --> ";
	cin>>num;
	
	if(num%2==0) cout<<"The number is an even number"<<endl;
	else cout<<"The number is an odd number"<<endl;
	
	return 0;
}
```
#### #2
```
//To print all numbers divisible by 3 upto a given limit

#include"dynavar.h"

int main(){
	var limit;
	
	cout<<"Enter a limit --> ";
	cin>>limit;
	
	var i;
	for(i=0.0; i<limit; i++){
		if(i%3==0) cout<<i<<" is divisible by 3\n";
	}
	
	return 0;
}
```
#### #3
```
//To check whether two given names are equal or not

#include"dynavar.h"

int main(){
	var name1, name2;
	
	cout<<"Enter the first name --> ";
	cin>>name1;
	cout<<"Enter the second name --> ";
	cin>>name2;
	
	if(name1==name2) cout<<"The names are the same\n";
	else cout<<"The names are different\n";
	
	return 0;
}
```
These are a few sample programs to give a basic understanding of how the ```var``` object might work. For full documentation, see the wiki (still in progress).

### Built With
* [Textmate](https://macromates.com/)
* [Clang C++ Compiler](https://clang.llvm.org/)

### Author
* Arjun Aravind

### Acknowledgements
* Thanks to Divya G, for input on the usage of templates in v1.0.
* Stack Overflow
