$OSNAME="404OS"
$BUILDDIR="$pwd/VM/IMG"
$OVMFDIR="$pwd/VM/OVMFbin"
qemu-system-x86_64 -d cpu_reset -monitor stdio -drive file="$BUILDDIR/$OSNAME.img" -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$OVMFDIR/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$OVMFDIR/OVMF_VARS-pure-efi.fd" -net none

#$BUILDDIR/$OSNAME.img
#$(CC) $(LDFLAGS) -o $(FINALDIR)/bootx64.sys $(BUILDDIR)/main.o