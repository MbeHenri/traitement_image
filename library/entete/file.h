#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

typedef struct i_file i_file;
struct i_file
{
    char* name;
    char* directory;
    char* format;
};
i_file* info_file(const char* path);
void free_i_file(i_file*);
#endif