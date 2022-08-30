CC=g++
CC_FLAGS=-lssl -lcrypto

all:
	$(CC) src/main.cpp -o x509.bin $(CC_FLAGS)

clean:
	rm -rf *.o x509.bin
