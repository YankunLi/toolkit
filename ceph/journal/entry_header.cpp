/*
 *
 *
 */

//#include <sys/types.h>
//#include <stddef.h>

typedef long off64_t;

typedef unsigned long long    uint64_t;
typedef unsigned int          uint32_t;

struct entry_header_t {
    uint64_t seq;
    uint32_t crc32;
    uint32_t len;
    uint32_t pre_pad, post_pad;
    uint64_t magic1;
    uint64_t magic2;

    static uint64_t make_magic(uint64_t seq, uint32_t len, uint64_t fsid) {
        return (fsid ^ seq ^ len);
    }

    bool check_magic(off64_t pos, uint64_t fsid) {
        return
            magic1 == (uint64_t) pos &&
            magic2 == (fsid ^ seq ^ len);
    }
} __attribute__((__packed__, aligned(4)));
