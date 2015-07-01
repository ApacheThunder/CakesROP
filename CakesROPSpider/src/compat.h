#ifndef __appcompat_h__
#define __appcompat_h__

#include <stdint.h>
#include "types.h"

struct file {
	s32 s;
	u32 pos;
	u32 size;
	u32 unk[5];
};

#define FILE_R 0x01
#define FILE_W 0x06

typedef struct compat_app_s
{
	int (*memcpy)(void *dst, const void *src, unsigned int len);
	int (*GX_SetTextureCopy)(const void *input_buffer, void *output_buffer, unsigned int size, int in_x, int in_y, int out_x, int out_y, int flags);
	int (*GSPGPU_FlushDataCache)(void *addr, unsigned int len);
	int (*svcSleepThread)(unsigned long long nanoseconds);
	int (*svcControlMemory)(void **outaddr, unsigned int addr0, unsigned int addr1, unsigned int size, int operation, int permissions);
	Result (*srvGetServiceHandle)(Handle* out, const char* name, unsigned int len);

	int (*IFile_Open)(struct file *f, const short *path, int flags);
	int (*IFile_Read)(struct file *f, unsigned int *read, void *buffer, unsigned int size);
	int (*IFile_Write)(struct file *f, unsigned int *written, void *src, unsigned int len, unsigned int flush);

	Handle* srv_handle;
} compat_app_s;

typedef struct compat_s
{
	// App specific
	compat_app_s app;

	// Firm specific
	uint32_t create_thread_patch;
	uint32_t svc_patch;
	uint32_t firmver;
	uint32_t patch_sel;
} compat_s;

void init_compat();

extern compat_s compat;

#endif