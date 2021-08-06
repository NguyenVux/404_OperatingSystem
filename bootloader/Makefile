
CFLAGS =-target x86_64-unknown-windows \
	-ffreestanding \
	-fshort-wchar \
	-mno-red-zone \
	-I../gnu-efi/inc -I../gnu-efi/inc/x86_64 -I../gnu-efi/inc/protocol
LDFLAGS =-target x86_64-unknown-windows \
	-nostdlib \
	-Wl,-entry:efi_main \
	-Wl,-subsystem:efi_application \
	-fuse-ld=lld-link
BUILDDIR = build
FINALDIR = bin
SRCDIR = src
SRC_FILES = $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC_FILES))
bootloader:link clean
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
link:$(OBJ_FILES) 
	$(CC) $(CFLAGS) -c -o $(BUILDDIR)/data.o ../gnu-efi/lib/data.c
	$(CC) $(LDFLAGS) -o $(FINALDIR)/bootx64.efi $^ $(BUILDDIR)/data.o

clean:
	pwsh -command "Get-ChildItem -Path ./$(BUILDDIR)/ -Include *.* -File -Recurse | foreach { $$_.Delete()}"
test:
	$(CC) $(CFLAGS) -c -o $(BUILDDIR)/main.o $(SRCDIR)/main.c
	$(CC) $(LDFLAGS) -o $(FINALDIR)/bootx64.efi $(BUILDDIR)/main.o $(BUILDDIR)/data.o

