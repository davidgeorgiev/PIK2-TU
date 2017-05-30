#ifndef MY_MENU_H
#define MY_MENU_H

char* option_descs[5];//глобален масив от указатели към тип char, който ще съдържа опциите на менюто
int selected_option = 0;//глобална променлива съдържаща номера на текущата избрана опция. Глобална е с цел да се запазва при презареждане на менюто
/*iterate_options(int curr,int up_or_down) - функцията приема номера на текущата избрана опция и посоката на
преместване и връща нов номер на съседна опция, като ако е в началото или в края превърта опцията*/
int iterate_options(int curr,int up_or_down){
	if(up_or_down){
		curr--;
	}else{
		curr++;
	}
	if(curr<0){curr = 4;}
	if(curr>4){curr = 0;}
	return curr;
}
/*menu_descs_init() - функцията инициализира масива от опциите с тяхното описание, копирайки съдържанието
на константни символни низове на съответните индекси*/
void menu_descs_init(){
	strcpy(option_descs[0]," add new file                           ");
	strcpy(option_descs[1]," search for file and show info          ");
	strcpy(option_descs[2]," count files in directory and show size ");
	strcpy(option_descs[3]," print all list                         ");
	strcpy(option_descs[4]," exit                                   ");
}
/*make_them_caps_or_not(char* str,int caps_or_not) - функцията е свързана главно с дизайна на менюто
тя уголемява или намалява буквите на опцията с подаден аргумент, от който се определя кое от двете
да направи*/
void make_them_caps_or_not(char* str,int caps_or_not){
	int j;char start,end,step;
	if(caps_or_not){
		start = 'a';end = 'z';step = -32;
	}else{
		start = 'A';end = 'Z';step = 32;
	}
	for(j = 0;str[j]!='\0';j++){
		if((str[j]>=start)&&(str[j]<=end)){
			str[j]+=step;
		}
	}
}
/*menu_print(int selected_option) - функцията се грижи менюто да се изведе по правилен начин
в зависимост от избраната опция, която се подава като аргумент*/
void menu_print(int selected_option){
	int i;
	printf("%s",CLS);
	printf("%s                                          %s\n",BMAG,BNRM);
	printf("%s %s",BMAG,BNRM);
	printf("%s%s MENU OPTIONS                           ",BYEL,KBLU);
	printf("%s %s\n",BMAG,BNRM);
	printf("%s",KCYN);
	for(i = 0;i < 5;i++){
		printf("%s %s",BMAG,BNRM);
		if(selected_option == i){printf("%s%s",BMAG,KWHT);make_them_caps_or_not(option_descs[i],1);}
		printf("%s",option_descs[i]);
		if(selected_option == i){printf("%s%s",BNRM,KCYN);make_them_caps_or_not(option_descs[i],0);}
		printf("%s %s\n",BMAG,BNRM);
	}
	printf("%s",KWHT);
	printf("%s                                          %s\n",BMAG,BNRM);
}
/*menu_run() - функцията следи за натискане на бутоните със стрелките, като променя опцията,
използвайки функцията iterate_options(int curr,int up_or_down), в зависимост от избраната стрелка,
извиква функцията за опресняване на менюто - menu_print(int selected_option) описана по-горе и
се грижи да изпълни подходящата функция от другия ми header file с име primary functions*/
int menu_run(){
	char c = ' ';
	do{
		system ("/bin/stty cooked");
		if (c == '\033') { // if the first value is esc
			getchar(); // skip the [
			switch(getchar()) { // the real value
				case 'A':
				// code for arrow up
				selected_option = iterate_options(selected_option,1);
				break;
				case 'B':
				// code for arrow down
				selected_option = iterate_options(selected_option,0);
				break;
				//case 'C':
				// code for arrow right
				//break;
				//case 'D':
				// code for arrow left
				//break;
			}
		}
		menu_print(selected_option);
		system ("/bin/stty raw");
	}while((c=getchar())!= 13);
	system ("/bin/stty cooked");
	switch(selected_option){
		case 0:add_a_file();return 0;
		case 1:search_for_file();return 0;
		case 2:count_files_in_directory();return 0;
		case 3:print_list();return 0;
		default: return -1;
	}
}
/*menu_loop() - функцията се грижи за цикъла на менюто, тя не приема аргументи и не връща стойност, 
но въпреки това е много важна, защото се грижи за правилното заделяне на паметта на указателите
към описанията на опциите, както и за освобождаването на тяхната памет. Функцията спира, когато
menu_run() върне стойност различна от 0, в случая стойността на -1*/
void menu_loop(){
	int i;
	for(i=0;i<5;i++){option_descs[i] = (char*)malloc(50);}
	menu_descs_init();
	while(menu_run()==0){printf("---press enter to return to menu---\n");fflush(stdin);getchar();}
	for(i=0;i<5;i++){free(option_descs[i]);}
	printf("%s",KNRM);//set colors default
	printf("%s",CLS);
}

#endif
