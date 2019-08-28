#pragma once

typedef struct loader_file_data loader_file_data_t;

struct loader_file_data
{
    size_t size;
    unsigned char* content;
};

loader_file_data_t loader_load_filepath(char const* path);
void loader_unload(loader_file_data_t file_data);
