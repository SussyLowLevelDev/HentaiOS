#include <drivers/video/Framebuffer.h>
#include <memory/GDT.h>
#include <memory/MemoryMap.h>
#include <acpi/acpi.h>
#include <util/string.h>


canvas_t canvas = {
    .x = 0,
    .y = 0,
    .draw_color = 0xFFFFFFFF
};


void _start(framebuffer_t lfb, ssfn_font_t* font, meminfo_t meminfo) {
    framebuffer_init(lfb, font);
    load_gdt();
    
    clearScreen(&canvas, 0x00000000);
    kwrite(&canvas, "Hello, World! - Привет мир!\n");
    kwrite(&canvas, "Looking for ACPI memory..\n");

    // ACPI stuff.
    void* acpi_base = fetch_acpi_memory(meminfo);

    if (!(acpi_base)) {
        kwrite(&canvas, "Cannot find ACPI memory :(\n");
        __asm__ __volatile__("cli; hlt");       // Halt CPU.
    } else {
        kwrite(&canvas, "ACPI segment found at address: ");
        kwrite(&canvas, hex2str((uint64_t)acpi_base));
        kwrite(&canvas, "\n");
    }

    while (1) {
        __asm__ __volatile__("hlt");
    }
}
