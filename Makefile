CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++20 -Iinclude -Ilibs/rtaudio -Ilibs/rtaudio/include 
LDFLAGS = -Llibs/rtaudio/build -lrtaudio

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
OBJS_NO_MAIN = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter-out $(SRCDIR)/main.cpp  $(SRCDIR)/main_timer.cpp, $(SRCS)))

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SRCS))

GTEST_LIBS = -lgtest -lgtest_main -pthread


# =========== Main Build Targets ===========

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
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# =========== Google Test Targets ===========

test: $(OBJDIR)/gtestBaseGameRule.o \
      $(OBJDIR)/gtestBot.o \
      $(OBJDIR)/gtestPathGame.o \
      $(OBJDIR)/gtestCharacters.o \
      $(OBJDIR)/gtestGameMode.o \
      $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test $^ $(GTEST_LIBS) $(LDFLAGS)
	$(BINDIR)/test
	$(BINDIR)/test --gtest_output=xml:$(DOCDIR)/test_report_new.xml


# =========== GTest Object Compilation ===========

$(OBJDIR)/gtestMain.o: $(TESTDIR)/gtestMain.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
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
	

# =========== Clean ===========

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(TIMERPATH) $(TIMER)


# =========== PHONY ===========

.PHONY: all clean test
