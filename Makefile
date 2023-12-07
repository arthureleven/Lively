SRC_DIR := ./src
OUT_DIR := ./out

CXX := g++
CXXFLAGS := -O3
LIBS := -lSDL2main -lSDL2 -lSDL2_Image -lavformat -lavcodec -lavutil -mwindows

INCLUDES := -I $(SRC_DIR)

SRCS := main.cpp engine.cpp player.cpp
OBJS := $(patsubst %.cpp,$(OUT_DIR)/%.o,$(SRCS))
DEPS := $(patsubst %,$(SRC_DIR)/%.hpp,engine player)

all: Lively

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDES) $(LIBS)

Lively: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$@ $^ $(INCLUDES) $(LIBS)

run: Lively
	$(OUT_DIR)/Lively

clean:
	del /s *.o