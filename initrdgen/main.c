#include <stdio.h>
#include <string.h>

/* File format
 * 1. 4 bytes for number of files
 *    2. For number of files
 * 	-4 bytes = size
 * 	-12 bytes = name
 *      -Byte dump of file
 */

int main(int argc, char* argv[])
{
  if(argc == 1)
  {
    printf("No files specified.\n");
    return 0;
  }
  FILE* initrd = fopen("initrd", "w+b");//initrd file
  int file_am = argc - 1;
  fwrite(&file_am, sizeof(int), 1, initrd); //write number of files
  int i;
  FILE* info;
  for(i = 1; i < argc; i++)
  {
    info = fopen(argv[i], "rb");
    fseek(info, 0, SEEK_END);
    int sz = ftell(info);
    fseek(info, 0, SEEK_SET);
    fwrite(&sz, sizeof(int), 1, initrd);
    char buff[12];
    strcpy(buff, argv[i]);
    buff[11] = '\0';
    fwrite(buff, 1, 12, initrd);
    int x;
    for(x = 0; x < sz; x++)
    {
      char byte_c;
      fread(&byte_c, sizeof(char), 1, info);
      fwrite(&byte_c, sizeof(char), 1, initrd);
    }
    fclose(info);
  }
  fclose(initrd);
  return 0;
}