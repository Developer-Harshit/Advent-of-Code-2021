
#include "include/utils.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>


array_functions(int)
array_functions_impl(int)


#define DIM 1000
typedef struct {
    int left;
    int top;
    int right;
    int bottom;
    Array_int arr;
} Ocean;

int ol[DIM][DIM] = {};
Ocean parse_input(FILE* file){
    char* line_data;
    Array_int arr = array_int_create();
    Ocean oc = {.left = 10000,.top = 10000,.right = -10000,.bottom = -10000,};
    int max_value = -10000;
    int min_value = 10000;
    while((line_data = read_line(file)) != NULL){
        char* tok = strtok(line_data," ->,");
        int counter = 0;
        while(tok != NULL){
            int value = atoi(tok);
            max_value = max_value < value ? value : max_value;
            min_value = min_value > value ? value : min_value;
            if (counter % 2 == 0){
                oc.left = oc.left > value ? value : oc.left;
                oc.right = oc.right < value ? value : oc.right;
            }
            else {
                oc.top = oc.top > value ? value : oc.top;
                oc.bottom = oc.bottom < value ? value : oc.bottom;
            }
            array_int_push(&arr,value);
            tok = strtok(NULL, " ->,");
            counter++;
        }
        assert(counter == 4);
        free_line(line_data);
    }
    array_int_shrink(&arr);
    oc.arr = arr;
    return oc;
}
void display(Ocean * oc,int ol[DIM][DIM]){
    printf("\033[36m");
    for (int j = oc->top; j <= oc->bottom; j++) {
        for (int i = oc->left; i <= oc->right; i++) {
            
            int value = (ol[j][i]);
            if (value ) {
                printf("%d",value);
            }
            else {
                printf(".");
            }
            
        }
        printf("\n");
    }
    printf("\n");
    printf("\033[37m");

}
int count_overlap(Ocean * oc ,int ol[DIM][DIM]){
    int counter = 0;
    for (int j = oc->top; j <= oc->bottom; j++) {
        for (int i = oc->left; i <= oc->right; i++) {
            if (ol[j][i] >= 2){
            counter++;
            }
        }
    }
    return counter;
}
void clean_ol(){
    for (int j = 0; j < DIM; j++) {
        for (int i = 0; i < DIM; i++) {
            ol[j][i] = 0;
        }
    }
}

void part_one(int mode){
    clean_ol();
    FILE* file = get_file(mode);
    Ocean oc = parse_input(file);
    assert(ol != NULL);
    int k = 0;
    
    // display(&oc, ol);
    while(k < oc.arr.offset){
        int
        fx = oc.arr.buffer[k+0],
        fy = oc.arr.buffer[k+1],
        tx = oc.arr.buffer[k+2],
        ty = oc.arr.buffer[k+3];
        if(fx == tx){
            int temp = fy;
            fy = ty < fy ? ty : fy;
            ty = ty > temp ? ty : temp;
        }
        else if (fy == ty){
            int temp = fx;
            fx = tx < fx ? tx : fx;
            tx = tx > temp ? tx : temp;

        }
        else {k+=4;continue;}
        for (int j = fy; j <= ty; j++) {
            for (int i = fx; i <= tx; i++) {
               ol[j][i] +=1;
            }
        }
        // display(&oc,ol);
        // getchar();
        k+=4;
    }
    printf("Part 1 _> %d\n",count_overlap(&oc, ol));
    array_int_free(&oc.arr);
}

void part_two(int mode){
    clean_ol();
    FILE* file = get_file(mode);
    Ocean oc = parse_input(file);
    assert(ol != NULL);
    int k = 0;
    
    while(k < oc.arr.offset){
        int
        fx = oc.arr.buffer[k+0],
        fy = oc.arr.buffer[k+1],
        tx = oc.arr.buffer[k+2],
        ty = oc.arr.buffer[k+3];
        if (!(fx == tx || fy == ty)) {
            int dx = tx-fx < 0 ? -1 : 1;
            int dy = ty-fy < 0 ? -1 : 1;

            int diff = (fy-ty) * dy * -1 + 1;
            for (int d = 0 ; d < diff ; d++) {
                int i = fx + d*dx;
                int j = fy + d*dy;
                ol[j][i] ++;   
            }
        }else {
            if(fx == tx){
                int temp = fy;
                fy = ty < fy ? ty : fy;
                ty = ty > temp ? ty : temp;
            }
            else if (fy == ty){
                int temp = fx;
                fx = tx < fx ? tx : fx;
                tx = tx > temp ? tx : temp;

            }
            for (int j = fy; j <= ty; j++) {
                for (int i = fx; i <= tx; i++) {
                ol[j][i] +=1;
                }
            }
        }
        k+=4;
    }
    printf("Part 2 _> %d\n",count_overlap(&oc, ol));
    array_int_free(&oc.arr);
}
