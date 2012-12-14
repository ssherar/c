/*
 * =====================================================================================
 *
 *       Filename:  node.c
 *
 *    Description:  Functions for manipulating linked list data structures
 *
 *        Version:  1.0
 *        Created:  12/01/2012 11:43:13 PM
 *       Revision:  none
 *       Compiler:  gcc -Wall
 *
 *         Author:  Samuel Sherar (sbs1), sbs1@aber.ac.uk
 *        Company:  Aberystwyth University
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"

Track find_track(Track *tracks, int node_from, int node_to, int no_tracks);
int get_time_from_char(char time[]);

/**
 * insert a node at the end of the list recursively.
 * @param current the current node
 * @param value the node to be inserted
 */
void insert_node(Course_Node* current, Course_Node* value) {
    if (current == NULL) {
        current = value;
    } else if (NULL == current->next) {
        current->next = value;
    } else {
        insert_node(current->next, value);
    }
}

/**
 * Find a node with a certain amount node identifier recursively
 * @param current the current node to be checked
 * @param node_id the node identifier
 * @return a pointer to the found node, NULL if not found
 */
Course_Node* find_node(Course_Node* current, int node_id) {
    if(current->node_id == node_id) {
        return current;
    } else {
        if(current == NULL) {
                return NULL;
        }
        return find_node(current->next, node_id);
    }
}

/**
 * An entry point to the find_node(current, id) when the parameter
 * is a pointer to a Course_Node pointer.
 * @param head the head of the list(as a Pointer to a Pointer)
 * @param node_id the node identifier
 * @return a pointer to the found node, NULL if not found
 */
Course_Node* find_node_head(Course_Node** head, int node_id) {
    return find_node((Course_Node*) head, node_id);
}

/**
 * Find the next node which is empty which has a certain identifier
 * @param head the head of the list (which is a pointer to a pointer)
 * @param id the node identifier
 * @return a pointer to the found node, NULL if not found.
 */
Course_Node* check_next_empty(Course_Node** head, int id) {
    Course_Node* current = (Course_Node*) head;
    while(current != NULL) {
        if(strcmp(current->type, "CP") == 0 && current->node_id == id) {
            if(current->time[0] == NULL) {
                return current;
            }
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Finds the last node which is not empty
 * @param head the head of the list
 * @return a pointer to the found node, NULL if not found
 */
Course_Node* find_current_node(Course_Node** head) {
    Course_Node* current = (Course_Node*) head;
    Course_Node* prev_cp;
    while(current != NULL) {
        if(strcmp(current->type, "CP") == 0) {
            if(current->time[0] == NULL) {
                return prev_cp;
            }
            prev_cp = current;
        }
        
        current = current->next;
    }
    return NULL;
}

/**
 * A debug function which prints out the list
 * @param head the head of the list
 */
void print_list(Course_Node** head) {
    Course_Node* current = (Course_Node*) head;
    while (current != NULL) {
        printf("%d\t%s\t%s\n", current->node_id, current->type, current->time);
        current = current->next;
    }
}

/**
 * A method which stores the data passed in from the file in the next 
 * empty node available
 * @param head the head of the list
 * @param comp_id the competitor id
 * @param checkpoint_id the checkpoint identifier
 * @param time the time
 */
void insert_checkpoint_data(Course** head, int comp_id, int checkpoint_id, char *time) {
    Course_Node* found = (Course_Node*) find_node_head(head, checkpoint_id);
    Course_Node* next_empty = (Course_Node*) check_next_empty(head, checkpoint_id);
    if(found != NULL && next_empty != NULL) {
        strcpy(next_empty->time, time);
        printf("Node %d was hit at %s by competitor %d\n",
                next_empty->node_id,
                next_empty->time,
                comp_id);
    } else {
        printf("Error: cannot find any empty times for Competitor %d \n",
                comp_id);
    }
}

/**
 * A method to insert the data manually
 * @param head the head of the list
 * @param comp_id the competitor id
 * @param checkpoint_id the checkpoint identifier
 * @param time the time
 */
void insert_checkpoint_data_manually(Course** head, int comp_id, int checkpoint_id, char time[]) {
    Course_Node* found = (Course_Node*) find_node_head(head, checkpoint_id);
    if(found != NULL) {
        strcpy(found->time, time);
        printf("Node %d was hit at %s by competitor %d\n",
                    found->node_id,
                    found->time,
                    comp_id);
    } else {
        printf("error: cannot find node %d", checkpoint_id);
    }
}

char* calc_total_time(Course course) {
    if(*course.start_time == NULL || *course.end_time == NULL) {
        return "";
    }
    int min_minutes, min_hours, max_minutes, max_hours,
            total_minutes, diff_hours, diff_minutes;
    char retVal[6];
    min_hours = atoi(strtok(course.start_time, ":"));
    min_minutes = atoi(strtok(NULL, ":"));
    
    max_hours = atoi(strtok(course.end_time, ":"));
    max_minutes = atoi(strtok(NULL, ":"));
    
    total_minutes = ((max_hours*60) + max_minutes)-((min_hours*60) + min_minutes);
    diff_hours = (total_minutes/60) % 60;
    diff_minutes = total_minutes % 60;
    sprintf(retVal, "%02d:%02d", diff_hours, diff_minutes);
    return retVal;
}

Track find_current_track(Course_Node** head, Track* tracks, int no_tracks) {
    Course_Node *last_node = find_current_node(head);
    Course_Node *current = (Course_Node*) head;
    int start_minutes = get_time_from_char(current->time);
    int end_minutes = get_time_from_char(last_node->time);
    int difference = end_minutes - start_minutes;
    int track_total = 0;
    while(current != NULL && current != last_node) {
        Track current_track = find_track(tracks, current->node_id, current->next->node_id, no_tracks);
        track_total += current_track.time;
        if(track_total > difference) {
            return current_track;
        }
        current = current->next;
    }
}

Track find_track(Track *tracks, int node_from, int node_to, int no_tracks) {
    int i = 0;
    for(i; i < no_tracks; i++) {
        if((tracks[i].start == node_to || tracks[i].start == node_from)
            && (tracks[i].finish == node_to || tracks[i].finish == node_from)) {
            return tracks[i];
        }
    }
    
}

int get_time_from_char(char time[]) {
    int minutes;
    minutes = atoi(strtok(time, ":")) * 60;
    minutes += atoi(strtok(NULL, ":"));
    return minutes;
}
