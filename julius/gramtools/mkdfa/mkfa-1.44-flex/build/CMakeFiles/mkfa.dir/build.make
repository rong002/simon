# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build

# Include any dependencies generated for this target.
include CMakeFiles/mkfa.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mkfa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mkfa.dir/flags.make

CMakeFiles/mkfa.dir/dfa.o: CMakeFiles/mkfa.dir/flags.make
CMakeFiles/mkfa.dir/dfa.o: ../dfa.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mkfa.dir/dfa.o"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mkfa.dir/dfa.o   -c /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/dfa.c

CMakeFiles/mkfa.dir/dfa.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mkfa.dir/dfa.i"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/dfa.c > CMakeFiles/mkfa.dir/dfa.i

CMakeFiles/mkfa.dir/dfa.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mkfa.dir/dfa.s"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/dfa.c -o CMakeFiles/mkfa.dir/dfa.s

CMakeFiles/mkfa.dir/dfa.o.requires:
.PHONY : CMakeFiles/mkfa.dir/dfa.o.requires

CMakeFiles/mkfa.dir/dfa.o.provides: CMakeFiles/mkfa.dir/dfa.o.requires
	$(MAKE) -f CMakeFiles/mkfa.dir/build.make CMakeFiles/mkfa.dir/dfa.o.provides.build
.PHONY : CMakeFiles/mkfa.dir/dfa.o.provides

CMakeFiles/mkfa.dir/dfa.o.provides.build: CMakeFiles/mkfa.dir/dfa.o
.PHONY : CMakeFiles/mkfa.dir/dfa.o.provides.build

CMakeFiles/mkfa.dir/main.o: CMakeFiles/mkfa.dir/flags.make
CMakeFiles/mkfa.dir/main.o: ../main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mkfa.dir/main.o"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mkfa.dir/main.o   -c /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/main.c

CMakeFiles/mkfa.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mkfa.dir/main.i"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/main.c > CMakeFiles/mkfa.dir/main.i

CMakeFiles/mkfa.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mkfa.dir/main.s"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/main.c -o CMakeFiles/mkfa.dir/main.s

CMakeFiles/mkfa.dir/main.o.requires:
.PHONY : CMakeFiles/mkfa.dir/main.o.requires

CMakeFiles/mkfa.dir/main.o.provides: CMakeFiles/mkfa.dir/main.o.requires
	$(MAKE) -f CMakeFiles/mkfa.dir/build.make CMakeFiles/mkfa.dir/main.o.provides.build
.PHONY : CMakeFiles/mkfa.dir/main.o.provides

CMakeFiles/mkfa.dir/main.o.provides.build: CMakeFiles/mkfa.dir/main.o
.PHONY : CMakeFiles/mkfa.dir/main.o.provides.build

CMakeFiles/mkfa.dir/nfa.o: CMakeFiles/mkfa.dir/flags.make
CMakeFiles/mkfa.dir/nfa.o: ../nfa.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mkfa.dir/nfa.o"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mkfa.dir/nfa.o   -c /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/nfa.c

CMakeFiles/mkfa.dir/nfa.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mkfa.dir/nfa.i"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/nfa.c > CMakeFiles/mkfa.dir/nfa.i

CMakeFiles/mkfa.dir/nfa.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mkfa.dir/nfa.s"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/nfa.c -o CMakeFiles/mkfa.dir/nfa.s

CMakeFiles/mkfa.dir/nfa.o.requires:
.PHONY : CMakeFiles/mkfa.dir/nfa.o.requires

CMakeFiles/mkfa.dir/nfa.o.provides: CMakeFiles/mkfa.dir/nfa.o.requires
	$(MAKE) -f CMakeFiles/mkfa.dir/build.make CMakeFiles/mkfa.dir/nfa.o.provides.build
.PHONY : CMakeFiles/mkfa.dir/nfa.o.provides

CMakeFiles/mkfa.dir/nfa.o.provides.build: CMakeFiles/mkfa.dir/nfa.o
.PHONY : CMakeFiles/mkfa.dir/nfa.o.provides.build

CMakeFiles/mkfa.dir/triplet.o: CMakeFiles/mkfa.dir/flags.make
CMakeFiles/mkfa.dir/triplet.o: ../triplet.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mkfa.dir/triplet.o"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mkfa.dir/triplet.o   -c /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/triplet.c

CMakeFiles/mkfa.dir/triplet.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mkfa.dir/triplet.i"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/triplet.c > CMakeFiles/mkfa.dir/triplet.i

CMakeFiles/mkfa.dir/triplet.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mkfa.dir/triplet.s"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/triplet.c -o CMakeFiles/mkfa.dir/triplet.s

CMakeFiles/mkfa.dir/triplet.o.requires:
.PHONY : CMakeFiles/mkfa.dir/triplet.o.requires

CMakeFiles/mkfa.dir/triplet.o.provides: CMakeFiles/mkfa.dir/triplet.o.requires
	$(MAKE) -f CMakeFiles/mkfa.dir/build.make CMakeFiles/mkfa.dir/triplet.o.provides.build
.PHONY : CMakeFiles/mkfa.dir/triplet.o.provides

CMakeFiles/mkfa.dir/triplet.o.provides.build: CMakeFiles/mkfa.dir/triplet.o
.PHONY : CMakeFiles/mkfa.dir/triplet.o.provides.build

CMakeFiles/mkfa.dir/voca.o: CMakeFiles/mkfa.dir/flags.make
CMakeFiles/mkfa.dir/voca.o: ../voca.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mkfa.dir/voca.o"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mkfa.dir/voca.o   -c /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/voca.c

CMakeFiles/mkfa.dir/voca.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mkfa.dir/voca.i"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/voca.c > CMakeFiles/mkfa.dir/voca.i

CMakeFiles/mkfa.dir/voca.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mkfa.dir/voca.s"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/voca.c -o CMakeFiles/mkfa.dir/voca.s

CMakeFiles/mkfa.dir/voca.o.requires:
.PHONY : CMakeFiles/mkfa.dir/voca.o.requires

CMakeFiles/mkfa.dir/voca.o.provides: CMakeFiles/mkfa.dir/voca.o.requires
	$(MAKE) -f CMakeFiles/mkfa.dir/build.make CMakeFiles/mkfa.dir/voca.o.provides.build
.PHONY : CMakeFiles/mkfa.dir/voca.o.provides

CMakeFiles/mkfa.dir/voca.o.provides.build: CMakeFiles/mkfa.dir/voca.o
.PHONY : CMakeFiles/mkfa.dir/voca.o.provides.build

CMakeFiles/mkfa.dir/gram.tab.o: CMakeFiles/mkfa.dir/flags.make
CMakeFiles/mkfa.dir/gram.tab.o: ../gram.tab.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mkfa.dir/gram.tab.o"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mkfa.dir/gram.tab.o   -c /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/gram.tab.c

CMakeFiles/mkfa.dir/gram.tab.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mkfa.dir/gram.tab.i"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/gram.tab.c > CMakeFiles/mkfa.dir/gram.tab.i

CMakeFiles/mkfa.dir/gram.tab.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mkfa.dir/gram.tab.s"
	/usr/lib64/ccache/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/gram.tab.c -o CMakeFiles/mkfa.dir/gram.tab.s

CMakeFiles/mkfa.dir/gram.tab.o.requires:
.PHONY : CMakeFiles/mkfa.dir/gram.tab.o.requires

CMakeFiles/mkfa.dir/gram.tab.o.provides: CMakeFiles/mkfa.dir/gram.tab.o.requires
	$(MAKE) -f CMakeFiles/mkfa.dir/build.make CMakeFiles/mkfa.dir/gram.tab.o.provides.build
.PHONY : CMakeFiles/mkfa.dir/gram.tab.o.provides

CMakeFiles/mkfa.dir/gram.tab.o.provides.build: CMakeFiles/mkfa.dir/gram.tab.o
.PHONY : CMakeFiles/mkfa.dir/gram.tab.o.provides.build

../gram.tab.c: ../gram.y
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "[BISON][Gram] Building parser with bison 2.4"
	cd /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex && /usr/bin/bison -d -o /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/gram.tab.c gram.y

../gram.tab.h: ../gram.tab.c

# Object files for target mkfa
mkfa_OBJECTS = \
"CMakeFiles/mkfa.dir/dfa.o" \
"CMakeFiles/mkfa.dir/main.o" \
"CMakeFiles/mkfa.dir/nfa.o" \
"CMakeFiles/mkfa.dir/triplet.o" \
"CMakeFiles/mkfa.dir/voca.o" \
"CMakeFiles/mkfa.dir/gram.tab.o"

# External object files for target mkfa
mkfa_EXTERNAL_OBJECTS =

mkfa: CMakeFiles/mkfa.dir/dfa.o
mkfa: CMakeFiles/mkfa.dir/main.o
mkfa: CMakeFiles/mkfa.dir/nfa.o
mkfa: CMakeFiles/mkfa.dir/triplet.o
mkfa: CMakeFiles/mkfa.dir/voca.o
mkfa: CMakeFiles/mkfa.dir/gram.tab.o
mkfa: CMakeFiles/mkfa.dir/build.make
mkfa: CMakeFiles/mkfa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable mkfa"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mkfa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mkfa.dir/build: mkfa
.PHONY : CMakeFiles/mkfa.dir/build

CMakeFiles/mkfa.dir/requires: CMakeFiles/mkfa.dir/dfa.o.requires
CMakeFiles/mkfa.dir/requires: CMakeFiles/mkfa.dir/main.o.requires
CMakeFiles/mkfa.dir/requires: CMakeFiles/mkfa.dir/nfa.o.requires
CMakeFiles/mkfa.dir/requires: CMakeFiles/mkfa.dir/triplet.o.requires
CMakeFiles/mkfa.dir/requires: CMakeFiles/mkfa.dir/voca.o.requires
CMakeFiles/mkfa.dir/requires: CMakeFiles/mkfa.dir/gram.tab.o.requires
.PHONY : CMakeFiles/mkfa.dir/requires

CMakeFiles/mkfa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mkfa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mkfa.dir/clean

CMakeFiles/mkfa.dir/depend: ../gram.tab.c
CMakeFiles/mkfa.dir/depend: ../gram.tab.h
	cd /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build /home/bedahr/Daten/simon/svn/trunk/julius/gramtools/mkdfa/mkfa-1.44-flex/build/CMakeFiles/mkfa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mkfa.dir/depend

