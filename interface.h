#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>

void print_list(FILE *fp);

char *trim_spaces(char *str);

int check_valid_date(char date[11]);

int check_valid_time(char time[100]);

void add_to_list(FILE *fp);

void delete_from_list();

void new_list();

void write_info(char subject[100], char subject_edit[100]);

void edit_info();

void revert_changes(FILE *fp);

#endif