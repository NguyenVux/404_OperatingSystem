CC = clang
CPP = clang++
WSL = C:\Windows\System32\wsl.exe
MAKE = mingw32-make
GLOBAL = CC=$(CC) CPP=$(CPP)
.PHONY: bootloader
bootloader:
	$(MAKE) -C bootloader bootloader $(GLOBAL)
test: 
	pwsh -c "wsl ./buildimg.sh"