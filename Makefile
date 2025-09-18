CC = g++
CFLAGS = -std=c++11 -Iinclude
SRC = src/1_main.cpp src/2_huffman.cpp src/fileio.cpp
OUT = huff.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	del /F $(OUT) *.huff *.out