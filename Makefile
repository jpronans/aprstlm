CFLAGS = -O2
LDFLAGS =	-lm -lncurses -lpanel

DIRS =	core pcsat pcsat2 raft ande castor pollux mim
OBJS =	core/*.o pcsat/*.o pcsat2/*.o raft/*.o ande/*.o mim/*.o  castor/*.o \
        pollux/*.o
HDRS =	include/aprstlm.h include/aprstlm-sockets.h include/aprstlm-ncurses.h

aprstlm:	$(OBJS) $(HDRS)
		for i in $(DIRS); do \
		(cd $$i; make) ;\
		done
		gcc $(CFLAGS) $(LDFLAGS) -o aprstlm $(OBJS)

core/*.o:	core/*.c
		cd core; make

pcsat/*.o:	pcsat/*.c
		cd pcsat; make

pcsat2/*.o:	pcsat2/*.c
		cd pcsat2; make

raft/*.o:	raft/*.c
		cd raft; make

ande/*.o:	ande/*.c
		cd ande; make

castor/*.o:	castor/*.c
		cd castor; make

pollux/*.o:	pollux/*.c
		cd pollux; make

mim/*.o:	mim/*.c
		cd mim; make

clean:
		for i in $(DIRS); do \
		(cd $$i; rm -f *.o ) ;\
		done
		rm -f aprstlm
