#include "include/utils.h"
#include <corecrt.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include <string.h>
#include <assert.h>


typedef unsigned long long bigint_t ;

bigint_t to_decimal(long long n) {
  bigint_t dec = 0, i = 0, rem;
  while (n != 0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return dec;
}
void part_one(int mode){

    FILE* file = get_file(mode);
    char* line_data = read_line(file);
    size_t k = strlen(line_data);
    int one_count[k] = {} , zero_count[k] = {};
    
    while(line_data  != NULL ){
        assert(strlen(line_data) == k);
        for (int i = 0; i < k; i++) {
            if ( line_data[i] == '1') one_count[i] ++;
            else zero_count[i]++;
        }
        free_line(line_data);
        line_data = read_line(file);
    }
    
    bigint_t gamma_rate = 0,epsilon_rate = 0;
    for (int i = 0 ; i < k ; i++) {
        bigint_t value = powl( 10 ,  k -i -1);
        if (one_count[i] > zero_count[i]) gamma_rate += value;
        else epsilon_rate += value;
    
    }
    fclose(file);
    bigint_t power_consuption = to_decimal(gamma_rate) * to_decimal(epsilon_rate);

    printf("Part 1 -> %llu\n",power_consuption);
}


bigint_t find_rating(int type,int rows ,int cols , char* line_data){

    int c , indices[rows] = {};
    bigint_t rating = 0;
    for ( c = 0 ; c < cols; c++) {
        int zero_count = 0,one_count = 0 ,r;
        for (r = 0; r < rows; r++) {
            if(indices[r]) continue;
            char bit = line_data[c + r * (cols+1)];
            if (bit == '1') one_count ++;
            else  zero_count++;

        }
        char common_bit = one_count >= zero_count ? '1' : '0';
        if (type) common_bit = one_count < zero_count ? '1' : '0';

        int counter = 0 , last_idx = 0;
        for (r = 0; r < rows; r++) {
            if(indices[r]) continue;
            if ( line_data[c + r * (cols+1)] ==  common_bit )
            {
                counter ++;
                last_idx = r;
            }
            else 
            {
                indices[r] = 1;
            }
        }
        if (counter == 1) {
            for ( c  = 0 ; c < cols ; c++) {
                char bit = line_data[c + last_idx * (cols+1)];
                if (bit == '1'){
                    rating += (bigint_t) powl( 10,  cols - c - 1);
                }
            }
            break;
        }
    }
    assert(rating != 0);
    return to_decimal(rating);
}

void part_two(int mode){

    FILE* file = get_file(mode);
    char* line_data = read_line(file);
    int cols = strlen(line_data);
    free_line(line_data);
    fseek(file, 0, SEEK_SET);
    line_data = read_until(file,EOF);
    int rows = 1 + (strlen(line_data) - 1 ) / (cols +1);

    bigint_t
    o2_rating = find_rating(0, rows,cols,line_data),
    co2_rating = find_rating(1, rows,cols,line_data),
    life_support_ratting = o2_rating * co2_rating;
    printf("Part 2 -> %llu",life_support_ratting);

    free_line(line_data);
    fclose(file);
    
}