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
 * @brief Compares two numbers. Function is necessary for qsort function. 
 * @param a Pointer to the first number to comapre.
 * @param b Pointer to the second number to comapre.
 * @return A value, -1,0,1 depending if a<b,a>b,a=b accordingly. 
 */

int compare_nums(void const *a, void const *b){
	
	// Insert the given pointer values into local integers inside the function.
	int num_a = *(int const *)a;
	int num_b = *(int const *)b;

	if (num_a < num_b){
		return -1;
	} else if (num_a > num_b){
		return 1;
	} else {
		return 0;
	}
}

/**
 * @brief Check if the sum of two numbers in the array equals to target
 * 
 * This function will sort the input array using quick-sort. If the input is
 * already sorted, then we will check to avoid using quick-sort in complexity of
 * O(nums_size^2), otherwise we will use quick-sort in complexity 
 * O(num_size*log(num_size)).
 * 
 * Later on we will use an algorithm to if there are two numbers in the array 
 * that equal to target, in time-complexity O(n).
 *
 * The function will print the indexes of the first two numbers that equal
 * target.
*/

void twoSum(int nums[], int nums_size, int target) {
	// A boolean to check if the input array is already sorted.
	bool is_sorted = true;

	// These integers are the indexes that will be used in the algorithm.
	int left = 0;
	int right = nums_size-1;
	
	int nums_copy[MAX_ARRAY_SIZE] = {0};
	
	// Copy the original array to an auxiliry array. 
	for (int i = 0; i < nums_size-1; i++){
		nums_copy[i] = nums[i];
	}

	for (int i = 0; i < nums_size-1; i++){
		if (nums[i] > nums[i+1]){
			is_sorted = false;
			break;
		}
	}

	// Will use quick-sort to sort the array if nums isn't already sorted.
	if (!is_sorted){
		qsort(nums, nums_size,sizeof(int),compare_nums);
	}

	/** 
	 * We are guaranteed to have at least one pair of numbers so the loop is 
	 * isn't inifinte.
	*/
	while (1){
		int sum_of_two = nums[left]+nums[right];
		
		if (sum_of_two > target){
			right--;
		} else if (sum_of_two < target){
			left++;
		} else{
			// Found a pair of numbers that equal target
			break;
		}
	}

	for (int i = 0; i < nums_size; i++){
		if (nums[left] == nums_copy[i]){
			left = i;
		}
	}

	for (int i = 0; i < nums_size; i++){
		if ((nums[right] == nums_copy[i]) && (i != left)){
			right = i;
		}
	}

	printf("(%d, %d)",(left<right) ? left : right, (left<right) ? right : left);

}
