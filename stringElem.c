/*  */
#include "structures.h"

int stringValidate(char *x, char *op, char *y) {
    int diff = strcmp(x, y);
    if (strcmp(op, "<") == 0) {
        return (diff < 0 ? 1 : 0);

    } else if (strcmp(op, "<=") == 0) {
        return (diff <= 0 ? 1 : 0);

    } else if (strcmp(op, "==") == 0) {
        return (diff == 0 ? 1 : 0);

    } else if (strcmp(op, "!=") == 0) {
        return (diff != 0 ? 1 : 0);

    } else if (strcmp(op, ">=") == 0) {
        return (diff >= 0 ? 1 : 0);

    } else {
        return (diff > 0 ? 1 : 0);
    }
}

void printStringCell(t_stringCell *cell) {
    int nrChars;
    printf("%s %n", cell->value, & nrChars);

    for (; nrChars <= MAX_COLUMN_NAME_LEN; nrChars++) {
        printf(" ");
    }
}

void printStringLine(t_stringLine *line) {
    if (line != NULL) {
        if (line->cells != NULL) {
            t_stringCell *cell = line->cells;

            while (cell != NULL) {
                printStringCell(cell);
                cell = cell->next;
            }
            printf("\n");
        }
    }
}

void deleteStringCell(t_stringCell *cell) {
    if (cell != NULL) {
        if (cell->value != NULL) {
            free(cell->value);
        }

        free(cell);
    }
}

void deleteStringLine(t_stringLine *line) {
    if (line->cells != NULL) {
        t_stringCell *aux, *c = line->cells;

        while (c != NULL) {
            aux = c;
            c = c->next;
            deleteStringCell(aux);
        }
    }

    line->cells = NULL;
    free(line);
}

int validateStringLine(t_stringLine *line, char *val, char *rel, int col) {
    if (line->cells != NULL) {
        t_stringCell *c = line->cells;

        while (c != NULL && col > 1) {
            col--;
            c = c->next;
        }
        return stringValidate(c->value, rel, val);
    }

    return 0;
}

void browseStringLines(t_stringLine *line, void(*lineFunc)(t_stringLine*)) {
    t_stringLine *aux;

    while (line != NULL) {
        aux = line;
        line = line->next;
        lineFunc(aux);
    }
}

void qryDelString(t_table *table, int columnNo, char *relation, char *val) {
    t_stringLine *l = (t_stringLine*)table->lines, *prev = NULL, *aux = NULL;

    while (l != NULL) {
        if (validateStringLine(l, val, relation, columnNo) == 1) {
            if (prev == NULL) {
                table->lines = (void*)l->next;
                aux = l;
                l = l->next;
                deleteStringLine(aux);

            } else {
                aux = l;
                l = l->next;
                prev->next = l;
                deleteStringLine(aux);
            }

        } else {
            prev = l;
            l = l->next;
        }
    }
}

void qryPrintString(t_table *table, int columnNo, char *relation, char *val) {
    t_stringLine *l = (t_stringLine*)table->lines;

    while (l != NULL) {
        if (validateStringLine(l, val, relation, columnNo) == 1) {
            printStringLine(l);
        }

        l = l->next;
    }
}

t_stringCell* createStringCell(char *val) {
    t_stringCell *c = (t_stringCell*)calloc(1, sizeof(t_stringCell));
    if (c == NULL) {
        return NULL;
    }

    c->value = (char*)calloc(strlen(val) + 1, sizeof(char));
    if (c->value == NULL) {
        free(c);
        return NULL;
    }

    strcpy(c->value, val);

    return c;
}

t_stringLine* createStringLine(char *values) {
    t_stringLine *line = (t_stringLine*)calloc(1, sizeof(t_stringLine));
    if (line == NULL) {
        return NULL;
    }

    if (values != NULL) {
        char *val = strtok(values, " ");
        line->cells = createStringCell(val);
        t_stringCell *c = line->cells;

        val = strtok(NULL, " ");
        while (val != NULL) {
            c->next = createStringCell(val);

            if (c->next == NULL) {
                deleteStringLine(line);
                return NULL;
            }

            c = c->next;
            val = strtok(NULL, " ");
        }
    }

    return line;
}

void addStringLines(t_table *t, char *values) {
    if (t->lines != NULL) {
        t_stringLine *l = t->lines;

        while (l->next != NULL) {
            l = l->next;
        }
        l->next = (void*)createStringLine(values);
        
    } else {
        t->lines = (void*)createStringLine(values);
    }
}
