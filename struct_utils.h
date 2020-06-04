/* */
#ifndef INCLUDE_STRUCT_UTILS_H
#define INCLUDE_STRUCT_UTILS_H

#include "structures.h"

// function that returns a newly allocated database, with a given name
t_db *initDB(char *name);

// procedure that frees the memory allocated for a given table
void deleteTable(t_table *table);

// procedure that frees the memory allocated for a given database
void deleteDB(t_db **db);
/*
 * procedure that searches in the database for a table with a given name and
 * applies to it the procedure passed by the "tableFunc" parameter
 */
void findNamedTable(t_db *db, char *name, void (*tableFunc)(t_table*));

// procedure that outputs a linked list of given columns
void printColumns(t_column *column);

// procedure that outputs the contents of a given table
void printTable(t_table* table);

// procedure that outputs the contents of a given database
void printDB(t_db* db);

// function that returns a newly allocated column linked list with given names
t_column* createColumn(char *name);

/*function that returns a newly allocated table of a given type and with a
 * given name - also allocates the columns with given names
 */
t_table* createTable(char *name, char *type, char *columns);

/*
 * function that returns the position of the column whose elements the
 * commands "SEARCH" and "DELETE" are looking for: returns -1 if no column is
 * found
 */
int whichColumn(t_table *table, char *columnName);

// frees the memory allocated for a given table
void clearTable(t_table *table);

#endif
