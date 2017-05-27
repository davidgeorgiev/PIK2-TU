#include "libra.h"
#include "my_list.h"

void add_a_file();
void search_for_file();
void count_files_in_directory();
void print_list();
int menu();

int main(){
	reconstruct_list();
	read_bin_file_to_list();
	while(menu()==0){printf("\t---press enter to return to menu---\n\t");fflush(stdin);getchar();}
	printf("%s",KNRM);//set colors default
	return 0;
}
void add_a_file(){
  char full_filename[768];
  printf("\n\tAdding new file");
  printf("\n\t enter the full path of your file: ");
  getchar();
  InputString(full_filename);
  if(path_exists(full_filename)){
  	FileInformation* obj_ptr = make_an_object_and_return_address_by_filename(full_filename);
  	append_object_to_list_by_address(obj_ptr);
  	save_current_list_to_file();
  }else{printf("\t%sSorry this file doesn't exists%s\n",KRED,KWHT);}
}
void search_for_file(){
	printf("\tSearching for file\n");
	printf("\t enter file to search: ");
	char search_file[256];
	getchar();
	InputString(search_file);
	print_all_files_with_name(search_file);
}
void count_files_in_directory(){
	getchar();
	printf("\tCounting files in dir\n");
	printf("\t enter dir to search: ");
	char search_dir[512];
	InputString(search_dir);
	print_all_files_in_dir(search_dir);
}
void print_list(){
	FileInformation* temp = head;int i = 0;
	while(temp->next != NULL){
		i++;
		temp = (FileInformation*)(temp->next);
		printf_object_by_address(temp,i);
	}getchar();
}
int menu(){
  printf("%s-----------------------------------------------\n",KCYN);
  printf("MENU OPTIONS:");
  printf("\n1.add new file\n");
  printf("2.search for file and show info\n");
  printf("3.count files in directory and show size\n");
  printf("4.print all list\n");
  printf("5.exit\n");
  char selected_option;
  printf("Enter an option please:\noption = ");
  fflush(stdin);
  scanf(" %c",&selected_option);
  printf("-----------------------------------------------%s\n",KWHT);
  switch(selected_option){
    case '1':add_a_file();return 0;
    case '2':search_for_file();return 0;
    case '3':count_files_in_directory();return 0;
    case '4':print_list();return 0;
    default: return -1;
  }
}
