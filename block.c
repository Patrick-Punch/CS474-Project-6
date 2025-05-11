/*
Patrick Punch
5/4/2025
CS 474
*/
#include <unistd.h>
#include "image.h"
#include "block.h"
#include "free.h"

#define BLOCK_SIZE 4096

unsigned char *bread(int block_num, unsigned char *block){
    off_t offset = block_num * BLOCK_SIZE;
    lseek(image_fd, offset, SEEK_SET);
    read(image_fd, block, BLOCK_SIZE);
    return block;
}

void bwrite(int block_num, unsigned char *block){
    off_t offset = block_num * BLOCK_SIZE;
    lseek(image_fd, offset, SEEK_SET);
    write(image_fd, block, BLOCK_SIZE);
}

int alloc(void){
    unsigned char block_map[4096];
    bread(2, block_map);

    int free_block = find_free(block_map);
    if (free_block != -1){
        set_free(block_map, free_block, 1);
        bwrite(2, block_map);
        return free_block;
    }
    return -1;
}