#include <stdio.h>
#include <stdlib.h>

void allocate_float_ptr_array (float ***, int *);
void allocate_data_set_sizes_array (int **, int);
void store_set_sizes_and_float_data (float **, int *, int);
int select_data_set();
int select_option_num();
void print_result(int, float **, int *, int);
float minimum(float **, int *, int);
float maximum(float **, int *, int);
float summation(float **, int *, int);
float mean(float **, int *, int);
void print_values(float **, int *, int);
void exit_program(float **, int *);

/*Author: Tianyuan Li

The program provide some calculations for an unknown number of data sets. Each data set includes a number of floating point values. The number of data sets, the number of floats in each data set, and the floats in each data set will be input by the user.*/

int main() {
	float **data_sets_ptr;
	int *data_set_sizes;
	int num_sets;
	int data_set_num;
	int option_num;

	allocate_float_ptr_array (&data_sets_ptr, &num_sets);
	allocate_data_set_sizes_array (&data_set_sizes, num_sets);
	store_set_sizes_and_float_data (data_sets_ptr, data_set_sizes, num_sets);

	/*Repeatly ask the user to select a data set and chooose an option to do calculations.*/
	while (1) {
		data_set_num = select_data_set();
		option_num = select_option_num();
		print_result(option_num, data_sets_ptr, data_set_sizes, data_set_num);
	}
	return 0;
}

/*This function is to read the number of data sets and allocate space for float pointers which point to float data sets.*/
void allocate_float_ptr_array (float ***data_sets_ptr_adr, int *num_sets_adr) {
	printf("Please enter the number of data sets(greater than 0): \n");
	scanf("%i", num_sets_adr);
	*data_sets_ptr_adr = malloc(*num_sets_adr * sizeof(float*));
	if (*data_sets_ptr_adr == NULL) {
		printf("Memory could not be allocated for all of the float pointer data.");
		printf("Terminating program.\n");
		exit(0);
	}
}

/*This function is to allocate space for ints which refer to the sizes of each data set.*/
void allocate_data_set_sizes_array (int **data_set_sizes_adr, int num_sets) {
	*data_set_sizes_adr = malloc(num_sets * sizeof(int));
	if (*data_set_sizes_adr == NULL) {
		printf("Memory could not be allocated for all of the int point data.");
		printf("Terminating program.\n");
		exit(0);
	}
}

/*This function is to read the number of floats and those floats in each data sets and then stored in the appropriate places, which has been declared above.*/
void store_set_sizes_and_float_data (float **data_sets_ptr, int *data_set_sizes, int num_sets) {
	int i,j;
	for (i = 0; i < num_sets; i++) {
		printf("Please enter the number of floats in the data set: \n");
		scanf("%i", (data_set_sizes + i));
		*(data_sets_ptr + i) = malloc(*(data_set_sizes + i) * sizeof(float));
		if (*(data_sets_ptr + i) == NULL) {
			printf("Memory could not be allocated for all of the floating point data.");
			printf("Terminating program.\n");
			exit(0);
		}
		else {
			printf("Please enter each float number in the set separated by spaces and ended by hitting enter: \n");
			for (j = 0; j < *(data_set_sizes + i); j++) {
			scanf("%f", *(data_sets_ptr + i) + j);
			}
		}
	}
}

/*This function is to ask the user to do calculations on which data set.*/
int select_data_set() {
	int temp;
	printf("please enter the number of the data set on which you wish to do calculations: \n");
	scanf("%i", &temp);
	return temp;
}

/*This function is to ask the user to do which calculation.*/
int select_option_num() {
	int temp;
	printf("Choose your option by typing the number: \n");
	printf("1. Find the minimum value.\n");
	printf("2. Find the maximum value.\n");	
	printf("3. Calculate the sum of all the values.\n");
	printf("4. Calculate the average of all the values.\n");
	printf("5. Print the values in the data set.\n");
	printf("6. Exit the program.\n");
	scanf("%i", &temp);
	return temp;
}

/*This function is to print the result of the calculation.*/
void print_result(int option_num, float **data_sets_ptr, int *data_set_sizes, int data_set_num) {
	float min, max, sum, avg;

	switch (option_num) {
		case 1:
			min = minimum(data_sets_ptr, data_set_sizes, data_set_num);
			printf("The minimum value in the data set is: %.2f\n", min);
			break;
		case 2:
			max = maximum(data_sets_ptr, data_set_sizes, data_set_num);
			printf("The maximum value in the data set is: %.2f\n", max);
			break;
		case 3:
			sum = summation(data_sets_ptr, data_set_sizes, data_set_num);
			printf("The sum of all the values in the data set is: %.2f\n", sum);
			break;
		case 4:
			avg = mean(data_sets_ptr, data_set_sizes, data_set_num);
			printf("The average of all the values in the data set is: %.2f\n", avg);
			break;
		case 5:
			printf("The values in the data set are: \n");
			print_values(data_sets_ptr, data_set_sizes, data_set_num);
			break;
		case 6:
			exit_program(data_sets_ptr, data_set_sizes);
			break;
		default:
			break;
	}

	printf("\n");
}

/*This function is to find the minimum value in a data set.*/
float minimum(float **data_sets_ptr, int *data_set_sizes, int data_set_num) {
	float *smallest = *(data_sets_ptr + data_set_num - 1);
	int i;
	for (i = 0; i < *(data_set_sizes + data_set_num - 1); i++) {
		if (*(*(data_sets_ptr + data_set_num - 1) + i) < *smallest) {
			smallest = *(data_sets_ptr + data_set_num - 1) + i;
		}
	}
	return *smallest;
}

/*This function is to find the maximum value in a data set.*/
float maximum(float **data_sets_ptr, int *data_set_sizes, int data_set_num) {
	float *largest = *(data_sets_ptr + data_set_num - 1);
	int i;
	for (i = 0; i < *(data_set_sizes + data_set_num - 1); i++) {
		if (*(*(data_sets_ptr + data_set_num - 1) + i) > *largest) {
			largest = *(data_sets_ptr + data_set_num - 1) + i;
		}
	}
	return *largest;
}

/*This function is to calculate the summation of values in a data set.*/
float summation(float **data_sets_ptr, int *data_set_sizes, int data_set_num) {
	float sum = 0;
	int i;
	for (i = 0; i < *(data_set_sizes + data_set_num - 1); i++) {
		sum += *(*(data_sets_ptr + data_set_num - 1) + i);
	}
	return sum;
}

/*This function is to calculate the mean of values in a data set.*/
float mean(float **data_sets_ptr, int *data_set_sizes, int data_set_num) {
	float sum = 0;
	int i;
	for (i = 0; i < *(data_set_sizes + data_set_num - 1); i++) {
		sum += *(*(data_sets_ptr + data_set_num - 1) + i);
	}
	return sum / *(data_set_sizes + data_set_num - 1);
}

/*this function is to print each value in a data set in the order of which the user entered.*/
void print_values(float **data_sets_ptr, int *data_set_sizes, int data_set_num)	{
	int i;
	for (i = 0; i < *(data_set_sizes + data_set_num - 1); i++) {
		printf("%.2f\t", *(*(data_sets_ptr + data_set_num - 1) + i));
	}
	printf("\n");
}

/*This function is to exit the program and free the space allocated above.*/
void exit_program(float **data_sets_ptr, int *data_set_sizes) {
	free(data_sets_ptr);
	free(data_set_sizes);
	exit(0);
}

		
