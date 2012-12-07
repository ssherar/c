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

typedef struct Event_Info {
   char name[79];
   char date[79];
   char time[6];
} Event_Info;

typedef struct Course{
   char id_name;
   int length;
   //char start_time[5];
   int *start_time;
   char end_time[5];
   struct Course_Node **head;
} Course;

typedef struct Course_Node {
    int node_id;
    char type[2];
    char time[5];
    struct Course_Node *next;
} Course_Node;

typedef struct Competitor {
    int id;
    char course_id;
    Course course;
    char name[50];
} Competitor;

typedef struct Node {
    int id;
    char type[2];
} Node;

typedef struct Track {
   int id;
   int start;
   int finish;
   int time;
} Track;