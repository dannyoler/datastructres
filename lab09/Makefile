all: heap heap_full

heap_full: heap_full.c
	$(CC) -Wall -g -o $@ $< -lm

heap: heap.c
	$(CC) -Wall -g -o $@ $< -lm

clean:
	$(RM) heap
