/*
Author: Tianyuan Li

This part of the lab is to read series of lines of input character by character and convert them into 
corresponding floating point numbers by converting each char into a interger and assembling them 
correctly.
*/

#include<stdio.h>

int main(){

	int size, i, digit, temp;
	float value, j, total = 0;
	
	/*ask for the size of input*/
	printf("Enter the size of input: \n");
	scanf("%d", &size);
	printf("Enter %d numbers: \n",size);
	getchar();

	/*read new numbers*/
	for (i = 0; i < size; i++){
		value = 0;

		/*scan the number character by character and convert them into floating numbers*/
		while((temp = getchar()) != '\n'){

			/*scan the part of the number which is greater than 0(before the decimal point*/
			if(temp != '.' ){
				digit = temp - '0'; /*change the charater into its numeric value*/
				value = value * 10 + digit;
			} 
			
			/*scan the part of the number which is less than 0(after the decimal point)*/
			else {
				j = 0.1;
				while((temp = getchar()) != '\n'){
				digit = temp - '0'; 
				value = value + (float)digit * j;
				j = j * 0.1;
				}
				break;
			}
		}

		/*print the numeric form of the number with 3 digits of precision*/
		printf("%.3f\n", value);
		total += value;
		
	}

	/*print the total value of all the input numbers*/
	printf("Total: %.3f\n", total);
	return 0;
}

		
	



