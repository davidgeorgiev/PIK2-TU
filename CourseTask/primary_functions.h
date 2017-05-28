#ifndef PRIMARY_FUNCTIONS_H
#define PRIMARY_FUNCTIONS_H

/*add_a_file() - функцията добавя нов обект към списъка използвайки функциите InputString(char* char_pointer),
FileInformation* make_an_object_and_return_address_by_filename(char* filename),append_object_to_list_by_address(FileInformation* address),save_current_list_to_file() описани в заглавните ми файлове*/
void add_a_file(){
	printf("%s",CLS);
	char full_filename[768];
	printf("Adding new file\n");
	printf("enter the full path of your file: ");
	InputString(full_filename);
	if(path_exists(full_filename)){
		FileInformation* obj_ptr = make_an_object_and_return_address_by_filename(full_filename);
		append_object_to_list_by_address(obj_ptr);
		save_current_list_to_file();
	}else{printf("%sSorry this file doesn't exists%s\n",KRED,KWHT);}
}
/*search_for_file() - функцията проверява дали файл с въведено име фигурира в списъка и извежда
неговата информация използвайки функциите InputString(full_filename),
print_all_files_with_name(char* search_file) описани в заглавните ми файлове*/
void search_for_file(){
	printf("%s",CLS);
	printf("Searching for file\n");
	printf("enter file to search: ");
	char search_file[256];
	InputString(search_file);
	print_all_files_with_name(search_file);
}
/*count_files_in_directory() - по зададена от потребителя папка, показва колко файла има в нея и колко място заема тя на хардиска (файловете и рекурсивно папките в нея), чрез използване на функциите InputString(char* char_pointer) и print_all_files_in_dir(char* search_dir) описане в заглавните ми файлове*/
void count_files_in_directory(){
	printf("%s",CLS);
	printf("Counting files in dir\n");
	printf("enter dir to search: ");
	char search_dir[512];
	InputString(search_dir);
	print_all_files_in_dir(search_dir);
}
/*print_list() - извежда информация за всички обекти от списъка изпълзвайки функцията printf_object_by_address(FileInformation* address,int index) описана в заглавен файл - my_list.h*/
void print_list(){
	printf("%s",CLS);
	FileInformation* temp = head;int i = 0;
	while(temp->next != NULL){
		i++;
		temp = (FileInformation*)(temp->next);
		printf_object_by_address(temp,i);
	}
}
#endif
