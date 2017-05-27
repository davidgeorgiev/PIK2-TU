#include <stdio.h>
#include <stdlib.h>
#define BINFILE "house.bin"
//show all prices
//pass h or a and print all in address
//id [int],type [char],area [float],price [float],size of address [int],address [string]

char** ReadFile(char** ArrayOfPointers,int* len,char* filename){
    FILE* fin = fopen(filename,"rb");
    int* tempint;
    float* tempfloat;
    char* tempchar;
    char* stringpointer;
    int alldone = 0;
	int i = 0;

    if(fin != NULL){
        while(alldone == 0){
            tempint = (int*)malloc(sizeof(int));
            if(fread(tempint,sizeof(int),1,fin)!=1){
                alldone = 1;
            }else{
                ArrayOfPointers = (char**)realloc(ArrayOfPointers,sizeof(void*)*(++(*len)));
                ArrayOfPointers[*len-1] = (char*)tempint;
                printf("\nindex %d\n",*(int*)ArrayOfPointers[*len-1]);
            }
            tempchar = (char*)malloc(1);
            if(fread(tempchar,1,1,fin)!=1){
                alldone = 1;
            }else{
                ArrayOfPointers = (char**)realloc(ArrayOfPointers,sizeof(void*)*(++(*len)));
                ArrayOfPointers[*len-1] = tempchar;
                printf("%c\n",*(char*)ArrayOfPointers[*len-1]);
            }
            tempfloat = (float*)malloc(4);
            if(fread(tempfloat,4,1,fin)!=1){
                alldone = 1;
            }else{
                ArrayOfPointers = (char**)realloc(ArrayOfPointers,sizeof(void*)*(++(*len)));
                ArrayOfPointers[*len-1] = (char*)tempfloat;
                printf("%f\n",*(float*)ArrayOfPointers[*len-1]);
            }
            tempfloat = (float*)malloc(4);
            if(fread(tempfloat,4,1,fin)!=1){
                alldone = 1;
            }else{
                ArrayOfPointers = (char**)realloc(ArrayOfPointers,sizeof(void*)*(++(*len)));
                ArrayOfPointers[*len-1] = (char*)tempfloat;
                printf("%f\n",*(float*)ArrayOfPointers[*len-1]);
            }
            tempint = (int*)malloc(sizeof(int));
            if(fread(tempint,sizeof(int),1,fin)!=1){
                alldone = 1;
            }else{
                ArrayOfPointers = (char**)realloc(ArrayOfPointers,sizeof(void*)*(++(*len)));
                ArrayOfPointers[*len-1] = (char*)tempint;
                printf("%d\n",*(int*)ArrayOfPointers[*len-1]);
            }
            stringpointer = (char*)malloc(*tempint);
            if(fread(stringpointer,1,*tempint,fin)!=*tempint){
                alldone = 1;
            }else{
                ArrayOfPointers = (char**)realloc(ArrayOfPointers,sizeof(void*)*(++(*len)));
                ArrayOfPointers[*len-1] = (char*)stringpointer;
				for(i = 0;i<*tempint;i++){
					printf("%c",*(char*)(ArrayOfPointers[*len-1]+i));
				}
				printf("\n");
            }
        }
		//printf("done %d\n",alldone);
        fclose(fin);
    }
	
    return ArrayOfPointers;
}

void PrintPrices(char** ArrayOfPointers,int* len){
    int i;
	int k = 0;
    printf("len %d\n",*len);
    for(i = 1;i<*len;i++){
		k++;
        //printf("%d\n",k);
        if(k==3){
            printf("price %f\n",(*(float*)ArrayOfPointers[i-1])*(*(float*)ArrayOfPointers[i]));
			k=-3;
        }
    }
}

void AppendToFile(char* filename){
	FILE* fp = fopen(filename,"ab");
	int i = 3;
	char c = 'h';
	float f1 = 4.3;
	float f2 = 3.3;
	int sizeofstring = 7;
	char name[30] = "nadejda";
	
	fwrite(&i,sizeof(int),1,fp);
	fwrite(&c,sizeof(char),1,fp);
	fwrite(&f1,sizeof(float),1,fp);
	fwrite(&f2,sizeof(float),1,fp);
	fwrite(&sizeofstring,sizeof(int),1,fp);
	fwrite(&name,sizeof(char),sizeofstring,fp);
	
	fclose(fp);
}

int main()
{
    char** ArrayOfPointers = NULL;
    int len = 0;
	
	//AppendToFile(BINFILE);
    ArrayOfPointers = ReadFile(ArrayOfPointers,&len,BINFILE);
    PrintPrices(ArrayOfPointers,&len);
	
	
	
    return 0;
}
