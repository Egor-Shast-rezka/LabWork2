CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++17 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
DOCDIR = doc

TARGET = $(BINDIR)/Poker

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
OBJS_NO_MAIN = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter-out $(SRCDIR)/main.cpp, $(SRCS)))

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SRCS))

GTEST_LIBS = -lgtest -lgtest_main -pthread

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_base: $(OBJDIR)/gtestBaseGameRule.o $(OBJS_NO_MAIN)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_base $(OBJDIR)/gtestBaseGameRule.o $(OBJS_NO_MAIN) $(GTEST_LIBS)
	$(BINDIR)/test_base

test_bot: $(OBJDIR)/gtestBot.o $(OBJS_NO_MAIN)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_bot $(OBJDIR)/gtestBot.o $(OBJS_NO_MAIN) $(GTEST_LIBS)
	$(BINDIR)/test_bot

test_game: $(OBJDIR)/gtestPathGame.o $(OBJS_NO_MAIN)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_game $(OBJDIR)/gtestPathGame.o $(OBJS_NO_MAIN) $(GTEST_LIBS)
	$(BINDIR)/test_game

$(OBJDIR)/gtestBaseGameRule.o: $(TESTDIR)/gtestBaseGameRule.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/gtestBot.o: $(TESTDIR)/gtestBot.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/gtestPathGame.o: $(TESTDIR)/gtestPathGame.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/Poker $(BINDIR)/test_base $(BINDIR)/test_bot $(BINDIR)/test_game

.PHONY: all clean test_base test_bot test_game doc
