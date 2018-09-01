/*
Author: Tianyuan Li

This part of the lab is to read series of lines of input character by character and determind if they are valid C identifiers.

*/

#include<stdio.h>

int main(){

	int i, isValid;
	int size = 5;
	char temp;

	printf("Enter 5 strings: \n");

	/*put in five strings*/
	for (i = 0;i < size;i++){
		isValid = 1;
		temp = getchar();
		
		/*determind if the string starts wiht a letter or '_'*/
		if (!((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z') || (temp == '_'))){
			isValid = 0;
		}
		/*continue consuming the rest of the string and determind if it is a valid identifier or not*/
		while((temp = getchar()) != '\n'){
			if (!((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z') || (temp == '_') || (temp >= '0' 					&& temp <= '9'))){
				isValid = 0;
			}
		}
		/*print out if it is valid or not*/
		if(isValid){
			printf("Valid\n");
		} else {
			printf("Invalid\n");
		}

	}
	return 0;
}

