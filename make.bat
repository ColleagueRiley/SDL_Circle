@echo "setting vars"
SET LIBRARIES=-lSDL2 -lSDL2_mixer
SET NAME=example.exe
SET BUILD=build
SET FILES=example.cpp

@echo "Creating file"
g++ %FILES% %LIBRARIES% -o %BUILD%\%NAME%