/** node.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"

void insert_node(Course_Node* current, Course_Node* value) {
    if (current == NULL) {
        current = value;
    } else if (NULL == current->next) {
        current->next = value;
    } else {
        insert_node(current->next, value);
    }
}

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

Course_Node* find_node_head(Course_Node** head, int node_id) {
    return find_node((Course_Node*) head, node_id);
}


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

void print_list(Course_Node** head) {
    Course_Node* current = (Course_Node*) head;
    while (current != NULL) {
        printf("%d\t%s\t%s\n", current->node_id, current->type, current->time);
        current = current->next;
    }
}


void insert_checkpoint_data(Course** head, int comp_id, int checkpoint_id, char *time) {
    Course_Node* found = (Course_Node*) find_node_head(head, checkpoint_id);
    Course_Node* next_empty = (Course_Node*) check_next_empty(head, checkpoint_id);
    if(found != NULL && next_empty != NULL) {
        //if(found == next_empty) {
            strcpy(next_empty->time, time);
            printf("Node %d was hit at %s by competitor %d\n",
                    next_empty->node_id,
                    next_empty->time,
                    comp_id);
        /*} else {
            printf("Not at correct checkpoint for COMP %d at NODE %d\n",
                    comp_id, checkpoint_id);
        }*/
    } else {
        printf("Error: cannot find any empty times for Competitor %d\n");
    }
}

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
