CC=gcc

TARGET=main

LIBS=-lpbc -lgmp -lcrypto

all:
	$(CC) main.c setup.c hash.c extract.c encrypt.c trapdoor.c test.c decrypt.c -o $(TARGET) $(LIBS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)