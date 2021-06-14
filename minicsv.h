/*
miniCSV reader library 
14 Jun 2021, Stefano Braconi, calico.vae@gmail.com

This library implements a simple CSV reader

Released under GPLv3 licence.
*/
#include <iostream>

#define ISASTRING 1
#define NOSTRING 0

#define MAX_FIELD_LENGTH 100	// Field dimension
#define MAX_LINE_MULTIPLIER 10	// Read CSV line dimension
#define MAX_ROW 100		// Maximum number of rows
#define MAX_COL 100		// Maximum number of columns

// #define _CRT_SECURE_NO_WARNINGS

typedef struct
{
	int rows;
	int columns;
	char value[MAX_ROW][MAX_COL][MAX_FIELD_LENGTH];
} csvsheet;

csvsheet readcsv(const char *file, char comma, char cstring);