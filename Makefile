CC=g++
CFLAGS=-g -Wall -std=c++11
LDFLAGS=-lPocoNet -lPocoFoundation -lprotobuf
IFLAGS=-I./inc -I./lib/network

BINDIR=bin/
LIBDIR=lib/
SRCDIR=src/
INCDIR=inc/

SHAREDSRCS=map/map2d.cpp
CLIENTSRCS=client.cpp
CLIENTSRCS+=$(SHAREDSRCS)
SERVERSRCS=server.cpp network/gameconnection.cpp
SERVERSRCS+=$(SHAREDSRCS)

CLIENTOBJS=$(addprefix $(LIBDIR),$(CLIENTSRCS:.cpp=.o))
SERVEROBJS=$(addprefix $(LIBDIR),$(SERVERSRCS:.cpp=.o))

SHAREDHEADERS=network/defaults.hpp network/gameconnectionfactory.hpp
CHEADERS=
CHEADERS+=$(SHAREDHEADERS)
CLIENTHEADERS=$(addprefix $(INCDIR),$(CHEADERS))
SHEADERS=
SHEADERS+=$(SHAREDHEADERS)
SERVERHEADERS=$(addprefix $(INCDIR),$(SHEADERS))

CLIENT=$(BINDIR)client
SERVER=$(BINDIR)server

MCC=protoc
MSRCDIR=src/network/messages/
MIFLAGS=-I=$(MSRCDIR)
MLIBDIR=lib/network/messages/
MCPPOUT=--cpp_out=$(MLIBDIR)
MESSAGENAMES=header map
MESSAGES=$(addprefix $(MLIBDIR),$(addsuffix .pb.cc,$(MESSAGENAMES)))
MESSAGEOBJECTS=$(MESSAGES:.pb.cc=.o)

all: $(MESSAGES) $(MESAGEOBJECTS) $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENTHEADERS) $(MESSAGEOBJECTS) $(CLIENTOBJS) |directories
	$(CC) $(CLIENTOBJS) $(MESSAGEOBJECTS) -o $@ $(LDFLAGS)

$(SERVER): $(SERVERHEADERS) $(MESSAGEOBJECTS) $(SERVEROBJS) |directories
	$(CC) $(SERVEROBJS) $(MESSAGEOBJECTS) -o $@ $(LDFLAGS)

$(LIBDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBDIR)%.o : $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(MLIBDIR)%.o : $(MLIBDIR)%.pb.cc $(MLIBDIR)%.pb.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(MLIBDIR)%.pb.cc : $(MSRCDIR)%.proto |directories
	$(MCC) $(MIFLAGS) $(MCPPOUT) $<

directories:
	mkdir -p bin lib/network/messages lib/map

.PHONY:
clean:
	rm -rf bin/client bin/server lib/*
