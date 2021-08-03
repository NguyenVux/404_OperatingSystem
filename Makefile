CC = clang
CPP = clang++
WSL = C:\Windows\System32\wsl.exe
MAKE = mingw32-make
GLOBAL = CC=$(CC) CPP=$(CPP)
.PHONY: bootloader kernel
bootloader:
	$(MAKE) -C bootloader bootloader $(GLOBAL)
kernel:
	$(MAKE) -C kernel kernel $(GLOBAL)
test: 
	pwsh -c "wsl ./buildimg.sh"