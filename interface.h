#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>

void print_list(FILE *fp);

void add_to_list(FILE *fp);

void delete_list();

void edit_list(FILE *fp);

void new_list(FILE *fp);

void delete_from_list(FILE *fp);

#endif