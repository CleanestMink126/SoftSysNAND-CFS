#include "all.h"
//Reads numbers from a file and puts them into the global array PRIORITIES
void read_file()
{
    FILE *myFile;
    myFile = fopen("priorities.txt", "r");

    //read file into array
    int num_vals = 224;
    PRIORITIES = malloc(num_vals * sizeof(int));
    int i;

    for (i = 0; i < num_vals; i++)
    {
        fscanf(myFile, "%d", &PRIORITIES[i]);
    }

    for (i = 0; i < num_vals; i++)
    {
        printf("Number is: %d\n\n", PRIORITIES[i]);
    }
}
