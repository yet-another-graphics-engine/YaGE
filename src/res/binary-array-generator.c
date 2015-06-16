#include <stdio.h>
#include <string.h>
#define maxsize 15
unsigned char buffer[maxsize];
char* output_path = "convert.h";
char var_name[200] = "binary_";
void convert_var_name()
{
  int str_len = strlen(var_name);
  int i;
  for(i = str_len - 1;i > 0; i--)
  {
    switch(var_name[i])
    {
      case '+':
      case '-':
      case '*':
      case '/':
      case '\\':
      case '.':
      case ' ':
        var_name[i] = '_';
        break;
    }
  }
}

char* get_file_name(char* file_path)
{
  int len = strlen(file_path);
  int i;
  for(i = len - 1; i >= 0; i--)
  {
    if(file_path[i] == '/' || file_path[i] == '\\')
      break;
  }
  return file_path + i + 1;
}

int main(int argc,char** argv)
{
  if(argc != 2 && argc != 3)
  {
    printf("Usage:  binary-array-generator <input file> [output file]\n");
    return 1;
  }
  char* file_name = get_file_name(argv[1]);
  FILE* input_file = fopen(argv[1], "rb");
  if(input_file == NULL)
  {
    printf("Cannot open the file %s\n",file_name);
    return 1;
  }
  strcat(var_name, file_name);
  convert_var_name();

  if(argc == 3)
    output_path = argv[2];
  FILE* output_file = fopen(output_path, "w");
  if(output_file == NULL)
  {
    printf("Cannot write the output file.\n");
    return 1;
  }
  fprintf(output_file, "/*Generate automatically.DO NOT MODIFY*/\n");
  fprintf(output_file, "#pragma once\n");
  fprintf(output_file, "static const unsigned char %s[] = {\n", var_name);
  int i;
  int count;
  int start_flag = 1;
  while(1)
  {
    memset(buffer, 0, sizeof(buffer));
    count = fread((void*)buffer, 1, maxsize, input_file);
    //printf("count = %d\n",count);
    if(count != maxsize)
      break;

    if(!start_flag)
      fprintf(output_file, ",\n");
    else
      start_flag = 0;
    fprintf(output_file, "\t");
    for(i = 0;i < maxsize - 1; i++)
      fprintf(output_file, "0x%02hX, ", buffer[i]);
    fprintf(output_file, "0x%02hX", buffer[i]);
  }

  if(count > 0)
  {
    fprintf(output_file, ",\n\t0x%02hX", buffer[0]);
    for(i = 1; i < count; i++)
      fprintf(output_file, ", 0x%02hX", buffer[i]);
  }
  fprintf(output_file, "};\n");
  fclose(input_file);
  fclose(output_file);
  printf("Done.\n");
  return 0;
}
