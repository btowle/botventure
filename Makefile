CC=g++
CFLAGS=-g -Wall -std=c++11
LDFLAGS=-lPocoNet -lPocoFoundation -lprotobuf
IFLAGS=-I./inc -I./lib/network/messages

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

-include $(CLIENTOBJS:.o=.d)
-include $(SERVEROBJS:.o=.d)

CLIENT=$(BINDIR)client
SERVER=$(BINDIR)server

MCC=protoc
MSRCDIR=src/network/messages/
MIFLAGS=--proto_path=$(MSRCDIR)
MLIBDIR=lib/network/messages/
MOFLAGS=--cpp_out=$(MLIBDIR)
MESSAGENAMES=action botstatus enemy handshake header map sensor turn
MESSAGES=$(addprefix $(MLIBDIR),$(addsuffix .pb.cc,$(MESSAGENAMES)))
MESSAGEOBJECTS=$(MESSAGES:.pb.cc=.o)

all: $(MESSAGES) $(CLIENT) $(SERVER)

$(CLIENT): $(MESSAGEOBJECTS) $(CLIENTOBJS) | directories
	$(CC) $(CLIENTOBJS) $(MESSAGEOBJECTS) -o $@ $(LDFLAGS)

$(SERVER): $(MESSAGEOBJECTS) $(SERVEROBJS) | directories
	$(CC) $(SERVEROBJS) $(MESSAGEOBJECTS) -o $@ $(LDFLAGS)

$(LIBDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(CC) -MM -MT $@ $(CFLAGS) $(IFLAGS) $< > $(LIBDIR)$*.d

$(LIBDIR)%.o : $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(CC) -MM -MT $@ $(CFLAGS) $(IFLAGS) $< > $(LIBDIR)$*.d

$(MLIBDIR)%.o : $(MLIBDIR)%.pb.cc $(MLIBDIR)%.pb.h | directories
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(CC) -MM -MT $@ $(CFLAGS) $(IFLAGS) $< > $(MLIBDIR)$*.d

$(MLIBDIR)%.pb.cc : $(MSRCDIR)%.proto | directories
	$(MCC) $(MIFLAGS) $(MOFLAGS) $<

.PHONY: all clean directories
clean:
	rm -rf bin/client bin/server lib/*
directories:
	mkdir -p bin lib/network/messages lib/map
