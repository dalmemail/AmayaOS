AmayaOS 0.09
Copyright (C) 2009 Niek Linnenbank, 2012 Felipe Cabrera, 2014 AmayaOS Team

## English
### How to use AmayaOS
1. Compilation:
 * To compile AmayaOS, enter the folder containing the source code in a terminal and enter the below to compile the OS.
 
   `$ scons`
 * To compile it and make an ISO image type:
 
   `$ scons iso`
 * SCons detects all changes and it ignores all unchanged files, but in some cases you'll need to compile from scratch. If this happens type:
 
   `$ sh ./clean`
2. Test AmayaOS:

You can test this operating system with a virtual machine (Using VirtualBox or VMware), an emulator (Examples being QEMU and BOCHS) or you can try running it on physical hardware.

 * To test with QEMU open the folder where you compiled AmayaOS in a terminal and enter:

   `$ qemu -usb -cdrom boot/boot.iso`
   
 * Also you can use curses as terminal:

   `$ qemu -curses -usb -cdrom boot/boot.iso`
   
For testing AmayaOS on a real PC you may burn the boot ISO image in an empty CD/DVD, and reboot. You must set up your boot from CD/DVD device in the BIOS to use AmayaOS

*NOTE: AmayaOS can't be compiled on x86_64 computers.*

- - -

## Español
### Como usar AmayaOS
1. Compilación:
 * Para compilar AmayaOS, se debe entrar al directorio en que se encuentra el código fuente desde una consola y escribir:
 
  `$ scons`
 * Para compilar y crear una imagen ISO, debes escribir en la consola:
 
   `$ scons iso`
 * SCons detecta todos los cambios e ignora todos los archivos que no han sido alterados, pero en ciertos casos necesitarás compilar desde cero. En estos casos debes escribir:
 
  `$ sh ./clean`
  
2. Probar AmayaOS:
Para probar este sistema operativo, puedes hacerlo desde una máquina virtual (VirtualBox y VMWare, por ejemplo), un emulador (QEMU y BOCHS, p.ej.) o en un computador real.

 * Para probarlo en QEMU debes entrar a tu consola, entrar a la carpeta principal del código fuente de AmayaOS y escribir:
 
   `$ qemu -usb -cdrom boot/boot.iso`
   
 Se abrirá una ventana en la que se ejecutará AmayaOS.

 * También puedes redirigir la salida hacia la biblioteca *curses* mediante:

   `$ qemu -curses -usb -cdrom boot/boot.iso`
   
 Con lo que la salida se redirigirá hacia la consola que estes usando.

Para probar AmayaOS en una PC real debes quemar la imagen ISO en un CD virgen e insertarlo en tu PC, luego reinicias y se iniciará AmayaOS. En caso de no ocurrir esto último, deberás configurar la BIOS para que inicie desde tu lector/grabador de CD/DVD.

*NOTA: AmayaOS actualmente no puede ser compilado en arquitecturas de 64 bits.*
