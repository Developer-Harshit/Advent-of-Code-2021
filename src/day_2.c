#include "include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void part_one(int mode){
    char* line_data;
    FILE* file = get_file(mode);
    int h_pos = 0;
    int v_pos = 0;
    while((line_data = read_until(file,' ')) != NULL ){        
        char direction = line_data[0];
        free_line(line_data);
        line_data = read_until(file,'\n');
        int mag = atoi( line_data);
        free_line(line_data);

        if (direction == 'f'){
            h_pos += mag;
        }
        else if (direction == 'u'){
            v_pos -= mag;
        }
        else if(direction == 'd'){
            v_pos += mag;
        }
    }
    fclose(file);
    int result = h_pos * v_pos;
    printf("Part 1 -> %d\n",result);
}

void part_two(int mode){
    char* line_data;
    FILE* file = get_file(mode);
    int h_pos = 0;
    int v_pos = 0;
    int aim = 0;
    while((line_data = read_until(file,' ')) != NULL ){
        char direction = line_data[0];
        free_line(line_data);
        line_data = read_until(file,'\n');
        int mag = atoi( line_data);
        free_line(line_data);

        if (direction == 'f'){
            h_pos += mag;
            v_pos += mag * aim;
        }
        else if (direction == 'u'){
            aim -= mag;
        }
        else if(direction == 'd'){
            aim += mag;
        }
        
    }
    fclose(file);
    int result = h_pos * v_pos;
    printf("Part 1 -> %d\n",result);
}
