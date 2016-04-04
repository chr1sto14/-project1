#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "SudokuVer.c"

//Project 1
// Katy Robison
// Christopher Miller

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
	
	char str[1000];
	char S[1000] = "";
	getchar();
	while (fgets(str, 50, f) != NULL) {
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


// Check specified row for non-repeating from perspective of the cell
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


// Check specified col for non-repeating from the perspective of the cell
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


//
// Check specified block for non-repeating from the perspective of the cell
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

int nextEmpty(int matSize, int array[matSize][matSize], struct Point2D *p) {
	for (int i=0;i<matSize;i++) {
		for (int j=0;j<matSize;j++) {
			if (array[i][j] == 0) {
				p->row = i;
				p->col = j;
				return 1;
			}	
		}
	}
	return 0;
}
//Print the matrix in raw form
void printMat(int matSize, int array[matSize][matSize]) {
	printf("printing matrix\n");
	for (int a = 0; a<matSize; a++) {
		for (int b=0; b<matSize; b++) {
			printf("%d",array[a][b]);
		}
		printf("\n");
	}
}

// Method to recursively solve sudoku
// Input matrix size, matrix, and Point2D of empty array
int canSolve(int matSize, int array[matSize][matSize],struct Point2D pt) {
	for (int i=1;i<=matSize;i++) { // guess values
		array[pt.row][pt.col] = i;
		
		if ( (is_row_valid2(matSize, array, pt)) && (is_col_valid2(matSize, array, pt))  && (is_block_valid2(matSize, array, pt)) ) {
			struct Point2D nextPoint; // make next empty pointer
			if (nextEmpty(matSize, array, &nextPoint) ) {
				if (canSolve(matSize, array, nextPoint)) {
					return 1;
				}
				
			}
			else {
				return 1;
			}
		}
		
		
	}
	array[pt.row][pt.col] = 0; //reset back to 0
	return 0;
}
//********************************************************************************
	

// Print matrix in pretty form
void output(int matSize, int array[matSize][matSize], char *filename) {

	printf("%s\n",filename);
	for (int c = 0; c < matSize; c++) { // iterate through rows
		if (c==0)  {
			printf("-------------------------\n");
		}
		else if ((c==3) || (c==6) ) {
			printf("--------+-------+--------\n");
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
	int matSize = 9; //dimensions of the sudoku analyzing
	int sudokuArray[matSize][matSize]; //2D array
	
	char filename[50]; // filename to open
	printf("Input file to open: ");
	scanf("%s",filename);
	
	// Read the file into an array
	input(matSize,sudokuArray,filename);
	//Print the empty matrix
	output(matSize,sudokuArray,filename);
	
	// Find first empty Point2D in 2D array
	struct Point2D firstPoint;
	nextEmpty(matSize,sudokuArray, &firstPoint);

	// Return solved sudoku or let user know not solvable 
	if (canSolve(matSize,sudokuArray,firstPoint)) {
		output(matSize,sudokuArray,filename);
	}
	else {
		printf("Grid not solvable\n");
	}
		
}

