#include <stdio.h>

#define TEMPFILENAME "mytempfile.temp"

int return_my_menu_result();
void EnterFileNames(char* infile, char* outfile,int option);
int check_input_file(char* infile);
int PerformACopyInputToFileIfNeeded(char* tempfilename,int option);


int main(){
	FILE * input_file;
	FILE * output_file;
	FILE * temp_file;
	char input_filename[255];
	char output_filename[255];
	int selected_option = -1;
	while((selected_option=return_my_menu_result())!=5){
		system("cls");
		EnterFileNames(input_filename, output_filename,selected_option);
		PerformACopyInputToFileIfNeeded(TEMPFILENAME,selected_option);
	}
	return 0;

}

int return_my_menu_result(){
	int i;
	system("cls");
	printf("input your selection\n");
	printf("file to file 1\n");
	printf("file to screen 2\n");
	printf("keyboard to file 3\n");
	printf("keyboard to screen 4\n");
	printf("exit 5\n");
	
	scanf("%d",&i);
	if((i>=1)&&(i<=5)){
		return i;
	}else{
		return -1;
	}
}

int check_input_file(char* infile){
	int index = 0;
	while(infile[index]!='\0'){
		index++;
	}
	index--;

	if((infile[index]=='c')||(infile[index]=='C')){
		if(infile[index-1]=='.'){
			return 0;
		}
	}
	printf("the filename must ends with \".c\" or \".C\"\n");
	

	return -1;
}

void EnterFileNames(char* infile, char* outfile,int option){
	if((option == 1)||(option == 2)){
		do{
			printf("Enter the name of the input file!\n");
			scanf("%s",infile);
		}while(check_input_file(infile)!=0);
	}
	if((option == 1)||(option == 3)){
		printf("Enter the name of the output file!\n");
		scanf("%s",outfile);
	}
}

int PerformACopyInputToFileIfNeeded(char* tempfilename,int option){
	FILE* my_temp_file;
	char c;
	if((option == 3)||(option == 4)){
		my_temp_file = fopen(tempfilename,"w+");
		while((c = getchar())!=EOF){
			fputc(c,my_temp_file);
		}
		fclose(my_temp_file);
		return 0;
	}
	return -1;

}
