#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>

void print_list(FILE *fp);

char *trim_spaces(char *str);

int check_valid_date(char date[11]);

int check_valid_time(char time[100]);

void add_to_list(FILE *fp);

void delete_from_list(FILE *fp);

void edit_list(FILE *fp);

void new_list();

void revert_changes(FILE *fp);

#endif