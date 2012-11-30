/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main file for the assignment
 *
 *        Version:  1.0
 *        Created:  11/28/2012 06:33:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel Sherar (ss), sbs1@aber.ac.uk
 *        Company:  Aberystwyth University
 *
 * =====================================================================================
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	"data_struct.h"


typedef struct Event_Info event;
	
void menu();
void startup();

int main ( int argc, char *argv[] )
{
	startup();
	menu();
	return EXIT_SUCCESS;
}

void menu() {
	char menu_choice = 'A';
	do {
		printf("1)\tQuery Location of Competitor\n");
		printf("q)\tExit the application\n");
		printf("\nPlease enter your choice > ");
		scanf(" %c", &menu_choice);
	} while(menu_choice != 'q');
}

void startup() {
	char info_filename[30];
	printf("Please enter the file for the event information > ");
	scanf(" %30s", &info_filename);
	load_info_file(info_filename);
}

void load_info_file(char filename[]) {
	FILE* fp = NULL;
	char line[128];
	fp = fopen(filename, "r");
	if(NULL == fp) {
		printf("\n File Error: cannot load %s", filename);
		return;
	}
	
	fgets(event.name, sizeof event.name, fp);
	printf("Event name: %s", event.name);	
}
