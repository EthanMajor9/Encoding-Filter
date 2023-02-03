#
# this makefile will compile and and all source
# found in the "MyApp" directory.  This represents a sample
# development directory structure and project
# 
# =======================================================
#                  MyApp Example
# =======================================================
# FINAL BINARY Target
./bin/encodeInput : ./obj/encodeInput.o ./obj/asm.o ./obj/srec.o
	cc ./obj/encodeInput.o ./obj/asm.o ./obj/srec.o -o ./bin/encodeInput

#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/encodeInput.o : ./src/encodeInput.c ./inc/encode.h
	cc -g -c ./src/encodeInput.c -o ./obj/encodeInput.o

./obj/asm.o : ./src/asm.c ./inc/encode.h
	cc -g -c ./src/asm.c -o ./obj/asm.o

./obj/srec.o : ./src/srec.c ./inc/encode.h
	cc -g -c ./src/srec.c -o ./obj/srec.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


