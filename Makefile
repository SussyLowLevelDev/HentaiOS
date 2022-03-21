IMGNAME = HentaiOS

all:
	cd src/bootloader; make; mv $(IMGNAME).efi ../../; cd ../../
	cd src/kernel/; bash buildall.sh
	rm src/kernel/*.d src/kernel/*.o
	mv src/kernel/kernel.elf src/bootloader/root
	dd if=/dev/zero of=$(IMGNAME).img bs=512 count=93750
	mformat -i $(IMGNAME).img
	mmd -i $(IMGNAME).img ::/EFI
	mmd -i $(IMGNAME).img ::/EFI/BOOT
	mcopy -i $(IMGNAME).img $(IMGNAME).efi ::/EFI/BOOT
	mcopy -i $(IMGNAME).img src/bootloader/root/startup.nsh ::
	mcopy -i $(IMGNAME).img src/bootloader/root/kernel.elf ::
	mcopy -i $(IMGNAME).img src/bootloader/root/me.png ::
	mcopy -i $(IMGNAME).img src/bootloader/root/font.sfn ::
	rm $(IMGNAME).efi
	rm src/bootloader/*.o
	cd src/kernel; bash clean.sh

run:
	qemu-system-x86_64 -drive file=$(IMGNAME).img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="OVMFBin//OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="OVMFBin/OVMF_VARS-pure-efi.fd" -net none -monitor stdio -d int -no-reboot -D logfile.txt -M smm=off

fs:
	qemu-system-x86_64 -drive file=$(IMGNAME).img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="OVMFBin//OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="OVMFBin/OVMF_VARS-pure-efi.fd" -net none -monitor stdio -d int -no-reboot -D logfile.txt -M smm=off -full-screen
