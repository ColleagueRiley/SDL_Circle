LIBRARIES = -lSDL2 -lSDL2_mixer 
NAME = example.out
FILES = example.cpp
BUILD = build
#To change the output to, .exe, .AppImage or to .output when you're not on the right os change the var
OS = $(shell uname)
#Windows_MT - for windows, Linux - for Linux, Anything else - .output
ifeq ($(OS), Linux)
	NAME = SDL_Thing.AppImage
endif
ifeq ($(OS), Windows_MT)
	NAME = SDL_Thing.exe
endif


create: 
	@echo "Creating file and make directories"; \
	if [ -d "$(BUILD)" ]; then \
		echo ""; \
    else \
        mkdir build; \
	fi
	g++ $(FILES) $(LIBRARIES) -o $(BUILD)/$(NAME) 