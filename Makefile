CC = gcc
OBJ = linux_hw.o oled.o sensirion_common.o sht3x_example_usage.o main.o oled_display.o sht3x.o
CPPFLAGS = -Icommon -Isht3x -Ioled
VPATH = common:sht3x:oled

bbb: $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f bbb *.o */*.o
