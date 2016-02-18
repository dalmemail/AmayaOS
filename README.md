AmayaOS 0.08
Copyright (C) 2009 Niek Linnenbank, 2012 Felipe Cabrera, 2014 AmayaOS Team

## English
### How to use AMAYA-OS
1. Compilation:
 * To compile FNX, enter the folder containing the source code in a terminal and enter the below to compile the OS.
 
   `$ scons`
 * To compile it and make an ISO image type:
 
   `$ scons iso`
 * SCons detects all changes and it ignores all unchanged files, but in some cases you'll need to compile from scratch. If this happens type:
 
   `$ sh ./clean`
2. Test AMAYA:

You can test this operating system with a virtual machine (Using VirtualBox or VMware), an emulator (Examples being QEMU and BOCHS) or you can try running it on physical hardware.

 * To test with QEMU open the folder where you compiled AmayOS in a terminal and enter:

   `$ qemu -usb -cdrom boot/boot.iso`
   
 * Also you can use curses as terminal:

   `$ qemu -curses -usb -cdrom boot/boot.iso`
   
For testing Fnx on a real PC you may burn the boot ISO image in an empty CD/DVD, and reboot. You must set up your boot from CD/DVD device in the BIOS to use AmayOS


*NOTE 1: Using FNX on a physical PC isn't a bright idea, as it is unlikely to fully work.*

*NOTE 2: AMAYA OS v 0.02/0.05 has been tested in many x86 arquitectures with good results.*

*NOTE 3: AmayaOS can't be compiled on x86_64 computers.*

- - -

## Español
### Como usar AMAYA-OS
1. Compilación:
 * Para compilar Fnx, se debe entrar al directorio en que se encuentra el código fuente desde una consola y escribir:
 
  `$ scons`
 * Para compilar y crear una imagen ISO, debes escribir en la consola:
 
   `$ scons iso`
 * SCons detecta todos los cambios e ignora todos los archivos que no han sido alterados, pero en ciertos casos necesitarás compilar desde cero. En estos casos debes escribir:
 
  `$ sh ./clean`
2. Probar AMAYA OS:
Para probar este sistema operativo, puedes hacerlo desde una máquina virtual (VirtualBox y VMWare, por ejemplo), un emulador (QEMU y BOCHS, p.ej.) o en un computador real (No recomendado aún).

 * Para probarlo en QEMU debes entrar a tu consola, entrar a la carpeta principal del código fuente de Fnx y escribir:
 
   `$ qemu -usb -cdrom boot/boot.iso`
   
 Se abrirá una ventana en la que se ejecutará Fnx.

 * También puedes redirigir la salida hacia la biblioteca *curses* mediante:

   `$ qemu -curses -usb -cdrom boot/boot.iso`
   
 Con lo que la salida se redirigirá hacia la consola que estes usando.

Para probar Fnx en una PC real debes quemar la imagen ISO en un CD virgen e insertarlo en tu PC, luego reinicias y se iniciará AMAYA. En caso de no ocurrir esto último, deberás configurar la BIOS para que inicie desde tu lector/grabador de CD/DVD.

*NOTA 1: No es recomendable usar Fnx en una PC real, ya que no ha sido testeado profundamente en una arquitectura real.*

*NOTA 2: La Versión 0.02/0.05 de AMAYA OS ha sido testada en distintos pcs X86 con buenos resultados.*

*NOTA 3: AmayaOS actualmente no puede ser compilado en arquitecturas de 64 bits.*
