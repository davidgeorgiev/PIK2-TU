#include <stdio.h>
#define num_rows 6
#define num_columns 6
int main(){
	int box[num_rows][num_columns];
	int row, column;

	for(row = 0; row<num_rows; row++){
		for(column = 0; column<num_columns; column++){
			box[row][column] = column + (row*num_columns);
		}
	}
	for(row=0;row<num_rows;row++){
		for(column = 0; column<num_columns; column++){
			printf("%d\t",box[column][row]);
		}
		printf("\n");
	}
	return 0;
}
