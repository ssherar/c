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
        printf("Checking %d\n", current->node_id);
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
