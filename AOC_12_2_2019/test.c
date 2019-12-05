#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXCHAR 1000
int sizeOfCsv(char *input)
{
    int count = 0;
    int inc = 0;
    while(input[inc] != '\0')
    {
        if(input[inc] == ',')
        {
            count++;
        }
        inc++;
    }
    return count+1;
}

int printIntCodeProgram(int *program, int progSize)
{
    int i = 0;
    while(i < progSize)
    {
        printf(" %d ",program[i]);
        i++;
    }
    printf("\n");
}

int handleOpCodeOne(int *program, int pos)
{
    // Opcode 1 adds together numbers read from two positions 
    // and stores the result in a third position. 
    // The three integers immediately after the opcode tell 
    // you these three positions - the first two indicate
    // the positions from which you should 
    // read the input values, 
    // and the third indicates the position at which 
    // the output should be stored.
    program[program[pos+3]] = program[program[pos+1]] + program[program[pos+2]];
}

int handleOpCodeTwo(int *program, int pos)
{
    // Opcode 2 works exactly like opcode 1, 
    // except it multiplies the two inputs instead 
    // of adding them. Again, the three integers 
    // after the opcode indicate where the inputs 
    // and outputs are, not their values.
    program[program[pos+3]] = program[program[pos+1]] * program[program[pos+2]];
}

int populateIntCodeProgramFromCsv(char *input, int *program)
{
    char *temp = malloc(sizeof(input));
    int inc = 0;
    int tempPos = 0;
    int outputPos = 0;
    while(input[inc] != '\0')
    {
        if(input[inc] == ',')
        {
            program[outputPos] = atoi(temp);
            tempPos = 0;
            outputPos++;
        }
        else {
            temp[tempPos] = input[inc];
            tempPos++;
        }
        temp[tempPos] = '\0';
        inc++;
    }
    program[outputPos] = atoi(temp);
    free(temp);
}

int setNounAndVerb(int *program, int noun, int verb)
{
    program[1] = noun;
    program[2] = verb;
}

int main(int argc, char *argv[]) 
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    int noun = atoi(argv[2]);
    int verb = atoi(argv[3]);
    char *str = malloc(sizeof(char)*MAXCHAR);
    if(fp == NULL) {
        printf("No such file found with path %s\n", argv[1]);
        return 1;
    }
    fgets(str, MAXCHAR, fp);
    fclose(fp);
    int program[sizeOfCsv(str)];
    populateIntCodeProgramFromCsv(str, program);
    int progSize = sizeof(program)/sizeof(int);
    int i = 0;
    free(str);
    setNounAndVerb(program, noun, verb);
    while(i < progSize)
    {
        if(program[i] == 99)
        {
            break;
        }
        if(program[i] == 1)
        {
            handleOpCodeOne(program, i);
        }
        else if(program[i] == 2)
        {
            handleOpCodeTwo(program, i);
        }
        i = i + 4;
    }
    printIntCodeProgram(program, progSize);
    return 0;
}
