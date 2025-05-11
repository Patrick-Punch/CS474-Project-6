# Very Very Simple Filesystem (VVSFS)

## Building

Command line:

* `make` to build. An executable called `testfs` will be produced.
* `make clean` to remove all object files.
* `make pristine` to clean everything.

VS Code:

* The default build task runs `make`.

## Files

* `block.c`, `block.h`: Provide block-level read/write access to a virtual disk image.
* `image.c`, `image.h`: Handle opening, closing, and managing the backing store image file (e.g. `test.img`).
* `ctest.h`: Lightweight testing framework used to write and run unit tests.
* `testfs.c`: Contains test cases that validate the behavior of the image and block layer.
* `Makefile`: Build configuration for compiling the project.

## Data

The system simulates a very simple block-based filesystem using a virtual disk image:

* The disk image is treated as a flat file (`test.img`) containing fixed-size blocks.
* Blocks are accessed via low-level routines in `block.c`, and the image file is managed by `image.c`.

Key data elements:

* **Image file**: A file on the host system representing the "disk".
* **Block size**: Fixed-size chunks read and written to/from the image file.
* **Block index**: Integer offsets used to seek to the correct position in the file.

## Functions

* `main()` (in `testfs.c`)
  * Calls functions to test the image and block layers
* `image_open(const char *filename, int truncate)`
  * Opens or creates a disk image file
* `image_close()`
  * Closes the currently open disk image
* `block_read(int block_num, void *buf)`
  * Reads a block of data from the disk image into a buffer
* `block_write(int block_num, const void *buf)`
  * Writes a block of data from a buffer to the disk image

## Notes

* The test executable (`testfs`) uses assertions via `ctest.h` to validate image and block-level operations.
* Filesystem logic such as directories, file metadata, or content storage is not yet implemented.
* This code is a foundation for building a more complete filesystem on top of image and block abstractions.
* `test.img` is the simulated disk; it is created or overwritten when tests are run.