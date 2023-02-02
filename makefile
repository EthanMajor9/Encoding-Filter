#
# this makefile will compile and and all source
# found in the "MyApp" directory.  This represents a sample
# development directory structure and project
# 
# =======================================================
#                  MyApp Example
# =======================================================
# FINAL BINARY Target
./bin/encodeInput : ./obj/encodeInput.o
	cc ./obj/encodeInput.o -o ./bin/encodeInput

#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/encodeInput.o : ./src/encodeInput.c 
	cc -c ./src/encodeInput.c -o ./obj/encodeInput.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


