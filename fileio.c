/*
 * =====================================================================================
 *
 *       Filename:  fileio.c
 *
 *    Description:  The file handling file, which stores the data in the 
 *                  relevant data structures created in data_struct.h
 *
 *        Version:  1.0
 *        Created:  11/30/2012 02:15:43 PM
 *       Revision:  none
 *       Compiler:  gcc -Wall
 *
 *         Author:  Samuel Sherar (sbs), sbs1@aber.ac.uk
 *        Company:  Aberystwyth University
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "node.h"

/**
 * The method to read in the info file
 * @param filename the filename of the event file
 * @param event a pointer to the event data structure
 */
void load_info_file(char filename[], Event_Info *event) {
    FILE* fp = NULL;

    fp = fopen(filename, "r");
    if (NULL == fp) {
        printf("\n File Error: cannot load %s", filename);
        return;
    }

    fscanf(fp, " %79[a-zA-Z0-9- ]", event->name);
    fscanf(fp, " %79[a-zA-Z0-9 ]", event->date);
    fscanf(fp, " %5s", event->time);

    fclose(fp);
}

/**
 * Reads through the whole file checking for the
 * occurrences of the NL character  
 * @param filename
 * @return the amount of lines in the file.
 */
int get_number_lines(char filename[]) {
    FILE* fp_number_lines = NULL;
    char character;
    int lines = 0;

    fp_number_lines = fopen(filename, "r");
    if (NULL == fp_number_lines) {
        printf("File not found\n");
        return -1;
    }
    while ((character = fgetc(fp_number_lines)) != EOF) {
        if ('\n' == character) {
            lines++;
        }
    }
    fclose(fp_number_lines);
    if (0 == lines) {
        lines++;
    }
    return lines;
}

/**
 * Loads the competitors from the file given in the parameter 
 * @param filename the filename
 * @param lines the amount of lines in the filename
 * @param comp the competitor data structure to fill
 */
void load_comp_file(char filename[], int lines, Competitor comp[]) {
    FILE* fp;
    int i = 0;
    fp = fopen(filename, "r");
    for (i = 0; i < lines; i++) {
        fscanf(fp, "%d %c %50[A-Za-z ]\n",
                &comp[i].id,
                &comp[i].course_id,
                comp[i].name);
    }
    fclose(fp);
}

/**
 * Loads the nodes from the file given in the parameter
 * @param filename the filename
 * @param lines the amount of lines in the filename
 * @param node_types the nodes data structure to fill
 */
void load_node_file(char filename[], int lines, Node *node_types) {
    FILE* fp;
    int i = 0;
    fp = fopen(filename, "r");
    for (i = 0; i < lines; i++) {
        fscanf(fp, "%d %2s",
                &node_types[i].id,
                node_types[i].type);
    }
    fclose(fp);
}

/**
 * Loads the courses and creates a linked list of Course_Nodes for each
 * competitor.
 * @param filename the filename
 * @param lines the amount of lines in the filename
 * @param node_types the data structure of the different types of nodes
 * @param comp the competitor data structures to fill
 * @param comp_lines the amount of competitors
 */
void load_courses_file(char filename[], int lines,
        Node *node_types, Competitor *comp, int comp_lines) {
    FILE* fp;
    fp = fopen(filename, "r");
    int i;
    //for lines
    for (i=0; i < lines; i++) {
        //malloc array for nodes
        int amount, *nodes, node_index, comp_index;
        char id;
        fscanf(fp, "%c %d", &id, &amount);
        nodes = malloc(amount * sizeof(int));
        //for amount of nodes
        for(node_index = 0; node_index < amount; node_index++) {
                //assign to array
            int val;
            fscanf(fp," %d", &val);
            nodes[node_index] = val;
        }
        fscanf(fp, "\n");
        //foreach competitors
        for(comp_index = 0; comp_index < comp_lines; comp_index++) {
                //if course id matches
            if(id == comp[comp_index].course_id) {
                        //create linked list
                
                for(node_index = 0; node_index < amount; node_index++) {
                    Course_Node *tmp = malloc(sizeof(Course_Node));
                    int node_val = nodes[node_index];
                    strcpy(tmp->type, node_types[node_val - 1].type);
                    tmp->time[0] = NULL;
                    tmp->node_id = nodes[node_index];
                    tmp->next = NULL;
                    if(0 == node_index) {
                        comp[comp_index].course.head = tmp;
                        comp[comp_index].course.start_time = &tmp->time;
                    } else if(node_index == (amount -1)) {
                        insert_node((Course_Node*) comp[comp_index].course.head
                                , tmp);
                        comp[comp_index].course.end_time = &tmp->time;
                    } else {
                        insert_node((Course_Node*) comp[comp_index].course.head
                                , tmp);
                    }
                }
            }
        }
    }
    fclose(fp);
}

/**
 * Loads the tracks from the file
 * @param filename the filename
 * @param length the amount of lines in the filename
 * @param tracks the data structure to fill
 */
void load_track_file(char filename[], int length, Track *tracks) {
    FILE* fp;
    int i = 0;

    fp = fopen(filename, "r");
    for (i = 0; i < length; i++) {
        fscanf(fp,
                "%d %d %d %d",
                &tracks[i].id,
                &tracks[i].start,
                &tracks[i].finish,
                &tracks[i].time);
    }
    fclose(fp);
}

/**
 * Loads the time files and insert it into the relevant competitor
 * @param filename the filename
 * @param length the amount of lines in the file
 * @param comp the competitor data structure
 */
void load_time_file(char filename[], int length, Competitor* comp) {
    FILE* fp;
    int i = 0, node_index, comp_index;
    char cp_type, date[6];
    fp = fopen(filename, "r");
    for(i = 0; i < length; i++) {
        fscanf(fp, "%c %d %d %5s\n",
                &cp_type,
                &node_index,
                &comp_index,
                date);
        
        if(cp_type == 'T') {
            insert_checkpoint_data(comp[comp_index - 1].course.head, comp_index, node_index, date);
        }
    }
    fclose(fp);
}