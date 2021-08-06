VMDIR="VM/img"
OSNAME="404OS"
BUILDDIR="bin"
KERNELDIR="kernel"
#mv bootloader/$BUILDDIR/bootx64.efi VM/img/main.efi
rm "$VMDIR/$OSNAME.img"
dd if=/dev/zero of="$VMDIR/$OSNAME.img" bs=512 count=93750
	mformat -i "$VMDIR/$OSNAME.img" -f 1440 ::
	mmd -i "$VMDIR/$OSNAME.img" ::/EFI
	mmd -i "$VMDIR/$OSNAME.img" ::/EFI/BOOT
	mmd -i "$VMDIR/$OSNAME.img" ::/404OS
	mcopy -i "$VMDIR/$OSNAME.img" "bootloader/$BUILDDIR/bootx64.efi" ::/EFI/BOOT
	mcopy -i "$VMDIR/$OSNAME.img" "$VMDIR/startup.nsh" ::
        mcopy -i "$VMDIR/$OSNAME.img" "$KERNELDIR/$BUILDDIR/kernel.sys" ::404OS/
	#/404OS
for filename in "$KERNELDIR/$BUILDDIR/*"; do
done