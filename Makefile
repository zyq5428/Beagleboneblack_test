CC = gcc
CFLAGS = -g

INCLUDES = $(wildcard ./*.h ./common/*.h ./sht3x/*.h ./oled/*.h)
SOURCES = $(wildcard ./*.c ./common/*.c ./sht3x/*.c ./oled/*.c)
INCLUDE_DIRS = -I./common -I./sht3x -I./oled

TARGET = bbb
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
