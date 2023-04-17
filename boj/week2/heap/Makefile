OBJS = int_max_heap.o main.o

%.o: %.c
	gcc -c $<

main: $(OBJS)
	gcc $(OBJS) -o main

.PHONY: clean
clean:
	rm -f $(OBJS) main