#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

//=============================================================
//INITIALIZATION PART
//=============================================================
typedef struct{
	char nomenclature_number[13];
	char name[51];
	float price;
	int amount;
	char expiration_date[11];
	struct Goods* next;
}Goods;
Goods head;
char current_opened_storage_filename[30];
//=============================================================

//=============================================================
//FUNCTIONS DECLARATIONS
//=============================================================
void INIT_HEAD();
void Clear_current_opened_storage_filename();
void Enter_current_opened_storage_filename();
void Show_existing_storages();
void Create_a_new_storage();
void Open_a_storage_by_name();
void Add_goods_in_opened_storage();
void Show_all_goods_in_opened_storage();
void Change_amount_of_goods_by_nomenclature_number_in_opened_storage();
void Show_all_expired_goods_in_opened_storage();
void Show_info_for_goods_by_nomenclature_number_in_opened_storage();
void Run_an_option(int option);
int menu();
int check_if_file_is_bin(char* filename);
void Clear_list();
int Check_if_a_storage_is_opened();
void Add_goods();
void Save_current_list_to_file();
void Print_goods_info_by_address(Goods* goods);
int Count_goods_in_memory();
void Load_goods_from_file();
void Delete_goods_by_address(Goods* goods);
Goods* Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number);
char* Return_reversed_date(char* date);
//=============================================================


int main(){
	INIT_HEAD();
	Clear_current_opened_storage_filename();
	int option;
	char c;
	while(1){
		option = menu();
		if(option==9){
			printf("exiting program...\nBYE! :)\n");
			break;
		}else{
			Run_an_option(option);
		}
		printf("\n--->press ENTER to show menu again<---\n");
		scanf("%c",&c);
		scanf("%c",&c);
	}
	return 0;
}

//=============================================================
//PRIMARY FUNCTIONS PART
//=============================================================
void Show_existing_storages(){
	int if_exists_any_storage = 0;
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL){
		//fprintf(stdout, "Current working dir: %s\n", cwd);
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir (cwd)) != NULL) {
			/* print all the files and directories within directory */
			printf("\n\n\t==========================================\n");
			printf("\tNOW PRINTING STORAGES\n");
			printf("\t==========================================\n");
			while ((ent = readdir (dir)) != NULL) {
				if(check_if_file_is_bin(ent->d_name)){
					printf ("\t  %s\b\b\b\b    \n", ent->d_name);
					if_exists_any_storage = 1;
				}
			}
			closedir (dir);
			if(!if_exists_any_storage){
				printf("\t  No storages found!\n\t  You must create some in menu option 2\n");
			}
			printf("\t==========================================\n");
		} else {
			/* could not open directory */
			perror ("");
		}
	}
}
void Create_a_new_storage(){
	printf("\n\n\t==========================================\n");
	printf("\tNOW CREATING A NEW STORAGE\n");
	printf("\t==========================================\n");
	char filename[1024];
	int i;
	FILE* fp;
	char c = 'y';
	int number_of_goods = 0;
	while(1){
		c = 'y';
		printf("\t  Enter the name of the new storage: ");
		scanf(" %s",filename);
		i = strlen(filename);
		filename[i] = '.';i++;
		filename[i] = 'b';i++;
		filename[i] = 'i';i++;
		filename[i] = 'n';i++;
		filename[i] = '\0';i++;
		if((fp = fopen(filename,"r"))!=NULL){
			fclose(fp);
			printf("\t  This storage already exists. Do you want to replace it? y/n: ");
			scanf("%c",&c);
			scanf("%c",&c);
		}
		if(c == 'y'){
			printf("\t  The storage \"%s\b\b\b\b\" was created\n",filename);
			fp = fopen(filename,"wb");
			fwrite(&number_of_goods,sizeof(int),1,fp);
			fclose(fp);
			break;
		}
	}
	printf("\t==========================================\n");
}
void Open_a_storage_by_name(){
	printf("\n\n\t==========================================\n");
	printf("\tNOW OPENING A STORAGE\n");
	printf("\t==========================================\n");
	Enter_current_opened_storage_filename();
	FILE* fp = fopen(current_opened_storage_filename,"r");
	if(fp != NULL){
		printf("\tStorage \"%s\b\b\b\b\" is successfuly opened\n",current_opened_storage_filename);
		fclose(fp);
		Load_goods_from_file();
	}else{
		printf("\tStorage \"%s\b\b\b\b\" not exists\n",current_opened_storage_filename);
		current_opened_storage_filename[0]='\0';
	}
	printf("\t==========================================\n");
}
void Add_goods_in_opened_storage(){
	printf("\n\n\t==========================================\n");
	printf("\tNOW ADDING GOODS");
	if(Check_if_a_storage_is_opened()){
		printf(" TO \"%s\b\b\b\b\" STORAGE\n",current_opened_storage_filename);
	}else{
		printf("\n");
	}
	printf("\t==========================================\n");
	if(!Check_if_a_storage_is_opened()){
		printf("\tFirst you have to open a storage from menu!\n");
		printf("\t==========================================\n");
		return;
	}else{
		Add_goods();
		Save_current_list_to_file();
	}
	printf("\t==========================================\n");
}
void Show_all_goods_in_opened_storage(){
	int if_anything_printed = 0;
	printf("\n\n\t==========================================\n");
	printf("\tNOW PRINTING GOODS");
	if(Check_if_a_storage_is_opened()){
		printf(" FROM \"%s\b\b\b\b\" STORAGE\n",current_opened_storage_filename);
	}else{
		printf("\n");
	}
	printf("\t==========================================\n");
	if(!Check_if_a_storage_is_opened()){
		printf("\tFirst you have to open a storage from menu!\n");
		printf("\t==========================================\n");
		return;
	}else{
		Goods* temp = &head;
		while(temp->next != NULL){
			temp = (Goods*)(temp->next);
			printf("\n");
			Print_goods_info_by_address(temp);
			if_anything_printed = 1;
		}
	}
	if(!if_anything_printed){
		printf("\t  No goods in this storage.\n\t  You can add some from option 4 in menu\n");
	}
	printf("\t==========================================\n");

	
	
}
void Change_amount_of_goods_by_nomenclature_number_in_opened_storage(){
	char nomenclature_number[13];
	Goods* Address_to_goods_for_change;
	printf("\n\n\t==========================================\n");
	printf("\tNOW CHANGING AMOUNT OF GOODS BY NOMENCLATURE\n\tNUMBER FROM OPENED STORAGE\n");
	printf("\t==========================================\n");
	if(!Check_if_a_storage_is_opened()){
		printf("\tFirst you have to open a storage from menu!\n");
		printf("\t==========================================\n");
		return;
	}else{
		printf("\t  Enter nomenclature number to change goods amount: ");
		scanf(" %s",nomenclature_number);
		Address_to_goods_for_change = Return_address_by_nomenclature_number_in_opened_storage(nomenclature_number);
		if(Address_to_goods_for_change!=NULL){
			Print_goods_info_by_address(Address_to_goods_for_change);
			printf("\t  Enter new amount: ");
			scanf(" %d",&(Address_to_goods_for_change->amount));
			if(Address_to_goods_for_change->amount==0){
				Delete_goods_by_address(Address_to_goods_for_change);
				Address_to_goods_for_change=NULL;
			}
			Save_current_list_to_file();
		}else{
			printf("\t  No such nomenclature number!\n");
		}
	}
	printf("\t==========================================\n");
}
void Show_all_expired_goods_in_opened_storage(){
	char current_date[11];
	char* reversed_current_date;
	char* reversed_expiration_date;
	int if_exists_expired = 0;
	printf("\n\n\t==========================================\n");
	printf("\tNOW PRINTING EXPIRED GOODS \n\tFROM OPENED STORAGE\n");
	printf("\t==========================================\n");
	if(!Check_if_a_storage_is_opened()){
		printf("\tFirst you have to open a storage from menu!\n");
		printf("\t==========================================\n");
		return;
	}else{
		printf("\t  Enter the date of today (for example 01.01.2017): ");
		scanf(" %s",current_date);
		reversed_current_date = Return_reversed_date(current_date);
		Goods* temp = &head;
		while(temp->next != NULL){
			temp = (Goods*)(temp->next);
			reversed_expiration_date = Return_reversed_date(temp->expiration_date);
			if(strcmp(reversed_current_date,reversed_expiration_date)>0){
				free(reversed_expiration_date);
				printf("\n");
				Print_goods_info_by_address(temp);
				if_exists_expired = 1;
			}
		}
		if(!if_exists_expired){
			printf("\t  No expired goods found\n");
		}
		free(reversed_current_date);
	}
	printf("\t==========================================\n");
}
void Show_info_for_goods_by_nomenclature_number_in_opened_storage(){
	char Nomenclature_number[13];
	int if_something_found = 0;
	printf("\n\n\t==========================================\n");
	printf("\tNOW PRINTING INFO BY NOMENCLATURE NUMBER\n");
	printf("\t==========================================\n");
	if(!Check_if_a_storage_is_opened()){
		printf("\tFirst you have to open a storage from menu!\n");
		printf("\t==========================================\n");
		return;
	}else{
		printf("\t  Enter nomenclature number to search: ");
		scanf(" %s",Nomenclature_number);
		printf("\t  ------------------------------------\n");
		printf("\t  now searching...\n");
		printf("\t  ------------------------------------\n");
		Goods* temp = &head;
		while(temp->next != NULL){
			temp = (Goods*)(temp->next);
			if(strcmp(Nomenclature_number,temp->nomenclature_number)==0){
				if_something_found = 1;
				Print_goods_info_by_address(temp);
			}
		}
		if(!if_something_found){
			printf("\t  no such nomenclature number\n");
		}
	}
	printf("\t==========================================\n");
}
//=============================================================


//=============================================================
//SECONDARY FUNCTIONS PART
//=============================================================
char* Return_reversed_date(char* date){
	char* reversed_date = (char*)malloc(sizeof(char)*11);
	reversed_date[8] = date[0];
	reversed_date[9] = date[1];
	reversed_date[7] = date[2];
	reversed_date[5] = date[3];
	reversed_date[6] = date[4];
	reversed_date[4] = date[5];
	reversed_date[0] = date[6];
	reversed_date[1] = date[7];
	reversed_date[2] = date[8];
	reversed_date[3] = date[9];
	reversed_date[10] = '\0';
	return reversed_date;
}
Goods* Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number){
	int if_something_found = 0;
	Goods* temp = &head;
	while(temp->next != NULL){
		temp = (Goods*)(temp->next);
		if(strcmp(nomenclature_number,temp->nomenclature_number)==0){
			if_something_found = 1;
			return temp;
		}
	}
	if(!if_something_found){
		return NULL;
	}
}
void Delete_goods_by_address(Goods* goods){
	Goods* temp = &head;
	Goods* prev;
	while(temp->next != NULL){
		prev = temp;
		temp = (Goods*)(temp->next);
		if(temp==goods){
			prev->next = temp->next;
			printf("\t  Deleting goods because the amount is 0...\n");
			//Print_goods_info_by_address(temp);
			free(temp);
		}
	}
}
void Load_goods_from_file(){
	if(!Check_if_a_storage_is_opened()){return;}
	Clear_list();
	int i = 0;
	int number_of_goods;
	Goods* temp = &head;
	FILE* fp = fopen(current_opened_storage_filename,"rb");
	if(fp!=NULL){
		fread(&number_of_goods,sizeof(int),1,fp);
		//printf("read %d\n",number_of_goods);
		while(i < number_of_goods){
			temp->next = (Goods*)malloc(sizeof(Goods));
			temp = (Goods*)(temp->next);
			fread(temp,sizeof(Goods),1,fp);
			//printf("read:\n");
			//Print_goods_info_by_address(temp);
			temp->next = NULL;
			i++;
		}
		fclose(fp);
	}
}
int Count_goods_in_memory(){
	Goods* temp = &head;
	int i = 0;
	while(temp->next != NULL){
		temp = (Goods*)(temp->next);
		i++;
	}
	return i;
}
void Clear_list(){
	Goods* temp = &head;
	Goods* temp_next;
	int if_null = 1;
	if(head.next!=NULL){
		temp = (Goods*)(temp->next);
		if_null = 0;
	}
	while(temp->next != NULL){
		temp_next = (Goods*)(temp->next);
		//Print_goods_info_by_address(temp);
		free(temp);
		temp = temp_next;
	}
	if(!if_null){
		//Print_goods_info_by_address(temp);
		free(temp);
	}
	INIT_HEAD();
}
void Add_goods(){
	char temp_nom_num[13];
	Goods* temp = &head;
	while(temp->next != NULL){temp = (Goods*)(temp->next);}
	temp->next = (Goods*)malloc(sizeof(Goods));
	temp = (Goods*)(temp->next);
	temp->next = NULL;
	while(1){
		printf("\t  Enter nomenclature number (12 digits number): ");
		scanf(" %s",temp_nom_num);
		if(Return_address_by_nomenclature_number_in_opened_storage(temp_nom_num)!=NULL){
			printf("\t  Sorry this nomenclature number is already used try again!\n");
		}else{
			strcpy(temp->nomenclature_number,temp_nom_num);
			break;
		}
	}
	printf("\t  Enter name (for example: potatoes): ");
	scanf(" %s",temp->name);
	printf("\t  Enter price (for example: 5.25): ");
	scanf(" %f",&(temp->price));
	printf("\t  Enter amount (for example: 5): ");
	scanf(" %d",&(temp->amount));
	printf("\t  Enter expiration date (DD.MM.YYYY): ");
	scanf(" %s",temp->expiration_date);
}
void Print_goods_info_by_address(Goods* goods){
	printf("\t  Nomenclature number: %s\n",goods->nomenclature_number);
	printf("\t  Name: %s\n",goods->name);
	printf("\t  Price: %f\n",goods->price);
	printf("\t  Amount: %d\n",goods->amount);
	printf("\t  Expiration date: %s\n",goods->expiration_date);
}
void Save_current_list_to_file(){
	FILE* fp = fopen(current_opened_storage_filename,"wb");
	int number_of_goods = Count_goods_in_memory();
	if(fp!=NULL){
		//printf("writing %d to file\n",number_of_goods);
		fwrite(&number_of_goods,sizeof(int),1,fp);
		Goods* temp = &head;
		while(temp->next != NULL){
			temp = (Goods*)(temp->next);
			//printf("writing this:\n");
			//Print_goods_info_by_address(temp);
			fwrite(temp,sizeof(Goods),1,fp);
		}
		fclose(fp);
	}
}
int Check_if_a_storage_is_opened(){
	if(current_opened_storage_filename[0] == '\0'){
		return 0;
	}else{
		return 1;
	}
}
void INIT_HEAD(){
	head.next = NULL;
}
void Clear_current_opened_storage_filename(){
	current_opened_storage_filename[0] = '\0';
}
void Enter_current_opened_storage_filename(){
	printf("\tPlease enter the name of a storage to open: ");
	scanf("%s",current_opened_storage_filename);
	int i = strlen(current_opened_storage_filename);
	current_opened_storage_filename[i] = '.';i++;
	current_opened_storage_filename[i] = 'b';i++;
	current_opened_storage_filename[i] = 'i';i++;
	current_opened_storage_filename[i] = 'n';i++;
	current_opened_storage_filename[i] = '\0';
}
int check_if_file_is_bin(char* filename){
	int if_bin = 1;
	int i = 0;
	while(filename[i]!='\0'){
		i++;
	}
	i--;
	if(filename[i]!='n')
		if_bin = 0;
	i--;
	if(filename[i]!='i')
		if_bin = 0;
	i--;
	if(filename[i]!='b')
		if_bin = 0;
	i--;
	if(filename[i]!='.')
		if_bin = 0;
	return if_bin;
}

void Run_an_option(int option){
	switch(option){
		case 1:Show_existing_storages();break;
		case 2:Create_a_new_storage();break;
		case 3:Open_a_storage_by_name();break;
		case 4:Add_goods_in_opened_storage();break;
		case 5:Show_all_goods_in_opened_storage();break;
		case 6:Change_amount_of_goods_by_nomenclature_number_in_opened_storage();break;
		case 7:Show_all_expired_goods_in_opened_storage();break;
		case 8:Show_info_for_goods_by_nomenclature_number_in_opened_storage();break;
	}
}

int menu(){
	printf("\n\n==========================================\n");
	printf("MENU\n");
	printf("==========================================\n");
	printf("OPTIONS FOR STORAGES\n");
	printf("------------------------------------------\n");
	printf("  1.Show existing storages\n");
	printf("  2.Create a new storage\n");
	printf("  3.Open a storage by name\n");
	printf("------------------------------------------\n");
	printf("OPTIONS FOR GOODS\n");
	printf("------------------------------------------\n");
	printf("  4.Add goods in opened storage\n");
	printf("  5.Show all goods in opened storage\n");
	printf("  6.Change amount of goods by nomenclature number in opened storage\n");
	printf("  7.Show all expired goods in opened storage\n");
	printf("  8.Show info for goods by nomenclature number in opened storage\n");
	printf("------------------------------------------\n");
	printf("OTHER OPTIONS\n");
	printf("------------------------------------------\n");
	printf("  9.EXIT\n");
	printf("==========================================\n");
	int option;
	printf("ENTER AN OPTION: ");
	scanf(" %d",&option);
	if(!((option<=9)&&(option>=1))){
		option = -1;
	}
	return option;
}
//=============================================================
