/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Fnx/Kernel.h>
#include <Fnx/Memory.h>
#include <Fnx/Process.h>
#include <Fnx/Scheduler.h>
#include <Fnx/Multiboot.h>
#include <Fnx/BootImage.h>
#include <UserProcess.h>
#include <String.h>

Kernel::Kernel()
{
    MultibootModule *mod;
    BootImage *image;
    String str;

    /* Inicia los modulos de inicio. */
    for (Size n = 0; n <  multibootInfo.modsCount; n++) {
        mod = &((MultibootModule *) multibootInfo.modsAddress)[n];

        /* Es una imagen de inicio? */
        if (str.match((char *) mod->string, "*.img.gz")) {
            /* Mapea la imagen de inicio dentro del espacio de direcciones. */
            image = (BootImage *) memory->mapVirtual(mod->modStart);
            memory->mapVirtual(mod->modStart + PAGESIZE);

            /* Verifica si es una imagen de inicio correcta. */
            if (image->magic[0] == BOOTIMAGE_MAGIC0 &&
                image->magic[1] == BOOTIMAGE_MAGIC1 &&
                image->layoutRevision == BOOTIMAGE_REVISION)
            {
                /* Loop BootPrograms. */
                for (Size i = 0; i < image->programsTableCount; i++)
                     loadBootProcess(image, mod->modStart, i);
            }
        }
    }
}

void Kernel::loadBootProcess(BootImage *image, Address imagePAddr, Size index)
{
    Address imageVAddr = (Address) image, args;
    BootProgram *program;
    BootSegment *segment;
    ArchProcess *proc;
    
    /* Puntero hacia el programa y la tabla de segmentos. */
    program = &((BootProgram *) (imageVAddr + image->programsTableOffset))[index];
    segment = &((BootSegment *) (imageVAddr + image->segmentsTableOffset))[program->segmentsOffset];

    /* Crea los procesos. */
    proc = new ArchProcess(program->entry);
    proc->setState(Ready);

    /* Loop program segments. */
    for (Size i = 0; i < program->segmentsCount; i++) {
        /* Mapea los segmentos del programa dentro de la memoria virtual. */
        for (Size j = 0; j < segment[i].size; j += PAGESIZE) {
            memory->mapVirtual(proc,
                        imagePAddr + segment[i].offset + j,
                        segment[i].virtualAddress + j,
                        PAGE_PRESENT | PAGE_USER | PAGE_RW);
        }
    }
    /* Mapea y copia los argumentos del programa. */
    args = memory->allocatePhysical(PAGESIZE);
    memory->mapVirtual(proc, args, ARGV_ADDR, PAGE_PRESENT | PAGE_USER | PAGE_RW);
    strlcpy( (char *) memory->mapVirtual(args), program->path, ARGV_SIZE);
    
    /* Schedule process. */
    scheduler->enqueue(proc);
}
