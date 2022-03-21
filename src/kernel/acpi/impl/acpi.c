#include <acpi/acpi.h>


void* fetch_acpi_memory(meminfo_t meminfo) {
    uint32_t mmap_entries = mmap_get_entries(meminfo);
    for (int i = 0; i < mmap_entries; ++i) {
        memdesc_t* desc = mmap_iteration_helper(meminfo, i);
        if (desc->type == EFI_ACPI_MEMORY_NVS) {
            return desc;
        }
    }

    return NULL;
}
