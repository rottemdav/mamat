#include <stdio.h>  // printf, scanf
#include <stdlib.h> // malloc, free
#include <string.h> // strlen, strcat, etc.
#include <math.h>   // sqrt, pow, floor, ceil, etc.
#include <stdbool.h> // booleans

#define MAX_ARRAY_SIZE 10000

void twoSum(int nums[], int nums_size, int target);

int main() {
	int target;
	int nums[MAX_ARRAY_SIZE] = {0};
	int array_size = 0;

	scanf("%d", &target);

	while (scanf("%d", &nums[array_size++]) == 1);
	array_size--;

	twoSum(nums, array_size, target);

	return (0);
}

/**
 * @brief Check if the sum of two numbers in the array equals to target
 * 
 * This function go through all the possible sums from two different numbers 
 * in the array, if they equal.
*/

void twoSum(int nums[], int nums_size, int target) {
	
	bool is_found = false;

	for (int i = 0; i < nums_size; i++){
		for (int j = 0; j < nums_size; j++){
			if (i == j){
				continue;
			}
			else if (target == (nums[i] + nums[j])){
				printf("(%d,%d)", i,j);
				is_found = true;
				break;
			}
		}	
		if (is_found){
			break;
		}
	}

}
