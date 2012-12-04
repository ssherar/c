/* 
 * File:   fileio.h
 * Author: sam
 *
 * Created on December 4, 2012, 6:26 PM
 */

#ifndef FILEIO_H
#define	FILEIO_H

#include "data_struct.h"

void load_info_files(char filename[], Event_Info *event);
void load_comp_file(char filename[], int lines, Competitor *comp);
void load_node_file(char filename[], int lines, Node *node_types);
void load_courses_file(char filename[], int lines, 
        Course *course, Node *node_types);
void load_track_file(char filename[], int lines, Track *tracks);
int get_number_lines(char filename[]);

#endif	/* FILEIO_H */

