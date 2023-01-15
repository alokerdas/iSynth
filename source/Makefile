IVERILOG_INSTALL_DIR =$(HOME)/projects/install/iverilog
OBJECTS = generateLpms.o synthMain.o massageHandler.o
INCDIRS = -I$(IVERILOG_INSTALL_DIR)/include/iverilog
LIBDIRS = -L$(IVERILOG_INSTALL_DIR)/lib/ivl
CFLAGS = -g -fPIC
#CFLAGS = -O2 -fPIC
LDFLAGS = -shared
CC = gcc

all: install

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIRS) -c $<
synth.tgt: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)
install: synth.tgt
	cp synth.tgt $(IVERILOG_INSTALL_DIR)/lib/ivl
	cp synth*.conf $(IVERILOG_INSTALL_DIR)/lib/ivl
clean:
	rm -rf synth.tgt *.o
