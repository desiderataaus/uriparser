# Copyright (c) National Acoustic Laboratiors
#
#  Makefile
#

MACHINE=/MACHINE:X86

OEXT = obj
CC = cl
CXX = $(CC)
CXX_OUT = -o
CXXFLAGS = /DWIN32 /I . /RTC1 /EHa /W3  /nologo /TP /Z7 

LD=link.exe /NOLOGO
LD_OUT = /OUT:

LFLAGS=/NOLOGO $(MACHINE)

TARGET = uriparser.exe

OBJS = uriparser.$(OEXT) uritest.$(OEXT) 

uriparser.$(OEXT):uriparser.h

all:$(OBJS) $(TARGET)

.cpp.$(OEXT):
	$(CXX) $(CXXFLAGS) -c $(CXX_OUT) $(@) $(<)

$(TARGET): $(OBJS)
	 $(LD) $(LD_OUT)$(TARGET) $(LFLAGS)  $(OBJS)

clean:
	del /F /Q *.obj $(TARGET)