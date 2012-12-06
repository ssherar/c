#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "node.h"
//#include "data_struct.h"

void load_info_file(char filename[], Event_Info *event) {
    FILE* fp = NULL;

    fp = fopen(filename, "r");
    if (NULL == fp) {
        printf("\n File Error: cannot load %s", filename);
        return;
    }

    fscanf(fp, " %79[a-zA-Z0-9- ]", event->name);
    fscanf(fp, " %79[a-zA-Z0-9 ]", event->date);
    fscanf(fp, " %5s", event->time);

    fclose(fp);
}

int get_number_lines(char filename[]) {
    FILE* fp_number_lines = NULL;
    char character;
    int lines = 0;

    fp_number_lines = fopen(filename, "r");
    if (NULL == fp_number_lines) {
        printf("File not found\n");
        return -1;
    }
    while ((character = fgetc(fp_number_lines)) != EOF) {
        if ('\n' == character) {
            lines++;
        }
    }
    fclose(fp_number_lines);
    if (0 == lines) {
        lines++; //as end of files DONT have an \n
    }
    return lines;
}

void load_comp_file(char filename[], int lines, Competitor comp[]) {
    FILE* fp;
    int i = 0;
    fp = fopen(filename, "r");
    for (i = 0; i < lines; i++) {
        fscanf(fp, "%d %c %50[A-Za-z ]\n",
                &comp[i].id,
                &comp[i].course_id,
                comp[i].name);
    }
    fclose(fp);
}

void load_node_file(char filename[], int lines, Node *node_types) {
    FILE* fp;
    int i = 0;
    fp = fopen(filename, "r");
    for (i = 0; i < lines; i++) {
        fscanf(fp, "%d %2s",
                &node_types[i].id,
                node_types[i].type);
    }
    fclose(fp);
}

void load_courses_file(char filename[], int lines, Course *course, 
        Node *node_types, Competitor *comp, int comp_lines) {
    FILE* fp;
    int i = 0, j = 0, amount_nodes = 0, comp_index = 0;
    char id;
    fp = fopen(filename, "r");
    for (i = 0; i < lines; i++) {
        fscanf(fp, "%c %d", &id, &amount_nodes);
        course[i].id_name = id;
        course[i].length = amount_nodes;
        course[i].head = NULL;
        strcpy(course[i].start_time, "NULL");
        strcpy(course[i].end_time, "NULL");
        for (j = 0; j < amount_nodes; j++) {
            int val = 0;
            Course_Node *tmp;
            tmp = malloc(sizeof (Course_Node));
            fscanf(fp, " %d", &val);
            strcpy(tmp->type, node_types[val].type);
            tmp->node_id = val;
            tmp->next = NULL;
            if (0 == j) {
                course[i].head = tmp;
            } else {
                insert_node((Course_Node*) course[i].head, tmp);
            }
            fscanf(fp, "\n");
        }
        for(comp_index = 0; comp_index < comp_lines; comp_index++) {
            if(course[i].id_name == comp[comp_index].course_id) {
                comp[comp_index].course = course[i];
            }
        }
    }
    fclose(fp);
}

void load_track_file(char filename[], int length, Track *tracks) {
    FILE* fp;
    int i = 0;

    fp = fopen(filename, "r");
    for (i = 0; i < length; i++) {
        fscanf(fp,
                "%d %d %d %d",
                &tracks[i].id,
                &tracks[i].start,
                &tracks[i].finish,
                &tracks[i].time);
    }
    fclose(fp);
}

void load_time_file(char filename[], int length, Competitor* comp, int comp_length) {
    FILE* fp;
    int i = 0, node_index, comp_index;
    char cp_type[3], date[5];
    fp = fopen(filename, "r");
    for(i = 0; i < length; i++) {
        fscanf(fp,"%c %d %d %5s\n",
                cp_type,
                &node_index,
                &comp_index,
                date);
        if('T' == cp_type) {
            Course_Node *current = find_node((Course_Node*) comp[comp_index].course.head,
                    node_index);
            printf("%d\n", current->node_id);
        }
    }
    fclose(fp);
}