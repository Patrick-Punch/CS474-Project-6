/*
Patrick Punch
5/11/2025
CS 474
*/
#define CTEST_ENABLE
#include "ctest.h"
#include "image.h"
#include "block.h"
#include "free.h"
#include "inode.h"
#include <string.h>

void test_open_close_image(){
    int fd = image_open("test.img", 1);
    CTEST_ASSERT(fd >= 0, "image_open should succeed");
    int result = image_close();
    CTEST_ASSERT(result == 0, "image_close should succeed");
}

void test_block_read_write(){
    unsigned char write_buf[4096], read_buf[4096];
    memset(write_buf, 0xAB, 4096);
    image_open("test.img", 1);
    bwrite(2, write_buf);
    memset(read_buf, 0, 4096);
    bread(2, read_buf);
    image_close();

    CTEST_ASSERT(memcmp(write_buf, read_buf, 4096) == 0, "read data matches written data");
}

void test_set_free(){
    unsigned char block[4096] = {0};
    set_free(block, 10, 1);
    CTEST_ASSERT(block[10 / 8] & (1 << (10 % 8)), "10th bit should be set to 1");
    set_free(block, 10, 0); 

    CTEST_ASSERT(!(block[10 / 8] & (1 << (10 % 8))), "10th bit should be cleared (0)");
}

void test_find_free(){
    unsigned char block[4096] = {0};
    set_free(block, 10, 1);
    set_free(block, 15, 1);
    int free_idx = find_free(block);

    CTEST_ASSERT(free_idx == 0, "First free bit should be at index 0");

    for (int i = 0; i < (4096 * 8); i++){
        set_free(block, i, 1);
    }
    free_idx = find_free(block);

    CTEST_ASSERT(free_idx == -1, "Should not find any free bit when all are set");
}

void test_ialloc(){
    unsigned char inode_map[4096] = {0};
    image_open("test.img", 1);
    set_free(inode_map, 2, 0);
    set_free(inode_map, 3, 0);
    bwrite(1, inode_map);

    int inode = ialloc();
    CTEST_ASSERT(inode == 0, "Expected inode 0 to be allocated first");
    inode = ialloc();
    CTEST_ASSERT(inode == 1, "Expected inode 1 to be allocated next");

    image_close();
}

void test_alloc(){
    unsigned char block_map[4096] = {0};
    image_open("test.img", 1);
    set_free(block_map, 2, 0);
    set_free(block_map, 3, 0);
    bwrite(2, block_map);

    int block = alloc();
    CTEST_ASSERT(block == 0, "Expected block 0 to be allocated first");
    block = alloc();
    CTEST_ASSERT(block == 1, "Expected block 1 to be allocated next");

    image_close();
}

int main()
{
    test_open_close_image();
    test_block_read_write();
    test_set_free();
    test_find_free();
    test_ialloc();
    test_alloc();
    CTEST_RESULTS();
    return ctest_status;
}