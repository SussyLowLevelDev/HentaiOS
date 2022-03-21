#ifndef ACPI_H
#define ACPI_H

#include <memory/MemoryMap.h>
#include <stddef.h>
#include <acpi/tables.h>

void* fetch_acpi_memory(meminfo_t meminfo);

#endif
