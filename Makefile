CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++20 -Iinclude -Ilibs/rtaudio -Ilibs/rtaudio/include 
LDFLAGS = -Llibs/rtaudio/build -lrtaudio -lasound -lpthread
GTEST_LIBS = -lgtest -lgtest_main -pthread

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
DOCDIR = doc
TIMER = tmp
LIBSDIR = libs
TIMERPATH = /tmp/timerData

TARGET = $(BINDIR)/Poker

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS_NO_TIMER = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter-out $(SRCDIR)/main_timer.cpp, $(SRCS)))
OBJS_NO_MAIN = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter-out $(SRCDIR)/main.cpp  $(SRCDIR)/main_timer.cpp, $(SRCS)))

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SRCS))
	
	
# =========== Main Build Targets ===========

all: $(OBJDIR) $(BINDIR) $(TIMER) rtaudio $(TARGET) 

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


# =========== Build RtAudio ===========

rtaudio:
	@mkdir -p $(LIBSDIR)
	@if [ ! -d "libs/rtaudio" ]; then \
		echo "RtAudio not found. Cloning..."; \
		git clone --depth 1 https://github.com/thestk/rtaudio.git libs/rtaudio; \
	fi
	@mkdir -p libs/rtaudio/build
	@cd libs/rtaudio/build && cmake .. && make -j


# =========== Google Test Targets ===========

TEST_OBJS = $(OBJDIR)/gtestBaseGameRule.o \
            $(OBJDIR)/gtestBot.o \
            $(OBJDIR)/gtestPathGame.o \
            $(OBJDIR)/gtestCharacters.o \
            $(OBJDIR)/gtestGameMode.o
            
test: $(TEST_OBJS) $(OBJS_NO_MAIN) | $(OBJDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test $^ $(GTEST_LIBS) $(LDFLAGS)
	LD_LIBRARY_PATH=libs/rtaudio/build $(BINDIR)/test
	LD_LIBRARY_PATH=libs/rtaudio/build $(BINDIR)/test --gtest_output=xml:$(DOCDIR)/test_report_new.xml


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


run: $(TARGET)
	LD_LIBRARY_PATH=libs/rtaudio/build ./$(TARGET)

# =========== Clean ===========

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBSDIR) /tmp/timerData tmp libs/rtaudio $(DOCDIR)/test_report_new.xml

# =========== PHONY ===========

.PHONY: all clean test rtaudio run
