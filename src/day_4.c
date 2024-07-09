#include "include/utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DISPLAY_STUFF 0

typedef  struct {
    int* buffer;
    int size;
} UInt_Array;

int comparator(int c){
    return 1;
}

UInt_Array parse_to_int_array(char* line_data,const char* delimeter){
    char* tok = strtok(line_data,delimeter);

    int offset = 0,size = sizeof(int) * 4;

    int* buffer = malloc(size);
    assert(buffer != NULL);

    while(tok != NULL){
        if (sizeof(int) * offset == size - sizeof(int)){
            size *= 2;
            buffer = realloc(buffer, size);
            assert(buffer != NULL);
        }
        buffer[offset++] = atoi(tok);
        tok = strtok(NULL, delimeter);
    }
    if (offset < size-1) {
        buffer = realloc(buffer,sizeof(int)*offset + 1);
        assert(buffer != NULL);
    }
    buffer[offset] = -1;
    assert(buffer != NULL);
    UInt_Array arr = {.buffer = buffer,.size = offset};
    free_line(line_data);
    return arr;
    
}

void display(UInt_Array* board,int* m_board){

    int b_count = board->size / 25;
    printf("\n");
    for (int k = 0; k < b_count; k++) {
        int off = k * 25;
        printf("\033[37m");
        printf("--- Board %d ---\n",k+1);
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 5; i++) {
                int index = off + i + j * 5;
                if (m_board[index]) printf("\033[31m");
                else printf("\033[36m");

                int value = board->buffer[index];
                if (value > 9)printf("%d ",value);
                else printf(" %d ",value);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\033[37m");
}
int check_win(UInt_Array* board ,int* m_board,int offset){
    offset = offset * 25;
    for (int j = 0; j < 5; j++) {
        int row_counter = 0;
        int col_counter = 0;
        for (int i = 0; i < 5; i++) {
            int r_idx = offset + i + j * 5;
            int c_idx = offset + j + i * 5;
            row_counter+= m_board[r_idx];
            col_counter+= m_board[c_idx];
        }
        assert(row_counter <= 5);
        assert(col_counter <= 5);
        if (row_counter == 5) return 1;
        if (col_counter == 5) return 1;
    }
    return 0;
}
int mark_number(UInt_Array* board ,int* m_board,int number){
    for (int i = 0 ; i < board->size; i++) {
        if(board->buffer[i] == number){
            m_board[i] = 1;
        }
    }
    return -1;

}
int unmarked_sum(UInt_Array* board ,int* m_board,int offset){
    offset = offset * 25;
    int sum = 0;
    for (int i = offset ; i < offset + 25; i++) {
        if (!m_board[i]){
            sum += board->buffer[i];
        }
    }
    return sum;
}
void part_one(int mode){
    FILE* file = get_file(mode);
    UInt_Array sequence = parse_to_int_array(read_line(file), ",");
    free_line(read_line(file));
    UInt_Array board = parse_to_int_array( _read_until(file, comparator) , " \n");
    int m_board[board.size] = {};
    fclose(file);

    
    for (int s = 0; s < sequence.size; s++) {
        int number = sequence.buffer[s];
        
        mark_number(&board,m_board,number);

        #if DISPLAY_STUFF
            display(&board, m_board);
            printf("Round-> %d\tMarked -> %d\n",s+1,number);
        #endif

        int b_count = board.size / 25;
        int someone_won = 0;
        for (int i = 0; i < b_count; i++) {
            someone_won = check_win(&board, m_board, i);
            if (someone_won > 0){
                int u_sum = unmarked_sum(&board, m_board, i);

                #if DISPLAY_STUFF
                    printf("Board %d Won\tWinning Number Was -> %d\tUnmarked Sum -> %d\n",i/25 +1,number,u_sum);
                #endif
                
                printf("Part 1 -> %d\n",number * u_sum);
                break;
            }
        }
        if (someone_won) break;
        #if DISPLAY_STUFF
            getchar();
         #endif
        
    }
    free(sequence.buffer);
    free(board.buffer);
}

void part_two(int mode){

    FILE* file = get_file(mode);
    UInt_Array sequence = parse_to_int_array(read_line(file), ",");
    free_line(read_line(file));
    UInt_Array board = parse_to_int_array( _read_until(file, comparator) , " \n");
    int m_board[board.size] = {};
    fclose(file);

    int b_count = board.size / 25;
    int won_boards[b_count] = {};
    for (int s = 0; s < sequence.size; s++) {
        int number = sequence.buffer[s];
        
        mark_number(&board,m_board,number);

        #if DISPLAY_STUFF
            display(&board, m_board);
            printf("Round-> %d\tMarked -> %d\n",s+1,number);
        #endif
        
        int won_count = 0;
        int last_winner = -1;
        for (int i = 0; i < b_count; i++) {

            int someone_won = 0;
            
            someone_won = check_win(&board, m_board, i);
            won_count += someone_won || won_boards[i];
            if (won_boards[i]) continue;
            if (someone_won){
                won_boards[i] = 1;
                last_winner = i;
            }
        }
        if (won_count == board.size / 25){
            int u_sum = unmarked_sum(&board, m_board, last_winner);
            printf("Part 2 -> %d\n",number * u_sum);
            break;
        }
        #if DISPLAY_STUFF
            getchar();
        #endif
    }
    free(sequence.buffer);
    free(board.buffer);

}
