SHELL = /bin/sh
CEXECNAME = get_time
COBJECTS = socket_client.c
CFLAGS = `` -Wall -Werror -Wextra -pedantic -g -std=c17 -O2
LDFLAGS = `` -L
LDLIBS = `` -l
CC = gcc-9

$(CEXECNAME): $(COBJECTS)
	$(CC) $(CFLAGS) $(COBJECTS) $(LDFLAGS) $(LDLIBS) -o $(CEXECNAME)