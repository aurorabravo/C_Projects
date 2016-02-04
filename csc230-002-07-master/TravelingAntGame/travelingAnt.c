#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
    @file travelingAnt.c
    @author Aurora Bravo (aibravoe)

    This program takes in a file, reads the file and prints out a grid based
    on the input file. It also prints coordinates for the simulation of an ant traveling to its home
    and it prints out the total amount of steps taken.
    If the ant does not find its home before running out of steps, this program prints out
    the amount of steps taken as -1
*/

/** Matched amount */
#define MATCHED2 2

/** Minimum steps. */
#define MINSTEP 3

/** Minimum rows. */
#define MINROWS 2

/** Maximum rows. */
#define MAXROWS 100

/** Maximum types. */
#define MAXTYPES 4

/** Maximum dirctions. */
#define MAXDIR 4

/** Food Ratio. */
#define FOOD_RATIO 0.2

/** Puddle. */
#define PUDDLE 0

/** Empty. */
#define EMPTY 1

/** Start. */
#define START 2

/** Home. */
#define HOME 3

/** Food. */
#define FOOD 4

/** North. */
#define NORTH 0

/** East. */
#define EAST 1

/** South. */
#define SOUTH 2

/** West. */
#define WEST 3

/** Init. */
#define INIT -1

/** Args */
#define ARGS 2

/**
   Returns the maximum number of steps that the ant should take. This number is also
   the first number of the input file.
   Exits the program with an EXIT_FAILURE status if the maximum number of steps is invalid.
   
   @param antFile File * The input file

   @return num int the number of steps taken
 */
int getLifetime(FILE * antFile)
{
   int num;
   char c;
   int matched = fscanf(antFile, "%d%c", &num, &c);
   if (matched != MATCHED2) {   //if num is not an int or c is not a char
      printf("Invalid max steps.\n");
      exit(EXIT_FAILURE);
   } else if (!(num >= MINSTEP)) {   //if num is not greater than or equal to 3
      printf("Invalid max steps.\n");
      exit(EXIT_FAILURE);
   } else if (c != '\n') {
      printf("Invalid max steps.\n");
      exit(EXIT_FAILURE);
   } else {
      return num;
   }
}

/**
   Reads the input and figures out the amount of rows and columns that the grid has.
   The rows number is the first integer in the second line of the file.
   The columns number is the second integer in the second line of the file.
   The rows and columns should be between 2 and 100
   Exits the program with an EXIT_FAILURE status if row and/or column are invalid.
   
   @param antFile File * The input file.
   @param rowsp int* Pointer to the rows variable.
   @param columnsp int* Pointer to the columns variable.
 */
void getGridSize(FILE * antFile, int* rowsp, int* columnsp)
{
   int row;
   int col;
   char c;
   int matched = fscanf(antFile, "%d%c", &row, &c);
   if (matched != MATCHED2) { //should take care of row/col being integers and if either one is missing
      printf("Invalid size.\n");
      exit(EXIT_FAILURE);
   } else if ( !(row >= MINROWS && row <= MAXROWS) ) {
      printf("Invalid size.\n");
      exit(EXIT_FAILURE);
   } else if ( c != ' ') {
      printf("Invalid size.\n");
      exit(EXIT_FAILURE);
   } else {
      *rowsp = row;
   }

   matched = fscanf(antFile, "%d%c", &col, &c);
   if (matched != MATCHED2) { //should take care of row/col being integers and if either one is missing
      printf("Invalid size.\n");
      exit(EXIT_FAILURE);
   }else if ( !(col >= MINROWS && col <= MAXROWS) ) {
      printf("Invalid size.\n");
      exit(EXIT_FAILURE);
   } else if (c != '\n') {
      printf("Invalid size.\n");
      exit(EXIT_FAILURE);
   } else {
      *columnsp = col;
   }
}

/**
   Reads the input records the values (in the grid section of the input)
   into a 2D array called grid. Exits with an EXIT_FAILURE status
   if the grid is not valid or if the map is not valid. The map is not valid if
   there is more than one starting point, more than
   one exit point, and more than 20% food of total rows*columns.
   
   @param antFile File * The input file.
   @param rows int Number of rows in the grid.
   @param columns int Number of columns in the grid.
 */
void getGrid(FILE * antFile, int rows, int columns, int grid[rows][columns])
{
   int num;
   char c;
   int matched = 0;
   int start = 0;
   int entrance = 0;
   int food = 0;
   //printf("columns %d\n", columns);
   //printf("rows %d\n", rows);
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         //printf("j %d\n", j);
         if ((j+1) == columns) { //if we're at the last column check if \n or extra
            //printf("j %d\n", j);
            matched = fscanf(antFile, "%d%c", &num, &c);
            //printf("num %d\n", num);
            if (matched != MATCHED2) {  //check if it is digit and char
               printf("Invalid column.\n");
               exit(EXIT_FAILURE);
            } else if (c != '\n') { //check if char is \n
               //printf("num '%d'", num);
               //printf("c '%c'", c);
               printf("Invalid column.\n");
               exit(EXIT_FAILURE);
            } else if (!(num >= 0 && num <= MAXTYPES) ){
               printf("Invalid value.\n");
               exit(EXIT_FAILURE);
            } else if (num == START) {   //only one starting point
               if (start >= 1) {
                  printf("Map error.\n");
                  exit(EXIT_FAILURE);
               } else {
                  start++;
                  grid[i][j] = num;
               }
            } else if (num == HOME) {   //only one entrance point
               if (entrance >= 1) {
                  printf("Map error.\n");
                  exit(EXIT_FAILURE);
               } else {
                  entrance++;
                  grid[i][j] = num;
               }
            } else if (num == FOOD) {
                food++;
                grid[i][j] = num;
            } else {
               grid[i][j] = num;
            }
         } else { //we are not at last column, check if valid int
            matched = fscanf(antFile, "%d%c", &num, &c);
            if ( num == EOF) {
               printf("Invalid row.\n");
               exit(EXIT_FAILURE);
            } else if (matched != MATCHED2) { //if not int, exit
               printf("Invalid value.\n");
               exit(EXIT_FAILURE);
            } else if ( !(num >= 0 && num <= MAXTYPES) ) { //check if between 0 and 4
               printf("Invalid value.\n");
               exit(EXIT_FAILURE);
            } else if (c != ' ') {
               printf("Invalid column.\n");
               exit(EXIT_FAILURE);
            } else if (num == START) {
               if (start >= 1) {
                  printf("Map error.\n");
                  exit(EXIT_FAILURE);
               } else {
                  start++;
                  grid[i][j] = num;
               }
            } else if (num == HOME) {   //only one entrance point
               if (entrance >= 1) {
                  printf("Map error.\n");
                  exit(EXIT_FAILURE);
               } else {
                  entrance++;
                  grid[i][j] = num;
               }

            } else if (num == FOOD) {
               food++;
               grid[i][j] = num;
            } else {
               grid[i][j] = num;
            }
         }
      }
   }

   //at the end of the supposed row by column array, check if extra rows
   char c2;
   matched = fscanf(antFile, "%c", &c2);
   //printf("matched '%d'\n", matched);
   //if int c2 is null
   if ( matched > 0 ) {
     // printf("c2 '%d'", c2);
     // printf("c2 '%c'", c2);
      printf("Invalid row.\n");
      exit(EXIT_FAILURE);
   }
   if (start == 0) {
      printf("Map error.\n");
      exit(EXIT_FAILURE);
   }
   if (entrance == 0) {
      printf("Map error.\n");
      exit(EXIT_FAILURE);
   }
   if (food > ((rows * columns)*FOOD_RATIO)) {
      printf("Map error.\n");
      exit(EXIT_FAILURE);
   }

}

/**
   Prints the grid array using nested for loops. The end of the column ends with "\n"
   Prints an extra line after the array.
   
   @param rows int Number of rows in the grid.
   @param columns int Number of columns in the grid.
   @param grid int array
 */
void printGrid(int rows, int columns, int grid[rows][columns])
{
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         if (j + 1 == columns) { //if last column
            printf("%d\n", grid[i][j]);
         } else {
            printf("%d ", grid[i][j]);
         }
      }
   }
   printf("\n");
   
}

/**
   Reverses the direction of the parameter and returns it.
   
   @param direction int Direction of entry
   @return int Reversed direcrion
 */
int reverse (int direction)
{
   return (direction + 2) % MAXDIR;
}

/**
   Returns the clockwise direction of the parameter as an int.
   
   @param direction int Direction of entry
   @return int Clockwise direcrion

 */
int clockwise(int direction)
{
   return (direction + 1) % MAXDIR;
}

/**
   Determines the path that the ant takes through the grid.
   Prints out the coordinates [row][column] of the current position and the total amount of steps taken.
   Amount of steps taken is -1 if the ant did not find its house.

   @param maxSteps int Maximum number of steps taken
   @param rows int Number of rows in the grid
   @param columns int Number of columns in the grid
   @param grid int array
 */
void travel(int maxSteps, int rows, int columns, int grid[rows][columns])
{
   int remaining_steps = maxSteps;
   int steps = 0;

   int row = 0;
   int col = 0;
   int entry_dir = NORTH;

   bool start_found = false;
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         if (grid[i][j] == START) {
            printf("Current Position: [%d][%d] - Number of remaining steps: %d\n", i, j, remaining_steps);
            row = i;
            col = j;
            start_found = true;
            break;
         }
      }
      if (start_found) {
         break;
      }
   }

   bool foundHouse = false;
   while (remaining_steps != 0) {
      int numberOfDir = 0;
      bool available[MAXDIR] = {false, false, false, false};
      int xchange[MAXDIR] = {0, 1, 0, -1};
      int ychange[MAXDIR] = {-1, 0, 1, 0};
      if (row > 0) {
         available[NORTH] = true;
         numberOfDir++;
      }
      if (row + 1 < rows) {
         available[SOUTH] = true;
         numberOfDir++;
      }
      if (col > 0) {
         available[WEST] = true;
         numberOfDir++;
      }
      if (col+ 1 < columns) {
         available[EAST] = true;
         numberOfDir++;
      }
      int directions[numberOfDir];
      int i = clockwise(entry_dir);
      int j = 0;
      while (j != numberOfDir) {
         if (available[i]) {
            directions[j] = i;
            j++;
         }
         i = clockwise(i);
      }

      int firstHome = INIT;
      int firstFood = INIT;
      int firstEmpty = INIT;
      for (i = numberOfDir - 1; i > -1; i--){
         int direction = directions[i];
         int newRow = row + ychange[direction];
         int newCol = col + xchange[direction];
//         printf("i: %d, newRow: %d, newCol: %d\n", i, newRow, newCol);
         if (grid[newRow][newCol] == HOME ) {
            firstHome = directions[i];
         }
         if (grid[newRow][newCol] == FOOD) {
            firstFood = directions[i];
         }
         if (grid[newRow][newCol] == EMPTY) {
            firstEmpty = directions[i];
         }
         if (grid[newRow][newCol] == START) {
            firstEmpty = directions[i];
         }
      }

//      printf("row %d; col %d; north %d; east %d; south %d; west %d\n", row, col, available[north], available[east], available[south], available[west]);
//      printf("number of directions: %d; dir0: %d; dir1: %d\n", numberOfDir, directions[0], directions[1]);
//      printf("home %d; food %d; EMPTY %d\n", firstHome, firstFood, firstEmpty);
      if (firstHome != INIT) {
         steps++;
         remaining_steps--;
         col += xchange[firstHome];
         row += ychange[firstHome];
         entry_dir = reverse(firstHome);
         printf("Current Position: [%d][%d] - Number of remaining steps: %d\n", row, col, remaining_steps);
         foundHouse = true;
         break;
      } else if (firstFood != INIT) {
         steps++;
         remaining_steps = maxSteps;
         col += xchange[firstFood];
         row += ychange[firstFood];
         grid[row][col] = EMPTY;
         entry_dir = reverse(firstFood);
         printf("Current Position: [%d][%d] - Number of remaining steps: %d\n", row, col, remaining_steps);
      } else if (firstEmpty != INIT) {
         steps++;
         remaining_steps--;
         col += xchange[firstEmpty];
         row += ychange[firstEmpty];
         entry_dir = reverse(firstEmpty);
         printf("Current Position: [%d][%d] - Number of remaining steps: %d\n", row, col, remaining_steps);
      } else {
         //printf("What the, I am surrounded!");
         steps = INIT;
         break;
      }
   }
   if (!foundHouse) {
      steps = INIT;
   }
   printf("Steps: %d\n", steps);
}

/**
    Program starting point, reads file and simulates an ant traveling to its home
    based on travel direction and the objects around it.
    It calls getLifeTime, getGridSize, printGrid, travel

    @param argc number of command-line arguments
    @param argv list of command-line arguments
    
    @return program exit status
*/
int main(int argc, char *argv[])
{
   //The number of command line arguments is stored in argc.
   //The command line arguments are stored in argv, which is an
   //array of strings (where each string is a char * type).
   //The executable is always the value stored in argv[0].

   //There should always be a check for the right number of
   //command line arguments.
   if (argc != ARGS) {
      printf("Usage: ./travelingAnt <flagstone-file>\n");
      exit(EXIT_FAILURE);
   }

   //The filename is stored in argv[1].  It's type is a
   //char *, which is appropriate to use in fopen().
   FILE * antFile = fopen(argv[1], "r");
   if (antFile == NULL) {  //if file does not exist
      printf("Cannot read file.\n");
      exit(EXIT_FAILURE);
   }

   //get number of max steps
   int maxSteps = getLifetime(antFile);
   //printf("%d\n", maxSteps); //to check maxsteps

   //get grid size
   int rows = 0;
   int columns = 0;
   int* rowsp = &rows;
   int* columnsp = &columns;
   getGridSize(antFile, rowsp, columnsp);
   //printf("rows:%d\n cols:%d\n", rows, columns); //to check rows/cols

   //get grid
   int grid[rows][columns];
   //int* ap = &a[rows][columns];
   getGrid(antFile, rows, columns, grid);

   printGrid(rows, columns, grid);

   travel(maxSteps, rows, columns, grid);

   return EXIT_SUCCESS;
}
