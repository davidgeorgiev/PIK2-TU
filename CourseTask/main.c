#include "libra.h"
#include "my_list.h"
#include "primary_functions.h"
#include "my_menu.h"

int main(){
	reconstruct_list();
	read_bin_file_to_list();
	menu_loop();
	return 0;
}



