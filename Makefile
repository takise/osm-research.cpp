TARGET_EXEC ?= a.out
 
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
LIB_DIRS ?= ./lib
 
SRCS := $(shell (find . -name *.cpp))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
 
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++11
CXX ?= g++

build: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "Compilation succeeded!"

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
 
# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(BUILD_DIR)/$(SRC_DIRS)
	mkdir -p build/lib/UnionFind
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
 
.PHONY: clean
 
clean:
	$(RM) -r $(BUILD_DIR)
 
-include $(DEPS)
 
extract_graph: $(BUILD_DIR)/$(TARGET_EXEC)
	build/a.out $@ $(CITYNAME)

generate_trip: $(BUILD_DIR)/$(TARGET_EXEC)
	build/a.out $@ $(CITYNAME) $(HOURS) $(NUM_SAMPLES)

run: $(BUILD_DIR)/$(TARGET_EXEC)
	build/a.out $@ $(CITYNAME) $(TAXI_DATA_NAME) $(METHOD)

list:
	@echo "- extract_graph <cityname(tokyo)>"
	@echo "- generate_trip <cityname(tokyo)> <hours[0,24]> <num_samples(5000)>"
