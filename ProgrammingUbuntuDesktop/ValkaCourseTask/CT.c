#include <stdio.h>
#include <stdlib.h>
//DEFINING HEIGHT INTERVAL
#define MINHEIGHT 0
#define MAXHEIGHT 100
//DEFINING TYPES
#define VEGETATION 0
#define WASTELAND 1
#define WATER 2
#define ROAD 3
#define BUILDING 4
//DEFINING FILES
#define BINFILENAME "bin.bin"

typedef struct Block{
	int type;
	int height;
	float attendance;
	struct Block* next;
}Block;
void CreateMap(Block* head,int x,int y);//x and y are the size of the map
int GetRandomVal(int min,int max);//including min and max
void PushNewBlock(Block* head);
void PrintMapHeight(Block* head,int x,int y);
void PrintMapTypes(Block* head,int x,int y);
void SaveToFile(Block* head,int x,int y,char* binfilename);
void TryToLoadFromFileOrCreateNewMapIfDoesntExists(Block* head,int* x,int* y,char* binfilename);
Block* GetBlockByCoordinates(Block* head, int xcoord, int ycoord,int xsize,int ysize);

int main(){
	srand (time(NULL));//initialize random seed
	Block* head = (Block*)malloc(sizeof(Block));
	int MapSize[2];
	MapSize[0] = 10;
	MapSize[1] = 10;
	
	TryToLoadFromFileOrCreateNewMapIfDoesntExists(head,&MapSize[0],&MapSize[1],BINFILENAME);
	PrintMapHeight(head,MapSize[0],MapSize[1]);
	PrintMapTypes(head,MapSize[0],MapSize[1]);
	SaveToFile(head,MapSize[0],MapSize[1],BINFILENAME);
	
	//BEGIN EXAMPLE OF USING GET BLOCK BY COORDINATES
		int neededx = 5;
		int neededy = 4;
		Block* NeededBlock = GetBlockByCoordinates(head, neededx, neededy,MapSize[0],MapSize[1]);
		printf("\ntype of block on x=%d and y=%d is %d\n",neededx,neededy,NeededBlock->type);
	//END OF EXAMPLE OF USING GET BLOCK BY COORDINATES
	
	return 0;
}

void CreateMap(Block* head,int x,int y){
	int NumberOfBlocks = x*y;
	int i;
	for(i = 0;i<NumberOfBlocks;i++){
		PushNewBlock(head);
	}
}
int GetRandomVal(int min,int max){
	return rand() % (max + 1 - min) + min;
}
void PushNewBlock(Block* head){
	Block* temp = head;
	while(temp->next!=NULL){temp = temp->next;}
	temp->next = (Block*)malloc(sizeof(Block));
	
	temp = temp->next;
	temp->height = GetRandomVal(MINHEIGHT,MAXHEIGHT);
	temp->type = GetRandomVal(VEGETATION,BUILDING);
	temp->attendance = 0;
	temp->next = NULL;
}

void PrintMapHeight(Block* head,int x,int y){
	printf("PRINTING HEIGHT MAP\n");
	Block* temp = head;
	int k = 0;
	while(temp->next!=NULL){
		k++;
		temp = temp->next;
		printf("%d\t",temp->height);
		if(k==x){
			k = 0;
			printf("\n");
		}
	}
}
void PrintMapTypes(Block* head,int x,int y){
	printf("PRINTING TYPES MAP\n");
	Block* temp = head;
	int k = 0;
	while(temp->next!=NULL){
		k++;
		temp = temp->next;
		printf("%d\t",temp->type);
		if(k==x){
			k = 0;
			printf("\n");
		}
	}
}

void SaveToFile(Block* head,int x,int y,char* binfilename){
	FILE* fp = fopen(binfilename,"wb");
	Block* temp = head;
	fwrite(&x,sizeof(int),1,fp);
	fwrite(&y,sizeof(int),1,fp);
	while(temp->next!=NULL){
		temp = temp->next;
		fwrite(temp,sizeof(Block),1,fp);
	}
	fclose(fp);
}

void TryToLoadFromFileOrCreateNewMapIfDoesntExists(Block* head,int* x,int* y,char* binfilename){
	FILE* fp = fopen(binfilename,"rb");
	if(fp != NULL){
		fread(x,sizeof(int),1,fp);
		fread(y,sizeof(int),1,fp);
		Block* temp = head;
		int i = 0;
		while(i < ((*x)*(*y))){
			i++;
			temp->next = (Block*)malloc(sizeof(Block));
			temp = temp->next;
			fread(temp,sizeof(Block),1,fp);
			temp->next = NULL;
		}
		
		fclose(fp);
	}else{
		CreateMap(head,*x,*y);
	}
}

Block* GetBlockByCoordinates(Block* head, int xcoord, int ycoord,int xsize,int ysize){
	if(((xcoord > xsize)||(ycoord > ysize))&&((xcoord <= 0)||(ycoord <= 0))){return NULL;}
	Block* temp = head;
	int xcount = 0;
	int ycount = 0;
	while(temp->next != NULL){
		temp = temp->next;
		xcount++;
		if(xcount == xsize){
			xcount = 0;
			ycount++;
		}
		if((xcount == xcoord)&&(ycount == ycoord)){
			return temp;
		}
	}	
}
