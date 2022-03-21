#include <memory/MemoryMap.h>


uint32_t mmap_get_entries(meminfo_t meminfo) {
    return meminfo.map_size / meminfo.desc_size;
}


memdesc_t* mmap_iteration_helper(meminfo_t meminfo, int32_t i) {
    return (memdesc_t*)((uint64_t)(meminfo.mMap) + (i * meminfo.desc_size));
}
