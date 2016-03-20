#include <stdio.h>
#include <string.h>

//Print the matrix
int matSize = 9;
void printMat(int array[matSize][matSize], int matSize) {
	printf("printing matrix\n");
	for (int a = 0; a<matSize; a++) {
		for (int b=0; b<matSize; b++) {
			//printf("array[%d][%d] = %d\n",a,b,array[a][b]);
			printf("%d",array[a][b]);
		}
		printf("\n");
	}
}

int is_row_valid(int row[]) {
	for(int i=0;i<9;i++) {
		for (int j=i+1;j<9;j++) {
			if (row[i] ==0) {
				return 0;
			}
			if (row[i] == row[j]) {
				return 0;
			}
		}
	}
	return 1;
	
}

int is_col_valid(int col[]) {
	return 1;
}

int is_block_valid(int block[]) {
	return 1;
}
	
int main() {
//**************************** Open the file ********************************
	FILE *f; //create file pointer
	f = fopen("notvalidex.txt", "r"); //open file
	if (f == NULL) {
		printf("Error: File not found\n");
		fclose(f);
	}
//***************************************************************************	
	int matSize = 9;
	char str[1000];
	char S[1000];
	while (fgets(str, 1000, f) != NULL) {
		strcat(S, str); //collect input into a string
	}
	//printf("%s\n",S);

	int array[matSize][matSize];
	int i = 0;
	int j = 0;
	int k = 0;
	char out[1000];
	
	while (S[k] != '\0') { //collect numbers into a matrix
		if ((S[k] == '\n') && (S[k+1]!='\n')) {	
			i++; 
			j=0;
		}
		else if ((S[k] != ' ') && (S[k] != '\n')){
			array[i][j] = S[k] - '0';
			j++;	
		}
		k++;	
	}
	
	printMat(array, matSize);
	
	//Need to change the c==0,2 and d==0,2,3 to automatically change depending on input size
	printf("FIX ME: print input file name\n");
	for (int c = 0; c<matSize; c++) {
		if (c==0)  {
			printf("-------------------------\n");
		}
		else if ((c==3) || (c==6) ) {
			printf("------------+------------\n");
		}
		for (int d=0; d<matSize; d++) {
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
	
	printf("array[0]: %p\n",array[0]);
	printf("size of array: %d\n", sizeof(array)/sizeof(array[0]));
	int x=is_row_valid(array[0]);
	printf("is row valid? %d\n",x);
	
	fclose(f);
}
