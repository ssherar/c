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


struct Event_Info event;
struct Competitor *competitor;
int no_competitors = 0;

void menu();
void startup();
void load_info_files(char filename[]);
void print_competitors();
void load_comp_file(char filename[], int lines);
void print_competitor(struct Competitor comp);

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
                printf("2)\tList competitors\n");
		printf("q)\tExit the application\n");
		printf("\nPlease enter your choice > ");
		scanf(" %c", &menu_choice);
                if('1' == menu_choice) {
                    
                } else if('2' == menu_choice) {
                    int i;
                    for(i = 0; i < no_competitors; i++) {
                        print_competitor(competitor[i]);
                    }
                }
	} while(menu_choice != 'q');
}

void startup() {
	char info_filename[30], competitor_filename[30];
        int competitor_lines;
	printf("Please enter the file for the event information > ");
	scanf(" %30s", info_filename);
	load_info_file(info_filename);
        
        printf("Please enter the file for the competitors > ");
        scanf(" %30s", competitor_filename);
        printf("Filename: %s\n", competitor_filename);
        competitor_lines = get_number_lines(competitor_filename);
        if(0 < competitor_lines) {
            printf("Number of lines: %d\n", competitor_lines);
            //*competitors = malloc(competitor_lines * sizeof(struct Competitor));
            competitor = malloc(competitor_lines * sizeof(struct Competitor));
            load_comp_file(competitor_filename, competitor_lines);
        }
        
        no_competitors = competitor_lines;
        //nodes
        //tracks
        //courses
}

void load_info_file(char filename[]) {
	FILE* fp = NULL;

	fp = fopen(filename, "r");
	if(NULL == fp) {
		printf("\n File Error: cannot load %s", filename);
		return;
	}

        fscanf(fp, " %79[a-zA-Z0-9- ]", event.name);
        fscanf(fp, " %79[a-zA-Z0-9 ]", event.date);
        fscanf(fp, " %5s", event.time);
        
        printf("Event: %s \nOn %s %s\n",
                event.name, event.date, event.time);
        fclose(fp);
}

int get_number_lines(char filename[]) {
    FILE* fp_number_lines = NULL;
    char character;
    int lines = 0;
    
    fp_number_lines = fopen(filename, "r");
    if(NULL == fp_number_lines) {
        printf("File not found\n");
        return -1;
    }
    while((character = fgetc(fp_number_lines)) != EOF) {
        if('\n' == character) {
            lines++;
        }
    }
    fclose(fp_number_lines);
    if(0 == lines) {
        lines++; //as end of files DONT have an \n
    }
    return lines;
}

void load_comp_file(char filename[], int lines) {
    FILE* fp;
    int i = 0;
    char name[50];
    fp = fopen(filename, "r");
    for(i = 0; i < lines; i++) {
        fscanf(fp, "%d %c %50[A-Za-z ]\n", 
                &competitor[i].id, 
                &competitor[i].course_id, 
                competitor[i].name);
    }
    fclose(fp);
}

void print_competitor(struct Competitor comp) {
    printf("Name: %s \t ID: %d \t Course ID: %c \n",
            comp.name,
            comp.id,
            comp.course_id);
}