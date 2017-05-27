#ifndef MY_LIST_H_INCLUDED
#define MY_LIST_H_INCLUDED
#include "bin_filename.h"
#include "my_input_string.h"
#include "my_file_methods.h"
/*global part*/
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
/*prototypes*/
void clear_list();
void reconstruct_list();
int count_elements_in_list();
void save_current_list_to_file();
void read_bin_file_to_list();
void append_object_to_list_by_address(FileInformation* address);
FileInformation* make_an_object_and_return_address_by_filename(char* filename);
void printf_object_by_address(FileInformation* address,int index);
void print_all_files_with_name(char* search_file);
void print_all_files_in_dir(char* search_dir);
/*functions*/
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
void append_object_to_list_by_address(FileInformation* address){
	FileInformation* temp = head;
	while(temp->next != NULL){temp = (FileInformation*)(temp->next);}
	temp->next = (struct FileInformation*)address;
	temp = (FileInformation*)(temp->next);
	temp->next = NULL;
	printf("\t%sfile successfuly added to list\n%s",KGRN,KWHT);
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
void printf_object_by_address(FileInformation* address,int index){
	printf("\t%sNOW SHOWING INFO FOR FILE %d\n",KGRN,index);
	printf("\t%spath                 = %s\n",KYEL,address->path);
	printf("\tfilename             = %s\n",address->filename);
	printf("\tsize in bytes        = %ld\n",address->size_in_bytes);
	printf("\tdate of creation     = %s\n",address->date_of_creation);
	printf("\tdate of modification = %s\n",address->date_of_modification);
	printf("\tflags                = %s%s\n",address->flags,KWHT);
}
void print_all_files_with_name(char* search_file){
	int something_found = 0,i = 0;
	FileInformation* temp = head;
	while(temp->next != NULL){
		i++;
		temp = (FileInformation*)(temp->next);
		if(strcmp(temp->filename,search_file)==0){
			something_found = 1;
			printf_object_by_address(temp,i);
		}
	}
	if(!something_found){
		printf("\t%sNo files with name \"%s\"%s\n",KRED,search_file,KWHT);
	}
}
void print_all_files_in_dir(char* search_dir){
	int i,if_in_dir,j,counter = 0;long int summed_size = 0;
	FileInformation* temp = head;
	while(temp->next != NULL){
		i++;
		temp = (FileInformation*)(temp->next);
		if_in_dir = 1;
		for(j = 0;search_dir[j]!='\0';j++){
			if(search_dir[j]!=(temp->path)[j]){
				if_in_dir = 0;
				break;
			}
		}
		if(if_in_dir){
			counter++;
			summed_size+=temp->size_in_bytes;
		}
	}
	if(!counter){
		printf("\t%sNo file in such directory in the list%s\n",KRED,KWHT);
	}else{
		printf("\t%sCounted files: %d; Summed size: %ld%s\n",KGRN,counter,summed_size,KWHT);
	}
}
#endif
