#
# OMNeT++/OMNEST Makefile for SmartParkingSystem
#

# Output
TARGET = SmartParkingSystem

# C++ sources
SRCS = src/ParkingController.cc src/ParkingSlot1.cc

# Generated sources
MSGFILES = src/SmartParkingMessages.msg
GENERATED_SOURCES = $(MSGFILES:.msg=_m.cc)

# Include path
INCLUDE_PATH = -I. -Isrc

# Build rules
all: checkmakefiles $(TARGET)

$(TARGET): $(SRCS) $(GENERATED_SOURCES)
	cd src && $(MAKE)

%_m.cc %_m.h: %.msg
	cd src && opp_msgc ../$<

clean: checkmakefiles
	cd src && $(MAKE) clean
	rm -f src/*_m.cc src/*_m.h

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile src/*_m.cc src/*_m.h

makefiles:
	cd src && opp_makemake -f --deep -O out -KINET_PROJ=../../inet4

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi

.PHONY: all clean cleanall makefiles checkmakefiles