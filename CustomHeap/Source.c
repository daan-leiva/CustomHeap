#include <stdio.h>
#include <stdlib.h>

struct Block {
	int block_size; // # of bytes in the data section
	struct Block *next_block; // next block in singly linked list
	void *data; // reference to the data
};

// global variables
// size of void* on this compiler
int const void_size = sizeof(void*); // space for the "next" pointer
// space for the "next" pointer and the size value
int const overhead = sizeof(void*) + sizeof(int);
// points to FIRST free block
struct Block *free_head;

// functions
void my_initialize_heap(int);
void* my_alloc(int);
void my_free(void *);

// Step 1 -- Done
// Step 2 -- Done
// Step 3 -- Done
// Step 4 -- Done
// Step 5 -- Done	
// Step 6
// Step 7

// Test 1
// Test 2
// Test 3
// Test 4

// Program 1
// Program 2
// Program 3
// Program 4

int main()
{
	// ask the user to enter a positive integer n
	int n;
	printf("Enter a positive integer n:");

	// take user input
	scanf_s("%d", &n);

	// initialize heap
	my_initialize_heap(n);

	// allocate an int

}

// uses malloc to initialize a bufer of given size to use in your custome allocator
void my_initialize_heap(int size)
{
	free_head = malloc(size);
	free_head->block_size = size - overhead;
	free_head->next_block = NULL;
	free_head->data = free_head + overhead;
}

// Fills an allocation request of size bytes and
// returns a pointer to the data portion of the block
// used to satisfy the request	
void* my_alloc(int size)
{
	char keep_going = 1;
	struct Block *temp_block = free_head;

	// run through the block using the first fit heuristic
	while (keep_going)
	{
		// check that the current block has enough size
		if (temp_block->block_size > size)
		{
			// check that the data size is a multiple of void*
			if (size%void_size == 0)
			{
				// at this point the data will be allocated so do not continue
				keep_going = 0;

				// need a second temp pointer to switch stuff
				struct Block* chosen_block = temp_block;

				// case 1: head and split
				if (temp_block == free_head && temp_block->block_size - size > overhead + void_size)
				{
					int shift_length = size + overhead;
					// switch temp block next's reference

					// null the original next pointer

					// move the free head reference

				}
				// case 2: head and no split
				else if (temp_block == free_head)
				{
					// 
				}
				// ccase 3: not head and split
				else if (temp_block != free_head  && temp_block->block_size - size > overhead + void_size)
				{

				}
				// case 4: not head and no split
				else
				{

				}
				// decide whether to split or not
				if (temp_block->block_size - size > overhead + void_size)
				{
					//
					// split
					//

					// move the free head
					free_head = free_head + size + overhead;
					// return pointer to the data section of new space
					return temp_block->data;
				}
				else
				{
					// TO_DO: no split
				}
			}
		}
		// update temp to next
		temp_block = temp_block->next_block;
	}

	// if no block can be found return null
	return NULL;
}

void my_free(void *data)
{
	// store current location of the freehead for later
	struct  Block* temp_pointer = free_head;

	// cast data to an address location in order to
	// do pointer arithmetic
	free_head = (struct Block*)((unsigned char*)data) - overhead;

	// move the free heads next pointer
	free_head->next_block = temp_pointer;
}

void main_test()
{

}