//INCLUDE LIBRARIES AND DEFINE CONSTANTS
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  #define BIN_FILENAME "bin.dat"
//END INCLUDE LIBRARIES AND DEFINE CONSTANTS

//GLOBAL PART
  typedef struct{
  	char tax_registry_number[14];
  	char name[41];
  	float earnings[5];
  	char date_of_registration[11];
  	struct Firm* next;
  }Firm;
  Firm* head = NULL;
//END GLOBAL PART

//PROTOTYPNING
  //primary functions
    void add_new_firm();
    void update_firm();
    void show_information_for_firm_by_tax_registration_number();
    void show_info_for_firms_in_interval();
  //end primary functions
  //secondary functions
    char* get_reversed_date(char* date);
    int get_current_year();
    void read_list_from_bin_file(char* filename);
    void save_list_to_bin_file(const char* filename);
    char* add_txt_at_the_end_of_the_file(char* filename);
    void save_a_firm_into_a_text_file_by_index(int index);
    void save_all_firms_into_text_files();
    int get_size();
    void free_list();
    void reconstruct_list();
    int check_format_of_date(char* date);
    char* get_registry_tax_number();
    void input_info_on_address(Firm* address);
    int check_if_tax_number_exists(char* tax_number);
    char* get_date(const char* type_of_date);
    void print_info_by_address(Firm* address);
    int menu();
  //end secondary functions
//END PROTOTYPING

//MAIN FUNCTION
  int main(){
  	char c;
  	reconstruct_list();
    int size;
  	read_list_from_bin_file(BIN_FILENAME);
  	while(menu()==0){
  		printf("\t===press enter to return menu===\n");
  		fflush(stdin);
  		scanf("%c",&c);
  	}

  	return 0;
  }
//END MAIN FUNCTION

//PRIMARY FUNCTIONS
  void add_new_firm(){
  	char* tax_number;
  	printf("\tadding new firm\n");
  	Firm* temp = head;
  	while(temp->next!=NULL){
  		temp = (Firm*)(temp->next);
  	}
  	tax_number = get_registry_tax_number();
  	temp->next = (struct Firm*)malloc(sizeof(Firm));
  	temp = (Firm*)(temp->next);
  	temp -> next = NULL;

    strcpy(temp->tax_registry_number,tax_number);
  	free(tax_number);
  	input_info_on_address(temp);
  	save_list_to_bin_file(BIN_FILENAME);
  	save_all_firms_into_text_files();
  }
  void update_firm(){
  	char tax_registry_number[14];
  	printf("\tupdate firm\n");
  	printf("\t enter tax registry number of the firm you want update: ");
  	fflush(stdin);
  	scanf("%s",tax_registry_number);
  	int if_found_firm = 0;
  	Firm* temp = head;
  	while(temp->next!=NULL){
  		temp = (Firm*)(temp->next);
  		if(strcmp(tax_registry_number,temp->tax_registry_number)==0){
  			input_info_on_address(temp);
  			if_found_firm = 1;
  		}
  	}
  	if(!if_found_firm){
  		printf("\t---firm not found---\n");
  	}
  	save_list_to_bin_file(BIN_FILENAME);
  	save_all_firms_into_text_files();
  }
  void show_information_for_firm_by_tax_registration_number(){
  	int if_found_firm = 0;
  	char tax_registry_number[14];
  	printf("\tshow info for firm by tax registration number\n");
  	printf("\t enter tax registry number of the firm you want search for: ");
  	fflush(stdin);
  	scanf("%s",tax_registry_number);
  	Firm* temp = head;
  	while(temp->next!=NULL){
  		temp = (Firm*)(temp->next);
  		if(strcmp(temp->tax_registry_number,tax_registry_number)==0){
  			if_found_firm = 1;
  			print_info_by_address(temp);
  		}
  	}
  	if(!if_found_firm){
  		printf("\t---firm not found---\n");
  	}
  }
  void show_info_for_firms_in_interval(){
  	int i;
  	int if_all_earnings_are_positive;
  	printf("\tprinting all firms with earnings for all 5 years in custom interval!\n");
  	char* start_date = get_date(" start ");
  	char* final_date = get_date(" final ");
  	char* reversed_start_date = get_reversed_date(start_date);
  	char* reversed_final_date = get_reversed_date(final_date);
  	free(start_date);
  	free(final_date);
  	char* reversed_current_date;
  	Firm* temp = head;
  	int something_found = 0;
  	while(temp->next!=NULL){
  		temp = (Firm*)(temp->next);
  		if_all_earnings_are_positive = 1;
  		reversed_current_date = get_reversed_date(temp->date_of_registration);
  		if((strcmp(reversed_start_date,reversed_current_date)<=0)&&(strcmp(reversed_final_date,reversed_current_date)>=0)){
  			//printf("\tstart = %s; current = %s; final = %s\n",reversed_start_date,reversed_current_date,reversed_final_date);
  			for(i = 0;i<5;i++){
  				if((temp->earnings)[i]<=0){
  					if_all_earnings_are_positive = 0;
  				}
  			}
  			if(if_all_earnings_are_positive){
  				print_info_by_address(temp);
  			}
  			something_found = 1;
  		}
  		free(reversed_current_date);
  	}
  	if(!something_found){
  		printf("\t---not found firms in interval [%s;%s]---\n",reversed_start_date,reversed_final_date);
  	}
  	free(reversed_start_date);
  	free(reversed_final_date);
  }
  void show_information_for_all_firms(){
    Firm* temp = head;
    while(temp->next!=NULL){
      temp = (Firm*)(temp->next);
      print_info_by_address(temp);
    }
  }
//END OF PRIMARY FUNCTIONS

//SECONDARY FUNCTIONS
  char* get_reversed_date(char* date){
  	char* reversed_date = (char*)malloc(11);
  	reversed_date[0] = date[0];
  	reversed_date[1] = date[1];
  	reversed_date[2] = date[2];
  	reversed_date[3] = date[3];
    reversed_date[4] = date[4];
  	reversed_date[8] = date[5];
  	reversed_date[9] = date[6];
    reversed_date[7] = date[7];
  	reversed_date[5] = date[8];
  	reversed_date[6] = date[9];
  	reversed_date[10] = date[10];
  	return reversed_date;
  }
  int get_current_year(){
  	time_t now;
  	if ( time(&now) != (time_t)(-1) )
  	{
  	  struct tm *mytime = localtime(&now);
  	  if ( mytime )
  	  {
  	     char year [ 5 ];
  	     if ( strftime(year, sizeof year, "%Y", mytime) )
  	     {
  	        return atoi(year);
  	     }
  	  }
  	}
  	return 0;
  }
  void read_list_from_bin_file(char* filename){
  	FILE* fp = fopen(filename,"rb");
  	int number_of_elements;
  	int i;
  	if(fp!=NULL){
  		fread(&number_of_elements,4,1,fp);
  		Firm* temp = head;
  		for(i = 0;i<number_of_elements;i++){
  			temp->next = (struct Firm*)malloc(sizeof(Firm));
  			temp = (Firm*)(temp->next);
  			fread(temp,sizeof(Firm),1,fp);
  		}
  		temp -> next = NULL;
      fclose(fp);
  	}else{
  		printf("\t---file open error!---\n");
  	}
  }
  void save_list_to_bin_file(const char* filename){
  	FILE* fp = fopen(filename,"wb");
  	int number_of_elements = get_size();
  	if(fp!=NULL){
  		fwrite(&number_of_elements,4,1,fp);
  		Firm* temp = head;
  		while(temp->next!=NULL){
  			temp = (Firm*)(temp->next);
  			fwrite(temp,sizeof(Firm),1,fp);
  		}
      fclose(fp);
  	}else{
  		printf("\t---File can\'t be created! :(---\n");
  	}
  }
  char* add_txt_at_the_end_of_the_file(char* filename){
  	char* new_name = (char*)malloc(18);
  	int i;
  	for(i=0;filename[i]!='\0';i++){
  		new_name[i] = filename[i];
  	}
  	new_name[i] = '.';
  	i++;
  	new_name[i] = 't';
  	i++;
  	new_name[i] = 'x';
  	i++;
  	new_name[i] = 't';
  	i++;
  	new_name[i] = '\0';
  	return new_name;
  }
  void save_a_firm_into_a_text_file_by_index(int index){
    int i;
    int j = 0;
    FILE* fp;
    Firm* temp = head;
    int current_year;
    char*  filename;
  	while(temp->next!=NULL){
      j++;
      //printf("%d\n",j);
  		temp = (Firm*)(temp->next);
  		if(j==index){
  			//printf("\n\t tax registry number: %s\n",temp->tax_registry_number);
      	current_year = get_current_year();
        filename = add_txt_at_the_end_of_the_file(temp->tax_registry_number);
      	fp = fopen(filename,"w");
      	if(fp!=NULL){
      		fprintf(fp,"%s\n",temp->name);
      		for(i=0;i<5;i++){
      			current_year--;
      			fprintf(fp,"earning for %d year = %.2f\n",current_year,(temp->earnings)[i]);
      		}
      		fprintf(fp,"date of registration: %s\n",(temp->date_of_registration));
      		fclose(fp);
      		free(filename);
      	}else{
      		printf("\t---File can\'t be created! :(---\n");
      	}
      }
    }
  }
  void save_all_firms_into_text_files(){
    int size = get_size();
  	int i;
    for(i=1;i<=size;i++){
  		save_a_firm_into_a_text_file_by_index(i);
  	}
  }
  int get_size(){
  	Firm* temp = head;
  	int size = 0;

  	while(temp->next!=NULL){
  		temp = (Firm*)temp->next;
  		++size;
  	}
  	return size;
  }
  void free_list(){
  	Firm* temp = head;
  	Firm* next;
  	while(head->next!=NULL){
  		temp = (Firm*)(temp->next);
  		next = (Firm*)(temp->next);
  		free(temp);
  		head->next = (struct Firm*)next;
  	}
  	free(head);
  	head = NULL;
  }
  void reconstruct_list(){
  	if(head != NULL){
  		free_list();
  	}
  	head = (Firm*)malloc(sizeof(Firm));
  	head->next = NULL;
  }
  int check_format_of_date(char* date){
  	if(!((date[0]<='9')&&(date[0]>='0'))){
  		return 0;
  	}
  	if(!((date[1]<='9')&&(date[1]>='0'))){
  		return 0;
  	}
  	if(!((date[2]<='9')&&(date[2]>='0'))){
  		return 0;
  	}
  	if(!((date[3]<='9')&&(date[3]>='0'))){
  		return 0;
  	}
  	if(date[4]!='.'){
  		return 0;
  	}
  	if(!((date[5]<='9')&&(date[0]>='0'))){
  		return 0;
  	}
  	if(!((date[6]<='9')&&(date[0]>='0'))){
  		return 0;
  	}
  	if(date[7]!='.'){
  		return 0;
  	}
  	if(!((date[8]<='9')&&(date[0]>='0'))){
  		return 0;
  	}
  	if(!((date[9]<='9')&&(date[0]>='0'))){
  		return 0;
  	}
  	return 1;
  }
  char* get_registry_tax_number(){
  	char* tax_number = (char*)malloc(200);
  	int first_time = 1;
  	do{
  		if(!first_time){
  			printf("\t---tax registry number may exists already---\n");
        printf("\t---also the task number must be 13 chars---\n");
  		}
  		printf("\t Enter tax registry number: ");
  		fflush(stdin);
  		scanf("%s",tax_number);
  		first_time = 0;
  	}while((strlen(tax_number)!=13)||(check_if_tax_number_exists(tax_number)));
  	return tax_number;
  }
  void input_info_on_address(Firm* address){
  	printf("\t Enter new firm name: ");
  	fflush(stdin);
  	fgets(address->name,41,stdin);

  	char* date;
  	date = get_date(" ");
  	strcpy(address->date_of_registration,date);
  	free(date);
  	int current_year;
  	int i;
  	current_year = get_current_year();
  	for(i = 0;i < 5;i++){
  		current_year--;
  		printf("\t Enter new average earnings for %d year: ",current_year);
  		fflush(stdin);
  		scanf("%f",&((address->earnings)[i]));//(address->earnings)+i;
  	}
  }
  int check_if_tax_number_exists(char* tax_number){
    int if_exists = 0;
    Firm* temp = head;
    while(temp->next!=NULL){
      temp = (Firm*)(temp->next);
      if(strcmp(tax_number,temp->tax_registry_number)==0){
        if_exists = 1;
      }
    }
    return if_exists;
  }
  char* get_date(const char* type_of_date){
  	char* date = (char*)malloc(11);
  	int first_time = 1;
  	do{
  		if(first_time==0){
  			printf("\t---Date format error, the format must be \"YYYY.DD.MM\"!---\n");
  		}
  		printf("\t Enter%sdate [YYYY.DD.MM]: ",type_of_date);
  		fflush(stdin);
  		scanf("%s",date);
  		first_time = 0;
  	}while(!check_format_of_date(date));
  	return date;
  }
  void print_info_by_address(Firm* address){
  	Firm* temp = head;
  	while(temp->next!=NULL){
  		temp = (Firm*)(temp->next);
  		if(temp==address){
  			printf("\n\t tax registry number: %s\n",temp->tax_registry_number);
  			printf("\t firm name: %s\n",temp->name);
  			printf("\t date of registration: %s\n",temp->date_of_registration);

  			int current_year;
  			int i;
  			current_year = get_current_year();
  			for(i = 0;i < 5;i++){
  				current_year--;
  				printf("\t earnings for %d year: %f\n",current_year,temp->earnings[i]);
  			}
  		}
  	}
  }
  int menu(){
  	printf("MENU\n");
  	printf("1. add_new_firm();\n");
  	printf("2. update_firm();\n");
  	printf("3. show_info_for_firms_in_interval();\n");
  	printf("4. show_information_for_firm_by_tax_registration_number();\n");
    printf("5. show_information_for_all_firms();\n");
  	printf("6. exit\n");
  	char option;
  	fflush(stdin);
  	scanf("%c",&option);
  	switch(option){
  		case '1':add_new_firm();return 0;
  		case '2':update_firm();return 0;
  		case '3':show_info_for_firms_in_interval();return 0;
  		case '4':show_information_for_firm_by_tax_registration_number();return 0;
      case '5':show_information_for_all_firms();return 0;
  		default:return -1;
  	}
  }
//END SECONDARY FUNCTIONS
