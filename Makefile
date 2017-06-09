TARGET_EXEC ?= SPLIT

BUILD_DIR ?= build
SRC_DIRS ?= engine

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX=clang++
LDFLAGS=-L/usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics -stdlib=libc++
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -std=c++11 -I/usr/local/include

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
