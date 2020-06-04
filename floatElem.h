/* */
#ifndef INCLUDE__FLOATELEM_H
#define INCLUDE__FLOATELEM_H_

#include "structures.h"

/* all functions and procedures in this header are for t_floatCell and
 * t_floatLine data types only
 */

/*
 * function used to determine wether the element of the line makes its line
 * the one the commands "SEARCH" or "DELETE" are looking for: returns 1 if it
 * is and 0 if it is not
 */
int floatValidate(float x, char *op, float y);

// procedure that frees the memory allocated for a given line and its elements
void deleteFloatLine(t_floatLine *line);

/*
 * procedure that prints a given cell and provides the required padding for
 * allignment
 */
void printFloatCell(t_floatCell *cell);

/*
 * procedure that traverses the cells of a line, applying for each of them
 * their specific printing procedure
 */
void printFloatLine(t_floatLine *line);

/*
 * procedure used to traverse each line of a table, applying to each of them
 * the given procedure passed by the parameter "lineFunc"
 */
void browseFloatLines(t_floatLine *line, void (*lineFunc)(t_floatLine*));

/*
 * function that searches for the cell required to tell if the line is the one
 * that the commands "SEARCH" or "DELETE" are looking for: returns 1 if indeed
 * it is the wanted one, and 0 if it is not
 */
int validateFloatLine(t_floatLine *line, float val, char *rel, int col);

/*
 * procedure used by the "DELETE" command; it traverses the lines of a given
 * table and deletes the ones that satisfy the condition given by the user
 */
void qryDelFloat(t_table *table, int columnNo, char *relation, int val);

/*
 * procedure used by the "SEARCH" command; it traverses the lines of a given
 * table and outputs the ones that satisfy the condition given by the user
 */
void qryPrintFloat(t_table *table, int columnNo, char *relation, int val);

// function that returns a newly allocated cell with a given float value
t_floatCell* createFloatCell(float val);

// function that returns a newly allocated line with given float values
t_floatLine* createFloatLine(char *values);

// procedure that adds lines of given float values to a given table
void addFloatLines(t_table *t, char *values);

#endif
