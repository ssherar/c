/*
 * =====================================================================================
 *
 *       Filename:  fileio.h
 *
 *    Description:  the header file for the filio.c
 *
 *        Version:  1.0
 *        Created:  11/30/2012 04:45:03 PM
 *       Revision:  none
 *       Compiler:  gcc -Wall
 *
 *         Author:  Samuel Sherar (sbs1), sbs1@aber.ac.uk
 *        Company:  Aberystwyth University
 *
 * =====================================================================================
 */

#ifndef FILEIO_H
#define	FILEIO_H

#include "data_struct.h"

void load_info_files(char filename[], Event_Info *event);
void load_comp_file(char filename[], int lines, Competitor * comp);
void load_node_file(char filename[], int lines, Node *node_types);
void load_courses_file(char filename[], int lines, 
         Node *node_types, Competitor *comp, int comp_lines);
void load_track_file(char filename[], int lines, Track *tracks);
int get_number_lines(char filename[]);
void load_time_file(char filename[], int length, Competitor* comp);

#endif	/* FILEIO_H */

