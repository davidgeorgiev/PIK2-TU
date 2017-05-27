#ifndef MY_INPUT_STRING_HEADER
#define MY_INPUT_STRING_HEADER
/*functions*/
/*InputString(char* char_pointer) - моя функция за прочитане на символен низ от клавиатурата*/
void InputString(char* char_pointer){
	fflush(stdin);
	int i = 0;
	do{
		char_pointer[i++] = getchar();
	}while(char_pointer[i-1]!='\n');
	char_pointer[i-1] = '\0';
}
#endif
