all: xeuclid

xeuclid : xeuclid.c
	gcc xeuclid.c -L.. -lcrypto  -I../include/crypto -o xeuclid
	
clean:
	rm -f xeuclid *.o
