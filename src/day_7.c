#include "include/utils.h"
#include "include/utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

array_functions(int)
array_functions_impl(int)

void parse_input(int mode,Array_int* arr){
    FILE* file = get_file(mode);
    char* line_data = read_line(file);
    char* tok = strtok(line_data,",");
    while(tok != NULL){
        array_int_push(arr,atoi(tok));
        tok = strtok(NULL,",");        
    }
    free_line(line_data);
    fclose(file);
    
}
double calc_std_deviation(Array_int* arr){
    double mean_value = 0;
    for (int i = 0; i < arr->offset; i++) {
        mean_value += (double)arr->buffer[i];
    }
    mean_value/= arr->offset;
    double std_deviation = 0;
    for (int i = 0; i < arr->offset; i++) {
        std_deviation +=( (double)arr->buffer[i] - mean_value ) * ( (double)arr->buffer[i] - mean_value );
    }
    std_deviation /= arr->offset;
    return sqrt(std_deviation);
}

void part_one(int mode){
    Array_int crabs = array_int_create();
    parse_input(mode,&crabs);

    double std_deviation = calc_std_deviation(&crabs);
    int from = std_deviation - 100;
    int to = std_deviation + 100;

    int min_fuel = 100000000;
    for (int hx = from; hx < to; hx++) {
        int fuel = 0;
        for (int i = 0; i < crabs.offset; i++) {
            int value = crabs.buffer[i] - hx;
            if (value < 0) value *= -1;
            fuel += value;
        }
        min_fuel = fuel < min_fuel ? fuel : min_fuel;
    }
    printf("Part 1 -> %d\n",min_fuel);
}

void part_two(int mode){
    Array_int crabs = array_int_create();
    parse_input(mode,&crabs);

    double std_deviation = calc_std_deviation(&crabs);
    int from = std_deviation - 100;
    int to = std_deviation + 100;

    int min_fuel = 100000000;
    for (int hx = from; hx < to; hx++) {
        int fuel = 0;
        for (int i = 0; i < crabs.offset; i++) {
            int value = crabs.buffer[i] - hx;
            if (value < 0) value *= -1;
            value = ((double)value)/2 + 0.5 * (double)(value*value);
            fuel += value;
        }
        min_fuel = fuel < min_fuel ? fuel : min_fuel;
    }
    printf("Part 2 -> %d\n",min_fuel);
}
