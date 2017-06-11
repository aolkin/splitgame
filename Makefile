TARGET_EXEC ?= SPLIT

BUILD_DIR ?= build
SRC_DIRS ?= src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#INC_DIRS := $(shell find . -type d -name include)
INC_DIRS ?= include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX=clang++
LDFLAGS=-L/usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics -stdlib=libc++ -framework sfeMovie
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -std=c++11 -I/usr/local/include

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET_EXEC) $(CXXFLAGS) $(LDFLAGS)

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

docs: Doxyfile
	doxygen

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p
