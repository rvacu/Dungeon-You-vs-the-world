#Raul Valencia
#Dungeon_Cube

CC = gcc
CFLAGS = -Wall -pedantic-errors
TARGET = cubic_dungeon

$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)

clean:
	rm $(TARGET)
