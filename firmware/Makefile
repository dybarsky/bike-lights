SOURCES = src/sources
HEADERS = src/headers
OUT = build

export OBJ
OBJ += $(OUT)/timer.o
OBJ += $(OUT)/shift.o
OBJ += $(OUT)/servo.o
OBJ += $(OUT)/switch.o
OBJ += $(OUT)/main.o

CC = msp430-gcc
CFLAGS = -g -mmcu=msp430g2553
INCFLAGS = -I/usr/local/include -I$(HEADERS)

help:
	@echo "Targets: clean, build, flash" 

clean:
	@echo "Clean"
	rm -rf build

build-dir:
	mkdir -p build

.SILENT: clean build-dir
.PHONY: clean build-dir flash build

flash: $(OUT)/firmware.elf
	@echo "Flashing";\
	mspdebug rf2500 "prog $(OUT)/firmware.elf"

build: $(OUT)/firmware.elf
	@echo "SUCCESSFUL";\

$(OUT)/firmware.elf: | build-dir $(OBJ)
	@echo "Link firmware";\
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(OUT)/firmware.elf

$(OUT)/main.o: $(SOURCES)/main.c $(HEADERS)/*.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/main.c -o $(OUT)/main.o

$(OUT)/shift.o: $(SOURCES)/shift.c $(HEADERS)/shift.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/shift.c -o $(OUT)/shift.o

$(OUT)/switch.o: $(SOURCES)/switch.c $(HEADERS)/switch.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/switch.c -o $(OUT)/switch.o

$(OUT)/servo.o: $(SOURCES)/servo.c $(HEADERS)/servo.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/servo.c -o $(OUT)/servo.o

$(OUT)/timer.o: $(SOURCES)/timer.c $(HEADERS)/*.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/timer.c -o $(OUT)/timer.o
