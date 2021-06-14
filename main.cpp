/*
miniCSV reader library 
14 Jun 2021, Stefano Braconi, calico.vae@gmail.com

test main function
*/

#include "minicsv.h"


int main()
{
	csvsheet sheet;
	sheet=readcsv("test.csv",';','"');
	printf("rows: %d    columns: %d",sheet.rows, sheet.columns);
	
	return 0;
}
