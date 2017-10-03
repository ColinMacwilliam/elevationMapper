#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct pgm {
	int rows;
	int cols;
	int **pixels;
} pgmPic;


int main(int argc, char*argv[]) {

int numRows = 0;
int numCols = 0;
int a = 0;


FILE* fp = fopen(argv[1], "r");

if (fp == NULL) {
	printf("Error: data file does not exist!\n");
	return -1;
}

fscanf(fp, "%d %d", &numRows, &numCols);


pgmPic *myPic = (pgmPic *) malloc (sizeof(pgmPic));
myPic->pixels = (int**)malloc(sizeof(int*) * numRows);
for (a=0; a<numRows; a++) {
	myPic->pixels[a] = (int*)malloc(sizeof(int) * numCols);
}

myPic->rows = numRows;
myPic->cols = numCols;

int i = 0;
int j = 0;


	for (i = 0; i<numRows; i++) {

		for (j = 0; j<numCols; j++) {
			fscanf(fp, "%d", &myPic->pixels[i][j]);
		}
	}

fclose(fp);


int max = myPic->pixels[0][0];
int min = myPic->pixels[0][0];


	for (i = 0; i<numRows; i++) {
		for (j = 0; j<numCols; j++) {
			if (myPic->pixels[i][j] > max) max=myPic->pixels[i][j];
		
			if (myPic->pixels[i][j] < min) min=myPic->pixels[i][j];
		}
	}


int range = max - min;

double multiplier;
multiplier = (double) 200/range;


	for (i = 0; i<numRows; i++) {
		for (j = 0; j<numCols; j++) {
			myPic->pixels[i][j] = (int)(round((myPic->pixels[i][j] - min) * multiplier));

myPic->pixels[i][j] = (255 - myPic->pixels[i][j]);

		}
	}


char* outFile = (char*)malloc(strlen(argv[1]) + 5);
strcpy(outFile, argv[1]);
strcat(outFile, ".pgm");

FILE* fpOut = fopen(outFile, "w");

fprintf(fpOut, "P2\n");
fprintf(fpOut, "%d\n", numCols);
fprintf(fpOut, "%d\n", numRows);
fprintf(fpOut, "255\n");

for (i = 0; i<numRows; i++) {
	for (j=0; j<numCols; j++) {
		fprintf(fpOut, "%d ", myPic->pixels[i][j]);
		}
	fprintf(fpOut, "\n");
}

fclose(fpOut);


if ((strcmp(argv[2], "S-N") != 0) && (strcmp(argv[2], "N-S") != 0) && (strcmp(argv[2], "W-E") != 0) && (strcmp(argv[2], "E-W") != 0)) {

printf("Error: choose a valid direction for the path.\n");
return -1;
}


if (strcmp(argv[2], "W-E") == 0) {

i = numRows/2;
		for (j = 0; j<numCols; j++) {

int n1 = myPic->pixels[i][j+1];
int n2 = 1;
int n3 = 1;
			
		if (i+1 > numRows) { n2 = 0;}
		if (i-1 < 0) {n3 = 0;}		


	if (n2!=0) 
	{
		n2 = myPic->pixels[i+1][j+1];
	}
	if (n3!=0) 
	{
		n3 = myPic->pixels[i-1][j+1];
	}

		myPic->pixels[i][j] = 0;
		
		if (n1>=n2 && n1>=n3) { continue;}
		if (n2>=n1 && n2>=n3) {if(n2==n1){continue;} i = i + 1; continue;}
		if (n3>=n1 && n3>=n2) {if(n3==n1){continue;} i = i - 1; continue;}	
			
		
		}
			
		
}


if (strcmp(argv[2], "E-W") == 0) {

i = numRows/2;

		for (j = numCols-1; j>=0; j--) {	
int n1 = 0;
int n2 = 1;
int n3 = 1;
		if (i+1 > numRows) {n2 = 0;}
		if (i-1 < 0) {n3 = 0;}
	
		n1 = myPic->pixels[i][j-1];
if (n2!=0){
		n2 = myPic->pixels[i+1][j-1];
}
if (n3!=0){
		n3 = myPic->pixels[i-1][j-1];	
}

		myPic->pixels[i][j]= 0;

		if (n1>=n2 && n1>=n3) { continue;}
		if (n2>=n1 && n2>=n3) { if (n2==n1){continue;} i = i + 1; continue;}
		if (n3>=n1 && n3>=n2) { if (n3==n1){continue;} i = i - 1; continue;}

		}

}

if (strcmp(argv[2], "N-S") == 0) {


j = numCols/2;

		for (i = 0; i<myPic->rows; i++) {
if (i == myPic->rows - 1) { myPic->pixels[i][j] = 0; continue;}

int n1 = 1;
int n2 = 1;
int n3 = 1;
 
n1 = myPic->pixels[i+1][j];
n2 = myPic->pixels[i+1][j-1];
n3 = myPic->pixels[i+1][j+1];	
		
		myPic->pixels[i][j] = 0;
				
		if (n1>=n2 && n1>=n3) { continue;}
		if (n2>=n1 && n2>=n3) { if (n2==n1){continue;} j = j - 1; continue;}
		if (n3>=n1 && n3>=n2) { if (n3==n1){continue;} j = j + 1; continue;}

		}

}

if (strcmp(argv[2], "S-N") == 0) {

j = numCols/2;


	for (i = numRows-1; i>=0; i--) {
if (i == 0) { myPic->pixels[i][j] = 0; break;}

int n1 = 0;
int n2 = 1;
int n3 = 1;

if (j+1 > numCols) { n2 = 0;}
if (j-1 < 0) { n3 = 0;} 

n1 = myPic->pixels[i-1][j];
if (n2!=0){
n2 = myPic->pixels[i-1][j+1];
}
if (n3!=0){
n3 = myPic->pixels[i-1][j-1];	
}
	
		myPic->pixels[i][j] = 0;

		if (n1>=n2 && n1>=n3) { continue;}
		if (n2>=n1 && n2>=n3) { if (n2==n1){continue;} j = j + 1; continue;}
		if (n3>=n1 && n3>=n2) { if (n3==n1){continue;} j = j - 1; continue;}
	}

}


char* trailFile = (char*)malloc(strlen(argv[1]) + 11);
strcpy(trailFile, argv[1]);
strcat(trailFile, "-trail.pgm");

FILE* trailOut = fopen(trailFile, "w");

fprintf(trailOut, "P2\n");
fprintf(trailOut, "%d\n", numCols);
fprintf(trailOut, "%d\n", numRows);
fprintf(trailOut, "255\n");


	for (i = 0; i < numRows; i++) {
		for (j=0; j<numCols; j++) {
			fprintf(trailOut, "%d ", myPic->pixels[i][j]);
			}
		fprintf(trailOut, "\n");
	}

fclose(trailOut);

















return 0;
}
