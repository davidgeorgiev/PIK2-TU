#include "libra.h"
#include "my_list.h"
#include "primary_functions.h"
#include "my_menu.h"

/*Главната функция на програмата. Тя извиква функцията - reconstruct_list() - конструктор на списъка и функцията read_bin_file_to_list(), която прочита бинарния файл и го записва в списъка, намиращи се в моя header file с име my_list.h, след което изпълнява функцията menu_loop(), грижеща се за менюто на програмата, която се намира в моя header file с име my_menu.h*/
int main(){
	reconstruct_list();
	read_bin_file_to_list();
	menu_loop();
	return 0;
}



