CC=clang++
LD=clang
CFLAGS =-target x86_64-unknown-windows \
	-ffreestanding \
	-fshort-wchar \
	-mno-red-zone \
	-I../gnu-efi/inc -I../gnu-efi/inc/x86_64 -I../gnu-efi/inc/protocol
LDFLAGS =-target x86_64-unknown-windows \
	-nostdlib \
	-Wl,-entry:_start \
	-Wl,-subsystem:efi_application \
	-fuse-ld=lld-link

	
BUILDDIR = build
FINALDIR = bin
SRCDIR = src
# SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
# SUBSRC_FILES = $(wildcard $(SRCDIR)/**/*.cpp)
# SRC = $(SRC_FILES) $(SUBSRC_FILES)
# OBJ_FILES :=  $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_FILES)) $(patsubst %.cpp,$(BUILDDIR)/%.o,$(notdir $(SUBSRC_FILES)))
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(wildcard $(SRCDIR)/*.cpp)          
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))
OBJST = $(patsubst $(BUILDDIR)/%/%, 1, $(OBJS))
kernel:$(OBJS)
	$(CC) $(LDFLAGS) -o $(FINALDIR)/kernel.sys $^
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	pwsh -command "Get-ChildItem -Path ./$(BUILDDIR)/ -Include *.* -File -Recurse | foreach { $$_.Delete()}"

test: 
	@echo $(OBJS)