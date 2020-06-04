/* */
#include "structures.h"

int intValidate(int x, char *op, int y) {
    int diff = x - y;
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

void deleteIntLine(t_intLine *line) {
    if (line != NULL) {
        if (line->cells != NULL) {
            t_intCell *aux, *c = line->cells;

            while (c != NULL) {
                aux = c;
                c = c->next;
                free(aux);
            }
        }

        line->cells = NULL;
    }
    free(line);
}

void printIntCell(t_intCell *cell) {
    int nrChars;
    printf("%d %n", cell->value, & nrChars);

    for (; nrChars <= MAX_COLUMN_NAME_LEN; nrChars++) {
        printf(" ");
    }
}

void printIntLine(t_intLine *line) {
    if (line != NULL) {
        if (line->cells != NULL) {
            t_intCell *cell = line->cells;

            while (cell != NULL) {
                printIntCell(cell);
                cell = cell->next;
            }
            printf("\n");
        }
    }
}

void browseIntLines(t_intLine *line, void(*lineFunc)(t_intLine*)) {
    t_intLine *aux;

    while (line != NULL) {
        aux = line;
        line = line->next;
        lineFunc(aux);
    }
}

int validateIntLine(t_intLine *line, int val, char *rel, int col) {
    if (line->cells != NULL) {
        t_intCell *c = line->cells;

        while (c != NULL && col > 1) {
            col--;
            c = c->next;
        }

        return intValidate(c->value, rel, val);
    }

    return 0;
}

void qryDelInt(t_table *table, int columnNo, char *relation, int val) {
    t_intLine *l = (t_intLine*)table->lines, *prev = NULL, *aux = NULL;

    while (l != NULL) {
        if (validateIntLine(l, val, relation, columnNo) == 1) {
            if (prev == NULL) {
                table->lines = (void*)l->next;
                aux = l;
                l = l->next;
                deleteIntLine(aux);

            } else {
                aux = l;
                l = l->next;
                prev->next = l;
                deleteIntLine(aux);
            }

        } else {
            prev = l;
            l = l->next;
        }
    }
}

void qryPrintInt(t_table *table, int columnNo, char *relation, int val) {
    t_intLine *l = (t_intLine*)table->lines;

    while (l != NULL) {
        if (validateIntLine(l, val, relation, columnNo) == 1) {
            printIntLine(l);
        }

        l = l->next;
    }
}

t_intCell* createIntCell(int val) {
    t_intCell *c = (t_intCell*)calloc(1, sizeof(t_intCell));
    if (c == NULL) {
        return NULL;
    }

    c->value = val;

    return c;
}

t_intLine* createIntLine(char *values) {
    t_intLine *line = (t_intLine*)calloc(1, sizeof(t_intLine));
    if (line == NULL) {
        return NULL;
    }

    if (values != NULL) {
        char *val = strtok(values, " ");
        line->cells = createIntCell(atoi(val));
        t_intCell *c = line->cells;

        val = strtok(NULL, " ");
        while (val != NULL) {
            c->next = createIntCell(atoi(val));

            if (c->next == NULL) {
                deleteIntLine(line);
                return NULL;
            }

            c = c->next;
            val = strtok(NULL, " ");
        }
    }

    return line;
}

void addIntLines(t_table *t, char *values) {
    if (t->lines != NULL) {
        t_intLine *l = t->lines;

        while (l->next != NULL) {
            l = l->next;
        }
        l->next = (void*)createIntLine(values);
        
    } else {
        t->lines = (void*)createIntLine(values);
    }
}
