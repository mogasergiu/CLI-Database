/* */
#include "intElem.h"
#include "stringElem.h"
#include "floatElem.h"

t_db* initDB(char *name) {
    t_db *newDB = (t_db*)calloc(1, sizeof(t_db));
    if (newDB == NULL) {
        return NULL;
    }

    strcpy(newDB->name, name);
    newDB->name[strlen(newDB->name) - 1] = '\0';

    return newDB;
}

void deleteTable(t_table *table) {
    if (table != NULL) {
        if (table->columns != NULL) {
            t_column *aux, *c = table->columns;

            while (c != NULL) {
                aux = c;
                c = c->next;
                free(aux);
            }
            table->columns = NULL;
        }

        if (table->lines != NULL) {
            switch (table->type) {
                case INT:
                    browseIntLines((t_intLine*)table->lines, deleteIntLine);
                    break;
                case STRING:
                    browseStringLines((t_stringLine*)table->lines,
                                        deleteStringLine);
                    break;
                case FLOAT:
                    browseFloatLines((t_floatLine*)table->lines,
                                        deleteFloatLine);
                    break;
            }

            table->lines = NULL;
        }

        free(table);
    }
}

void deleteDB(t_db **db) {
    if (*db != NULL) {
        if ((*db)->tables != NULL) {
            t_table *aux, *t = (*db)->tables;

            while (t != NULL) {
                aux = t;
                t = t->next;
                deleteTable(aux);
            }
            (*db)->tables = NULL;
        }
    }

    free(*db);
    *db = NULL;
}

void findNamedTable(t_db *db, char *name, void(*tableFunc)(t_table*)) {
    if (db != NULL) {
        if (db->tables != NULL) {
            t_table *aux = NULL, *t = db->tables;
            while (t != NULL && strcmp(t->name, name) != 0) {
                aux = t;
                t = t->next;
            }

            if (t == NULL) {
                printf("Table \"%s\" not found in database.\n", name);
                return;
            }

            /*
             * if the found table is to be deleted, an extra step must be
             * taken into consideration: unless the found table is the first
             * one in the table list, in which case the first table of the
             * list will be the one after the found table, the previous table
             * ("aux") has to be connected to the table after the found table
             */
            if (tableFunc == &deleteTable) {
                if (aux == NULL) {
                    db->tables = t->next;
                } else {
                    aux->next = t->next;
                }
            }

            tableFunc(t);

        } else {
            printf("Table \"%s\" not found in database.\n", name);
        }
    }
}

void printColumns(t_column *column) {
    int nrChars, nrCol = 0;

    for (; column != NULL; column = column->next) {
        printf("%s %n", column->name, &nrChars);
        nrCol++;

        for (; nrChars <= MAX_COLUMN_NAME_LEN; nrChars++) {
            printf(" ");  // outputs the required padding for allignment
        }
    }
    printf("\n");

    for (; nrCol > 0; nrCol--) {
        printf("------------------------------ ");
    }
    printf("\n");
}

void printTable(t_table *table) {
    printf("TABLE: %s\n", table->name);
    printColumns(table->columns);

    switch (table->type) {
        case INT:
            browseIntLines((t_intLine*)table->lines, printIntLine);
            break;
        case FLOAT:
            browseFloatLines((t_floatLine*)table->lines, printFloatLine);
            break;
        case STRING:
            browseStringLines((t_stringLine*)table->lines, printStringLine);
            break;
    }
    printf("\n");
}

void printDB(t_db *db) {
    if (db != NULL) {
        printf("DATABASE: %s\n\n", db->name);

        if (db->tables != NULL) {
            t_table *t = db->tables;

            while (t != NULL) {
                printTable(t);
                t = t->next;
            }
        }
    }
}

t_column* createColumn(char *name) {
    t_column *c = (t_column*)calloc(1, sizeof(t_column));
    if (c == NULL) {
        return NULL;
    }

    strcpy(c->name, name);

    return c;
}

t_table* createTable(char *name, char *type, char *columns) {
    t_table *newTable = (t_table*)calloc(1, sizeof(t_table));
    if (newTable == NULL) {
        return NULL;
    }

    strcpy(newTable->name, name);

    if (strcmp(type, "INT") == 0) {
        newTable->type = INT;

    } else if (strcmp(type, "STRING") == 0) {
        newTable->type = STRING;

    } else if (strcmp(type, "FLOAT") == 0) {
        newTable->type = FLOAT;

    } else {
        printf("Unknown data type: \"%s\".\n", type);
        return NULL;
    }

    char *columnName = strtok(columns, " ");
    newTable->columns = createColumn(columnName);
    if (newTable->columns == NULL) {
        free(newTable);
        return NULL;
    }

    t_column *c = newTable->columns;
    while ((columnName = strtok(NULL, " ")) != NULL) {
        c->next = createColumn(columnName);
        if (c->next == NULL) {
            deleteTable(newTable);
            return NULL;
        }

        c = c->next;
    }

    return newTable;
}

int whichColumn(t_table *table, char *columnName) {
    if (table != NULL && columnName != NULL) {
        t_column *column;
        int nrCol = 0;
        for (column = table->columns; column != NULL; column = column->next) {
            nrCol++;
            if (strcmp(column->name, columnName) == 0) {
                return nrCol;
            }
        }
    }

    return -1;
}

void clearTable(t_table *table) {
    if (table != NULL) {
        switch (table->type) {
            case INT:
                browseIntLines((t_intLine*)table->lines, deleteIntLine);
                break;
            case FLOAT:
                browseFloatLines((t_floatLine*)table->lines, deleteFloatLine);
                break;
            case STRING:
                browseStringLines((t_stringLine*)table->lines,
                                    deleteStringLine);
                break;
        }

            table->lines = NULL;
    }
}
