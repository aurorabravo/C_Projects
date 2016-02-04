#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
    @file reminder.c
    @author Aurora Bravo (aibravoe)

    This program takes in a file, reads the file, prints out a menu with the
    option to add a reminder, delete a reminder, list reminders by due date,
    list reminders by priority, or to quit.
    Uppon quitting, the input file is rewritten with a sorted
    list of reminders by due date.
*/

/** Args */
#define ARGS 2

/** Max size of reminder */
#define MAX_REMINDER_SIZE 70

/** Initial size of array*/
#define INITIAL_SIZE 10

/** Number of items matched */
#define MATCHED 1

/** Number of items matched */
#define MATCHED3 3

/** Number of items matched */
#define MATCHED4 4

/** Initial motnh */
#define INITIAL_MONTH 1

/** Final month*/
#define FINAL_MONTH 12

/** Initial day */
#define INITIAL_DAY 1

/** Final Day */
#define FINAL_DAY 31

/** Priority 1 */
#define PRIORITY1 1

/** Priority 2 */
#define PRIORITY2 2

/** Priority 3 */
#define PRIORITY3 3

/** Positive */
#define POS 1

/** Negative */
#define NEG -1

/** Two */
#define TWO 2

/** Four */
#define FOUR 4

/** Six */
#define SIX 6

/** Nine */
#define NINE 9

/** Eleven */
#define ELEVEN 11

/** February */
#define FEB 2

/** Twenty Eight */
#define TWENTY_EIGHT 28

/** Thirthy */
#define THIRTHY 30

/** Five */
#define FIVE 5

/** Size Variable */
int size = INITIAL_SIZE;

/** List of reminders */
char **list;

/**
   Reads the input file and allocates memory dynamically for an array of characters (reminders)
   and stores it into a dynamically allocated list of reminders
   
   @param reminderFile File * The input file.
 */
void readFile(FILE * reminderFile)
{

   int month;
   int day;
   char priority;
   char message[MAX_REMINDER_SIZE];
   char whitespace;
   bool added = false;
   int i = 0;

   char * reminder;

   while (1) {

      //allocate memory for reminder char array with size 70
      if ( NULL == (reminder = (char *) calloc(MAX_REMINDER_SIZE, sizeof (char))) ) {
         printf("1Reminder cannot be added\n");
         exit(EXIT_FAILURE);
      }
      if (fgets(reminder, MAX_REMINDER_SIZE, reminderFile) == NULL) { //read until end of line
         free(reminder);
         break;
      }

      int matched = sscanf(reminder, "%d %d %c%c %1s", &month, &day, &priority, &whitespace, message); //read in all

      if (matched != FIVE) {
         printf("2Reminder cannot be added\n");
         //printf("Month: %d, Day: %d, Char: %c", month, day, priority);
      } else if (month < INITIAL_MONTH || month > FINAL_MONTH) {
         printf("3Reminder cannot be added\n");
         //printf("Month: %d, Day: %d, Char: %c", month, day, priority);
      } else if (day < INITIAL_DAY || day > FINAL_DAY) {
         printf("4Reminder cannot be added\n");
      } else if (priority != 'h' && priority != 'H' && priority != 'm' && priority != 'M'
                                                   && priority != 'l' && priority != 'L') {
         printf("5Reminder cannot be added\n");
         //printf("priority %c\n", priority);
      } else if (month == TWO) {
         if (day > TWENTY_EIGHT) {
            printf("6Reminder cannot be added\n");
         }
      } else if (whitespace != ' ' && whitespace != '\n' && whitespace != '\t' && whitespace != '\r'
         && whitespace != '\v' && whitespace != '\f') {
         printf("7Reminder cannot be added\n");
         //printf("'%c'\n", whitespace);
         //printf("Month %d Day %d P '%c' mess '%1s'\n", month, day, priority, message);
         //printf("Month %d Day %d P '%c' mess '%c'\n", month, day, priority, message);
      } else if (month == FOUR || month == SIX || month == NINE || month == ELEVEN) {
         if (day > THIRTHY) {
            printf("8Reminder cannot be added\n");
         }
      } else {
         added = true;
      }

      if (added == true) {
         i++;

         if (i > size) {
            size = i;
            list = (char **) realloc(list, size * sizeof(char *));
         }

            list[i-1] = reminder;
            printf("Reminder added\n");
         }
   }
   size = i;

}

/**
   Adds new reminders to the end of the list of reminders. Gets input for new reminder from console.
 */
void addReminder()
{
   int month;
   int day;
   //char priority[2];
   char message[MAX_REMINDER_SIZE];
   char priority;
   char whitespace;
   //char message;

   //bool added = false;
   char * newReminder;
   //dynamically allocate space for 70 chars
   if ( NULL == (newReminder = (char *) calloc(MAX_REMINDER_SIZE, sizeof (char))) ) {
      printf("Reminder cannot be added\n");
      free(newReminder);
      exit(EXIT_FAILURE);
   }

   printf("Reminder? ");

   //getchar();

   fgets(newReminder, MAX_REMINDER_SIZE, stdin);

   int c;
   if (newReminder[strlen(newReminder)-1]!='\n'){
      do{
        c=getchar();
     } while (c!='\n');
   }


   //printf("New reminder is %s\n", newReminder);

   int matched = sscanf(newReminder, "%d %d %c%c %1s", &month, &day, &priority, &whitespace, message); //read in all
   if (matched != FIVE) {
      printf("Reminder cannot be added\n");
      //printf("Month %d Day %d P '%c' mess '%c'\n", month, day, priority, message);
      free(newReminder);
      return;
   } else if (month < INITIAL_MONTH || month > FINAL_MONTH) {
      printf("Reminder cannot be added\n");
      free(newReminder);
      return;
   } else if (day < INITIAL_DAY || day > FINAL_DAY) {
      printf("Reminder cannot be added\n");
      //printf("Month %d Day %d P %s mess %s\n", month, day, priority, message);
      free(newReminder);
      return;
   } else if ( priority != 'h' && priority != 'H' && priority != 'm' && priority != 'M'
                                             && priority != 'l' && priority != 'L') {
      printf("Reminder cannot be added\n");
      //printf("priority %s\n", priority);
      free(newReminder);
      //printf("priority %c\n", priority);
      return;
   } else if (whitespace != ' ' && whitespace != '\n' && whitespace != '\t' && whitespace != '\r'
      && whitespace != '\v' && whitespace != '\f') {
      printf("Reminder cannot be added\n");
      //printf("'%c'\n", whitespace);
      //printf("Month %d Day %d P '%c' mess '%1s'\n", month, day, priority, message);
      free(newReminder);
      //printf("Month %d Day %d P '%c' mess '%c'\n", month, day, priority, message);
      return;
   } else if (month == TWO) {
      if (day > TWENTY_EIGHT) {
         printf("Reminder cannot be added\n");
         free(newReminder);
         return;
      }
   } else if (month == FOUR || month == SIX || month == NINE || month == ELEVEN) {
      if (day > THIRTHY) {
         printf("Reminder cannot be added\n");
         free(newReminder);
         return;
      }
   }
   //printf("Month %d Day %d P '%c' mess '%1s'\n", month, day, priority, message);
   //printf("'%c'\n", whitespace);
   /*if (month == 2) {
      if (day > 28) {
         printf("Reminder cannot be added\n");
         free(newReminder);
      }
   } else if (month == 4 || month == 6 || month == 9 || month == 11) {
      if (day > 30) {
         printf("Reminder cannot be added\n");
         free(newReminder);
      }
   } */

   size++;
   list = (char **) realloc(list, size * sizeof(char *));
   list[size-1] = newReminder;
   printf("Reminder added\n");
   return;
   
}

/**
   Removes a reminder at an index. Gets index from console.
 */
void removeReminder()
{
   int index;
   printf("Index to remove? ");
   int matched = scanf("%d", &index);
   scanf("%*[^\n]");
   getchar();
   if (matched != 1) {
      printf("Reminder cannot be removed\n");
      return;
   } else if (index < 0 || index > (size - 1)) {
      printf("Reminder cannot be removed\n");
      return;
   }

   printf("Reminder removed\n");
   free(list[index]);
   for (int i = index; i < size-1 ; i++) {
      //shift to the left
      list[i] = list[i+1];
   }
   size--;
   //realloc memory to new size.
   list = (char **) realloc(list, size * sizeof(char *));
   return;


}

/**
   Compares two strings by due date.
   
   @param a void * The string to be compared
   @param b void * The string to be compared
 */
int dueDateCompare (const void * a, const void * b)
{
   char *p1 = *(char**)a;
   char *p2 = *(char**)b;
   char c1, c2;
   int month1, day1, month2, day2;
   sscanf(p1, "%d %d %c", &month1, &day1, &c1);
   sscanf(p2, "%d %d %c", &month2, &day2, &c2);

   if (c1 == 'H' || c1 == 'h') {
      c1 = PRIORITY1;
   } else if (c1 == 'm' || c1 == 'M') {
      c1 = PRIORITY2;
   } else if (c1 == 'l' || c1 == 'L') {
      c1 = PRIORITY3;
   }

   if (c2 == 'H' || c2 == 'h') {
      c2 = PRIORITY1;
   } else if (c2 == 'm' || c2 == 'M') {
      c2 = PRIORITY2;
   } else if (c2 == 'l' || c2 == 'L') {
      c2 = PRIORITY3;
   }

   if (month1<month2) {
      return NEG;
   } else if (month1 > month2) {
      return POS;
   } else {
      if (day1 < day2){
         return NEG;
      } else if (day1 > day2) {
         return POS;
      } else {
         if (c1 < c2) {
            return NEG;
         } else if (c1 > c2) {
            return POS;
         } else {
            return 0;
         }
      }
      return 0;
   }
}

/**
   Compares two strings by Priority in order of high hedium low.
   
   @param a void * The string to be compared
   @param b void * The string to be compared
 */
int priorityCompare (const void * a, const void * b)
{
   int month1, day1, month2, day2;
   char *p1 = *(char**)a;
   char *p2 = *(char**)b;
   char c1, c2;
   sscanf(p1, "%d %d %c", &month1, &day1, &c1);
   sscanf(p2, "%d %d %c", &month2, &day2, &c2);

   if (c1 == 'H' || c1 == 'h') {
      c1 = PRIORITY1;
   } else if (c1 == 'm' || c1 == 'M') {
      c1 = PRIORITY2;
   } else if (c1 == 'l' || c1 == 'L') {
      c1 = PRIORITY3;
   }

   if (c2 == 'H' || c2 == 'h') {
      c2 = PRIORITY1;
   } else if (c2 == 'm' || c2 == 'M') {
      c2 = PRIORITY2;
   } else if (c2 == 'l' || c2 == 'L') {
      c2 = PRIORITY3;
   }

   if (c1 < c2) {
      return NEG;
   } else if (c1 > c2) {
      return POS;
   } else {
      if (month1<month2) {
         return NEG;
      } else if (month1 > month2) {
         return POS;
      } else {
         if (day1 < day2){
            return NEG;
         } else if (day1 > day2) {
            return POS;
         } else {
            return 0;
         }
      }
   }
}

/**
   Lists the reminders by due date, then priority.
 */
void listByDue()
{

   qsort(list, size, sizeof(char *), dueDateCompare);
 //do your printy things
   for (int i = 0; i < size; i++) {
      printf("%3i) %s", i, list[i]);
   }
}

/**
   Lists the reminders by priority, then due date.
 */
void listByPriority()
{
   qsort(list, size, sizeof(char *), priorityCompare);
   for (int i = 0; i < size; i++) {
      printf("%3i) %s", i, list[i]);
   }
}

/**
   Closes the file. Opens the file to write a sorted list of reminders by due date.

   @param file char * The file to be closed
 */
void close(char * file)
{
   qsort(list, size, sizeof(char *), dueDateCompare);
   /*for (int i = 0; i < size; i++) {
      printf("%3i) %s", i, list[i]);
   } */


   //fclose(reminderFile);
   FILE * newfile = fopen(file, "w");
   for (int i = 0; i < size; i++) {
      fprintf(newfile, "%s", list[i]);
      free(list[i]);
   }
   free(list);
   fclose(newfile);


}

/**
   Prints out a menu and prompts the user to add a reminder, remove a reminder, list by due date,
   list by priority and quit. Takes in the first from any string that the user inputs.
   If user inputs q or a string that starts with q, the program exits and the file is rewritten with
   the reminder list sorted by due date.

   @param reminderFile File * The input file.
   @param file char * The file to be closed
 */
void menu(FILE * reminderFile, char * file)
{

   while (1) {

      printf("\nReminders Menu:\n(a)dd a reminder\n(r)emove a reminder\nlist by (d)ue date\nlist by (p)riority\n(q)uit\n");
      char c = getchar();
      scanf("%*[^\n]");
      getchar();
      //printf("'%c'", c);
      if ( c == 'q' ) {
         fclose(reminderFile);

         close(file);
         //close file here
         break;
      } else if ( c == 'a' ) {
         addReminder();

      } else if ( c == 'r' ) {
         removeReminder();

      } else if ( c == 'd' ) {
         listByDue();

      } else if ( c == 'p' ) {
         listByPriority();

      }
   }

   //close i

}

/**
    Program starting point, reads file, prompts the user to add
    reminders, to remove reminders, or to list reminders by due date
    or priority or to quit.
    Upon quitting, the input file is rewritten with a sorted
    list of reminders by due date.

    @param argc number of command-line arguments
    @param argv list of command-line arguments
    
    @return program exit status
*/
int main(int argc, char *argv[])
{
   //There should always be a check for the right number of
   //command line arguments.
   if (argc != ARGS) {
      printf("Usage: ./reminder <reminder-file>\n");
      exit(EXIT_FAILURE);
   }

   //The filename is stored in argv[1].  It's type is a
   //char *, which is appropriate to use in fopen().
   FILE * reminderFile = fopen(argv[1], "r");
   if (reminderFile == NULL) {  //if file does not exist
      printf("Cannot read file.\n");
      exit(EXIT_FAILURE);
   }

   list = (char **) malloc(size * sizeof (char *));
   //truct list * remList = (struct reminder *) malloc(50*sizeof(struct reminder));
   readFile(reminderFile);

   menu(reminderFile, argv[1]);

   //after done, close file, then open it for writing and save & exit

   return EXIT_SUCCESS;
}
