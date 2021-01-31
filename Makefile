LIBRARIES = -lSDL2 -lSDL2_mixer 

create: 
	@echo "Creating file and make directories"; \
	if [ -d "$(BUILD)" ]; then \
		echo ""; \
    else \
        mkdir build; \
		cd build; \
		mkdir lib; \
		mkdir include; \
		cd ..; \
	fi
	
	gcc -shared source/SDL_circle.c -o build/lib/libSDL_circle.so -fPIC

	cp SDL_circle.h build/include