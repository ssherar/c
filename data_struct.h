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

typedef struct Course{
   char id_name;
   int length;
   struct Course_Node **head;
} Course;

typedef struct Course_Node {
    int node_id;
    char type[2];
    struct Course_Node *next;
} Course_Node;

struct Competitor {
    int id;
    char course_id;
    char name[50];
};

struct Node {
    int id;
    char type[2];
};

typedef struct Track {
   int id;
   int start;
   int finish;
   int time;
} Track;