CXX= g++
CXXFLAGS= -W -Wall -pedantic
CXXFLAGS_DEBUG= -g
CXXFLAGS_RELEASE= -O2
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE= -I./include/
SOURCES= main.cpp Cell.cpp Model.cpp View.cpp Frame.cpp Widget.cpp Tab.cpp Button.cpp Page.cpp Pannel.cpp Text.cpp NumericBar.cpp Slider.cpp Intro.cpp Listeners.cpp Virus.cpp
OBJECTS= $(SOURCES:.cpp=.o)
EXEC= gol

CXXFLAGS_TYPE= $(CXXFLAGS_RELEASE)

.PHONY: all, clean

all: $(OBJECTS)
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS_TYPE) $(LDFLAGS)

main.o: src/main.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS_TYPE) $(INCLUDE)

%.o: src/%.cpp include/%.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS_TYPE) $(INCLUDE)

clean:
	@rm -rf *.o *~ $(EXEC)
