KFVER=130

CC = gcc
CFLAGS += -fPIC -O2 -MMD -I./include
#CFLAGS += -fPIC -O0 -g -pg -MMD -I./include


.SUFFIXES:
.SUFFIXES: .c .o

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<


bin = xcorr_test
lib = libkiss_fft.a

LIBOBJS = src/kiss_fft.o src/kiss_fftr.o src/kiss_fftnd.o src/kiss_fftndr.o \
	   src/kfc.o src/kiss_xcorr.o
OBJS = ${LIBOBJS} xcorr_test.o
DEPS := $(OBJS:%.o=%.d)

all : ${bin}

${lib} : ${LIBOBJS}
	${AR} ruv $@ $^

xcorr_test : xcorr_test.o ${lib} 
	${CC} $^ -o $@ -lm

clean : 
	rm -f ${OBJS} ${DEPS} ${lib} ${bin}
