/* */
#ifndef INCLUDE_STRINGELEM_H
#define INCLUDE_STRINGELEM_H

#include "structures.h"

/* all functions and procedures in this header are for t_stringCell and
 * t_stringLine data types only
 */

/*
 * function used to determine wether the element of the line makes its line
 * the one the commands "SEARCH" or "DELETE" are looking for: returns 1 if it
 * is and 0 if it is not
 */
int stringValidate(char *x, char *op, char *y);

/*
 * procedure that prints a given cell and provides the required padding for
 * allignment
 */
void printStringCell(t_stringCell *cell);

/*
 * procedure that traverses the cells of a line, applying for each of them
 * their specific printing procedure
 */
void printStringLine(t_stringLine *line);

// procedure that frees the memory allocated fora given t_stringCell
void deleteStringCell(t_stringCell *cell);

// procedure that frees the memory allocated for a given line and elements
void deleteStringLine(t_stringLine *line);

/*
 * procedure used to traverse each line of a table, applying to each of them
 * the given procedure passed by the parameter "lineFunc"
 */
void browseStringLines(t_stringLine *line, void (*lineFunc)(t_stringLine*));

/*
 * function that searches for the cell required to tell if the line is the one
 * that the commands "SEARCH" or "DELETE" are looking for: returns 1 if indeed
 * it is the wanted one, and 0 if it is not
 */
int validateStringLine(t_stringLine *line, char *val, char *rel, int col);

/*
 * procedure used by the "DELETE" command; it traverses the lines of a given
 * table and deletes the ones that satisfy the condition given by the user
 */
void qryDelString(t_table *table, int columnNo, char *relation, char *val);

/*
 * procedure used by the "SEARCH" command; it traverses the lines of a given
 * table and outputs the ones that satisfy the condition given by the user
 */
void qryPrintString(t_table *table, int columnNo, char *relation, char *val);

// function that returns a newly allocated cell with a given string
t_stringCell* createStringCell(char *val);

// function that returns a newly allocated line with given strings
t_stringLine* createStringLine(char *values);

// procedure that adds lines of given strings to a given table
void addStringLines(t_table *t, char *values);

#endif
