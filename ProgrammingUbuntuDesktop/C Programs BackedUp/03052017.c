#include <stdio.h>
#include <stdlib.h>

typedef struct List{
	int id;
	struct List* next;
}List;

void PushBack(List* head,int i){
	List* temp = head;
	while(temp->next!=NULL){temp=temp->next;}
	temp->next = (List*)malloc(sizeof(List));
	temp->next->id = i;
	temp = temp->next;
	temp->next = NULL;
}

void PrintList(List* head){
	List* temp = head;
	//printf("PRINTING LIST\n");
	while(temp->next!=NULL){
		temp = temp->next;
		printf("%d,",temp->id);
		
	}
	printf("\n\n");
}

int CountElements(List* head){
	
	int size = 0;
	List* temp = head;
	while(temp->next!=NULL){
		temp = temp->next;
		size++;
	}
	return size;
}



void ReverseList(List* head,int size){
	printf("\tREVERSING\n");
	int i;
	List* curr;
	List* temp1;
	List* temp2;
	int k = 1;
	int realsize = size;
	for(i = 0;i<realsize;i++){
		printf("\n");
		curr = head;
		while(k<size){
			temp1 = curr;
			curr = temp1->next;
			temp2 = curr->next->next;
			curr->next->next = curr;
			temp1->next = curr->next;
			curr->next = temp2;
			curr = temp1->next;
			printf("\t");
			PrintList(head);
			k++;
		}
		size--;
		k=1;
	}
}

int main(){
	List* head = (List*)malloc(sizeof(List));
	head->next = NULL;
	int number = 10;
	int i = 0;
	while(i<number){
		PushBack(head,i);
		i++;
	}
	printf("Size is: %d\n",CountElements(head));
	printf("PRINTING LIST\n");
	PrintList(head);
	ReverseList(head,CountElements(head));
	PrintList(head);
	
	return 0;
}
