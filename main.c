
#include <unistd.h>


#include "memtools.h"

int main(){
	char * str = MEMTOOLS_MALLOC(1024); 
	char * str1 = MEMTOOLS_MALLOC(2);
	int * a = MEMTOOLS_MALLOC(4 * 20);

	memtools_report();
	
	MEMTOOLS_FREE(str);
	MEMTOOLS_FREE(str1);
	MEMTOOLS_FREE(a);
	
	memtools_report();

}
