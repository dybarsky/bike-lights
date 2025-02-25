SOURCES = src/sources
HEADERS = src/headers
OUT = build

export OBJ
OBJ += $(OUT)/pattern.o
OBJ += $(OUT)/switch.o
OBJ += $(OUT)/timer.o
OBJ += $(OUT)/spi.o
OBJ += $(OUT)/main.o

CC = msp430-gcc
CFLAGS = -g -mmcu=msp430g2553
INCFLAGS = -I/usr/local/include -I$(HEADERS)

help:
	@echo "Tasks: clean, build, flash, all"

all: | clean build flash

rebuild: | clean build

clean:
	@echo "Clean"
	rm -rf build

build-dir:
	mkdir -p build

wait:
	sleep 1

flash: | $(OUT)/firmware.elf wait
	@echo "Flashing";\
	mspdebug rf2500 "prog $(OUT)/firmware.elf"

build: $(OUT)/firmware.elf
	@echo '   ___ _   _  ___ ___ ___  ___ ___ '
	@echo '  / __| | | |/ __/ __/ _ \/ __/ __|'
	@echo '  \__ \ |_| | (_| (_|  __/\__ \__ \'
	@echo '  |___/\__,_|\___\___\___||___/___/'
	@echo ''

$(OUT)/firmware.elf: | build-dir $(OBJ)
	@echo "Link firmware";\
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(OUT)/firmware.elf

$(OUT)/main.o: $(SOURCES)/main.c $(HEADERS)/*.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/main.c -o $(OUT)/main.o

$(OUT)/spi.o: $(SOURCES)/spi.c $(HEADERS)/spi.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/spi.c -o $(OUT)/spi.o

$(OUT)/switch.o: $(SOURCES)/switch.c $(HEADERS)/switch.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/switch.c -o $(OUT)/switch.o

$(OUT)/timer.o: $(SOURCES)/timer.c $(HEADERS)/timer.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/timer.c -o $(OUT)/timer.o

$(OUT)/pattern.o: $(SOURCES)/pattern.c $(HEADERS)/pattern.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/pattern.c -o $(OUT)/pattern.o

.SILENT: clean build-dir wait
.PHONY: clean build-dir flash build
