#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear printf("\033[H\033[J")

int checkiffirst = 1;

char* inputNameforWritingInTheBinaryFile();
void openBinaryFileWritesData(FILE *fp, int* counter, char* name, int* number_of_chars);
 
void printingDataStoredOnBinFile(char* all_names,int* fac_numberV2, double* EGNV2, float* AvarageMarkV2, int* how_many_records_ridden
, char **array_chars_pointers);
 
float avarageMarkofTheGroup(float sum_for_avarage_mark_of_the_group_function, int* how_many_records_ridden, float* AvarageMarkV2);
 
 
int main(){
    FILE *fp;
    int* counter;
    int* how_many_records_ridden;
    int* number_of_chars;
    int tempCHARS=0;
    number_of_chars = &tempCHARS;
    int TemporaryMemory=0;
    int TemporaryMemoryB=0;
    counter = &TemporaryMemory;
    how_many_records_ridden = &TemporaryMemoryB;
    int temp;
    int* fac_numberV2;
    double* EGNV2;
    int* SizeOfName;
    float* AvarageMarkV2;
    float sum_for_avarage_mark_of_the_group_function = 0;
	char* name = NULL;
 
 
    openBinaryFileWritesData(fp, counter, name, number_of_chars);
 
    fac_numberV2 = (int*) malloc(sizeof(int));
    if(fac_numberV2 == NULL){
            printf("error50");
            exit(50);
    }
   
    EGNV2 = (double *) malloc(8);
    if(EGNV2 == NULL){
        printf("error50");
        exit(50);
    }
       
    AvarageMarkV2 = (float*) malloc(4);
    if(AvarageMarkV2 == NULL){
        printf("error50");
        exit(50);
    }  
   
    fp = fopen("samba.bin","rb");
    if (fp == NULL){
        printf("\nError with openning samba.bin for reading That's right\n");
        exit(5);
    }
    int n,i=0;
   
    int reading_last_four_bytes;
    int Counter_For_Ultimate_Function=1;
    int size_of_string_wich_we_read_from_bfile=0;
   
    char **array_chars_pointers;
    array_chars_pointers = (char **) malloc(1);
 	
 	char* all_names = NULL;
 	int sizeof_all_names = 0;
 	int index_of_all_names = 0;
    while(1){
    	sizeof_all_names += sizeof(int);
    	all_names = (char*)realloc(all_names,sizeof_all_names);
    	if (fread(all_names+index_of_all_names , sizeof(int) , 1 , fp) != 1){
            printf("Error reading name from file  \n");
            break;
        }
        sizeof_all_names += *(int*)(all_names+index_of_all_names);
    	all_names = (char*)realloc(all_names,sizeof_all_names);
    	index_of_all_names += sizeof(int);
        if (fread(all_names+index_of_all_names , 1 , *(int*)(all_names+index_of_all_names-sizeof(int)) , fp) != *(int*)(all_names+index_of_all_names-sizeof(int))){
            printf("Error reading name from file  \n");
            
            break;
        }
        index_of_all_names += *(int*)(all_names+index_of_all_names-sizeof(int));
    
        if (fread(&fac_numberV2[i] , sizeof(int) , 1 , fp) != 1){
            printf("This is the data from the binary file  \n");
            break;
        }
       
        if (fread(&EGNV2[i], 8 , 1 , fp) != 1){
            printf("Error with reading EGN in the binary file \n");
            exit(7);
        }
       
       
        if (fread(&AvarageMarkV2[i], 4 , 1 , fp) != 1){
            printf("Error with reading Avarage Marks in the binary file \n");
            exit(8);
        }
    
        i++;
        *how_many_records_ridden=i;
        
        Counter_For_Ultimate_Function++;
       
        fac_numberV2 = (int*) realloc(fac_numberV2, sizeof(int) * (i+2));
        if(fac_numberV2 == NULL){
            printf("Error 11");
            exit(-10);
        }
        EGNV2 = (double *) realloc(EGNV2, 8 * (i+2));
        if(EGNV2 == NULL){
            printf("Error 12");
            exit(-11);
        }      
        AvarageMarkV2 = (float*) realloc(AvarageMarkV2, 4 * (i+2));
       
        if(AvarageMarkV2 == NULL){
            printf("Error 13");
            exit(-12);
        }      
       
        array_chars_pointers = (char **) realloc(array_chars_pointers,Counter_For_Ultimate_Function);
    }
    fclose(fp);
    clear;
    printingDataStoredOnBinFile(all_names,fac_numberV2, EGNV2, AvarageMarkV2, how_many_records_ridden, array_chars_pointers);
   
   
    return 0;
}
 
void openBinaryFileWritesData(FILE *fp, int* counter,  char* name, int* number_of_chars){
    int flag_state_end_of_bin_file;
    int TEMPA, STOP;
    double TEMPB;
    float TEMPC;
 
    fp = fopen("samba.bin","wb");
    if (fp == NULL){
        printf("Error with the openning of the file samba.bin for writing ");
        exit(1);
    }
    int j,n;
    char* input_text;
    while(1){
        (*counter)++;
   
        printf("\nRecord number %d : \n",*counter);
        
        printf("\nenter name: \n");
        name = inputNameforWritingInTheBinaryFile();
        
        if (fwrite(name , 1 , *(int*)name+sizeof(int) , fp) != *(int*)name+sizeof(int)){
            printf("Error with recording fac_Number in the binary file \n");
            exit(2);
        }
        
        printf("Enter facultetniq number \t");
        scanf("%d",&TEMPA);
       
        if (fwrite(&TEMPA , sizeof(int) , 1 , fp) != 1){
            printf("Error with recording fac_Number in the binary file \n");
            exit(2);
        }
       
        printf("Enter egn of the student\t");
        scanf("%lf",&TEMPB);
       
       
        if (fwrite(&TEMPB , 8 , 1 , fp) != 1){
            printf("Error with recording EGN in the binary file \n");
            exit(3);
        }
       
       
        printf("Enter avarage mark of the student ");
        scanf("%f",&TEMPC);
       
        if (fwrite(&TEMPC , 4 , 1 , fp) != 1){
            printf("Error with recording Avarage Marks in the binary file \n");
            exit(4);
        }
       
        printf("\nDo you want to add more records? \n If yes, enter 1, if not enter 0\t");
        scanf("%d",&STOP);
       
        if (STOP == 0){
            flag_state_end_of_bin_file = 0;
       
            printf("\n%d records succesful writen in the database\n",*counter);
 
			break;
        }
		flag_state_end_of_bin_file=1;
    }
    fclose(fp);
}
 
void printingDataStoredOnBinFile(char* all_names,int* fac_numberV2, double* EGNV2, float* AvarageMarkV2, int* how_many_records_ridden
, char **array_chars_pointers){
 	int current_name_index = 0;
 	int current_name_size = 0;
    int i; 
    int k;
    float sum_for_avarage_mark_of_the_group_function = 0;
    printf("name\t");
    printf("fac Number\t");
    printf("EGN\t");
    printf("\tAvarage mark\n");
 
    for(i=0; i<(*how_many_records_ridden) ;i++){
    	current_name_size = *(int*)(all_names+current_name_index);
    	current_name_index+=sizeof(int);
    	for(k = 0;k < current_name_size; k++){
    		printf("%c",*(all_names+current_name_index+k));
    	}
    	current_name_index+=current_name_size;
    	printf("\t");
        printf("%d\t",fac_numberV2[i]);
        printf("%.0lf\t",EGNV2[i]);
        printf("%.2f\n",AvarageMarkV2[i]);
    }
   
    printf("There are %d students recorded in the binary file\n",*how_many_records_ridden);
    printf("The avarage mark of the group is: ");
    printf("%.2f\n", avarageMarkofTheGroup(sum_for_avarage_mark_of_the_group_function, how_many_records_ridden, AvarageMarkV2));
   
       
    free(fac_numberV2);
    free(EGNV2);
    free(AvarageMarkV2);
}
 
char* inputNameforWritingInTheBinaryFile(){
	int i=sizeof(int);
	char* input_text;
    input_text = (char *) malloc(sizeof(int));
    
    char ch;
    if(checkiffirst == 1){
    	checkiffirst = 0;
    }else{
    	getchar();
    }
    while((ch = fgetc(stdin)) != '\n'){
        input_text = (char *) realloc(input_text,(++i));
        input_text[i-1]=ch;
    }
    *(int*)input_text = i-sizeof(int);
    
   
    //printf("\nproverka na stringa\n%s\nproverka na stringa\n",input_text);
   
    return input_text;
 
 
 
}
 
float avarageMarkofTheGroup(float sum_for_avarage_mark_of_the_group_function, int* how_many_records_ridden, float* AvarageMarkV2){
    int i;
    sum_for_avarage_mark_of_the_group_function = 0;
   
    if ( *how_many_records_ridden == 0 ){
        return 0;
    }
   
    for( i = 0; i <  *how_many_records_ridden ; i++ ){
        sum_for_avarage_mark_of_the_group_function += AvarageMarkV2[i];
    }
   
    return (sum_for_avarage_mark_of_the_group_function / ((float)*how_many_records_ridden));
}
 
 
/*
 
exit(1) -> Openning file for writing error
exit(2) -> Error writing int data in binary file
exit(3) -> Error writing long int data in binary file
exit(4) -> Error writing float data in binary file
exit(5) -> Openning file for reading error
exit(6) -> Error reading int data from binary file
exit(7) -> Error reading long int data in binary file
exit(8) -> Error reading float data in binary file
 
*/


