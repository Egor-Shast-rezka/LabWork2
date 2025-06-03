CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++20 -Iinclude -Ilibs/rtaudio -Ilibs/rtaudio/include 
LDFLAGS = -Llibs/rtaudio/build -lrtaudio -lasound -lpthread

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
	if [ ! -d libs/rtaudio ]; then git clone --depth 1 https://github.com/thestk/rtaudio.git libs/rtaudio; fi
	mkdir -p libs/rtaudio/build
	cd libs/rtaudio/build && cmake -D RTAUDIO_API_ALSA=ON -D BUILD_SHARED_LIBS=ON .. && make -j
	cd libs/rtaudio/build && \
	if [ -f librtaudio.so ]; then \
		echo "Dynamic library exists"; \
	elif ls librtaudio.so.* 1> /dev/null 2>&1; then \
		ln -sf $$(ls librtaudio.so.* | head -n1) librtaudio.so; \
	elif [ -f librtaudio.a ]; then \
		ln -sf librtaudio.a librtaudio.so; \
	else \
		echo "Error: No rtaudio library found!"; exit 1; \
	fi

libs/rtaudio/build/librtaudio.so: rtaudio

# =========== Google Test Targets ===========

test: rtaudio libs/rtaudio/build/librtaudio.so \
      $(OBJDIR)/gtestBaseGameRule.o \
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
	rm -rf $(OBJDIR) $(BINDIR) $(TIMERPATH) $(TIMER) libs/rtaudio/build


# =========== PHONY ===========

.PHONY: all clean test
