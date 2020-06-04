/* */
#ifndef INCLUDE_INTELEM_H
#define INCLUDE_INTELEM_H

#include "structures.h"

/* all functions and procedures in this header are for t_intCell and t_intLine
 * data types only
 */

/*
 * function used to determine wether the element of the line makes its line
 * the one the commands "SEARCH" or "DELETE" are looking for: returns 1 if it
 * is and 0 if it is not
 */
int intValidate(int x, char *op, int y);

// procedure that frees the memory allocated for a given line and elements
void deleteIntLine(t_intLine *line);

/*
 * procedure that prints a given cell and provides the required padding for
 * allignment
 */
void printIntCell(t_intCell *cell);

/*
 * procedure that traverses the cells of a line, applying for each of them
 * their specific printing procedure
 */
void printIntLine(t_intLine *line);

/*
 * procedure used to traverse each line of a table, applying to each of them
 * the given procedure passed by the parameter "lineFunc"
 */
void browseIntLines(t_intLine *line, void (*lineFunc)(t_intLine*));

/*
 * function that searches for the cell required to tell if the line is the one
 * that the commands "SEARCH" or "DELETE" are looking for: returns 1 if indeed
 * it is the wanted one, and 0 if it is not
 */
int validateIntLine(t_intLine *line, int val, char *rel, int col);

/*
 * procedure used by the "DELETE" command; it traverses the lines of a given
 * table and deletes the ones that satisfy the condition given by the user
 */
void qryDelInt(t_table *table, int columnNo, char *relation, int val);

/*
 * procedure used by the "SEARCH" command; it traverses the lines of a given
 * table and outputs the ones that satisfy the condition given by the user
 */
void qryPrintInt(t_table *table, int columnNo, char *relation, int val);

// function that returns a newly allocated cell with a given int value
t_intCell* createIntCell(int val);

// function that returns a newly allocated line with given int values
t_intLine* createIntLine(char *values);

// procedure that adds lines of given int values to a given table
void addIntLines(t_table *t, char *values);

#endif
