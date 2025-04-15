###############################################################################
# Final Makefile for C++ Project (No STL)
#
# Builds:
#   1) "bitcoin_project"  (main application from src/*.cpp)
#   2) "test_structures"  (test file: test_structures.cpp)
#   3) "test_sorting"     (test file: test_sorting.cpp)
#   4) "test_analytics"   (test file: test_analytics.cpp)
#
# Folder Layout (assumed):
#   ProjectRoot/
#     ├── src/
#     │    ├── main.cpp
#     │    ├── DataStructures.cpp
#     │    ├── Sorting.cpp
#     │    └── Analytics.cpp
#     ├── tests/
#     │    ├── test_structures.cpp
#     │    ├── test_sorting.cpp
#     │    └── test_analytics.cpp
#     ├── include/
#     │    ├── DataStructures.hpp
#     │    ├── Sorting.hpp
#     │    └── Analytics.hpp
#     ├── data/
#     │    ├── chunk_0.csv
#     │    └── ...
#     └── Makefile
#
# Usage:
#   make               -> build everything
#   make clean         -> remove object files and executables
#   make check         -> run valgrind on the main executable
#
#   To run each test:
#     ./test_structures
#     ./test_sorting
#     ./test_analytics
#
#   To run the main application:
#     ./bitcoin_project
###############################################################################

CXX       := g++
CXXFLAGS  := -std=c++11 -Wall -Wextra -pedantic -O2
LDLIBS    := 
OBJDIR    := build
SRCDIR    := src
TESTDIR   := tests
INCDIR    := include

# -----------------------------------------------------------------------------
# 1) Main Application Files
# -----------------------------------------------------------------------------
MAIN_SOURCES := \
  $(SRCDIR)/main.cpp \
  $(SRCDIR)/DataStructures.cpp \
  $(SRCDIR)/Sorting.cpp \
  $(SRCDIR)/Analytics.cpp

MAIN_OBJECTS := \
  $(OBJDIR)/main.o \
  $(OBJDIR)/DataStructures.o \
  $(OBJDIR)/Sorting.o \
  $(OBJDIR)/Analytics.o

MAIN_TARGET := bitcoin_project

# -----------------------------------------------------------------------------
# 2) Test Files -> Each one becomes its own executable
# -----------------------------------------------------------------------------

# Test 1: test_structures
TEST_STRUCTURES_SOURCES := $(TESTDIR)/test_structures.cpp
TEST_STRUCTURES_OBJECTS := $(OBJDIR)/test_structures.o
TEST_STRUCTURES_TARGET  := test_structures

# Test 2: test_sorting
TEST_SORTING_SOURCES := $(TESTDIR)/test_sorting.cpp
TEST_SORTING_OBJECTS := $(OBJDIR)/test_sorting.o
TEST_SORTING_TARGET  := test_sorting

# Test 3: test_analytics
TEST_ANALYTICS_SOURCES := $(TESTDIR)/test_analytics.cpp
TEST_ANALYTICS_OBJECTS := $(OBJDIR)/test_analytics.o
TEST_ANALYTICS_TARGET  := test_analytics

# -----------------------------------------------------------------------------
# Default "all" -> build main app + all test executables
# -----------------------------------------------------------------------------
all: $(MAIN_TARGET) \
     $(TEST_STRUCTURES_TARGET) \
     $(TEST_SORTING_TARGET) \
     $(TEST_ANALYTICS_TARGET)

# -----------------------------------------------------------------------------
# MAIN TARGET BUILD RULE
# -----------------------------------------------------------------------------
$(MAIN_TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ $^ $(LDLIBS)

# -----------------------------------------------------------------------------
# TEST TARGET BUILD RULES
# Each test links against specific object(s) from src if needed
# -----------------------------------------------------------------------------
$(TEST_STRUCTURES_TARGET): \
  $(TEST_STRUCTURES_OBJECTS) \
  $(OBJDIR)/DataStructures.o
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ $^ $(LDLIBS)

$(TEST_SORTING_TARGET): \
  $(TEST_SORTING_OBJECTS) \
  $(OBJDIR)/Sorting.o
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ $^ $(LDLIBS)

$(TEST_ANALYTICS_TARGET): \
  $(TEST_ANALYTICS_OBJECTS) \
  $(OBJDIR)/DataStructures.o \
  $(OBJDIR)/Analytics.o
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ $^ $(LDLIBS)

# -----------------------------------------------------------------------------
# Compilation Rules for .cpp -> .o
# -----------------------------------------------------------------------------
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/DataStructures.o: $(SRCDIR)/DataStructures.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/Sorting.o: $(SRCDIR)/Sorting.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/Analytics.o: $(SRCDIR)/Analytics.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Tests
$(OBJDIR)/test_structures.o: $(TEST_STRUCTURES_SOURCES)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/test_sorting.o: $(TEST_SORTING_SOURCES)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/test_analytics.o: $(TEST_ANALYTICS_SOURCES)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# -----------------------------------------------------------------------------
# Utility Targets
# -----------------------------------------------------------------------------
clean:
	rm -rf $(OBJDIR)/*.o \
	       $(MAIN_TARGET) \
	       $(TEST_STRUCTURES_TARGET) \
	       $(TEST_SORTING_TARGET) \
	       $(TEST_ANALYTICS_TARGET)

# Run Valgrind on the main application
check: $(MAIN_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(MAIN_TARGET)

.PHONY: all clean check