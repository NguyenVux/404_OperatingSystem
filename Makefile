CC = clang
CPP = clang++
WSL = C:\Windows\System32\wsl.exe
MAKE = make
GLOBAL = CC=$(CC) CPP=$(CPP)
.PHONY: bootloader kernel
bootloader:
	$(MAKE) -C bootloader bootloader $(GLOBAL)
kernel:
	$(MAKE) -C kernel kernel $(GLOBAL)
buildimg: 
	pwsh -c "wsl ./buildimg.sh"
run:
	pwsh -f run2.ps1
clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C bootloader clean
all: bootloader kernel buildimg run
