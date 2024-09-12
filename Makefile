C_FLAGS := -g -Wall

%.bin: %.c
	gcc $(C_FLAGS) -o $@ $<
