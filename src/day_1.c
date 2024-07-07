
#include "include/utils.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
void part_one(int mode){

    FILE* file = get_file(mode);
    char* line_data = read_line(file);
    int prev = atoi(line_data);
    int counter = 0;
    while(line_data != NULL){
        free_line(line_data);
        line_data = read_line(file);
        int curr = atoi(line_data);
        if (curr > prev) counter++;
        prev = curr;
    }
    fclose(file);
    printf("Part 1 -> %d\n",counter);
}

void part_two(int mode){
    FILE* file = get_file(mode);
    char* line_data ;
    int _value_count = 0;
    int _value_size = sizeof(int) * 2000;
    int* values = malloc(_value_size);

    while((line_data = read_line(file)) != NULL){
        assert(_value_count*sizeof(int) < _value_size);
        values[_value_count++] = atoi(line_data);
        free_line(line_data);
    }
    fclose(file);
    int i = -1;
    int sum = 0;
    while(i++,i < 3 && i < _value_count ){
        sum +=values[i];
    }
    int couner = 0;
    while(i < _value_count){
        int new_sum = sum - values[i - 3] + values[i];
        if (new_sum > sum ) couner ++;
        sum = new_sum;
        i++;
    }
    printf("Part 2 -> %d\n",couner);
}
