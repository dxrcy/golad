CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

TARGET = golad

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run

