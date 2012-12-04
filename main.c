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
#include        "fileio.h"


struct Event_Info event;
struct Competitor *competitor;
struct Node *node_types;
Course *course;
Track *tracks;
int no_competitors = 0;

void menu();
void startup();
void print_competitor(struct Competitor comp);
void print_competitors();

int main(int argc, char *argv[]) {
    startup();
    menu();
    return EXIT_SUCCESS;
}

void menu() {
    char menu_choice = 'A';
    do {
        printf("Welcome to %s on %s %s! \n\n",
                event.name, event.date, event.time);
        printf("\t1)\tQuery Location of Competitor\n");
        printf("\t2)\tQuery status of competitors\n");
        printf("\t3)\tSupply times for individual competitors\n");
        printf("\t4)\tRead checkpoint data from file\n");
        printf("\t5)\tList competitors with times\n");
        printf("\tq)\tExit the application\n");
        printf("\n > ");
        scanf(" %c", &menu_choice);
        if ('1' == menu_choice) {

        } 
    } while (menu_choice != 'q');
}

void startup() {
    char info_filename[30], competitor_filename[30]
            , node_filename[30], course_filename[30], tracks_filename[30];
    int competitor_lines, node_lines, courses_lines, tracks_lines;

    printf("Please enter the file for the event information > ");
    scanf(" %30s", info_filename);
    load_info_file(info_filename, &event);

    printf("Please enter the file for the node type > ");
    scanf(" %30s", node_filename);
    node_lines = get_number_lines(node_filename);
    if (0 < node_lines) {
        node_types = malloc(node_lines * sizeof (struct Node));
        load_node_file(node_filename, node_lines, node_types);
    }

    printf("Please enter the file for the competitors > ");
    scanf(" %30s", competitor_filename);
    competitor_lines = get_number_lines(competitor_filename);

    if (0 < competitor_lines) {
        competitor = malloc(competitor_lines * sizeof (struct Competitor));
        load_comp_file(competitor_filename, competitor_lines, competitor);
    }
    printf("Please enter the file for the courses > ");
    scanf(" %30s", course_filename);
    courses_lines = get_number_lines(course_filename);

    if (0 < courses_lines) {
        course = malloc(courses_lines * sizeof (Course));
        load_courses_file(course_filename, courses_lines,
                course, node_types);
    }

    printf("Please enter the file for the tracks > ");
    scanf(" %30s", tracks_filename);
    tracks_lines = get_number_lines(tracks_filename);

    if (0 < tracks_lines) {
        tracks = malloc(tracks_lines * sizeof (Track));
        load_track_file(tracks_filename, tracks_lines, &tracks);
    }

    no_competitors = competitor_lines;
}


void print_competitor(struct Competitor comp) {
    printf("Name: %s \t ID: %d \t Course ID: %c \n",
            comp.name,
            comp.id,
            comp.course_id);
}



/** node.c */
void insert_node(Course_Node* current, Course_Node* value) {
    if (current == NULL) {
        current = value;
    } else if (NULL == current->next) {
        current->next = value;
    } else {
        insert_node(current->next, value);
    }
}

void print_list(Course_Node** head) {
    Course_Node* current = (Course_Node*) head;
    while (current != NULL) {
        printf("%s\n", current->type);
        current = current->next;
    }
}