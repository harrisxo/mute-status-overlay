# Makefile for Mute Status Overlay TS3 Plugin

# Compiler settings
CC = g++
CFLAGS = -std=c++11 -Wall -O2
INCLUDES = -I. -Ipluginsdk/include -Ipluginsdk/include/teamspeak

# Libraries
LIBS = -lcomctl32 -lgdi32 -luser32 -lkernel32

# Source files
SOURCES = mute_status_overlay.cpp
TARGET = mute_status_overlay.dll

# Default target
all: $(TARGET)

# Compile the plugin
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -shared -o $(TARGET) $(SOURCES) $(LIBS)

# Clean build files
clean:
	del /Q $(TARGET) *.o 2>nul || true

# Install plugin (copy to TS3 plugins directory)
install: $(TARGET)
	@echo Installing plugin...
	@if not exist "%APPDATA%\TS3Client\plugins" mkdir "%APPDATA%\TS3Client\plugins"
	copy $(TARGET) "%APPDATA%\TS3Client\plugins\"
	copy mute_status_overlay.ts3_plugin "%APPDATA%\TS3Client\plugins\"
	@echo Plugin installed successfully!

# Uninstall plugin
uninstall:
	@echo Uninstalling plugin...
	del /Q "%APPDATA%\TS3Client\plugins\$(TARGET)" 2>nul || true
	del /Q "%APPDATA%\TS3Client\plugins\mute_status_overlay.ts3_plugin" 2>nul || true
	@echo Plugin uninstalled successfully!

.PHONY: all clean install uninstall 