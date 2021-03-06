#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Point structure to hold x and y coordinates
struct Point2D {
	int row, col;
};

// Input
//  -Open file
//  -Read file to string
//  -Convert string to matrix
void input(int matSize, int array[matSize][matSize], char *filename) {
	//**************************** Open the file ********************************
	FILE *f; //create file pointer
	f = fopen(filename, "r"); //open file
	if (f == NULL) {
		printf("Error: File not found\n");
		fclose(f);
	}
	//***************************************************************************
	
	char str[12];
	char S[1000];
	while (fgets(str, 12, f) != NULL) {
		strcat(S, str); //collect input into a string
	}
	
	int i = 0; // row iterator
	int j = 0; // col iterator
	int k = 0; // char array iterator
	char out[1000];
	
	while (S[k] != '\0') { //collect numbers into a matrix
		if ((S[k] == '\n') && (S[k+1]!='\n')) {	// reset to beginning of next row
			i++; 
			j=0;
		}
		else if ((S[k] != ' ') && (S[k] != '\n')){ 
			array[i][j] = S[k] - '0'; // add int value to matrix
			j++;	
		}
		k++;	
	}
	
	fclose(f);
	return;
}

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

// Check specified row for non-repeating
// return 0 for invalid
// return 1 for valid
int is_row_valid2(int matSize, int array[matSize][matSize], struct Point2D pnt) {
	for(int i = 0; i < pnt.col; i++) { // iterate through columns less than point
		if (array[pnt.row][pnt.col] == array[pnt.row][i]) {
			return 0;
		}
	}
	for(int i = pnt.col + 1; i < matSize; i++) { // iterate through columns greater than point
		if (array[pnt.row][pnt.col] == array[pnt.row][i]) {
			return 0;
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


// Check specified col for non-repeating
// return 0 for invalid
// return 1 for valid
int is_col_valid2(int matSize, int array[matSize][matSize], struct Point2D pnt) {
	for(int i = 0; i < pnt.row; i++) { // iterate through rows less than point
		if (array[pnt.row][pnt.col] == array[i][pnt.col]) {
			return 0;
		}
	}
	for(int i = pnt.row + 1; i < matSize; i++) { // iterate through columns greater than point
		if (array[pnt.row][pnt.col] == array[i][pnt.col]) {
			return 0;
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
//
// Check specified block for non-repeating
// return 0 for invalid
// return 1 for valid
int is_block_valid2(int matSize, int array[matSize][matSize],struct Point2D pnt) {
	
	int startingRow = (int)(pnt.row / sqrt(matSize) ) * sqrt(matSize);
	int startingCol = (int)(pnt.col / sqrt(matSize) ) * sqrt(matSize);
	int endingRow = startingRow + (int)sqrt(matSize);
	int endingCol = startingCol + (int)sqrt(matSize);

	int tmpArray[matSize];
	int count = 0;
	for (int i = startingRow; i < endingRow; i++) { //reformat block into an array
		for (int j = startingCol; j < endingCol; j++) {
			if ( (i == pnt.row) && (j == pnt.col)) {
				continue;
			}
			tmpArray[count] = array[i][j];
			count++;
		}
	}
	for (int m = 0; m < matSize - 1; m++) { //check validity
		if (array[pnt.row][pnt.col] == tmpArray[m]) {
				return 0;
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
			return 0;
		}
	}
	for (int blck = 1; blck <= 4; blck++) { //check blocks
		if (!(is_block_valid(matSize,array,blck))) {
			return 0;
		}
	}
	return 1;
}
	
//Print the matrix in raw form
void printMat(int matSize, int array[matSize][matSize]) {
	printf("printing matrix\n");
	for (int a = 0; a<matSize; a++) {
		for (int b=0; b<matSize; b++) {
			//printf("array[%d][%d] = %d\n",a,b,array[a][b]);
			printf("%d",array[a][b]);
		}
		printf("\n");
	}
}

// Print matrix in pretty form
void output(int matSize, int array[matSize][matSize], char *filename) {

	//Need to change the c==0,2 and d==0,2,3 to automatically change depending on input size
		// Does it need to depend on size? Can't we just assume a 9x9 sudoku? -CM 3/27/2016
	printf("%s\n",filename);
	for (int c = 0; c < matSize; c++) { // iterate through rows
		if (c==0)  {
			printf("-------------------------\n");
		}
		else if ((c==3) || (c==6) ) {
			printf("--------+--------+-------\n");
		}
		for (int d=0; d<matSize; d++) { // iterate through cols
			if ((d==0) || (d==3) || (d==6) ) { //printf | before the numbers
				printf("| ");
				if (array[c][d]==0) {
					printf(". ");
				}
				else {
					printf("%d ", array[c][d]);
				}
			}
			else if (d==8) { //print | after the last number in the row
				if (array[c][d]==0) {
					printf(". ");
				}
				else {
				printf("%d ", array[c][d]);
				}
				printf("|\n");
			}
			else {
				if (array[c][d]==0) {
					printf(". ");
				}
				else {
				printf("%d ", array[c][d]);
				}
			}
		}
		if (c==8) {
			printf("-------------------------\n");	
		}
	}
}
	
int main() {
	int matSize = 9;
	int sudokuArray[matSize][matSize];
	
	char filename[50]; // filename to open
	printf("Input file to open: ");
	scanf("%s",&filename);
	
	input(matSize,sudokuArray,filename);
	printMat(matSize, sudokuArray);
	
	printf("is block 1 valid? %d\n",is_block_valid(matSize,sudokuArray,1));
	printf("is block 2 valid? %d\n",is_block_valid(matSize,sudokuArray,2));
	printf("is block 3 valid? %d\n",is_block_valid(matSize,sudokuArray,3));
	printf("is block 4 valid? %d\n",is_block_valid(matSize,sudokuArray,4));
	printf("is sudoku valid? %d\n",verify(matSize,sudokuArray));
	output(matSize,sudokuArray,filename);
	
	struct Point2D testPnt; testPnt.row = 5; testPnt.col = 6;
	printf("is row 5 valid? %d\n",is_row_valid2(matSize,sudokuArray,testPnt));
	printf("is col 6 valid? %d\n",is_col_valid2(matSize,sudokuArray,testPnt));
	printf("is middle right block valid? %d\n",is_block_valid2(matSize,sudokuArray,testPnt));

	
	printf("\narray[0]: %p\n",sudokuArray);
	printf("size of array: %d\n", sizeof(sudokuArray)/sizeof(sudokuArray[0]));
	

}
