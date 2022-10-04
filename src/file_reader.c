#include "toml/file_reader.h"

#include <stdlib.h>
#include <stdio.h>

#include "toml/memory.h"

struct toml_file_reader {
    char const *filename;
    FILE *file;

    size_t line;
    size_t column;
    toml_boolean_t end;

    size_t capacity;
    size_t length;
    size_t index;
    char *buffer;
};

static toml_boolean_t will_reach_end(toml_file_reader_t *file_reader, size_t n)
{
    toml_boolean_t last_buffer = file_reader->length != file_reader->capacity;
    toml_boolean_t last_character = file_reader->index + n >= file_reader->length;

    return last_buffer && last_character;
}

static void read(toml_file_reader_t *file_reader)
{
    if (file_reader->end)
        return;

    FILE *file = file_reader->file;

    size_t index = file_reader->index;
    size_t capacity = file_reader->capacity;
    size_t count = (index != 0) * (capacity - index); 

    char *buffer = file_reader->buffer;
    char *buffer_pos = &file_reader->buffer[file_reader->index];

    toml_memmove(buffer, buffer_pos, count);
    
    file_reader->length = count + fread(buffer + count, sizeof(char), capacity - count, file);
    file_reader->index = 0;
    file_reader->end = will_reach_end(file_reader, 0);
}

toml_file_reader_t *toml_file_reader_create(char const *filename, size_t capacity)
{
    toml_file_reader_t *file_reader = malloc(sizeof(toml_file_reader_t));

    file_reader->filename = filename;
    file_reader->file = fopen(filename, "r");

    file_reader->line = 1;
    file_reader->column = 1;
    file_reader->end = file_reader->file == nullptr;

    file_reader->capacity = capacity;
    file_reader->length = 0;
    file_reader->index = 0;
    file_reader->buffer = malloc(capacity * sizeof(char));

    read(file_reader);

    return file_reader;
}

void toml_file_reader_destroy(toml_file_reader_t *file_reader)
{
    if (file_reader->file != nullptr)
        fclose(file_reader->file);
    free(file_reader->buffer);
    free(file_reader);
}

char const *toml_file_reader_get_filename(toml_file_reader_t *file_reader)
{
    return file_reader->filename;
}

size_t toml_file_reader_get_line(toml_file_reader_t *file_reader)
{
    return file_reader->line;
}

size_t toml_file_reader_get_column(toml_file_reader_t *file_reader)
{
    return file_reader->column;
}

char toml_file_reader_next(toml_file_reader_t *file_reader)
{
    if (file_reader->end)
        return 0;

    char c = file_reader->buffer[file_reader->index];
    file_reader->index++;
    file_reader->end = will_reach_end(file_reader, 0);

    if (c == '\n') {
        file_reader->line++;
        file_reader->column = 1;
    } else {
        file_reader->column++;
    }

    if (file_reader->index == file_reader->length)
        read(file_reader);

    return c;
}

char toml_file_reader_peek(toml_file_reader_t *file_reader, size_t n)
{
    if (n >= file_reader->capacity || will_reach_end(file_reader, n))
        return 0;
    
    if (file_reader->index + n >= file_reader->capacity)
        read(file_reader);

    return file_reader->buffer[file_reader->index + n];
}

toml_boolean_t toml_file_reader_end(toml_file_reader_t *file_reader)
{
    return file_reader->end;
}
