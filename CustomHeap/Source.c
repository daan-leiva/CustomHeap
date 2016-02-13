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
// Step 6 -- Done
// Step 7 -- Done

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
	// since we want the data portion to have "size" many bytes, we need to allocate
	// size + overehad space for our block
	free_head = malloc(size + overhead);
	free_head->block_size = size;
	free_head->next_block = NULL;
	free_head->data = (struct Block*)((unsigned char*)free_head + overhead);
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
		if (temp_block->block_size > size && size%void_size == 0)
		{
			// at this point the data will be allocated so do not continue
			keep_going = 0;

			// case 1: head and split
			if (temp_block == free_head && temp_block->block_size - size > overhead + void_size)
			{
				// block that will be carved out
				struct Block* split_block;
				// amount of shift to the new carved block
				int shift_length = size + overhead;
				// position new block
				split_block = ((unsigned char*)temp_block + shift_length);
				// set split block variables
				split_block->block_size = temp_block->block_size - size - overhead;
				split_block->data = (struct Block*)((unsigned char*)split_block + overhead);
				split_block->next_block = temp_block->next_block;
				// null the original next pointer
				temp_block->next_block = NULL;
				// update the size of the original block
				temp_block->block_size = size;
				// datat pointer remains the same
				// move the free head reference
				free_head = split_block;

				// return reference to data
				return temp_block->data;
			}
			// case 2: head and no split
			else if (temp_block == free_head)
			{
				// move free head reference
				free_head = temp_block->next_block;
				// since no block is being carved do not update the size of the block allocated
				// null the next reference of the allocated block
				temp_block->next_block = NULL;

				//return reference to data
				return temp_block->data;
			}
			// ccase 3: not head and split
			else if (temp_block != free_head  && temp_block->block_size - size > overhead + void_size)
			{
				// block that will be carved out
				struct Block* split_block;
				// amount of shift to the new carved block
				int shift_length = size + overhead;
				// position new block
				split_block = ((unsigned char*)temp_block + shift_length);
				// set split block variables
				split_block->block_size = temp_block->block_size - size - overhead;
				split_block->data = (struct Block*)((unsigned char*)split_block + overhead);
				split_block->next_block = temp_block->next_block;
				// update the size of the original block
				temp_block->block_size = size;
				// datat pointer remains the same

				// subroutine to find the Block that is pointing to our temp_block
				// start at the free head and move to the next until the next pointer is reference to our temp_block
				struct Block* previous_block = free_head;
				while (previous_block->next_block != temp_block) {
					previous_block = previous_block->next_block;
				}
				// update previous block reference to the next that temp_block has
				previous_block->next_block = temp_block->next_block;
				// null temp_block's next pointer
				temp_block->next_block = NULL;

				// return temp_block's data
				return temp_block->data;
			}
			// case 4: not head and no split
			else
			{
				// subroutine to find the Block that is pointing to our temp_block
				// start at the free head and move to the next until the next pointer is reference to our temp_block
				struct Block* previous_block = free_head;
				while (previous_block->next_block != temp_block) {
					previous_block = previous_block->next_block;
				}
				// update previous block reference to the next that temp_block has
				previous_block->next_block = temp_block->next_block;
				// null temp_block's next pointer
				temp_block->next_block = NULL;

				// return temp_block's data
				return temp_block->data;
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
	// new free block
	struct  Block* free_block = (struct Block*)((unsigned char*)data - overhead);
	// link the new block to the list of free blocks by swaping references with the free head
	free_block->next_block = free_head;
	// move free heads reference
	free_head = free_block;
}

void main_test()
{

}