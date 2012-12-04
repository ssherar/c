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
#include        <string.h>
#include	"data_struct.h"


struct Event_Info event;
struct Competitor *competitor;
struct Node *node_types;
Course *course;
int no_competitors = 0;

void menu();
void startup();
void load_info_files(char filename[]);
void print_competitors();
void load_comp_file(char filename[], int lines);
void print_competitor(struct Competitor comp);
void load_node_file(char filename[], int lines);

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
                printf("3)\tList Course\n");
		printf("q)\tExit the application\n");
		printf("\nPlease enter your choice > ");
		scanf(" %c", &menu_choice);
                if('1' == menu_choice) {
                    
                } else if('2' == menu_choice) {
                    int i;
                    for(i = 0; i < no_competitors; i++) {
                        print_competitor(competitor[i]);
                    }
                } else if('3' == menu_choice) {
                    print_list(course[0].head);
                }
	} while(menu_choice != 'q');
}

void startup() {
	char info_filename[30], competitor_filename[30]
           , node_filename[30], course_filename[30], tracks_filename[30];
        int competitor_lines, node_lines, courses_lines, tracks_lines;
        
	printf("Please enter the file for the event information > ");
	scanf(" %30s", info_filename);
	load_info_file(info_filename);
        
        printf("Please enter the file for the node type > ");
        scanf(" %30s", node_filename);
        node_lines = get_number_lines(node_filename);
        if(0 < node_lines) {
            node_types = malloc(node_lines * sizeof(struct Node));
            load_node_file(node_filename, node_lines);
        }
        
        printf("Please enter the file for the competitors > ");
        scanf(" %30s", competitor_filename);
        competitor_lines = get_number_lines(competitor_filename);
        
        if(0 < competitor_lines) {
            competitor = malloc(competitor_lines * sizeof(struct Competitor));
            load_comp_file(competitor_filename, competitor_lines);
        }
        printf("Please enter the file for the courses > ");
        scanf(" %30s", course_filename);
        courses_lines = get_number_lines(course_filename);
        
        if(0 < courses_lines) {
            course = malloc(courses_lines * sizeof(Course));
            load_courses_file(course_filename, courses_lines);
        }
        
        printf("Please enter the file for the tracks > ");
        scanf(" %30s", tracks_filename);
        tracks_lines = get_number_lines(tracks_filename);
        
        if(0 < tracks_lines) {
            
        }
        
        no_competitors = competitor_lines;
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

void load_node_file(char filename[], int lines) {
    FILE* fp;
    int i = 0;
    fp = fopen(filename, "r");
    for(i = 0; i < lines; i++) {
        fscanf(fp, "%d %2s\n",
                &node_types[i].id,
                node_types[i].type);
    }
    fclose(fp);
}

void load_courses_file(char filename[], int lines) {
    FILE* fp;
    int i = 0, j = 0, amount_nodes = 0;
    char id;
    fp = fopen(filename, "r");
    for(i = 0; i < lines; i++) {
        fscanf(fp, "%c %d", &id, &amount_nodes);
        course[i].id_name = id;
        course[i].length = amount_nodes;
        course[i].head = NULL;
        for(j = 0; j < amount_nodes; j++) {
            int val = 0;
            Course_Node *tmp;
            tmp = malloc(sizeof(Course_Node));
            fscanf(fp, " %d", &val);
            strcpy(tmp->type, node_types[val].type);
            tmp->node_id = val;
            tmp->next = NULL;
            if(0 == j) {
                course[i].head = tmp;
            } else {
                insert_node((Course_Node*) course[i].head, tmp);
            }
        }
    }
    fclose(fp);
}
/** node.c */
void insert_node(Course_Node* current, Course_Node* value) {
    if(current == NULL) {
        current = value;
    } else if(NULL == current->next) {
        current->next = value;
    } else {
        insert_node(current->next, value);
    }
}

void print_list(Course_Node** head) {
    Course_Node* current = (Course_Node*) head;
    while(current != NULL) {
        printf("%s\n", current->type);
        current = current->next;
    }
}