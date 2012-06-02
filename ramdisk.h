#ifndef _RAMDISK_H_
#define _RAMDISK_H_

typedef struct file file_t;
typedef struct dir  dir_t;

struct file
{
  u32int addr_start;
  u32int addr_end;

  char dir_name[16];
  char file_name[16]; //15 for the name, 16 = '/0'
};

struct dir
{
  u16int dir_num; //amount of directories inside
  u16int file_num; //amount of files
  
  dir_t *dir_contained;
  file_t *file_contained;
  
  char dir_name[16];
};

//MODULE STRUCT
struct ram_disk_info
{
  u16int dir_num;
  u16int file_num; //First 4 bytes are the amount of files
}__attribute__((packed));

struct file_info
{
  u32int addr_start;
  u32int addr_end;
  char name[16];
}__attribute__((packed));

struct dir_info
{
  u16int dir_contained;
  u16int file_contained;
  char name[16];
  u8int next_block_type;
}__attribute__((packed));
#define FILE 0
#define DIR  1

typedef struct ram_disk_info ram_disk_info_t;
typedef struct file_info     file_info_t;
typedef struct dir_info      dir_info_t;

/*Arrangement of HLEBRAMFS
 *2 bytes containing amount of directories 
 *2 bytes containing amount of files
 *For amount of directories, repeat- 
 *2 byte directories inside
 *2 byte files inside
 *16 byte directory name
 *1 byte is dir or is file 
 *dir=
 *repeat above
 *file=
 *4 byte file start address
 *4 byte file end address
 *16 byte file name
 *next_dir=
 */


#endif
