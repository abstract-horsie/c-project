# MAKEFILE \
	# Changes to this file are not recommended. \
	# As this file will get overriden if 'c-project edit' is ran.\
	# If you decided to delete the `c-project` file and directory, then feel free to edit.

CFLAGS = -std=c99
BUILD_FILES = src/main.c src/check.c src/create.c src/dir.c src/edit.c src/find.c src/message.c src/option.c src/scan.c src/status.c
EXECUTABLE = bin/c-proj

main: $(BUILD_FILES)
	clang $(CFLAGS) $(BUILD_FILES) -o $(EXECUTABLE)

.PHONY: test clean

clean: bin/name
	rm -f $(EXECUTABLE)

test: bin/name
	./$(EXECUTABLE)
