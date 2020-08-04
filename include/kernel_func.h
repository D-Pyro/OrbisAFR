#include "ps4.h"
#include "sparse.h"
#include "freebsd.h"

typedef uintptr_t vm_offset_t;
typedef void* vm_map_t;
typedef char *caddr_t;

// 672
#define	KERN_XFAST_SYSCALL 0x1C0
#define KERN_PROCESS_ASLR 0x003CECE1
#define KERN_PRISON_0 0x0113E518
#define KERN_ROOTVNODE 0x02300320
//#define KERN_PRIV_CHECK 0x14A3990
//#define KERN_PRIV_CHECK_CRED 0x2300B88
#define KERN_ALLOW_SYSTEM_LEVEL_DEBUGGING 0x00233BD0
#define KERN_COPYOUT 0x003C16B0
#define KERN_COPYIN 0x003C17A0
#define KERN_ALLPROC 0x022BBE80
#define KERN_PRINTF 0x00123280
#define KERN_PROC_RWMEM 0x0010EE10
#define KERN_CREATE_THREAD 0x004A6FB0
#define KERN_KILLPROC 0x0002DC80

#define	KERN_KMEM_ALLOC 0x00250730
#define	KERN_KMEM_FREE 0x00250900
#define KERN_KERNEL_MAP 0x0220DFC0

#define KERN_VMSPACE_ACQUIRE_REF 0x0044CB90
#define KERN_VM_MAP_LOCK_READ 0x0044CD40
#define KERN_VM_MAP_UNLOCK_READ 0x0044CD90
#define	KERN_VMSPACE_ALLOC 0x0044C710
#define	KERN_VMSPACE_FREE 0x0044C9C0
#define KERN_VM_MAP_LOOKUP_ENTRY 0x0044D330
#define KERN_VM_MAP_FINDSPACE 0x0044FE60
#define KERN_VM_MAP_INSERT 0x0044DEF0
#define KERN_VM_MAP_UNLOCK 0x0044CC60
#define KERN_VM_MAP_LOCK 0x0044CBF0
#define KERN_VM_MAP_DELETE 0x0044F8A0

#define KERN_M_TEMP 0x01540EB0
#define KERN_FREE 0x0000D9A0
#define KERN_MALLOC 0x0000D7A0
#define KERN_STRCPY 0x2390C0
#define KERN_STRCMP 0x00341810
#define KERN_STRNCMP 0x0039B6E0
#define KERN_STRLEN 0x002433E0
#define KERN_MEMCPY 0x003C15B0
#define KERN_MEMSET 0x001687D0


#define KERN_SYS_MMAP 0x000AB1A0
#define KERN_SYS_OPEN 0x49E970
#define KERN_SYS_DYNLIB_LOAD_PRX 0x0049E990

#define KERN_SYSENTS 0x0111E000

#define X86_CR0_WP (1 << 16)

typedef struct {
	char name[32];
	uint64_t start;
	uint64_t stop;
	int protection;
} Map;

struct kern_uap {
	uint64_t syscall;
	void* uap;
};

struct hook_data {
	void* sys_open_orig;
	char data_path[100];
	char cusa[5];
	char print_debug1[100];
	char print_debug2[100];
};

struct syscall_open {
	const char *path;
	int flags;
	int mode;
}  __attribute__((packed));

static inline __attribute__((always_inline)) uint64_t readMsr(uint32_t __register) {
	uint32_t __edx, __eax;

	__asm__ volatile (
	    "rdmsr"
	    : "=d"(__edx),
	    "=a"(__eax)
	    : "c"(__register)
	);

	return (((uint64_t)__edx) << 32) | (uint64_t)__eax;
}

static inline __attribute__((always_inline)) uint64_t readCr0(void) {
	uint64_t cr0;
	
	__asm__ __volatile__ (
		"movq %0, %%cr0"
		: "=r" (cr0)
		: : "memory"
 	);
	
	return cr0;
}

static inline __attribute__((always_inline)) void writeCr0(uint64_t cr0) {
	__asm__ __volatile__ (
		"movq %%cr0, %0"
		: : "r" (cr0)
		: "memory"
	);
}

uint8_t* get_kptr();
int jailbreak(struct thread *td);
