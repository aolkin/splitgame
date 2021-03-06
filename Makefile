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

MKDIR_P ?= mkdir -p

CXX=clang++
LDFLAGS=-L/usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics -lprotobuf -stdlib=libc++
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -std=c++14 -I/usr/local/include

build: setdebug setmovie $(TARGET_EXEC)

all: protobuf build docbuild

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET_EXEC) $(CXXFLAGS) $(LDFLAGS)

nodebug: setmovie $(TARGET_EXEC)

cleanmovie:
	$(RM) $(BUILD_DIR)/src/extra/movie.cpp.o
	$(RM) $(BUILD_DIR)/src/main.cpp.o

setdebug:
	$(eval CPPFLAGS += -DDEBUG_BUILD)

setnomovie: cleanmovie
	$(eval CPPFLAGS += -DNO_SFEMOVIE)

setmovie:
	$(eval LDFLAGS += -framework sfeMovie)

nomovie: setnomovie setdebug $(TARGET_EXEC)

run: build
	@./$(TARGET_EXEC)

fs: build
	@./$(TARGET_EXEC) --fullscreen

-include $(DEPS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cc.o: %.cc
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: genclean docbrowse setmovie cleanexe cleanmovie setdebug setmovie

docs: docbuild docbrowse

alldocs: alldocbuild alldocbrowse

alldocbuild: Doxyfile
	@(cat Doxyfile; echo "HTML_OUTPUT = alldocs") | doxygen -

docbuild: Doxyfile
	@(cat Doxyfile; echo "INPUT = include") | doxygen -

alldocbrowse:
	@open build/alldocs/index.html

docbrowse:
	@open build/docs/index.html

### Protocol buffers

PB_SRCS := $(shell find -E pb -regex '.*/[a-zA-Z0-9_]+\.proto')
PB_H := $(PB_SRCS:%.proto=$(GEN_DIR)/%.pb.h)
PB_PY := $(PB_SRCS:%.proto=$(GEN_DIR)/%_pb2.py)
PB_DEPS := $(PB_H:.pb.h=.d)

$(GEN_DIR)/%.pb.h: %.proto
	@$(MKDIR_P) $(dir $@)
	protoc $< --cpp_out=$(GEN_DIR) --python_out=$(GEN_DIR) --dependency_out=gen/$<.d

$(GEN_DIR)/%_pb2.py: %.pb.h

-include $(PB_DEPS)

protobuf: $(PB_H)

### PYTHON

editor: protobuf
	@PYTHONPATH=$(GEN_DIR) python3 tools/editor.py $(ARG)

ve: protobuf
	@PYTHONPATH=$(GEN_DIR) FLASK_DEBUG=1 FLASK_APP=tools/visual/ve.py flask run

### CLEANERS

clean: cleanexe
	$(RM) -r $(BUILD_DIR)

cleanexe:
	$(RM) $(TARGET_EXEC)

cleangen: genclean
genclean:
	$(RM) -r $(GEN_DIR)
	$(MKDIR_P) $(GEN_DIR)
	touch $(GEN_DIR)/.gitkeep

cleanall: clean cleangen

lines:
	@wc -l include/* include/*/* src/* src/*/* tools/* tools/*/* pb/* 2>/dev/null; true
