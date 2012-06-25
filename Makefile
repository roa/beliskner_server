WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB) -llua
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/beliskner_server

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB) -llua
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/beliskner_server

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/base/BaseServer.o $(OBJDIR_DEBUG)/src/base/Config.o $(OBJDIR_DEBUG)/src/base/InputHandler.o $(OBJDIR_DEBUG)/src/base/Logger.o $(OBJDIR_DEBUG)/src/base/main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/base/BaseServer.o $(OBJDIR_RELEASE)/src/base/Config.o $(OBJDIR_RELEASE)/src/base/InputHandler.o $(OBJDIR_RELEASE)/src/base/Logger.o $(OBJDIR_RELEASE)/src/base/main.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src/base || mkdir -p $(OBJDIR_DEBUG)/src/base

after_debug: 

debug: before_debug out_debug after_debug

out_debug: $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/src/base/BaseServer.o: src/base/BaseServer.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/BaseServer.cpp -o $(OBJDIR_DEBUG)/src/base/BaseServer.o

$(OBJDIR_DEBUG)/src/base/Config.o: src/base/Config.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/Config.cpp -o $(OBJDIR_DEBUG)/src/base/Config.o

$(OBJDIR_DEBUG)/src/base/InputHandler.o: src/base/InputHandler.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/InputHandler.cpp -o $(OBJDIR_DEBUG)/src/base/InputHandler.o

$(OBJDIR_DEBUG)/src/base/Logger.o: src/base/Logger.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/Logger.cpp -o $(OBJDIR_DEBUG)/src/base/Logger.o

$(OBJDIR_DEBUG)/src/base/main.o: src/base/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/main.cpp -o $(OBJDIR_DEBUG)/src/base/main.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src/base

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src/base || mkdir -p $(OBJDIR_RELEASE)/src/base

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/src/base/BaseServer.o: src/base/BaseServer.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/BaseServer.cpp -o $(OBJDIR_RELEASE)/src/base/BaseServer.o

$(OBJDIR_RELEASE)/src/base/Config.o: src/base/Config.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/Config.cpp -o $(OBJDIR_RELEASE)/src/base/Config.o

$(OBJDIR_RELEASE)/src/base/InputHandler.o: src/base/InputHandler.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/InputHandler.cpp -o $(OBJDIR_RELEASE)/src/base/InputHandler.o

$(OBJDIR_RELEASE)/src/base/Logger.o: src/base/Logger.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/Logger.cpp -o $(OBJDIR_RELEASE)/src/base/Logger.o

$(OBJDIR_RELEASE)/src/base/main.o: src/base/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/main.cpp -o $(OBJDIR_RELEASE)/src/base/main.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src/base

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

