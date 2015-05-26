CC=g++
CFLAGS=-g -Wall -std=c++11
LDFLAGS=-lPocoNet -lPocoFoundation
IFLAGS=-I./inc

BINDIR=bin/
LIBDIR=lib/
SRCDIR=src/
INCDIR=inc/

SHAREDSRCS=
CLIENTSRCS=client.cpp
CLIENTSRCS+=$(SHAREDSRCS)
SERVERSRCS=server.cpp network/gameconnection.cpp
SERVERSRCS+=$(SHAREDSRCS)

CLIENTOBJS=$(addprefix $(LIBDIR),$(CLIENTSRCS:.cpp=.o))
SERVEROBJS=$(addprefix $(LIBDIR),$(SERVERSRCS:.cpp=.o))

SHAREDHEADERS=network/defaults.hpp
CHEADERS=
CHEADERS+=$(SHAREDHEADERS)
CLIENTHEADERS=$(addprefix $(INCDIR),$(CHEADERS))
SHEADERS=
SHEADERS+=$(SHAREDHEADERS)
SERVERHEADERS=$(addprefix $(INCDIR),$(SHEADERS))

CLIENT=$(BINDIR)client
SERVER=$(BINDIR)server

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENTOBJS) $(CLIENTHEADERS) |directories
	$(CC) $(CLIENTOBJS) -o $@ $(LDFLAGS)

$(SERVER): $(SERVEROBJS) $(SERVERHEADERS) |directories
	$(CC) $(SERVEROBJS) -o $@ $(LDFLAGS)

$(LIBDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBDIR)%.o : $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

directories:
	mkdir -p bin lib/network

.PHONY:
clean:
	rm -rf bin/client bin/server lib/*
