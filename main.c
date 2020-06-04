/* */
#include "struct_utils.h"
#include "intElem.h"
#include "stringElem.h"
#include "floatElem.h"

int main() {
    char *cmd = (char*) malloc((MAX_CMD_LEN + 1) * sizeof(char));
    t_db *db;
    size_t maxCMD = MAX_CMD_LEN;
    while (getline(&cmd, &maxCMD, stdin)) {
        char *function = strtok(cmd, " ");
        if (strcmp(function, "INIT_DB") == 0) {
            char *dbName = strtok(NULL, " ");
            db = initDB(dbName);

        } else if (strcmp(function, "DELETE_DB\n") == 0) {
            deleteDB(&db);
            free(cmd);
            return 0;

        } else if (strcmp(function, "CREATE") == 0) {
            char *name = strtok(NULL, " ");
            char *type = strtok(NULL, " ");
            char *columns = strtok(NULL, "\n");

            if (db->tables == NULL) {
                db->tables = createTable(name, type, columns);
            } else {
                if (db->tables != NULL) {
                    t_table *t = db->tables, *aux;
                    int valid = 1;

                    while (t != NULL) {
                        if ((valid = strcmp(t->name, name)) == 0) {
                            printf("Table \"%s\" already exists.\n", name);
                            break;
                        }
                        aux = t;
                        t = t->next;
                    }
                    if (valid != 0) {
                        aux->next = createTable(name, type, columns);
                    }
                }
            }

        } else if (strcmp(function, "DELETE") == 0) {
            char *parameters = strtok(NULL, " ");

            // if a table is to be deleted
            if (parameters[strlen(parameters) - 1] == '\n') {
                parameters[strlen(parameters) - 1] = '\0';
                findNamedTable(db, parameters, deleteTable);

            } else {  // if a specific line is to be deleted
                char *tableName = parameters;
                if (db->tables != NULL) {
                    char *columnName = strtok(NULL, " ");
                    char *relation = strtok(NULL, " ");
                    char *value = strtok(NULL, "\n");
                    t_table *t = db->tables;
                    int auxint;
                    float auxfloat;

                    while (t != NULL) {
                        if (strcmp(t->name, tableName) == 0) {
                            break;
                        }
                        t = t->next;
                    }

                    if (t == NULL) {
                        printf("Table \"%s\" not found in database.\n",
                                tableName);
                        continue;
                    }

                    int columnNo = whichColumn(t, columnName);
                    if (columnNo == -1) {
                        printf("Table \"%s\" does not contain column \"%s\"."
                            "\n", tableName, columnName);
                        continue;
                    }

                    switch (t->type) {
                    case STRING:
                        qryDelString(t, columnNo, relation, value);
                        break;
                    case INT:
                        auxint = atoi(value);
                        qryDelInt(t, columnNo, relation, auxint);
                        break;
                    case FLOAT:
                        auxfloat = atof(value);
                        qryDelFloat(t, columnNo, relation, auxfloat);
                        break;
                    }
                } else {
                    printf("Table \"%s\" not found in database.\n", tableName);
                    continue;
                }
            }

        } else if (strcmp(function, "PRINT_DB\n") == 0) {
            printDB(db);

        } else if (strcmp(function, "PRINT") == 0) {
            char *name = strtok(NULL, " ");
            name[strlen(name) - 1] = '\0';
            findNamedTable(db, name, printTable);

        } else if (strcmp(function, "SEARCH") == 0) {
            char *tableName = strtok(NULL, " ");
            t_table *t = db->tables;

            int auxint;
            float auxfloat;
            while (t != NULL) {
                if (strcmp(t->name, tableName) == 0) {
                    break;
                }
                t = t->next;
            }

            if (t == NULL) {
                printf("Table \"%s\" not found in database.\n", tableName);
                continue;
            }

            char *columnName = strtok(NULL, " ");
            char *relation = strtok(NULL, " ");
            char *value = strtok(NULL, "\n");

            int columnNo = whichColumn(t, columnName);
            if (columnNo == -1) {
                printf("Table \"%s\" does not contain column \"%s\".\n",
                    tableName, columnName);
                continue;
            }

            printf("TABLE: %s\n", t->name);
            printColumns(t->columns);

            switch (t->type) {
            case STRING:
                qryPrintString(t, columnNo, relation, value);
                break;
            case INT:
                auxint = atoi(value);
                qryPrintInt(t, columnNo, relation, auxint);
                break;
            case FLOAT:
                auxfloat = atof(value);
                qryPrintFloat(t, columnNo, relation, auxfloat);
                break;
            }
            printf("\n");

        } else if (strcmp(function, "ADD") == 0) {
            char *tableName = strtok(NULL, " ");
            t_table *t = db->tables;

            while (t != NULL) {
                if (strcmp(t->name, tableName) == 0) {
                    break;
                }
                t = t->next;
            }

            if (t != NULL) {
                char *values = strtok(NULL, "\n");
                switch (t->type) {
                case INT:
                    addIntLines(t, values);
                    break;
                case STRING:
                    addStringLines(t, values);
                    break;
                case FLOAT:
                    addFloatLines(t, values);
                    break;
                }

            } else {
                printf("Table \"%s\" not found in database.\n", tableName);
            }

        } else if (strcmp(cmd, "CLEAR") == 0) {
            char *tableName = strtok(NULL, "\n");
            findNamedTable(db, tableName, clearTable);

        } else {
            printf("Unknown command: \"%s\".\n", function);
        }
    }

    free(cmd);
    cmd = NULL;

    return 0;
}
