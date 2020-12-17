OUT_DIR			= ./output
LINK_TARGET 	= $(OUT_DIR)/solveb.out
SRC_FILES 		= $(shell find *.cpp)
OBJS 			= $(patsubst %.cpp,$(OUT_DIR)/%.o, $(SRC_FILES))
REBUILDABLES	= $(OBJS) $(LINK_TARGET)
CC_FLAGS		= -std=c++17 -Wall -g
CC				= clang++

all: $(LINK_TARGET)
	@echo "compilation success ✅"

# $@ expands to the rule's target, solveb.out.
# $^ expands to the rule's dependencies, in this case the two files
$(LINK_TARGET): $(OBJS)
	$(CC) $(CC_FLAGS) -o $@ $^

$(OUT_DIR)/%.o: %.cpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

clean:
	rm -f $(OUT_DIR)/*
	@echo "clean done ✨"

run:
	./output/solveb.out
