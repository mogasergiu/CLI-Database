# CLI-Database
CLI Program that simulates the functionality of a Database. It reads commands
from the CLI and stores the data using linked lists.

Available commands:<br />
For Data Definitions:<br />
- INIT_DB <name> - will initialize the database with the given name
- DELETE_DB - will delete the database and free the allocated memory
- CREATE <table_name> <datatype> [column_name_array] - creates a table
  with the requested columns. Available types: INT/FLOAT/STRING
  example: CREATE Doctors STRING City Region First_Name Last_Name - this will
  create the table named "Doctors" with columns of type STRING, each named in
  order with the given names
- DELETE <table_name> - deletes the specified table from the database<br />

For Data Query:<br />
- PRINT_DB - prints all of the created tables of the database
- PRINT <table_name> - prints all the data stored in the specified table
- SEARCH <table_name> <column_name> <comparison> <value> - prints the values
  from the specified column of the specified table that return true when
  compared with the specified value. Available operators: “<” “<=” “==” “!=” “>=” “><br />

For Data Manipulation:<br />
- ADD <table_name> [values_for_each_column] - adds a new line to the specified
  table with the specified values for each column in order
- DELETE <table_name> <column_name> <comparison> <value> - the exact oposite of
  "CREATE", used with the same types of parameters
- CLEAR <table_name> - clears the contents of the specified table, leaving only
  its name and columns

Usage example:<br />
Input:<br />
INIT_DB Parking_Lot<br />
CREATE Cars STRING Brand License_Plate<br />
ADD Cars Ford ABC-123<br />
ADD Cars Dacia DEF-456<br />
PRINT Cars<br />
DELETE_DB<br />

Output: <br />
TABLE: Cars <br />
Brand&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;License_Plate <br />
............................ .............................<br />
Ford&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ABC-123<br />
Dacia&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DEF-456<br />
