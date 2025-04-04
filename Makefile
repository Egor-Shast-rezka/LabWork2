CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++17 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
DOCDIR = doc
TIMER = tmp
TIMERPATH = /tmp/timerData

TARGET = $(BINDIR)/Poker

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS_NO_TIMER = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter-out $(SRCDIR)/main_timer.cpp, $(SRCS)))
OBJS_NO_MAIN = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter-out $(SRCDIR)/main.cpp, $(SRCS)))

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SRCS))

GTEST_LIBS = -lgtest -lgtest_main -pthread

all: $(OBJDIR) $(BINDIR) $(TIMER) $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

$(TIMER):
	@mkdir -p $(TIMER)
	@mkfifo $(TIMERPATH)
 
$(TARGET): $(OBJS_NO_TIMER)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_base: $(OBJDIR)/gtestBaseGameRule.o $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_base $^ $(GTEST_LIBS)
	$(BINDIR)/test_base

test_bot: $(OBJDIR)/gtestBot.o $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_bot $^ $(GTEST_LIBS)
	$(BINDIR)/test_bot

test_game: $(OBJDIR)/gtestPathGame.o $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_game $^ $(GTEST_LIBS)
	$(BINDIR)/test_game

test_char: $(OBJDIR)/gtestCharacters.o $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_char $^ $(GTEST_LIBS)
	$(BINDIR)/test_char

test_mode: $(OBJDIR)/gtestGameMode.o $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test_mode $^ $(GTEST_LIBS)
	$(BINDIR)/test_mode

all_test: test_mode test_char test_game test_bot test_base
	
$(OBJDIR)/gtestBaseGameRule.o: $(TESTDIR)/gtestBaseGameRule.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/gtestBot.o: $(TESTDIR)/gtestBot.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/gtestPathGame.o: $(TESTDIR)/gtestPathGame.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/gtestCharacters.o: $(TESTDIR)/gtestCharacters.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(OBJDIR)/gtestGameMode.o: $(TESTDIR)/gtestGameMode.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(TIMERPATH) $(TIMER)


.PHONY: all clean test_base test_bot test_game test_char test_mode all_test
