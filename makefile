################################################################################
# CS 240 Chess Project Makefile
#
# INSTRUCTIONS: This is a starting makefile for the chess project. You are to 
# keep this up-to-date as you add source files. In addition to keeping it 
# up-to-date with new files you create, you need to make the following changes 
# to this makefile:
# 
#	- edit the command associated with the memcheck pseudo-target (i.e.,
#		the valgrind command. See the note above it for details).
# 
# NOTES: 
# 1. All the code for the GUI side of this project is provided for you. As a 
# result, there are some things in this makefile which you do not need to alter.
# Such items will be clearly marked with comments.
# 2. Out-of-the-box, without making any changes to this initial makefile, 
# running "make run" will compile the code and bring up an empty GUI. 
################################################################################

 
############### --- BEGIN UNTOUCHABLE SECTION - Do Not Edit --- ################
# Macros for GUI libraries.
GTKMM = gtkmm-2.4
SIGC = sigc++-2.0
LIBGLADE = libglademm-2.4

# TODO Re-phrase: CFLAGS are the -I values needed to compile files using the 
# GTKMM, SIGC, and LIBGLADE libraries
CFLAGS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --cflags`
# TODO Re-phrase: LIBS are the paths to the static libraries for GTKMM, SIGC,
# and LIBGLADE needed for linking
LIBS   = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --libs`
####################### --- END UNTOUCHABLE SECTION --- ########################

POS_INDEPENDENT = -fPIC

# TODO Re-phrase: Macros for directory tree locations
MODEL_SRC = model/src/
MODEL_INC = model/inc/
MODEL_OBJ = model/obj/
VIEW_SRC = view/src/
VIEW_INC = view/inc/
VIEW_OBJ = view/obj/
CONT_SRC = controller/src/
CONT_INC = controller/inc/
CONT_OBJ = controller/obj/
TEST_OBJ = test/obj/
TEST_INC = test/inc/
UTILS_INC = utils/inc
EXE = bin/chess			# normal executable
MEXE = bin/mchess			# executable for memory testing
#executable which runs unit tests
TEST_EXE = bin/testchess

# Macros for compilation flags
INCLUDES = -I$(MODEL_INC) -I$(VIEW_INC) -I$(CONT_INC) -I$(UTILS_INC)
DEBUG = -g # Uncomment this if you want to compile with debug info

# Uncomment the flag on this next line to turn off the logging messages from the
# GUI
LOG_FLAG = #'-DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO)'

# There are two different main.o files. One is for memory testing.
MAIN_O = $(CONT_OBJ)main.o
MEMMAIN_O = $(CONT_OBJ)memcheck_main.o
#test main o is also in TEST_OBJS
TESTMAIN_O = test/obj/TestDriver.o

# Store all of the object files created from my source files
MODEL_OBJS = $(patsubst model/src/%.cpp, model/obj/%.o, $(wildcard model/src/*.cpp))
CONT_OBJS = $(patsubst controller/src/%.cpp, controller/obj/%.o, $(wildcard controller/src/*.cpp))
CONT_OBJS_NOT_MAIN = $(filter-out $(MAIN_O), $(CONT_OBJS))
MY_OBJS =  $(MODEL_OBJS) $(CONT_OBJS_NOT_MAIN)
TEST_OBJS = $(patsubst test/src/%.cpp, test/obj/%.o, $(wildcard test/src/*.cpp))
TEST_OBJS_NOT_MAIN = $(filter-out test/obj/TestDriver.o, $(TEST_OBJS))

# These are all the object files that go into the library
LIB_OBJS = $(VIEW_OBJ)ChessView.o \
      $(VIEW_OBJ)ChessGuiBoardCell.o \
      $(VIEW_OBJ)ChessGuiBoard.o \
      $(VIEW_OBJ)ChessGui.o \
      $(VIEW_OBJ)ChessGuiImages.o \
      $(VIEW_OBJ)SelectDialog.o

#These are all of the object files that go into the CS240 Utils library
CS240_UTIL_OBJS := $(patsubst utils/src/%.cpp, utils/obj/%.o, $(wildcard utils/src/*.cpp))

#CS240 Util library header files that have no cpp counterpart
CS240_UTIL_H = $(UTILS_INC)/CS240Exception.h $(UTILS_INC)/InputStream.h $(UTILS_INC)/UnitTest.h $(UTILS_INC)/Referenceable.h $(UTILS_INC)/Reference.h

#Two libraries to be created
LIB_SO = lib/libchessGUI.so lib/libcs240utils.so

################################################################################
# Pseudo-targets

test: $(TEST_EXE)
	@echo test objs are $(TEST_OBJS)
	$(TEST_EXE)

mchecktest:	$(TEST_EXE)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp $(TEST_EXE) h c
#command-line args go here

mcheckgui:	$(EXE)
	export G_SLICE=always-malloc
	export G_DEBUG=gc-friendly
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=nip2.supp $(EXE) h h

run: runhh
	
	
runhh: $(EXE)
	$(EXE) h h
	
runhc: $(EXE)
	$(EXE) h c
	
runch: $(EXE)
	$(EXE) c h
	
runcc: $(EXE)
	$(EXE) c c

bin: $(EXE)

lib: $(LIB_SO)

backup: clean
	tar -cvf `date '+%m%d%y'`.tgz *

# Run the executable for memory testing
# Instructions: Edit the command below so that it runs the  
# memory-check executable in Human-Human mode (i.e., add necessary command  
# line arguments to the end of valgrind the command below).	
memcheck: $(MEXE)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp $(MEXE) h h

# Clean removes all of the .o files, libraries, and executables
clean:
	@rm -f $(MODEL_OBJ)*.o
	@rm -f $(VIEW_OBJ)*.o
	@rm -f $(CONT_OBJ)*.o
	@rm -f $(EXE)
	@rm -f $(MEXE)
	@rm -f $(LIB_OBJS)
	@rm -f $(CS240_UTIL_OBJS)
	@rm -f $(LIB_SO)
	@rm -f $(TEST_OBJ)*.o


################################################################################
# Targets for executables and main object files

# Explanation: There are two different executables, with two different main 
# object files, because main.cpp needs to be built differently depending on 
# whether you are doing memory testing or not. This is because the GTK library,
# and other GUI tools, have memory leaks that we cannot figure out how to 
# suppress. Therefore, when building an executable for memory testing, we use a
# macro (MEMCHECK) to tell the compiler to not include the code that builds the
# GUI. So when we check for memory leaks during passoff, we don't have to use
# the GUI.

# Main executable
$(EXE): $(MAIN_O) $(MY_OBJS) lib
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(EXE) $(MAIN_O) $(MY_OBJS) $(LIB_SO) $(CFLAGS) $(LIBS)
	chmod ugo+x $(EXE)

# Executable for memory testing
$(MEXE): $(MEMMAIN_O) $(MY_OBJS) lib
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(MEXE) $(MEMMAIN_O) $(MY_OBJS) $(LIB_SO) $(CFLAGS) $(LIBS)
	chmod ugo+x $(MEXE)

$(TEST_EXE): $(MY_OBJS) $(TEST_OBJS) lib/libcs240utils.so
#@echo $(TEST_EXE) depends on $(MY_OBJS) AND $(TEST_OBJS)
	g++ $(INCLUDES) -o $(TEST_EXE) $(TEST_OBJS) $(MY_OBJS) lib/libcs240utils.so

# Main object file
$(MAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp

# Main .o for memory testing
$(MEMMAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ -DMEMCHECK $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MEMMAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp

################################################################################
# Targets for controller and model object files
$(MODEL_OBJ)%.o: model/src/%.cpp model/inc/%.h
	g++ -c $(CFLAGS) -o $@ -I model/inc -I $(CONT_INC) -I $(UTILS_INC) -I $(VIEW_INC) $<

$(CONT_OBJ)%.o: controller/src/%.cpp controller/inc/%.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $@ -c $(LOG_FLAG) -I $(CONT_INC) -I $(VIEW_INC) -I $(UTILS_INC) $<

################################################################################
# Targets for test files
$(TEST_OBJ)%.o: test/src/%.cpp $(TEST_INC)%.h
	g++ -c $(DEBUG) -o $@ -I $(UTILS_INC) -I $(CONT_INC) -I $(MODEL_INC) -I $(VIEW_INC) -I $(TEST_INC) $<
	
#$(TEST_OBJ)TestLoad.o: test/src/TestLoad.cpp $(TEST_INC)TestLoad.h
#g++ -c $(DEBUG) -o $(TEST_OBJ)TestLoad.o -I $(UTILS_INC) -I $(CONT_INC) -I $(MODEL_INC) -I $(VIEW_INC) -I $(TEST_INC) test/src/TestLoad.cpp
	
$(TESTMAIN_O): test/src/TestDriver.cpp
	g++ -c $(DEBUG) -o $(TESTMAIN_O) -I $(UTILS_INC)/ -I $(CONT_INC) -I $(MODEL_INC) -I $(VIEW_INC) -I $(TEST_INC) test/src/TestDriver.cpp

################################################################################
# Targets for creating CS240 Utils and GUI libraries
lib/libchessGUI.so:	$(LIB_OBJS)
	g++ -shared -o lib/libchessGUI.so $(LIB_OBJS)

lib/libcs240utils.so:	$(CS240_UTIL_OBJS)
	g++ -shared -o lib/libcs240utils.so $(CS240_UTIL_OBJS)

################################################################################
# Targets for GUI-related object files
# Compiled as position-independent code
$(VIEW_OBJ)ChessView.o: $(VIEW_SRC)ChessView.cpp $(VIEW_INC)SelectDialog.h $(VIEW_INC)ChessView.h $(CONT_INC)IChessController.h
	g++ $(DEBUG) $(POS_INDEPENDENT) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessView.o -c $(LOG_FLAG) $(VIEW_SRC)ChessView.cpp

$(VIEW_OBJ)ChessGuiBoardCell.o: $(VIEW_SRC)ChessGuiBoardCell.cpp $(VIEW_INC)ChessGuiBoardCell.h $(VIEW_INC)ChessGuiImages.h
	g++ $(DEBUG) $(POS_INDEPENDENT) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoardCell.o -c $(VIEW_SRC)ChessGuiBoardCell.cpp

$(VIEW_OBJ)ChessGuiBoard.o: $(VIEW_SRC)ChessGuiBoard.cpp $(VIEW_INC)ChessGuiBoard.h $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h
	g++ $(DEBUG) $(POS_INDEPENDENT) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoard.o -c $(VIEW_SRC)ChessGuiBoard.cpp

$(VIEW_OBJ)ChessGui.o: $(VIEW_SRC)ChessGui.cpp $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)SelectDialog.h
	g++ $(DEBUG) $(POS_INDEPENDENT) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGui.o -c $(VIEW_SRC)ChessGui.cpp

$(VIEW_OBJ)ChessGuiImages.o: $(VIEW_SRC)ChessGuiImages.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)Inline.h
	g++ $(DEBUG) $(POS_INDEPENDENT) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiImages.o -c $(VIEW_SRC)ChessGuiImages.cpp

$(VIEW_OBJ)SelectDialog.o: $(VIEW_SRC)SelectDialog.cpp
	g++ $(DEBUG) $(POS_INDEPENDENT) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)SelectDialog.o -c $(VIEW_SRC)SelectDialog.cpp

################################################################################
# Targets for CS240 Utils object files
# Compiled as position-independent code
utils/obj/%.o: utils/src/%.cpp $(UTILS_INC)/%.h $(CS240_UTIL_H)
	g++ -c $(DEBUG) $(POS_INDEPENDENT) -o $@ -I $(UTILS_INC) $<


