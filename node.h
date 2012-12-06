/* 
 * File:   node.h
 * Author: sam
 *
 * Created on December 6, 2012, 5:09 PM
 */

#ifndef NODE_H
#define	NODE_H

#ifdef	__cplusplus
extern "C" {
#endif


    void insert_node(Course_Node* current, Course_Node* value);
    void print_list(Course_Node** head);
    Course_Node* find_node(Course_Node* current, int node_id);

#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */
