CXX := g++
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++11
TARGET ?= tradingEngine
MKDIR_P ?= mkdir -p

BUILD_DIR ?= ./build
BIN_DIR ?= ./bin
SRC_DIRS ?= ./src
INC_DIRS := ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)


$(BIN_DIR)/$(TARGET): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)



$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

