SHELL := pwsh -NoProfile
CC=clang++
LD=clang
ASM = nasm
ASMFLAGS =
INCLUDE_DIR = include
CFLAGS =-target x86_64-unknown-windows \
	-ffreestanding \
	-fshort-wchar \
	-mno-red-zone \
	-I./include
LDFLAGS =-target x86_64-unknown-windows \
	-nostdlib \
	-Wl,-entry:_start \
	-Wl,-subsystem:efi_application \
	-fuse-ld=lld-link \
	-WL,-T\
	-WL,-Bsymbolic\

	
BUILDDIR = build
FINALDIR = bin
SRCDIR = src
# SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
# SUBSRC_FILES = $(wildcard $(SRCDIR)/**/*.cpp)
# SRC = $(SRC_FILES) $(SUBSRC_FILES)
# OBJ_FILES :=  $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_FILES)) $(patsubst %.cpp,$(BUILDDIR)/%.o,$(notdir $(SUBSRC_FILES)))
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))


SRC_CPP = $(call rwildcard,$(SRCDIR),*.cpp)
SRC_ASM = $(call rwildcard,$(SRCDIR),*.asm) $(call rwildcard,$(SRCDIR),*.s)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC_CPP))\
	$(patsubst $(SRCDIR)/%.asm, $(BUILDDIR)/%_asm.o, $(SRC_ASM))\
	#$(patsubst $(SRCDIR)/%.s, $(BUILDDIR)/%_s.o, $(SRC_ASM))
_kernel:$(OBJS)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo !==== COMPILING $^
	@pwsh -noprofile -c "md -Force $(@D)| Out-Null"
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo.
	@echo.
$(BUILDDIR)/%_asm.o: $(SRCDIR)/%.asm	
	@echo !==== COMPILING $^
	$(ASM) $(ASMFLAGS) $^ -f win64  -o $@
	@echo.
	@echo.
$(BUILDDIR)/%_s.o: $(SRCDIR)/%.s	
	@echo !==== COMPILING $^
	$(ASM) $(ASMFLAGS) $^ -f win64  -o $@
	@echo.
	@echo.

_kernel_asm:
	@echo $(OBJS)

link:
	$(CC) $(LDFLAGS) -o $(FINALDIR)/kernel.sys $(OBJS)
clean:
	pwsh -command "Get-ChildItem -Path ./$(BUILDDIR)/ -Include * -Recurse | Remove-Item -Verbose -Recurse -Force -Confirm:$$false  "
buildimg: 
	cd .. && pwsh -c "wsl ./buildimg.sh"
run:
	cd .. && pwsh -f ./run2.ps1
all: kernel buildimg run
kernel: _kernel link