#include "include/utils.h"
#include <stdio.h>
#include <string.h>

void parse_input(int mode,unsigned long long* arr){
    FILE* file = get_file(mode);
    char* line_data = read_line(file);
    char* tok = strtok(line_data,",");
    while(tok != NULL){
        int value = atoi(tok);
        arr[value]++;
        tok = strtok(NULL,",");        
    }
    free_line(line_data);
    fclose(file);
}
void part_one(int mode){
    unsigned long long  fishes[9] ={0};
    parse_input(mode,fishes);
    
    int offset = 0;
    int DURATION = 80;
    for (int n = 0; n < DURATION; n++) {

        //////////////////// DEBUG /////////////////////////
        // printf("\nDAY_> %d\tOFFSET_> %d\n",n,offset);  //
        // for (int i = 0; i < 9; i++) {                  //
        //     int idx = (offset + i)%9;                  //
        //     printf("%llu | ",fishes[idx]);             //
        // }                                              //
        // printf("\n");                                  //
        // getchar();                                     //
        ////////////////////////////////////////////////////

        offset = (n+1) % 9;
        fishes[(offset+7)%9] += fishes[(offset)%9];
    }
    unsigned long long fishes_count = 0;
    for (int i = 0; i < 9; i++) {
        fishes_count += fishes[i];
    }
    printf("Part 1 -> %llu\n",fishes_count);
}

void part_two(int mode){
    unsigned long long  fishes[9] ={0};
    parse_input(mode,fishes);
    
    int offset = 0;
    int DURATION = 256;
    for (int n = 0; n < DURATION; n++) {
        fishes[(offset+7)%9] += fishes[(offset)%9];
        offset = (n+1) % 9;
    }
    unsigned long long fishes_count = 0;
    for (int i = 0; i < 9; i++) {
        fishes_count += fishes[i];
    }
    printf("Part 2 -> %llu\n",fishes_count);
}