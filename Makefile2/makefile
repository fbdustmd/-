CC = gcc
TARGET = pcap-test
SRC = pcap-test.c
LDLIBS = -lpcap
IFACE = ens33

all: $(TARGET)
	sudo ./$(TARGET) $(IFACE)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(LDLIBS)

clean:
	rm -f $(TARGET) *.o
