/** @file event_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process iCalendar
 *  events and printing them in a user-friendly format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief The maximum line length.
 *
 */
#define MAX_LINE_LEN 132

/** prototype*/
void format(char *date);
int ics_read(FILE *ics, char ics_detail[][4][1024]);
void inputRead(char *argv[]);
void process(char info[][100], char ics_detail[][4][1024], int numEvents);
int timeCheck(const char *date1, const char *date2, const char *word);
int convertTime(int hour);
void printout(char *dateDetail[], int *timeDetail[], int check);
const char *getAMPM(int hour);
void getUntilDate(const char* rruleLine, char* untilDate);
void addDaysToPreStartDate(char *preStartDate);
int compareDates(const char* preStartDate, const char* untilDate);
void getNextBufferInfo(FILE *ics, char position[], char summary[]);

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    if(argc != 4){
        return 1;
    }
    inputRead(argv);
    // TODO: your code.
    return 0;
}

/**
 * Function: inputRead
 * -------------------
 * @brief Reads and processes the input arguments and file.
 *
 * This function reads the command-line arguments and the input file specified in the arguments.
 * It processes the information and calls the necessary functions to perform the desired operations.
 *
 * @param argv The list of command-line arguments passed to the program.
 * @return void
 *
 */
void inputRead(char *argv[]) {
    char info[3][100];
    char ics_detail[50][4][1024];
    for (int i = 1; i <= 2; i++) {
        char *token = strtok(argv[i], "=");
        token = strtok(NULL, "=");
        format(token);
        strcpy(info[i - 1], token);
    }
    char *token = strtok(argv[3], "=");
    token = strtok(NULL, "=");
    strcpy(info[2], token);
    FILE *ics = fopen(info[2], "r");
    int numEvents = ics_read(ics, ics_detail);

    process(info, ics_detail, numEvents);

    fclose(ics);
}

/**
 * Function: format
 * ----------------
 * @brief Formats the date string in a specific format.
 *
 * This function takes a date string in the format "yyyy/mm/dd" and converts it into
 * the format "yyyymmdd" by removing the slashes (/) and padding the year, month, and day
 * with leading zeros if necessary. For example: format("2020/1/1") returns "20200101".
 *
 * @param date The date string to be formatted.
 * @return void
 *
 */
void format(char *date) {
    int year, month, day;
    sscanf(date, "%d/%d/%d", &year, &month, &day);
    sprintf(date, "%04d%02d%02d", year, month, day);
}

/**
 * Function: ics_read
 * ------------------
 * @brief Reads the content of the ICS file and extracts event details.
 *
 * This function reads the content of the provided ICS file line by line and extracts
 * the event details such as start date, end date, location, and summary. It stores
 * the extracted details in the ics_detail array.
 *
 * @param ics The file pointer to the ICS file.
 * @param ics_detail The array to store the extracted event details.
 * @return int The number of events extracted from the ICS file.
 *
 */
int ics_read(FILE *ics, char ics_detail[][4][1024]) {
    char buffer[81]; char untilDate[16];  char preStartDate[16]; char preEndDate[16]; int count = 0;  int numEvents = 0; // Initialize the number of events to 0
    char summary[48]; char position[48];
    while (fgets(buffer, sizeof(buffer), ics) != NULL) {
        if (strstr(buffer, "DTSTART") != NULL) {
            count = 1; numEvents++;
        } else if (strstr(buffer,"DTEND") != NULL){count = 2;}
        if (strstr(buffer, "RRULE") != NULL){
            getUntilDate(buffer, untilDate); addDaysToPreStartDate(preStartDate); addDaysToPreStartDate(preEndDate); count = 0;
            getNextBufferInfo(ics, ics_detail[numEvents - 1][count + 2], ics_detail[numEvents - 1][count + 3]);
            strcpy(summary, ics_detail[numEvents - 1][count + 3]); strcpy(position, ics_detail[numEvents - 1][count + 2]);
            while (compareDates(preStartDate, untilDate) <= 0 && compareDates(preEndDate, untilDate) <= 0){
                numEvents++; strcpy(ics_detail[numEvents - 1][count], preStartDate); strcpy(ics_detail[numEvents - 1][count+1], preEndDate);
                strcpy(ics_detail[numEvents - 1][count+2], position); strcpy(ics_detail[numEvents - 1][count+3], summary);
                addDaysToPreStartDate(preStartDate); addDaysToPreStartDate(preEndDate);
            }
        } 
        if (count >= 1 && count <= 4) {
            char *token = strtok(buffer, ":");
            token = strtok(NULL, ":");
            token[strcspn(token, "\n")] = '\0';
            strcpy(ics_detail[numEvents - 1][count - 1], token);
            if (count == 1) {
                strcpy(preStartDate, token);} else if (count == 2) {strcpy(preEndDate, token);
            }
            count++;
        }
    }
    return numEvents;
}

/**
 * Function: getNextBufferInfo
 * ---------------------------
 * @brief Reads the next buffer from the ICS file and extracts position and summary information.
 *
 * This function reads the next buffer from the provided ICS file and extracts the position
 * and summary information. It stores the extracted position in the 'position' array and the
 * extracted summary in the 'summary' array.
 *
 * @param ics The file pointer to the ICS file.
 * @param position The array to store the extracted position information.
 * @param summary The array to store the extracted summary information.
 *
 */
void getNextBufferInfo(FILE *ics, char position[], char summary[]) {
    char buffer[1024];
    char *token;

    fgets(buffer, sizeof(buffer), ics);
    buffer[strcspn(buffer, "\n")] = '\0';

    if (strstr(buffer, "LOCATION") != NULL) {
        token = strtok(buffer, ":");
        token = strtok(NULL, ":");
        strcpy(position, token);
    }

    fgets(buffer, sizeof(buffer), ics);
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (strstr(buffer, "SUMMARY") != NULL) {
        token = strtok(buffer, ":");
        token = strtok(NULL, ":");
        strcpy(summary, token);
    }
}

/**
 * Function: getUntilDate
 * ----------------------
 * @brief Extracts the UNTIL date from the given RRULE line.
 *
 * This function searches for the "UNTIL=" key in the provided RRULE line and extracts
 * the date string following it. The extracted date is stored in the 'untilDate' buffer.
 * If the "UNTIL=" key is not found, the 'untilDate' buffer is set to an empty string.
 * For example: getUntilDate("RRULE:FREQ=WEEKLY;UNTIL=20201231T000000Z") stores "20201231"
 * 
 * @param rruleLine The RRULE line to search for the "UNTIL=" key.
 * @param untilDate The buffer to store the extracted UNTIL date.
 *
 */
void getUntilDate(const char* rruleLine, char* untilDate) {
    const char* searchKey = "UNTIL=";

    const char* untilPos = strstr(rruleLine, searchKey);
    if (untilPos == NULL) {
        strcpy(untilDate, "");
        return;
    }

    untilPos += strlen(searchKey);
    strncpy(untilDate, untilPos, 8);
    untilDate[8] = '\0';
}

/**
 * Function: compareDates
 * ----------------------
 * @brief Compares two date strings and returns the result.
 *
 * This function compares the date portion of the two provided date strings:
 * 'preStartDate' and 'untilDate'. The date portion should be in the format "YYYYMMDD".
 * The function returns an integer value indicating the result of the comparison:
 *   - If 'preStartDate' is earlier than 'untilDate', a negative value is returned.
 *   - If 'preStartDate' is later than 'untilDate', a positive value is returned.
 *   - If 'preStartDate' is equal to 'untilDate', 0 is returned.
 *
 * @param preStartDate The date string to compare with 'untilDate'.
 * @param untilDate The date string to compare with 'preStartDate'.
 * @return int The result of the date comparison.
 *
 */
int compareDates(const char* preStartDate, const char* untilDate) {
    char preDate[9];
    strncpy(preDate, preStartDate, 8);
    preDate[8] = '\0';

    return strcmp(preDate, untilDate);
}

/**
 * Function: addDaysToPreStartDate
 * -------------------------------
 * @brief Adds 7 days to the provided preStartDate string.
 *
 * This function takes a date-time string 'preStartDate' in the format "YYYYMMDDTHHMMSS"
 * and adds 7 days to the date component. The updated date-time string is stored back
 * in the 'preStartDate' parameter.
 *
 * @param preStartDate The preStartDate string to update.
 *
 */
void addDaysToPreStartDate(char *preStartDate) {
    int year, month, day, hour, minute, second;

    sscanf(preStartDate, "%4d%2d%2dT%2d%2d%2d", &year, &month, &day, &hour, &minute, &second);

    day += 7;

    if (day > 28) {
        if ((month == 2 && day > 29) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || day > 31) {
            day = 1; month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
    sprintf(preStartDate, "%04d%02d%02dT%02d%02d%02d", year, month, day, hour, minute, second);
}

/**
 * Function: timeCheck
 * -------------------
 * @brief Compares two dates and checks if they satisfy a specific condition.
 *
 * This function compares two dates represented as strings ('date1' and 'date2')
 * in the format "YYYYMMDD" and checks if they satisfy a specific condition
 * indicated by the 'word' parameter. The condition can be either "Start" or "End".
 *
 * @param date1 The first date to compare.
 * @param date2 The second date to compare.
 * @param word  The condition to check. Possible values are "Start" or "End".
 * @return int  Returns 1 if the condition is satisfied, 0 otherwise.
 *
 */
int timeCheck(const char *date1, const char *date2, const char *word) {
    int year1, month1, day1; int year2, month2, day2;

    sscanf(date1, "%4d%2d%2d", &year1, &month1, &day1);
    sscanf(date2, "%4d%2d%2d", &year2, &month2, &day2);

    if (strcmp(word, "Start") == 0) {
        if (year1 < year2) {return 1;} 
            else if (year1 == year2) {
            if (month1 < month2) {return 1;}
                else if (month1 == month2) {if (day1 <= day2) {return 1;}}
        }
    } else if (strcmp(word, "End") == 0) {
        if (year1 > year2) {
            return 1;
        } else if (year1 == year2) {
            if (month1 > month2) {return 1;} 
                else if (month1 == month2) {
                if (day1 >= day2) {return 1;}
            }
        }
    }
    return 0;
}

/**
 * Function: process
 * -----------------
 * @brief Processes the events based on the given information and details.
 *
 * This function processes the events based on the given information and details.
 * It compares the start and end dates of each event with the provided date range
 * (info[0] to info[1]) and prints the relevant event details. The events are
 * stored in the ics_detail array.
 *
 * @param info      The array containing the information and date range.
 * @param ics_detail The array containing the event details.
 * @param numEvents The number of events in the ics_detail array.
 * @return void
 *
 */
void process(char info[][100], char ics_detail[][4][1024], int numEvents) {
    int matchFound = 1; int check = 1; char preDateLine[1024]; char dateLine[1024]; int first = 1;
    for (int i = 0; i < numEvents; i++) {
        if (timeCheck(info[0], ics_detail[i][0], "Start") == 1 &&
            timeCheck(info[1], ics_detail[i][1], "End") == 1) {
            char *DTstart = ics_detail[i][0]; char *DTend = ics_detail[i][1];
            char *location = ics_detail[i][2]; char *summary = ics_detail[i][3];
            size_t locationLength = strcspn(location, "\n"); location[locationLength] = '\0';
            size_t summaryLength = strcspn(summary, "\n"); summary[summaryLength] = '\0';
            int startHour, startMinute; int endHour, endMinute; int year, month, day;
            sscanf(DTend, "%4d%2d%2dT%2d%2d", &year, &month, &day, &endHour, &endMinute);
            sscanf(DTstart, "%4d%2d%2dT%2d%2d", &year, &month, &day, &startHour, &startMinute);
            char *monthNames[] = {"", "January", "February", "March", "April", "May", "June",
                                 "July", "August", "September", "October", "November", "December"};
            char monthN[20]; strcpy(monthN, monthNames[month]);
            char *dateDetail[] = {DTstart, DTend, location, summary, monthN};
            int *timeDetail[] = {&startHour, &startMinute, &endHour,
                                         &endMinute, &year, &month, &day};
            sprintf(dateLine, "%s %d, %d\n", dateDetail[4], *timeDetail[6], *timeDetail[5]);
            if(first){first=0; sprintf(preDateLine, "%s %d, %d\n", dateDetail[4], *timeDetail[6], *timeDetail[5]);}
            else if(strcmp(preDateLine, dateLine) == 0){check = 0;} else {
                check = 1; printf("\n");
                strcpy(preDateLine, dateLine);
            }
            printout(dateDetail, timeDetail,check);
            matchFound = 0;
        }
    }
}

/**
 * Function: printout
 * ------------------
 * @brief Prints the event details based on the provided information.
 *
 * This function prints the event details based on the provided date and time
 * information. It formats and displays the start and end times, along with
 * the event summary and location. If `check` is non-zero, it also prints the
 * formatted date line before the event details.
 *
 * @param dateDetail  An array containing the date and event details.
 * @param timeDetail  An array containing the time information.
 * @param check       Flag indicating whether to print the date line.
 * @return void
 *
 */
void printout(char *dateDetail[], int *timeDetail[],int check) {
    char dateLine[1024];
    if(check){
        sprintf(dateLine, "%s %02d, %d\n", dateDetail[4],*timeDetail[6], *timeDetail[4]);
        printf(dateLine);
        int lineLength = strlen(dateLine);
        printf("%.*s\n", lineLength - 1, "----------------------------------------------");
    }
    printf("%2d:%02d %s to %2d:%02d %s: %s {{%s}}\n", convertTime(*timeDetail[0]), *timeDetail[1], getAMPM(*timeDetail[0]), convertTime(*timeDetail[2]), *timeDetail[3], getAMPM(*timeDetail[2]), dateDetail[3], dateDetail[2]);
}

/**
 * Function: convertTime
 * ---------------------
 * @brief Converts a given hour value to a 12-hour format.
 *
 * This function takes an hour value and converts it to a 12-hour format.
 * If the hour is greater than 12, it subtracts 12 from it to get the
 * corresponding hour in the 12-hour format. Otherwise, it returns the
 * original hour value.
 *
 * @param hour The hour value to be converted.
 * @return int The hour value in the 12-hour format.
 *
 */
int convertTime(int hour) {
    if (hour > 12) {
        return hour - 12;
    }
    return hour;
}

/**
 * Function: getAMPM
 * -----------------
 * @brief Determines the appropriate AM/PM designation for a given hour.
 *
 * This function takes an hour value and determines the appropriate AM/PM
 * designation based on the given hour. If the hour is greater than or
 * equal to 12, it returns "PM". Otherwise, it returns "AM".
 *
 * @param hour The hour value.
 * @return const char* The AM/PM designation ("AM" or "PM").
 *
 */
const char *getAMPM(int hour) {
    if (hour >= 12) {
        return "PM";
    }
    return "AM";
}