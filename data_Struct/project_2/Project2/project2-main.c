/* 
    project2-main.c
    Project 2
    Jose D. Pague

    This is the driver for the course scheduling program. It gets the CSV file name from the command line argument and opens it for reading. It will read all the data from that CSV file into an array of CourseRecords structs. The main function will then call functions in schedule.c to get information and computations in that array, which will be printed to standard output. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"


int main( int argc, char *argv[] )
{
	/* Declare your other variables here, you will need more than these. */
	FILE *fileIn = NULL;
	int input, length;
        int key2Num = 0;
        int min = 0;
        char *key1Letter = "";
        SearchType st; 
       
        //array = (CourseRecord *)malloc(sizeof(CourseRecord));
       
        /* 
	The main will open the CSV file whose name is passed in through the command line argument. 
	1. Check for to see if at least one command line argument was entered.
	2. If no command line argument was entered, print out an error message and end the program.
	3. If a command line argument was entered, attempt to open the file. 
	4. If the file does not open, print out an error message and end the program. 
	5. Call fillCourses() to fill your array of CourseRecords 
	6. Call mergeSortRecords() to sort your array of CourseRecords 
	*/
          
        if ( argc <= 1 )
        { 
            printf( "Error: missing input file.\n"); // needs to end program if error
            return 1; 
        }
        fileIn = fopen ( argv[ 1 ], "r");
        if ( fileIn == NULL)
        {
            printf( "Error: can't open file.\n");
            return 2; // needs to end program if error
        }
        length = getCourseCount( fileIn );
        CourseRecord *origin;
        origin = (CourseRecord *) malloc((sizeof(CourseRecord) * length) + 1);
        if(origin == NULL) {
            fprintf(stderr, "No memory to allocate.\n");
            exit(-1);
        }
        
        //CourseRecord *origin = (CourseRecord *)malloc(sizeof(CourseRecord) * length);
        fillCourses(fileIn, origin, length); 
        
        mergeSortRecords(fileIn, min, length); // is min 0?
        

	/* This is the main program loop that will print the menu, ask the user for the option they want, and then additional input, and output the requested data. */    
    while( TRUE )
    {
    	printMenu();
    	scanf( "%d", &input );
    	
        int code;
        int found;
        char classDays[10];
        char nameofInstruct[10];
        CourseRecord *dest;
        dest = (CourseRecord *)malloc(sizeof(CourseRecord) * length);
    	switch( input )
    	{
    		case 1:
                    
    			/* 
    				This case will find a course by a CRN number.
    				1. Ask the user for a CRN 
    				2. Call the findCourses() function with this CRN
    				3. Since there should only be one course with this CRN, call printCourseInformation() to print out its information.
    				4. If no course was found with this CRN, print out an error. 
    			*/
                    
                   
                    st = CRN;
                    
                    printf("Enter a CRN: ");
                    scanf("%d", &code );
                    
                    
                    found = findCourses( origin, dest, length, key1Letter, code, st); 
                    
                    if ( found == 0)
                    {
                        printf("ERROR");
                    }
                    else 
                    {
                        printCourseInformation(*dest); 
                    }
                    
                    free(dest);
                    break;
			
    		case 2:
    			/* This case will find a course by its course number. 
    				1. Ask the user for a course number 
    				2. Call the findCourses() function with this course number and the SearchType COURSE.
    				3. Call printCourses() to print out its information. There may be more than one course with that number. 
    				4. If no course was found with this course number, print out an error. 
    			*/
                    
                    
                    st = COURSE;
                    
                    printf("Enter the course number: ");
                    scanf("%d", &code );
                   
                    
                    found = findCourses( origin, dest, length, key1Letter, code, st); 
                    
                    if ( found == 0)
                    {
                        printf("ERROR");
                    }
                    else 
                    {
                        printCourseInformation(*dest); // needs to printCourses ---> what is length? findcourses returns count // and is it a double?
                    }
                    free(dest);
			break;
    		case 3: 
    		
				/* This case will find a course by the days. 
    				1. Ask the user for a course number 
    				2. Call the findCourses() function with this course number and the SearchType DAY.
    				3. Call printCourses() to print out its information. There may be more than one course with that number. 
    				4. If no course was found with this course number, print out an error. 
    			*/
                         // one is an issue
                        st = DAYS;
                        
                        printf("Enter the days: ");
                        scanf("%s", classDays );
                        
                       
                        found = findCourses( origin, dest, length, classDays, key2Num, st); 
                        
                        if ( found == 0)
                        {
                            printf("ERROR");
                        }
                        else
                        {
                            printCourses(dest, found);
                        }
                        free(dest); 
    			break;	
				
    		case 4: 
    		
				/* This case will find a course by the instructor's last name. 
    				1. Ask the user for a course number 
    				2. Call the findCourses() function with this course number and the SearchType INSTRUCTOR.
    				3. Call printCourses() to print out its information. There may be more than one course with that number. 
    				4. If no course was found with this course number, print out an error. 
    			*/
                         
                        st = INSTRUCTOR;
                        
                        printf("Enter an instructor name: ");
                        scanf("%s", nameofInstruct );                       
              
                        found = findCourses( origin, dest, length, nameofInstruct, key2Num, st); 
                        
                        if ( found == 0)
                        {
                            printf("ERROR");
                        }
                        else
                        {
                            printCourses(dest, found);
                        }
                        free(dest); 
    			break;	
    		case 5:
    			/* This case calls printCourses */
                        printCourses(origin, length);
    			break;
    		case 6:
    			/* This case calls computeStats */
                        computeStats(origin, length);
    			break;
    		case 0:
    			printf( "Good-bye\n\n" );
    			return 0;
    		default:
    			printf( "Invalid option.\n\n" );
    			break;
    	}
      
    }   
   
}
