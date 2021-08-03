
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

bootloader:
	$(CC) $(CFLAGS) -c -o $(BUILDDIR)/main.o $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c -o $(BUILDDIR)/data.o ../gnu-efi/lib/data.c
	$(CC) $(LDFLAGS) -o $(FINALDIR)/bootx64.efi $(BUILDDIR)/main.o $(BUILDDIR)/data.o

