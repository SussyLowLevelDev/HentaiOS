@echo -off
mode 80 25

cls
if exist .\efi\boot\HentaiOS.efi then
 .\efi\boot\HentaiOS.efi
 goto END
endif

if exist fs0:\efi\boot\HentaiOS.efi then
 fs0:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs1:\efi\boot\HentaiOS.efi then
 fs1:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs2:\efi\boot\HentaiOS.efi then
 fs2:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs3:\efi\boot\HentaiOS.efi then
 fs3:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs4:\efi\boot\HentaiOS.efi then
 fs4:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs5:\efi\boot\HentaiOS.efi then
 fs5:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs6:\efi\boot\HentaiOS.efi then
 fs6:
 efi\boot\HentaiOS.efi
 goto END
endif

if exist fs7:\efi\boot\HentaiOS.efi then
 fs7:
 efi\boot\HentaiOS.efi
 goto END
endif

 echo "Unable to find bootloader".
 
:END
