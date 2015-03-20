PROGRAMS = test toolkit

INCLUDE = stk/include
SRC_PATH = stk/src
OBJECT_PATH = stk/objects
SN_SRC = src
SN_INCLUDE = include

CC       = g++
DEFS     =   -DHAVE_GETTIMEOFDAY -D__MACOSX_CORE__ -D__LITTLE_ENDIAN__
CFLAGS   = -O3 -Wall
CFLAGS  += -I$(INCLUDE) -I$(SRC_PATH)/include -I$(SN_INCLUDE)
LIBRARY = -lpthread -framework CoreAudio -framework CoreFoundation -framework CoreMidi

# create all the STK object files
%.o : $(SRC_PATH)/%.cpp $(OBJECT_PATH)/.placeholder
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $(OBJECT_PATH)/$@

%.o : $(SRC_PATH)/include/%.cpp $(OBJECT_PATH)/.placeholder
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $(OBJECT_PATH)/$@

all: $(PROGRAMS)

$(OBJECT_PATH)/.placeholder:
	mkdir -vp $(OBJECT_PATH)
	touch $(OBJECT_PATH)/.placeholder

# Please use .sn for all test executables, so we can add the .sn extension to gitignore!

test: test.cpp Stk.o SineWave.o RtWvOut.o RtAudio.o Mutex.o
	$(CC) $(LDFLAGS) $(CFLAGS) $(DEFS) -o test.sn test.cpp $(OBJECT_PATH)/Stk.o $(OBJECT_PATH)/SineWave.o $(OBJECT_PATH)/RtWvOut.o $(OBJECT_PATH)/RtAudio.o $(OBJECT_PATH)/Mutex.o $(LIBRARY)


toolkit: Stk.o SineWave.o RtWvOut.o RtAudio.o Mutex.o
	$(CC) $(LDFLAGS) $(CFLAGS) $(DEFS) -o toolkit.sn main.cpp $(OBJECT_PATH)/Stk.o $(OBJECT_PATH)/SineWave.o $(OBJECT_PATH)/RtWvOut.o $(OBJECT_PATH)/RtAudio.o $(OBJECT_PATH)/Mutex.o $(LIBRARY) $(SN_SRC)/Tempo.cpp $(SN_SRC)/Toolkit.cpp