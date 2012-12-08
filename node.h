/*
 * =====================================================================================
 *
 *       Filename:  node.h
 *
 *    Description:  Functions for manipulating linked list data structures
 *
 *        Version:  1.0
 *        Created:  12/02/2012 00:12:41 AM
 *       Revision:  none
 *       Compiler:  gcc -Wall
 *
 *         Author:  Samuel Sherar (sbs1), sbs1@aber.ac.uk
 *        Company:  Aberystwyth University
 *
 * =====================================================================================
 */


#ifndef NODE_H
#define	NODE_H

#ifdef	__cplusplus
extern "C" {
#endif


    void insert_node(Course_Node* current, Course_Node* value);
    void print_list(Course_Node** head);
    Course_Node* find_node(Course_Node* current, int node_id);
    Course_Node* find_node_head(Course_Node** head, int node_id);
    Course_Node* check_next_empty(Course_Node** head);
    void insert_checkpoint_data(Course** head, int comp_id, int checkpoint_id, char time[]);
    void insert_checkpoint_data_manually(Course** head, int comp_id, int checkpoint_id, char time[]);
    Course_Node* find_current_node(Course_Node** head);

#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

