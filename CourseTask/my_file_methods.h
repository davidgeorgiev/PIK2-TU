#ifndef MY_FILE_METHODS_HEADER
#define MY_FILE_METHODS_HEADER
/*prototypes*/
int path_exists(char* name);
char* get_dir_of_file(char* full_file_name);
char* get_name_of_file(char* full_file_name);
char* get_size_of_file_in_bytes(char* full_file_name);
char* get_dates_of_file(char* full_file_name,char which_date);
char* get_flags_of_file(char* full_file_name,char* just_filename);
int is_hidden(const char *name);
/*functions*/
int path_exists(char* name)
{
  struct stat buffer;
  return (stat (name, &buffer) == 0);
}
char* get_dir_of_file(char* full_file_name){
	char* dir = (char*)malloc(512);
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
	char* name = (char*)malloc(256);
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
    char* date = (char*)malloc(11);
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
    flags[2] = is_system(full_file_name);
	char* flags_pointer = (char*)malloc(100);
	sprintf(flags_pointer,"hidden = %d, read only = %d, sys = %d, exec = %d",flags[0],flags[1],flags[2],flags[3]);
	return flags_pointer;
}
int is_hidden(const char *name){
  return ((name[0] == '.')||(name[strlen(name)-1] == '~')) && (strcmp(name, ".") != 0) && (strcmp(name, "..") != 0);
}
int is_system(char* full_file_name){
  return ((full_file_name[0] == '/')&&(full_file_name[1] == 's')&&(full_file_name[2] == 'y')&&(full_file_name[3] == 's'));
}
#endif
