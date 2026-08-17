CC=gcc
CFLAGS=-g -Wall

# 중간 생성 *.o 목록
OBJS=main.o
TARGET=pith.out

all: $(TARGET)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
