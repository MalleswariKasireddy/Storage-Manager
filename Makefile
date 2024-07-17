CC= gcc
CFLAGS=-I.
output: test_assign1_1.c storage_mgr.c dberror.c
	$(CC) -o output test_assign1_1.c storage_mgr.c dberror.c


clean: 
	rm -f output

all: output