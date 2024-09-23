C_FLAGS := -g -Wall

%.bin: %.c lib.c lib.h
	gcc $(C_FLAGS) -o $@ $< lib.c
