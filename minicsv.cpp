#include "minicsv.h"

/*
	parameter file: name od CSV file
	comma: field character separator ex: ' ; '
	cstring: string delimiter character  ex:  ' " '
*/
csvsheet readcsv(const char *file, char comma, char cstring)
{
	csvsheet sheet;	// CSV spreadsheet
	char *res;
	char buffer[MAX_FIELD_LENGTH*MAX_LINE_MULTIPLIER];	//text line buffer
    int rows=0;
    int columns=0;
	FILE *pf=fopen(file,"r");	// Open file in read-only
	if (!pf)
	{
		perror("Error:");
		exit(1);
	}
	int idx_row=0;
	int idx_col=0;
	int idx_buffer=0;
	int idx_str=0;
	int flag=NOSTRING; // flag indicated field is or not a string

	while (!feof(pf))
	{
		res=fgets(buffer, MAX_FIELD_LENGTH*MAX_LINE_MULTIPLIER, pf);	// read entire text line
		if( res==NULL ) break;
		while (buffer[idx_buffer]!='\0')
		{
			if (buffer[idx_buffer]!=cstring) // Read field without quotation " mark (NOSTRING)
			{
				while (buffer[idx_buffer]!=comma && buffer[idx_buffer]!='\0' && buffer[idx_buffer]!='\n')
				{
					sheet.value[idx_row][idx_col][idx_str]=buffer[idx_buffer];
					idx_buffer++;
					idx_str++;
				}
				sheet.value[idx_row][idx_col][idx_str]='\0';
				idx_str=0;
				idx_buffer++;
				idx_col++;
				if (rows==0 )columns++;
			}
			else // The field init with quotation mark " (ISATRING) and now if i found a "" or ; the loop don't end
			{
				flag=ISASTRING;
				idx_buffer++;
				while (flag!=NOSTRING && buffer[idx_buffer]!='\0' && buffer[idx_buffer]!='\n' )
				{
					if (buffer[idx_buffer]==cstring && buffer[idx_buffer+1]!=cstring)  // Terminated string 
					{
						flag=NOSTRING;
						idx_buffer+=2;
					}
					else 
					{
						sheet.value[idx_row][idx_col][idx_str]=buffer[idx_buffer];
						idx_buffer++;
						idx_str++;
					}
				}
				sheet.value[idx_row][idx_col][idx_str+1]='\0';
				idx_col++;
				if (rows==0)columns++;
			}
			// printf("%s - ",sheet.value[idx_row][idx_col-1]); // DEBUG
			idx_str=0;			
		}
		// printf("\n"); // DEBUG
		idx_col=0;
		idx_row++;
		rows++;
		idx_buffer=0;
	}
	sheet.rows=rows;
	sheet.columns=columns;
	return sheet;
}
