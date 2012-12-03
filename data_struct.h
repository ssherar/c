/*
 * =====================================================================================
 *
 *       Filename:  data_struct.h
 *
 *    Description:  hold all the data structures needed
 *
 *        Version:  1.0
 *        Created:  11/29/2012 02:14:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel Sherar (ss), sbs1@aber.ac.uk
 *        Company:  Aberystwyth University
 *
 * =====================================================================================
 */

struct Event_Info {
   char name[79];
   char date[79];
   char time[6];
};

struct Course {
   char id_name;
   int length;
   struct Course_Node *head;
};

struct Course_Node {
    struct Node_Type 
    struct Course_Node *next;
};

struct Competitor {
    int id;
    char course_id;
    char name[50]; /* fprintf has to have type %50[a-zA-Z ] */
};

struct Node_Type {
    int id_number;
    char[2] type;
};
