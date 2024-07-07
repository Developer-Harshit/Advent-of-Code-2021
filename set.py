import os
import sys

args = sys.argv
if (len(args) < 2):
    print("NO ARGS GIVEN")
    exit()
DAY = args[1]
PATH = f"./src/day_{DAY}.c"

should_exit = False
try :
    f = open(PATH, "r")
    f.close()
    should_exit = True
    print("File Already Exist")
except: pass
if (should_exit) : exit()
f = open(PATH, "a")
f.write(
"""
#include "include/utils.h"
#include <stdio.h>
void part_one(int mode){
    char* line_data;
    FILE* file = get_file(mode);
    while((line_data = read_line(file)) != NULL ){
        free_line(line_data);
    }
    fclose(file);
    printf("Part 1\\n");
}

void part_two(int mode){
    char* line_data;
    FILE* file = get_file(mode);
    while((line_data = read_line(file)) != NULL ){
        free_line(line_data);
    }
    fclose(file);
    printf("Part 2\\n");
}
"""
)
f.close()
