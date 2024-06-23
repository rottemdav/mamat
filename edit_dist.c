#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100
#define MIN_SIZE 3

int edit_dist(char word1[], char word2[]);

/** 
 * @brief Function to find the lowest cell words_matrix between 3 cells.
 * @param top is the top cell above the current cell we are checking.
 * @param diag is the top left cell above the current cell.
 * @param left is the cell left to the current cell
 * @return the cell with the lowest amount of changes between the 3 cells.
*/
int min(int top, int diag, int left){
    int min_matrix[MIN_SIZE] = {top, diag, left};
    int min = min_matrix[0];
    
    for (int i = 1; i < MIN_SIZE; i++){
        if (min_matrix[i] < min){
            min = min_matrix[i];
        }
    }
    return min;
}

/**
 * @brief Compares between two characters
 * @param c_word1 character from the first word (on the row)
 * @param c_word2 character from the second word (on the column)
 * @return 0 - no match, 1 - match 
*/
int compare_chars(char c_word1, char c_word2){
    if (c_word1 == c_word2){
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char word1[MAX_WORD_LEN], word2[MAX_WORD_LEN];
    
    fgets(word1, MAX_WORD_LEN, stdin);
    word1[strlen(word1) - 1] = '\0';
    fgets(word2, MAX_WORD_LEN, stdin);
    word2[strlen(word2) - 1] = '\0';

    printf("%d\n", edit_dist(word1, word2));

    return 0;
}

/**
 * @brief A function to create the matrix that will be used to calculate the 
 * distance.
 * @param word1 the word we need to calculate the distance from.
 * @param word2 the word we need to calculate the distance to.
 * @return the distance of changes from word1 to word2.
 */

int edit_dist(char word1[], char word2[]) {
    int word1_len = strlen(word1);
    int word2_len = strlen(word2);

    int words_matrix[word2_len + 1][word1_len + 1];

    for (int i = 0; i <= word2_len; i++){
        for (int j = 0; j <= word1_len; j++){
            if (i == 0){
				words_matrix[i][j] = j;
			} else if (j == 0){
				words_matrix[i][j] = i;
			} else {
				int chars_match = compare_chars(word1[j-1], word2[i-1]);
                
				int cost = chars_match ? 0 : 1;

				words_matrix[i][j] = min(
					words_matrix[i-1][j] + 1, // Deletion
					words_matrix[i][j-1] + 1, // Insertion
					words_matrix[i-1][j-1] + cost // Substitution
				); 
			}
        }
    }
    return words_matrix[word2_len][word1_len];
}