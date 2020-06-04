/* */
#include "structures.h"

int floatValidate(float x, char *op, float y) {
    float diff = x - y;
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

void deleteFloatLine(t_floatLine *line) {
    if (line->cells != NULL) {
        t_floatCell *aux, *c = line->cells;

        while (c != NULL) {
            aux = c;
            c = c->next;
            free(aux);
        }
    }

    line->cells = NULL;
    free(line);
}

void printFloatCell(t_floatCell *cell) {
    int nrChars;
    printf("%f %n", cell->value, &nrChars);

    for (; nrChars <= MAX_COLUMN_NAME_LEN; nrChars++) {
        printf(" ");
    }
}

void printFloatLine(t_floatLine *line) {
    if (line != NULL) {
        if (line-> cells != NULL) {
            t_floatCell *cell = line->cells;

            while (cell != NULL) {
                printFloatCell(cell);
                cell = cell->next;
            }
            printf("\n");
        }
    }
}

void browseFloatLines(t_floatLine *line, void(*lineFunc)(t_floatLine*)) {
    t_floatLine *aux;

    while (line != NULL) {
        aux = line;
        line = line->next;
        lineFunc(aux);
    }
}

int validateFloatLine(t_floatLine *line, float val, char *rel, int col) {
    if (line->cells != NULL) {
        t_floatCell *c = line->cells;

        while (c != NULL && col > 1) {
            col--;
            c = c->next;
        }

        return floatValidate(c->value, rel, val);
    }

    return 0;
}

void qryDelFloat(t_table *table, int columnNo, char *relation, float val) {
    t_floatLine *l = (t_floatLine*)table->lines, *prev = NULL, *aux;

    while (l != NULL) {
        if (validateFloatLine(l, val, relation, columnNo) == 1) {
            if (prev == NULL) {
                table->lines = (void*)l->next;
                aux = l;
                l = l->next;
                deleteFloatLine(aux);

            } else {
                aux = l;
                l = l->next;
                prev->next = l;
                deleteFloatLine(aux);
            }

        } else {
            prev = l;
            l = l->next;
        }
    }
}

void qryPrintFloat(t_table *table, int columnNo, char *relation, float val) {
    t_floatLine *l = (t_floatLine*)table->lines;

    while (l != NULL) {
        if (validateFloatLine(l, val, relation, columnNo) == 1) {
            printFloatLine(l);
        }

        l = l->next;
    }
}

t_floatCell* createFloatCell(float val) {
    t_floatCell *c = (t_floatCell*) calloc(1, sizeof(t_floatCell));
    if (c == NULL) {
        return NULL;
    }

    c->value = val;

    return c;
}

t_floatLine* createFloatLine(char *values) {
    t_floatLine *line = (t_floatLine*) calloc(1, sizeof(t_floatLine));
    if (line == NULL) {
        return NULL;
    }

    if (values != NULL) {
        char *val = strtok(values, " ");
        line->cells = createFloatCell(atof(val));
        t_floatCell *c = line->cells;

        val = strtok(NULL, " ");
        while (val != NULL) {
            c->next = createFloatCell(atof(val));


            if (c->next == NULL) {
                deleteFloatLine(line);
                return NULL;
            }

            c = c->next;
            val = strtok(NULL, " ");
        }
    }

    return line;
}

void addFloatLines(t_table *t, char *values) {
    if (t->lines != NULL) {
        t_floatLine *l = t->lines;

        while (l->next != NULL) {
            l = l->next;
        }
        l->next = (void*)createFloatLine(values);

    } else {
        t->lines = (void*)createFloatLine(values);
    }
}
