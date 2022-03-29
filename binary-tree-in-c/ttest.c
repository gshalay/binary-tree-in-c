#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 128
struct record
{
  char last_name[STRLEN];
  char first_name[STRLEN];
  char phone_number[13];
};


int comp_first_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->first_name, rec2->first_name );

#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->first_name, rec2->first_name, result );
#endif
  return result;
}

int comp_last_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->last_name, rec2->last_name );
#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->last_name, rec2->last_name, result );
#endif
  return result;
}

int main( int argc, char **argv )
{
  FILE *fp;
  int result;
  char buffer[256];

  struct record record;
  struct Node *by_last_name=NULL;
  struct Node *by_first_name=NULL;
  struct Performance * lastNamePerformance = newPerformance();
  struct Performance * firstNamePerformance = newPerformance();

  // read names and phone numbers for the file, into record
  // add record to two different trees
  fp = fopen( "names1.txt", "r" );
  if (!fp)
  {
    fprintf( stderr, "Could not open \"names1.txt\"\n" );
    exit(-1);
  }

  fgets( buffer, 256, fp );	// skip header line

  while (!feof(fp))
  {
    result = fscanf( fp, "%s %s", record.first_name, record.last_name );
    result += fscanf( fp, "%s", record.phone_number );

    if (result==3)
    {
      printf( "Adding %s, %s\n", record.last_name, record.first_name );
      addItem( lastNamePerformance, &by_last_name, &comp_last_name, 
  	       &record, sizeof(record) );

      addItem( firstNamePerformance, &by_first_name, &comp_first_name, 
	       &record, sizeof(record) );
    }
  }
  fclose( fp );

  printf("First Name Performance:\n");
  printf( "reads:   %5d\n", firstNamePerformance->reads );
  printf( "writes:  %5d\n", firstNamePerformance->writes );
  printf( "mallocs: %5d\n", firstNamePerformance->mallocs );
  printf( "frees:   %5d\n", firstNamePerformance->frees );

  printf("Last Name Performance:\n");
  printf( "reads:   %5d\n", lastNamePerformance->reads );
  printf( "writes:  %5d\n", lastNamePerformance->writes );
  printf( "mallocs: %5d\n", lastNamePerformance->mallocs );
  printf( "frees:   %5d\n", lastNamePerformance->frees );

  printf( "Trees built\n" );

  strcpy( record.last_name, "Pollard" );
  if ( searchItem( lastNamePerformance, &by_last_name, &comp_last_name,
                   &record, sizeof(record) ) )
  {
    printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                               record.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  strcpy( record.first_name, "Frida" );
  if ( searchItem( firstNamePerformance, &by_first_name, &comp_first_name,
                   &record, sizeof(record) ) )
  {
    printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                               record.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  strcpy( record.last_name, "Kremer" );
  if ( searchItem( lastNamePerformance, &by_last_name, &comp_last_name,
                   &record, sizeof(record) ) )
  {
    printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                               record.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  freeTree( lastNamePerformance, &by_last_name );
  freeTree( firstNamePerformance, &by_first_name );
  
  printf("First Name Performance:\n");
  printf( "reads:   %5d\n", firstNamePerformance->reads );
  printf( "writes:  %5d\n", firstNamePerformance->writes );
  printf( "mallocs: %5d\n", firstNamePerformance->mallocs );
  printf( "frees:   %5d\n", firstNamePerformance->frees );

  printf("Last Name Performance:\n");
  printf( "reads:   %5d\n", lastNamePerformance->reads );
  printf( "writes:  %5d\n", lastNamePerformance->writes );
  printf( "mallocs: %5d\n", lastNamePerformance->mallocs );
  printf( "frees:   %5d\n", lastNamePerformance->frees );


  free( firstNamePerformance );
  free( lastNamePerformance );
}
