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
#include        "node.h"


struct Event_Info event;
struct Competitor* competitor;
struct Node *node_types;
Track *tracks;
int no_competitors = 0, no_courses;

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
        printf("\t3)\tSupply times for individual competitor\n");
        printf("\t4)\tRead checkpoint data from file\n");
        printf("\t5)\tList competitors with times\n");
        printf("\tq)\tExit the application\n");
        printf("\n > ");
        scanf(" %c", &menu_choice);
        if ('1' == menu_choice) {

        } else if('3' == menu_choice) {
            int id = -1, node_id = -1;
            int debug = -1;
            char time[5];
            printf("Please enter the ID for the competitor > ");
            scanf(" %d", &id);
            printf("Please enter the node which he has just hit > ");
            debug = scanf(" %d", &node_id);
            printf("%d\n", debug);
            printf("Please enter the time he reached the checkpoint > ");
            scanf(" %5s", time);
            insert_checkpoint_data_manually(competitor[id-1].course.head, id, node_id, time);
        } else if('2' == menu_choice) {
          printf("\t1)\tQuery how many which haven't started\n");
          printf("\t2)\tQuery how many people are on the courses\n");
          printf("\t3)\tQuery how many people have finished\n");
          printf("\n > ");
          scanf(" %c", &menu_choice);
          if('1' == menu_choice) {
              int not_started = find_not_started(competitor, no_competitors);
              printf("Number of competitors not started: %d\n", not_started);
          }
        } else if('4' == menu_choice) { 
            load_time_file("data/cp_times_1.txt", 29, competitor, no_competitors);
            //load_time_file("data/cp_data_2.txt", 32, competitor, no_competitors);
        } else if('5' == menu_choice) {
            //print_competitors();
            print_list((Course_Node*) competitor[0].course.head);
        }
    } while (menu_choice != 'q');
}

int find_not_started(Competitor comp[], int no_comp) {
    int amount = 0, i = 0;
    for(i = 0; i < no_comp; i++) {
        /*if(strcmp(comp[i].course.start_time, "NULL") == 0) {
            amount++;
        }*/
        if(*comp[i].course.start_time == NULL) {
            amount++;
        }
    }
    return amount;
}

int find_finished(Competitor comp[], int no_comp) {
    int amount =0, i = 0;
    for(i = 0; i < no_comp; i++) {
        if(*comp[i].course.end_time != NULL &&
                *comp[i].course.start_time != NULL) {
            amount++;
        } 
    }
    return amount;
}

void startup() {
    char info_filename[30], competitor_filename[30]
            , node_filename[30], course_filename[30], tracks_filename[30];
    int competitor_lines, node_lines, courses_lines, tracks_lines;

    printf("Please enter the file for the event information > ");
    //scanf(" %30s", info_filename);
    strcpy(info_filename,"data/event_info.txt");
    load_info_file(info_filename, &event);

    printf("Please enter the file for the node type > ");
    //scanf(" %30s", node_filename);
    strcpy(node_filename, "data/node.txt");
    node_lines = get_number_lines(node_filename);
    if (0 < node_lines) {
        node_types = (Node*) malloc(node_lines * sizeof (struct Node));
        load_node_file(node_filename, node_lines, node_types);
    }

    printf("Please enter the file for the competitors > ");
    //scanf(" %30s", competitor_filename);
    strcpy(competitor_filename, "data/comp_data.txt");
    competitor_lines = get_number_lines(competitor_filename);
    no_competitors = competitor_lines;
    
    if (0 < competitor_lines) {
        competitor = (Competitor*) malloc(competitor_lines * sizeof (Competitor));
        load_comp_file(competitor_filename, competitor_lines, competitor);
    }
    printf("Please enter the file for the courses > ");
    //scanf(" %30s", course_filename);
    strcpy(course_filename, "data/courses.txt");
    courses_lines = get_number_lines(course_filename);

    if (0 < courses_lines) {
        load_courses_file(course_filename, courses_lines,
                 node_types, competitor, no_competitors);
    }

    printf("Please enter the file for the tracks > ");
    strcpy(tracks_filename,"data/tracks.txt");
    tracks_lines = get_number_lines(tracks_filename);

    if (0 < tracks_lines) {
        tracks = (Track*) malloc(tracks_lines * sizeof (Track));
        load_track_file(tracks_filename, tracks_lines, tracks);
    }

    no_courses = courses_lines;
}

void print_competitors() {
    int i;
    for(i = 0; i < no_competitors; i++) {
        print_competitor(competitor[i]);
    }
}

void print_competitor(struct Competitor comp) {
    printf("Name: %30s \t ID: %2d \t Course ID: %c  Start: %s\tEnd: %s\n",
            comp.name,
            comp.id,
            comp.course_id,
            comp.course.start_time,
            comp.course.end_time);
}

