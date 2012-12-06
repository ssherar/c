/** node.c */
#include <stdio.h>
#include <stdlib.h>
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
        find_node(current->next, node_id);
    }
}

void print_list(Course_Node** head) {
    Course_Node* current = (Course_Node*) head;
    while (current != NULL) {
        printf("%s\n", current->type);
        current = current->next;
    }
}
