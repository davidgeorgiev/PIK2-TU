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
/*INIT_HEAD() - функция, която насочва началния елемент от списъка да сочи
към NULL, не получава параметри, защото работи с глобалния обект - head
*/void INIT_HEAD();

/*Clear_current_opened_storage_filename() - функция, която изчиства името на
текущият отворен склад, задавайки символът на нулев иднекс да бъде равен
на терминиращ знак, не получава параметри, защото работи с глобален
масив от символи - current_opened_storage_filename[30]
*/void Clear_current_opened_storage_filename();

/*Enter_current_opened_storage_filename() - функция, която изисква от
потребителя да въведе име на склад и го задава като съдържание на глобалния
масив - current_opened_storage_filename[30], добавяйки .bin накрая на името
за улеснение при отваряне на бинарния файл в бъдеще
*/void Enter_current_opened_storage_filename();

/*Show_existing_storages() - функция обхождаща директорията, в която се намира
текущата изпълнима програма и извежда на екрана имената на всички файлове
с разширение .bin (имената на складовете) ако са създадени складове
*/void Show_existing_storages();

/*Create_a_new_storage() - функция за създаване на нов склад. Функцията
изисква от потребителя да въведе име на склада и създава бинарен файл с
въведеното от потребителя име (функцията проверява за дублиране и пита
потребителя дали иска да замени съществуващия файл ако има дублиране)
*/void Create_a_new_storage();

/*Open_a_storage_by_name() - Функцията извиква по-горе описаната -
Enter_current_opened_storage_filename() функция и проверява дали
съществува такъв бинарен файл, ако не съществува извежда съобщение за
грешка и извиква функцията - Clear_current_opened_storage_filename()
*/void Open_a_storage_by_name();

/*Add_goods_in_opened_storage() - Функцията проверява дали е отворен склад,
ако е отворен склад извиква функцията за добавяне на стока към списъка -
Add_goods(), след което запазва списъка в бинарния файл с името на отворения
склад извиквайки функцията - Save_current_list_to_file(). Ако не е отворен
склад извежда съобщение за грешка подканващо потребителя да отвори склад
*/void Add_goods_in_opened_storage();

/*Show_all_goods_in_opened_storage() - Функцията проверява дали е отворен склад,
ако е отворен склад обхожда текущия списък започвайки от head и извежда на екрана
информация за всички стоки използвайки функцията - Print_goods_info_by_address(Goods* goods)
*/void Show_all_goods_in_opened_storage();

/*Change_amount_of_goods_by_nomenclature_number_in_opened_storage() - Функцията проверява дали е отворен склад,
ако е отворен склад подканва потребителя да въведе номенклатурен номер, взима адреса
на елемента с въведения номенклатурен номер ако има такъв елемент използвайки функцията -
Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number),
извежда на екрана информацията за стоката с въведения номенклатурен номер използвайки -
Print_goods_info_by_address(Goods* goods), подканва потребителя да въведе ново количество на стоката,
ако новото количество е равно на нула, се извиква функцията за изтриване на стока - Delete_goods_by_address(Goods* goods).
На финала текущото състояние на списъка се записва в бинарния файл чрез използване на функцията - Save_current_list_to_file()
*/void Change_amount_of_goods_by_nomenclature_number_in_opened_storage();

/*Show_all_expired_goods_in_opened_storage() - Функцията проверява дали е отворен склад,
ако е отворен склад подканва потребителя да въведе текущата дата и я сравнява с датите на
изтичане на срока на годност на стоките. Извежда на екрана информацията за стоките с изтекъл срок
използвайки функцията - Print_goods_info_by_address(Goods* goods).
*/void Show_all_expired_goods_in_opened_storage();

/*Show_info_for_goods_by_nomenclature_number_in_opened_storage() - Функцията проверява дали е отворен склад,
ако е отворен склад подканва потребителя да въведе номенклатурен номер на стока, обхожда списъка
итерирайки през всички елементи и извършвайки сравнение на номенклатурните им номера с въведения от потребителя номер.
При съвпадение на номенклатурния номер информацията за стоката се извежда на екрана чрез използване на функцията -
Print_goods_info_by_address(Goods* goods).
*/void Show_info_for_goods_by_nomenclature_number_in_opened_storage();

/*Run_an_option(int option) - Функцията получава аргумент - въведена опция от потребителя
число от 1 до 9 и предприема съответната операция (извиква подходящата функция) използвайки switch
*/void Run_an_option(int option);

/*menu() - Функцията извежда на екрана меню и подканва потребителя да въведе опция
ако въведената опция е в интервала [1;9] връща това число, ако не - връща (-1)
*/int menu();

/*check_if_file_is_bin(char* filename) - Функцията получава като параметър име на файл и връща информация дали той
е с разширение .bin под формата на 1 за "да" и 0 за "не"
*/int check_if_file_is_bin(char* filename);

/*Clear_list() - Функцията итерира през списъка освобождавайки паметта на всички елементи,
накрая насочва head към NULL, използвайки функцията INIT_HEAD()
*/void Clear_list();

/*Check_if_a_storage_is_opened() - Функцията проверява дали current_opened_storage_filename е празно
и ако е празно връща 0, ако не е празно връща 1
*/int Check_if_a_storage_is_opened();

/*Add_goods() - Функцията итерира през списъка до достигане на неговия край.
Подканва потребителя да въведе стойности на всяко поле за новата стока, записвайки
новата стока накрая на списъка
*/void Add_goods();

/*Save_current_list_to_file() - Функцията отваря за писане файла с текущото име на склада
(current_opened_storage_filename[30]), преброява елементите в текущия списък използвайки функцията
Count_goods_in_memory(), записва бройката на елементите в началото на бинарния файл под
формата на int, след което записва всички обекти от списъка във файла и накрая затваря въпросния файл
*/void Save_current_list_to_file();

/*Print_goods_info_by_address(Goods* goods) - Функцията приема за аргумент указател към
стока и извежда на екрана член-променливите на стоката т.е. поленцата с информация
*/void Print_goods_info_by_address(Goods* goods);

/*Count_goods_in_memory() - Функцията итерира през целия списък, като отброява елементите в него
и връща този брой под формата на int (цяло число)
*/int Count_goods_in_memory();

/*Load_goods_from_file() - Функцията проверява дали е отворен склад (дали името на текущия склад не е празно).
Ако е отворен склад тя извиква Clear_list() с помощта, на която изпразва текущия списък. Опитва да отвори
бинарния файл с името на склада в режим за четене, ако успее прочита всички стоки от него и ги записва
последователно в списъка.
*/void Load_goods_from_file();


/*Delete_goods_by_address(Goods* goods) - Функцията обхожда списъка търсейки съвпадение на адрес на някой от
елементите - с подадения към нея като аргумент адрес за изтриване на елемент. Когато намери съвпадение
освобождава паметта на съответния елемент и се грижи да насочи всички указатели коректно.
*/void Delete_goods_by_address(Goods* goods);


/*Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number) - Функцията обхожда списъка
търсейки съвпадение на подадения, като аргумент номенклатурен номер с някой от номенклатурните номера на стоките,
ако е намерено - функцията връща адрес към стоката със съответния номенклатурен номер.
*/Goods* Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number);

/*Return_reversed_date(char* date) - Функцията приема, като аргумент дата под формата на символен низ във формата DD.MM.YYYY,
заделя памет за нов символен низ, в който записва датата във формата YYYY.MM.DD и връща указателя към тази памет под формата на char*
*/char* Return_reversed_date(char* date);
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
/*
ПРИМЕР ЗА ИЗПОЛЗВАНЕ НА ПРОГРАМАТА:

==========================================
MENU
==========================================
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 2


        ==========================================
        NOW CREATING A NEW STORAGE
        ==========================================
          Enter the name of the new storage: Storage1
          The storage "Storage1" was created
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 3


        ==========================================
        NOW OPENING A STORAGE
        ==========================================
        Please enter the name of a storage to open: Storage1
        Storage "Storage1" is successfuly opened
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 4


        ==========================================
        NOW ADDING GOODS TO "Storage1" STORAGE
        ==========================================
          Enter nomenclature number (12 digits number): 123456789098
          Enter name (for example: potatoes): Bananas
          Enter price (for example: 5.25): 2.30
          Enter amount (for example: 5): 30
          Enter expiration date (DD.MM.YYYY): 18.05.2017
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 4


        ==========================================
        NOW ADDING GOODS TO "Storage1" STORAGE
        ==========================================
          Enter nomenclature number (12 digits number): 234546574382
          Enter name (for example: potatoes): Tomatoes
          Enter price (for example: 5.25): 3.45
          Enter amount (for example: 5): 48
          Enter expiration date (DD.MM.YYYY): 20.05.2017
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 4


        ==========================================
        NOW ADDING GOODS TO "Storage1" STORAGE
        ==========================================
          Enter nomenclature number (12 digits number): 984537543212
          Enter name (for example: potatoes): Peaches
          Enter price (for example: 5.25): 3.80
          Enter amount (for example: 5): 12
          Enter expiration date (DD.MM.YYYY): 12.05.2017
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 5


        ==========================================
        NOW PRINTING GOODS FROM "Storage1" STORAGE
        ==========================================

          Nomenclature number: 123456789098
          Name: Bananas
          Price: 2.300000
          Amount: 30
          Expiration date: 18.05.2017

          Nomenclature number: 234546574382
          Name: Tomatoes
          Price: 3.450000
          Amount: 48
          Expiration date: 20.05.2017

          Nomenclature number: 984537543212
          Name: Peaches
          Price: 3.800000
          Amount: 12
          Expiration date: 12.05.2017
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION: 7


        ==========================================
        NOW PRINTING EXPIRED GOODS
        FROM OPENED STORAGE
        ==========================================
          Enter the date of today (for example 01.01.2017): 19.05.2017

          Nomenclature number: 123456789098
          Name: Bananas
          Price: 2.300000
          Amount: 30
          Expiration date: 18.05.2017

          Nomenclature number: 984537543212
          Name: Peaches
          Price: 3.800000
          Amount: 12
          Expiration date: 12.05.2017
        ==========================================

--->press ENTER to show menu again<---



==========================================
MENU
==========================================
OPTIONS FOR STORAGES
------------------------------------------
  1.Show existing storages
  2.Create a new storage
  3.Open a storage by name
------------------------------------------
OPTIONS FOR GOODS
------------------------------------------
  4.Add goods in opened storage
  5.Show all goods in opened storage
  6.Change amount of goods by nomenclature number in opened storage
  7.Show all expired goods in opened storage
  8.Show info for goods by nomenclature number in opened storage
------------------------------------------
OTHER OPTIONS
------------------------------------------
  9.EXIT
==========================================
ENTER AN OPTION:

*/
