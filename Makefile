TARGET_EXEC ?= SPLIT

BUILD_DIR ?= build
GEN_DIR ?= gen
SRC_DIRS := src $(GEN_DIR)

SRCS := $(shell find -E $(SRC_DIRS) -regex '.*/[a-zA-Z0-9._]+\.[pc]{2,3}')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#INC_DIRS := $(shell find . -type d -name include)
INC_DIRS := include $(GEN_DIR)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX=clang++
LDFLAGS=-L/usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics -lprotobuf -stdlib=libc++ -framework sfeMovie
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -std=c++11 -I/usr/local/include

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET_EXEC) $(CXXFLAGS) $(LDFLAGS)

run: $(TARGET_EXEC)
	@./$(TARGET_EXEC)

fs: $(TARGET_EXEC)
	@./$(TARGET_EXEC) --fullscreen

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cc.o: %.cc
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean genclean docbrowse

docs: docbuild docbrowse

docbuild: Doxyfile
	@doxygen

docbrowse:
	@open build/docs/index.html

PB_SRCS := $(shell find -E pb -regex '.*/[a-zA-Z0-9_]+\.proto')
PB_H := $(PB_SRCS:%.proto=$(GEN_DIR)/%.pb.h)
PB_PY := $(PB_SRCS:%.proto=$(GEN_DIR)/%_pb2.py)
PB_DEPS := $(PB_H:.pb.h=.d)

$(GEN_DIR)/%.pb.h: %.proto
	@$(MKDIR_P) $(dir $@)
	protoc $< --cpp_out=gen --python_out=gen --dependency_out=gen/$<.d

$(GEN_DIR)/%_pb2.py: %.pb.h

-include $(PB_DEPS)

protobuf: $(PB_H)

### PYTHON

editor: $(PB_PY)
	@PYTHONPATH=$(GEN_DIR) python3 tools/editor.py $(ARG)

### CLEANERS

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(TARGET_EXEC)

cleangen: genclean
genclean:
	$(RM) -r $(GEN_DIR)
	$(MKDIR_P) $(GEN_DIR)

cleanall: clean cleangen

-include $(DEPS)

MKDIR_P ?= mkdir -p
