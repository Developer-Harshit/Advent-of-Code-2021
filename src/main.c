#include "include/day.h"
#include <stdio.h>


int main(int argc,char** args){
    if (argc > 1){
        if (args[1][0] == 'd'){
            printf("Test Input ->\n");
            part_one(0);
            part_two(0);
        }else if (args[1][0] == 'r'){
            printf("Big Input  ->\n");
            part_one(1);
            part_two(1);
        }
        return 0;
    }
    printf("Test Input ->\n");
    part_one(0);
    part_two(0);
    printf("\n\n");
    printf("Big Input  ->\n");
    part_one(1);
    part_two(1);
    return 0;
    
}