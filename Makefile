all:
	gcc -Wall -L /usr/local/lib/ -l nfc_nci_linux -o poll poll.c