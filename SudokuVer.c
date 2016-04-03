#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Christopher Miller & Katy Robison
// Project 1 step 1--Verification of completed sudoku

// Check specified row for non-zero, non-repeating
// return 0 for invalid
// return 1 for valid
int is_row_valid(int matSize, int array[matSize][matSize], int row) {
	for(int i=0;i<matSize;i++) {
		for (int j=i+1;j<matSize;j++) {
			if (array[row][i] == 0) {
				return 0;
			}
			if (array[row][i] == array[row][j]) {
				return 0;
			}
		}
	}
	return 1;
	
}
// Check specified col for non-zero, non-repeating
// return 0 for invalid
// return 1 for valid
int is_col_valid(int matSize, int array[matSize][matSize], int col) {
	for(int i=0;i<matSize;i++) {
		for (int j=i+1; j<matSize;j++) {
			if (array[i][col] == 0) {
				return 0;
			}
			if (array[i][col] == array[j][col]) {
				return 0;
			}
		}
	}
	return 1;
	
}

// Check specified block for non-zero, non-repeating
// return 0 for invalid
// return 1 for valid
int is_block_valid(int matSize, int array[matSize][matSize], int block) {
	
	int tmpArray[matSize];
	if (block == 1) { // top left
		int count = 0;
		for (int i = 0; i < 3; i++) { //reformat into an array
			for (int j = 0; j < 3; j++) {
				tmpArray[count] = array[i][j];
				count++;
			}
		}
		for (int m = 0; m < matSize; m++) { //check validity
			for (int n = m + 1; n < matSize; n++) {
				if (tmpArray[m] == 0) {
					return 0;
				} else if (tmpArray[m] == tmpArray[n]) {
					return 0;
				}
			}
		}
	} else if (block == 2) { // top right
		int count = 0;
		for (int i = 0; i < 3; i++) { //reformat into an array
			for (int j = 6; j < 9; j++) {
				tmpArray[count] = array[i][j];
				count++;
			}
		}
		for (int m = 0; m < matSize; m++) { //check validity
			for (int n = m + 1; n < matSize; n++) {
				if (tmpArray[m] == 0) {
					return 0;
				} else if (tmpArray[m] == tmpArray[n]) {
					return 0;
				}
			}
		}
	} else if (block == 3) { // bottom left
		int count = 0;
		for (int i = 6; i < 9; i++) { //reformat into an array
			for (int j = 0; j < 3; j++) {
				tmpArray[count] = array[i][j];
				count++;
			}
		}
		for (int m = 0; m < matSize; m++) { //check validity
			for (int n = m + 1; n < matSize; n++) {
				if (tmpArray[m] == 0) {
					return 0;
				} else if (tmpArray[m] == tmpArray[n]) {
					return 0;
				}
			}
		}
	} else if (block == 4) { // bottom right
		int count = 0;
		for (int i = 6; i < 9; i++) { //reformat into an array
			for (int j = 6; j < 9; j++) {
				tmpArray[count] = array[i][j];
				count++;
			}
		}
		for (int m = 0; m < matSize; m++) { //check validity
			for (int n = m + 1; n < matSize; n++) {
				if (tmpArray[m] == 0) {
					return 0;
				} else if (tmpArray[m] == tmpArray[n]) {
					return 0;
				}
			}
		}
	}
	return 1;
}

// Verify sudoku
// return 0 if not valid
// return 1 if valid
int verify(int matSize, int array[matSize][matSize]) {
	for (int itr = 0; itr < matSize; itr++) { //check rows & cols
		if (!is_row_valid(matSize,array,itr) || !is_col_valid(matSize,array,itr)) {
			printf("Invalid Solution\n");
			return 0;
		}
	}
	for (int blck = 1; blck <= 4; blck++) { //check blocks
		if (!(is_block_valid(matSize,array,blck))) {
			return 0;
		}
	}
	printf("Valid Solution\n");
	return 1;
}
	

