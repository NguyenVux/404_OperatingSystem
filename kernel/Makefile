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
SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_FILES))
kernel:$(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(FINALDIR)/kernel.sys $^
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	pwsh -command "Get-ChildItem -Path ./$(BUILDDIR)/ -Include *.* -File -Recurse | foreach { $$_.Delete()}"
