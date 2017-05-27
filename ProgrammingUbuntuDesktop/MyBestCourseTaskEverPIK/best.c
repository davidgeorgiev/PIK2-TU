#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define BIN_FILENAME "bin.bin"
typedef struct{
  char path[512];
  char filename[256];
  long int size_in_bytes;
  char date_of_creation[11];
  char date_of_modification[11];
  char flags[100];
  struct FileInformation* next;
}FileInformation;
FileInformation* head = NULL;
//PROTOTIPING
	//PRIMARY FUNCTIONS
		void add_a_file();
		void search_for_file();
		void count_files_in_directory();
		void print_list();
	//SECONDARY FUNCTIONS
		void clear_list();
		void reconstruct_list();
		int count_elements_in_list();
		void save_current_list_to_file();
		void read_bin_file_to_list();
		int menu();
		int file_exists(char* name);
		void append_object_to_list_by_address(FileInformation* address);
		void InputString(char* char_pointer);
		char* get_dir_of_file(char* full_file_name);
		char* get_name_of_file(char* full_file_name);
		char* get_size_of_file_in_bytes(char* full_file_name);
		char* get_dates_of_file(char* full_file_name,char which_date);
		char* get_flags_of_file(char* full_file_name,char* just_filename);
		FileInformation* make_an_object_and_return_address_by_filename(char* filename);
		void printf_object_by_address(FileInformation* address);
		int is_hidden(const char *name);
//END OF PROTOTIPING
int main(){
	reconstruct_list();
	read_bin_file_to_list();
	while(menu()==0){printf("\t---press enter to return to menu---\n\t");fflush(stdin);getchar();}
	return 0;
}
//PRIMARY FUNCTIONS
void add_a_file(){
  char full_filename[768];
  printf("\n\tAdding new file");
  printf("\n\t enter the full path of your file: ");
  getchar();
  InputString(full_filename);
  if(file_exists(full_filename)){
  	FileInformation* obj_ptr = make_an_object_and_return_address_by_filename(full_filename);
  	append_object_to_list_by_address(obj_ptr);
  	save_current_list_to_file();
  }else{printf("\tSorry this file doesn't exists\n");}
}
void search_for_file(){}
void count_files_in_directory(){}
void print_list(){
	FileInformation* temp = head;
	while(temp->next != NULL){
		temp = (FileInformation*)(temp->next);
		printf_object_by_address(temp);
	}getchar();
}
//SECONDARY FUNCTIONS
void clear_list(){
  FileInformation* current = head;
  FileInformation* temp;
  while(current->next!=NULL){
    current = (FileInformation*)current->next;
    temp = (FileInformation*)current->next;
    free(current);
    current = head;
  }
}
void reconstruct_list(){
  if(head==NULL){
    head = (FileInformation*)malloc(sizeof(FileInformation));
  }else{
    clear_list();
  }
  head->next = NULL;
}
int count_elements_in_list(){
  FileInformation* temp = head;
	int i = 0;
	while(temp->next != NULL){
		temp = (FileInformation*)(temp->next);
		i++;
	}
	return i;
}
void save_current_list_to_file(){
	FILE* fp = fopen(BIN_FILENAME,"wb");
	int number_of_elements = count_elements_in_list();
	if(fp!=NULL){
		fwrite(&number_of_elements,sizeof(int),1,fp);
		FileInformation* temp = head;
		while(temp->next != NULL){
			temp = (FileInformation*)(temp->next);
			fwrite(temp,sizeof(FileInformation),1,fp);
		}
		fclose(fp);
	}
}
void read_bin_file_to_list(){
  FILE* fp = fopen(BIN_FILENAME,"rb");
  int number_of_elements;
  if(fp!=NULL){
    fread(&number_of_elements,sizeof(int),1,fp);
    FileInformation* temp = head;
    for(;number_of_elements>0;number_of_elements--){
      temp->next = (struct FileInformation*)malloc(sizeof(FileInformation));
      temp = (FileInformation*)temp->next;
      fread(temp,sizeof(FileInformation),1,fp);
    }
    fclose(fp);
  }else{printf("Can\'t read file! It is possible that file not exists yet!\n");}
}
int menu(){
  printf("-----------------------------------------------\n");
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
  printf("-----------------------------------------------\n\n");
  switch(selected_option){
    case '1':add_a_file();return 0;
    case '2':search_for_file();return 0;
    case '3':count_files_in_directory();return 0;
    case '4':print_list();return 0;
    default: return -1;
  }
}
int file_exists(char* name)
{
  struct stat buffer;
  return (stat (name, &buffer) == 0);
}
void append_object_to_list_by_address(FileInformation* address){
	FileInformation* temp = head;
	while(temp->next != NULL){temp = (FileInformation*)(temp->next);}
	temp->next = (struct FileInformation*)address;
	temp = (FileInformation*)(temp->next);
	temp->next = NULL;
}

void InputString(char* char_pointer){
	int i = 0;
	do{
		char_pointer[i++] = getchar();
	}while(char_pointer[i-1]!='\n');
	char_pointer[i-1] = '\0';
}
char* get_dir_of_file(char* full_file_name){
	char* dir = (char*)malloc(sizeof(char)*512);
	int i = 0;
	while(full_file_name[i]!='\0'){i++;}
	while((full_file_name[i]!='\\')&&(full_file_name[i]!='/')){i--;}
	int j = 0;
	while(j<i){
		dir[j] = full_file_name[j++];
	}
	dir[i] = '/';
	dir[++i] = '\0';
	return dir;
}
char* get_name_of_file(char* full_file_name){
	char* name = (char*)malloc(sizeof(char)*256);
	int i = 0,j = 0;
	while(full_file_name[i]!='\0'){i++;}
	while((full_file_name[i]!='\\')&&(full_file_name[i]!='/')){i--;}
	while(full_file_name[i]!='\0'){
		name[j++] = full_file_name[++i];
	}
	name[++j] = '\0';
	return name;
}
char* get_size_of_file_in_bytes(char* full_file_name){
	struct stat st;
	stat(full_file_name, &st);
	long int* size = (long int*)malloc(sizeof(long int));
	*size = st.st_size;
	return (char*)size;
}
char* get_dates_of_file(char* full_file_name,char which_date){
	struct stat attrib;
    stat(full_file_name, &attrib);
    char* date = (char*)malloc(sizeof(char)*11);
    switch(which_date){
    	case 'c':strftime(date, 11, "%d.%m.%Y", localtime(&(attrib.st_ctime)));break;
    	case 'm':strftime(date, 11, "%d.%m.%Y", localtime(&(attrib.st_mtime)));break;
    	default:strcpy(date,"NO.DT.TYPE");
    }
    return date;
}
char* get_flags_of_file(char* full_file_name,char* just_filename){
	int flags[4],rval,i;
	for(i=0;i<4;i++){flags[i]=0;}
	if(is_hidden(just_filename)){flags[0]=1;}
	rval = access (full_file_name, R_OK); access (full_file_name, W_OK);
	if ((rval == 0)&&((errno == EACCES)||(errno == EROFS))){flags[1]=1;}
	struct stat attrib;
    stat(full_file_name, &attrib);
    if (stat(full_file_name, &attrib) == 0 && attrib.st_mode & S_IXUSR){flags[3]=1;}
	char* flags_pointer = (char*)malloc(sizeof(char)*100);
	sprintf(flags_pointer,"hidden = %d, read only = %d, sys = %d, exec = %d",flags[0],flags[1],flags[2],flags[3]);
	return flags_pointer;
}
FileInformation* make_an_object_and_return_address_by_filename(char* filename){
	FileInformation* obj_ptr = (FileInformation*)malloc(sizeof(FileInformation));
	char* file_info[6];int i;
	file_info[0] = get_dir_of_file(filename);
	file_info[1] = get_name_of_file(filename);
	file_info[2] = get_size_of_file_in_bytes(filename);
	file_info[3] = get_dates_of_file(filename,'c');
	file_info[4] = get_dates_of_file(filename,'m');
	file_info[5] = get_flags_of_file(filename,file_info[1]);
	strcpy(obj_ptr->path,file_info[0]);
	strcpy(obj_ptr->filename,file_info[1]);
	obj_ptr->size_in_bytes = *(long int*)(file_info[2]);
	strcpy(obj_ptr->date_of_creation,file_info[3]);
	strcpy(obj_ptr->date_of_modification,file_info[4]);
	strcpy(obj_ptr->flags,file_info[5]);
	for(i = 0;i<6;i++){free(file_info[i]);}
	return obj_ptr;
}
void printf_object_by_address(FileInformation* address){
	printf("\tnow showing info for a file\n");
	printf("\tpath                 = %s\n",address->path);
	printf("\tfilename             = %s\n",address->filename);
	printf("\tsize in bytes        = %ld\n",address->size_in_bytes);
	printf("\tdate of creation     = %s\n",address->date_of_creation);
	printf("\tdate of modification = %s\n",address->date_of_modification);
	printf("\tflags                = %s\n",address->flags);
}
int is_hidden(const char *name){
  return ((name[0] == '.')||(name[strlen(name)-1] == '~')) && (strcmp(name, ".") != 0) && (strcmp(name, "..") != 0);
}
