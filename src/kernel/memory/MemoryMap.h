#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <stdint.h>

typedef struct {
    uint32_t type;
    uint32_t pad;
    void* phys;
    void* virtualAddr;
    uint64_t nPages;
    uint64_t attr;
} memdesc_t;


typedef struct {
    memdesc_t* mMap;
    uint64_t map_size; 
    uint64_t map_key;
    uint64_t desc_size;
} meminfo_t;


typedef enum {
    EFI_RESERVED_MEMORY_TYPE,
    EFI_LOADER_CODE,
    EFI_LOADER_DATA,
    EFI_BOOT_SERVICES_CODE,
    EFI_BOOT_SERVICES_DATA,
    EFI_RUNTIME_SERVIES_CODE,
    EFI_RUNTIME_SERVICES_DATA,
    EFI_CONVENTIONAL_MEMORY,
    EFI_UNUSABLE_MEMORY,
    EFI_ACPI_RECLAIM_MEMORY,
    EFI_ACPI_MEMORY_NVS,
    EFI_MEMORY_MAPPED_IO,
    EFI_MEMORY_MAPPED_IO_PORT_SPACE,
    EFI_PAL_CODE,
} efi_segment_types;


uint32_t mmap_get_entries(meminfo_t meminfo);
memdesc_t* mmap_iteration_helper(meminfo_t meminfo, int32_t i);


#endif
