#include "inode.h"
#include "block.h"
#include "free.h"

int ialloc(void)
{
    unsigned char inode_map[4096];
    bread(1, inode_map); // Read inode map from disk (block 1)

    int free_inode = find_free(inode_map);
    if (free_inode != -1)
    {
        set_free(inode_map, free_inode, 1); // Mark as allocated
        bwrite(1, inode_map);               // Write updated map back to disk
        return free_inode;
    }
    return -1; // No free inodes
}