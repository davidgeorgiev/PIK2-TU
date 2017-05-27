#include <stdio.h> //включване на библиотеката за вход и изход
#include <stdlib.h> //включване на стандартната главна библиотека
#include <dirent.h> //включване на библиотеката за директории
#include <string.h> //включване на библиотеката за символни низове

//Инициализираща част
typedef struct{
  char nomenclature_number[13];
  char name[21];
  char availability;
  int amount;
  int minimum_regulatory_stock;
  char supplier_code[9];
  char supplier_info[81];
  char latest_income_date[11];
  char latest_outcome_date[11];
  char last_revaluation_date[11];
  float price;
  struct Storage* next;
}Storage;
Storage* head = NULL;
char current_opened_storage_filename[32];

//Декларации на функциите
void list_reconstruct();
/*функция за инициализиране на списъка наново. Ако списъкът не е празен
той се изпразва след, което главният възел - head се насочва към NULL*/
int menu();
/*функция за извеждане на менюто на програмата и извикване на главните и
функции. Връща -1 при изход*/
void create_new_storage();
/*функция, която създава нов склад (нов бинарен файл с име
въведено от потребителя)*/
void show_all_storages();
/*функция, която преглежда текущата директория и извежда на екрана имената
на всички бинарни файлове (всички складове) в текущата директория*/
void open_a_storage();
/*функция, която подканва потребителя да въведе склад и задава въведеното име
като име на текущия отворен склад*/
void register_material();
/*функция, която проверява дали има материал с това име и ако няма
създава такъв и подканва потребителя да въведе данните за нега, а ако
има такъв подканва потребителя да въведе какво количество от материала
внася в склада*/
void discharge_material();
/*функция, която изважда материал от съответния тип, като изисква от
потребителя да въведе, количество на материала, който ще се изнася от склада*/
void change_price();
/*функция, която променя цената на материал*/
void search_for_material_by_nomenclature_number();
/*функция, която търси материал по номенклатурен номер*/
void print_all_materials_in_opened_storage();
/*функция, която извежда на екрана всички материали в отворения склад
използвайки друга функция, която извежда информацията само за един
материал по подаден адрес в паметта*/
void clear_the_name_of_current_opened_storage();
/*функция, която изчиства името на текущия отворен склад*/
int check_if_file_is_bin(char* filename);
/*check_if_file_is_bin(char* filename) - Функцията получава като параметър име на файл и връща информация дали той
е с разширение .bin под формата на 1 за "да" и 0 за "не"
*/
void Enter_current_opened_storage_filename();
/*Show_existing_storages() - функция обхождаща директорията, в която се намира
текущата изпълнима програма и извежда на екрана имената на всички файлове
с разширение .bin (имената на складовете) ако са създадени складове
*/
void Load_materials_from_file();
/*функцията прочита файла на текущия отворен склад и зарежда материалите в
в едносвързания списък*/
int Check_if_a_storage_is_opened();
/*фукция, която проверява дали е отворен склад*/
Storage* check_if_material_name_exists(char* name);
/*функция, която проверява дали съществува в списъка материал с име
съответвстващо на подаденото като аргумент име. Връща NULL ако не съществува и
връща адрес към обекта (материала) ако съществува.*/
void add_new_material_with_name(char* material_name,char* date);
/*функция за добавяне на нов обект в списъка*/
void save_current_list_to_file();
/*функция, която съхранява текущото състояние на списъка във бинарния
файл с името на текущия отворен склад*/
int count_materials_in_memory();
/*функция, която преброява материалите в текущия списък и връща техния брой*/
void print_material_info_by_address(Storage* address,int index);
/*функция, която извежда на екрана информация за материал по подаден адрес*/
Storage* Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number);
/*Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number) - Функцията обхожда списъка
търсейки съвпадение на подадения, като аргумент номенклатурен номер с някой от номенклатурните номера на стоките,
ако е намерено - функцията връща адрес към стоката със съответния номенклатурен номер.*/

int main(){
  list_reconstruct();
  char c;
  while(menu()==0){
    printf("\t---press enter to return to menu---\n\t");
    scanf("%c",&c);
    scanf("%c",&c);
  }
  return 0;
}

void list_reconstruct(){
  if(head != NULL){
    Storage* current = head;
    Storage* temp;
    while(current->next!=NULL){
      current = (Storage*)current->next;
      temp = (Storage*)current->next;
      free(current);
      current = head;
    }
  }
  head = (Storage*)malloc(sizeof(Storage));
  head->next = NULL;
}
int menu(){
  printf("-----------------------------------------------\n");
  printf("MENU\nSTORAGE OPTIONS:");
  printf("\n\t1.Create a new storage\n\t2.Show all storages\n\t3.Open a storage\n");
  printf("MATERIAL OPTIONS");
  printf("\n\t4.Register material\n\t5.Discharge material");
  printf("\n\t6.Change price\n\t7.Search for material");
  printf(" by nomenclature number\n\t8. Show all materials in opened storage\n");
  printf("OTHER OPTIONS\n\t9.Exit\n");
  char selected_option;
  printf("Enter an option please:\n\toption = ");
  scanf(" %c",&selected_option);
  printf("-----------------------------------------------\n\n");
  switch(selected_option){
    case '1':create_new_storage();return 0;
    case '2':show_all_storages();return 0;
    case '3':open_a_storage();return 0;
    case '4':register_material();return 0;
    case '5':discharge_material();return 0;
    case '6':change_price();return 0;
    case '7':search_for_material_by_nomenclature_number();return 0;
    case '8':print_all_materials_in_opened_storage();return 0;
    default: return -1;
  }
}
void create_new_storage(){
	printf("\tNOW CREATING A NEW STORAGE\n");
	char filename[1024];
	int i;
	FILE* fp;
	char c = 'y';
	int number_of_materials = 0;
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
			fwrite(&number_of_materials,sizeof(int),1,fp);
			fclose(fp);
			break;
		}
	}
}
void show_all_storages(){
  int if_exists_any_storage = 0;
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL){
		//fprintf(stdout, "Current working dir: %s\n", cwd);
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir (cwd)) != NULL) {
			/* print all the files and directories within directory */
			printf("\tNOW PRINTING STORAGES\n");
			while ((ent = readdir (dir)) != NULL) {
				if(check_if_file_is_bin(ent->d_name)){
					printf ("\t  %s\b\b\b\b    \n", ent->d_name);
					if_exists_any_storage = 1;
				}
			}
			closedir (dir);
			if(!if_exists_any_storage){
				printf("\t  No storages found!\n\t  You must create some in menu option 1\n");
			}
		} else {
			/* could not open directory */
			perror ("");
		}
	}
}
void open_a_storage(){
  printf("\tNOW OPENING A STORAGE\n");
	Enter_current_opened_storage_filename();
	FILE* fp = fopen(current_opened_storage_filename,"r");
	if(fp != NULL){
		printf("\tStorage \"%s\b\b\b\b\" is successfuly opened\n",current_opened_storage_filename);
		fclose(fp);
    list_reconstruct();
		Load_materials_from_file();
	}else{
		printf("\tStorage \"%s\b\b\b\b\" not exists\n",current_opened_storage_filename);
		current_opened_storage_filename[0]='\0';
	}
}
void register_material(){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  char name_of_new_material[21];
  char date[11];
  int number_to_add;
  Storage* temp;
  char c;
  printf("\tNOW REGISTERING MATERIAL\n");
  printf("\tEnter the date of today here (DD.MM.YYYY): ");
  scanf("%s",date);
  printf("\tenter a name for the new material here: ");
  scanf("%s",name_of_new_material);
  if((temp = check_if_material_name_exists(name_of_new_material))!=NULL){
    printf("\tThis material exists how many you want to add?\n");
    printf("\tenter amount of material to add: ");
    scanf("%d",&number_to_add);
    temp->amount = (temp->amount) + number_to_add;
    strcpy(temp->latest_income_date,date);
  }else{
    printf("\tThis material not exists. Do you want to create it now y/n: ");
    scanf("%c",&c);
    scanf("%c",&c);
    if(c == 'y'){
      add_new_material_with_name(name_of_new_material,date);
    }
  }
  printf("\t---Material added successfuly---\n");
  save_current_list_to_file();
}
void discharge_material(){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  printf("\tNOW DISCHARGING MATERIAL\n");
  char name_to_discharge[21];
  char date[11];
  printf("\tEnter the date of today here (DD.MM.YYYY): ");
  scanf("%s",date);
  printf("\tEnter name of material you want to discharge: ");
  scanf(" %s",name_to_discharge);
  Storage* temp;
  int discharge_amount;
  int second_time = 0;
  if((temp = check_if_material_name_exists(name_to_discharge))!=NULL){

    do{
      if(second_time){
        printf("\tThe amount of %s is %d, but you want\n\t to discharge %d!!!\n",name_to_discharge,temp->amount,discharge_amount);
      }
      printf("\tEnter discharge amount here: ");
      scanf(" %d",&discharge_amount);
      second_time = 1;
    }while((temp->amount)-discharge_amount<0);
    temp->amount = (temp->amount)-discharge_amount;
    strcpy(temp->latest_outcome_date,date);
    printf("\t---Material discharged successfuly---\n");
    save_current_list_to_file();
  }else{
    printf("\tNo such material... :(\n");
  }
}
void change_price(){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  printf("\tNOW CHANGING PRICE\n");
  char name_to_change_price[21];
  char date[11];
  printf("\tEnter the date of today here (DD.MM.YYYY): ");
  scanf("%s",date);
  printf("\tEnter name of material you want to change price: ");
  scanf(" %s",name_to_change_price);
  Storage* temp;
  int new_price;
  int second_time = 0;
  if((temp = check_if_material_name_exists(name_to_change_price))!=NULL){
    do{
      if(second_time){
        printf("\tPrice must be positive number!\n");
      }
      printf("\tEnter new price here: ");
      scanf(" %f",&new_price);
      second_time = 1;
    }while(new_price<=0);
    temp->price = new_price;
    strcpy(temp->last_revaluation_date,date);
    printf("\t---Price changed successfuly---\n");
    save_current_list_to_file();
  }else{
    printf("\tNo such material... :(\n");
  }
}
void search_for_material_by_nomenclature_number(){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  Storage* temp;
  char nomenclature_number_to_search[13];
  printf("\tEnter nomenclature number to search: ");
  scanf(" %s",nomenclature_number_to_search);
  if((temp = Return_address_by_nomenclature_number_in_opened_storage(nomenclature_number_to_search))!=NULL){
    print_material_info_by_address(temp,0);
  }else{
    printf("\tNo material with this nomenclature number! :(\n");
  }
}
void print_all_materials_in_opened_storage(){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  Storage* temp = head;
  int i = 0;
  while(temp->next != NULL){
    temp = (Storage*)temp->next;
    i++;
    print_material_info_by_address(temp,i);
  }
  if(i==0){
    printf("\tThere is not materials yet!\n\tYou can add some in option 4 in menu.\n");
  }
}
void clear_the_name_of_current_opened_storage(){
  current_opened_storage_filename[0] = '\0';
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
void Load_materials_from_file(){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  FILE* fp = fopen(current_opened_storage_filename,"rb");
  int number_of_materials;
  int i;
  if(fp!=NULL){
    fread(&number_of_materials,sizeof(int),1,fp);
    Storage* temp = head;
    for(i = 0;i<number_of_materials;i++){
      temp->next = (struct Storage*)malloc(sizeof(Storage));
      temp = (Storage*)temp->next;
      fread(temp,sizeof(Storage),1,fp);
    }
    fclose(fp);
  }else{
    printf("Open file error! :(\n");
  }
}
int Check_if_a_storage_is_opened(){
  if(current_opened_storage_filename[0]=='\0'){return 0;}else{return 1;}
}
Storage* check_if_material_name_exists(char* name){
  Storage* return_address = NULL;
  Storage* temp = head;
  while(temp->next!=NULL){
    temp = (Storage*)temp->next;
    if(strcmp(name,temp->name)==0){
      return_address = temp;
    }
  }
  return return_address;
}
void add_new_material_with_name(char* material_name,char* date){
  if(!Check_if_a_storage_is_opened()){printf("\tYou first have to open a storage in option 3\n");return;}
  printf("\tNOW ADDING NEW MATERIAL\n");
  Storage* temp = head;
  while(temp->next!=NULL){temp = (Storage*)temp->next;}
  temp->next = (struct Storage*)malloc(sizeof(Storage));
  temp = (Storage*)temp->next;
  temp->next = NULL;
  strcpy(temp->latest_income_date,date);
  strcpy(temp->last_revaluation_date,date);
  strcpy(temp->latest_outcome_date,"none");
  char temp_nomenclature_number[13];
  int second_time = 0;
  do{
    if(second_time){
      printf("\t---There is already material with this nomenclature number!---\n");
      printf("\t---Try again!---\n");
    }
    printf("\tenter nomenclature number (12 digits): ");
    scanf(" %s",temp_nomenclature_number);
    second_time = 1;
  }while(Return_address_by_nomenclature_number_in_opened_storage(temp_nomenclature_number)!=NULL);
  strcpy(temp->nomenclature_number,temp_nomenclature_number);
  strcpy(temp->name,material_name);
  printf("\tenter price (float number): ");
  scanf(" %f",&(temp->price));
  printf("\tenter minimum regulatory stock: ");
  scanf(" %d",&(temp->minimum_regulatory_stock));
  second_time = 0;
  do{
    if(second_time){
      printf("\tTHE AMOUNT MUST BE NOT LESS THAN\n\tMINIMUM REGULATORY STORCK!!!\n");
    }
    printf("\tenter amount (number): ");
    scanf(" %d",&(temp->amount));
    second_time = 1;
  }while(temp->minimum_regulatory_stock>temp->amount);
  printf("\tenter supplier code (8 digits): ");
  scanf(" %s",temp->supplier_code);
  printf("\tenter supplier info (80 letters max):");
  scanf(" %s",temp->supplier_info);
  temp->availability = 1;
}
void save_current_list_to_file(){
	FILE* fp = fopen(current_opened_storage_filename,"wb");
	int number_of_materials = count_materials_in_memory();
	if(fp!=NULL){
		fwrite(&number_of_materials,sizeof(int),1,fp);
		Storage* temp = head;
		while(temp->next != NULL){
			temp = (Storage*)(temp->next);
			fwrite(temp,sizeof(Storage),1,fp);
		}
		fclose(fp);
	}
}
int count_materials_in_memory(){
  Storage* temp = head;
	int i = 0;
	while(temp->next != NULL){
		temp = (Storage*)(temp->next);
		i++;
	}
	return i;
}
void print_material_info_by_address(Storage* address,int index){
  printf("\n\tPRINTING INFO FOR MATERIAL ");
  if(index > 0){
    printf("%d",index);
  }
  printf("\n");
  printf("\tname: %s\n",address->name);
  printf("\tnomenclature number: %s\n",address->nomenclature_number);
  printf("\tprice: %f\n",address->price);
  printf("\tminimum regulatory stock: %d\n",address->minimum_regulatory_stock);
  printf("\tamount: %d\n",address->amount);
  printf("\tsupplier code: %s\n",address->supplier_code);
  printf("\tsupplier info: %s\n",address->supplier_info);
  printf("\tlatest income date: %s\n",address->latest_income_date);
  printf("\tlatest outcome date: %s\n",address->latest_outcome_date);
  printf("\tlatest revaluation date: %s\n\n",address->last_revaluation_date);
}
Storage* Return_address_by_nomenclature_number_in_opened_storage(char* nomenclature_number){
  int if_something_found = 0;
	Storage* temp = head;
	while(temp->next != NULL){
		temp = (Storage*)(temp->next);
		if(strcmp(nomenclature_number,temp->nomenclature_number)==0){
			if_something_found = 1;
			return temp;
		}
	}
	if(!if_something_found){
		return NULL;
	}
}
/*Пример за използване на програмата
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 2
-----------------------------------------------

        NOW PRINTING STORAGES
          No storages found!
          You must create some in menu option 1
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 1
-----------------------------------------------

        NOW CREATING A NEW STORAGE
          Enter the name of the new storage: Neda's_storage
          The storage "Neda's_storage" was created
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 4
-----------------------------------------------

        You first have to open a storage in option 3
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 3
-----------------------------------------------

        NOW OPENING A STORAGE
        Please enter the name of a storage to open: Neda's_storage
        Storage "Neda's_storage" is successfuly opened
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 4
-----------------------------------------------

        NOW REGISTERING MATERIAL
        Enter the date of today here (DD.MM.YYYY): 22.05.2017
        enter a name for the new material here: glass
        This material not exists. Do you want to create it now y/n: y
        NOW ADDING NEW MATERIAL
        enter nomenclature number (12 digits): 483596453423
        enter price (float number): 38.77
        enter minimum regulatory stock: 5
        enter amount (number): 2
        THE AMOUNT MUST BE NOT LESS THAN
        MINIMUM REGULATORY STORCK!!!
        enter amount (number): 10
        enter supplier code (8 digits): 45435432
        enter supplier info (80 letters max):Some/address,phone:02394894
        ---Material added successfuly---
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 4
-----------------------------------------------

        NOW REGISTERING MATERIAL
        Enter the date of today here (DD.MM.YYYY): 22.05.2017
        enter a name for the new material here: wood
        This material not exists. Do you want to create it now y/n: y
        NOW ADDING NEW MATERIAL
        enter nomenclature number (12 digits): 123456789098
        enter price (float number): 28.90
        enter minimum regulatory stock: 12
        enter amount (number): 25
        enter supplier code (8 digits): 54654345
        enter supplier info (80 letters max):firm,address,phone
        ---Material added successfuly---
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 4
-----------------------------------------------

        NOW REGISTERING MATERIAL
        Enter the date of today here (DD.MM.YYYY): 23.05.2017
        enter a name for the new material here: glass
        This material exists how many you want to add?
        enter amount of material to add: 12
        ---Material added successfuly---
        ---press enter to return to menu---
-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 5
-----------------------------------------------

        NOW DISCHARGING MATERIAL
        Enter the date of today here (DD.MM.YYYY): 30.12.2017
        Enter name of material you want to discharge: metal
        No such material... :(
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 5
-----------------------------------------------

        NOW DISCHARGING MATERIAL
        Enter the date of today here (DD.MM.YYYY): 12.12.2017
        Enter name of material you want to discharge: wood
        Enter discharge amount here: 300
        The amount of wood is 25, but you want
         to discharge 300!!!
        Enter discharge amount here: 20
        ---Material discharged successfuly---
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 6
-----------------------------------------------

        NOW CHANGING PRICE
        Enter the date of today here (DD.MM.YYYY): 13.08.2017
        Enter name of material you want to change price: glass
        Enter new price here: 30.58
        ---Price changed successfuly---
        ---press enter to return to menu---
        -----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 8
-----------------------------------------------


        PRINTING INFO FOR MATERIAL 1
        name: glass
        nomenclature number: 483596453423
        price: 30.000000
        minimum regulatory stock: 5
        amount: 22
        supplier code: 45435432
        supplier info: Some/address,phone:02394894
        latest income date: 23.05.2017
        latest outcome date: none
        latest revaluation date: 13.08.2017


        PRINTING INFO FOR MATERIAL 2
        name: wood
        nomenclature number: 123456789098
        price: 28.900000
        minimum regulatory stock: 12
        amount: 5
        supplier code: 54654345
        supplier info: firm,address,phone
        latest income date: 22.05.2017
        latest outcome date: 12.12.2017
        latest revaluation date: 22.05.2017

        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 7
-----------------------------------------------

        Enter nomenclature number to search: 123456789098

        PRINTING INFO FOR MATERIAL
        name: wood
        nomenclature number: 123456789098
        price: 28.900000
        minimum regulatory stock: 12
        amount: 5
        supplier code: 54654345
        supplier info: firm,address,phone
        latest income date: 22.05.2017
        latest outcome date: 12.12.2017
        latest revaluation date: 22.05.2017

        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please:
        option = 7
-----------------------------------------------

        Enter nomenclature number to search: 4534356546
        No material with this nomenclature number! :(
        ---press enter to return to menu---

-----------------------------------------------
MENU
STORAGE OPTIONS:
        1.Create a new storage
        2.Show all storages
        3.Open a storage
MATERIAL OPTIONS
        4.Register material
        5.Discharge material
        6.Change price
        7.Search for material by nomenclature number
        8. Show all materials in opened storage
OTHER OPTIONS
        9.Exit
Enter an option please: 9
*/
