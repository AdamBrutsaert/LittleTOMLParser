#include "reader/toml_reader.h"

#include <stdlib.h>
#include <stdio.h>

#include "utils/my_lib.h"

struct toml_reader {
    toml_string_t filename;
    FILE *file;

    size_t line;
    size_t column;

    toml_boolean_t reached_end;
    size_t capacity;
    size_t length;
    size_t index;
    toml_string_t buffer;
};

static toml_boolean_t will_reach_end(toml_reader_t reader, size_t offset)
{
    return reader->length != reader->capacity && reader->index + offset >= reader->length;
}

static void read_some(toml_reader_t reader, size_t offset)
{
    reader->length = offset + fread(reader->buffer + offset, sizeof(char), reader->capacity - offset, reader->file);
    reader->index = 0;
    reader->reached_end = will_reach_end(reader, 0);
}

toml_reader_t toml_reader_create(toml_string_t filename)
{
    toml_reader_t reader = malloc(sizeof(struct toml_reader));

    reader->filename = filename;
    reader->file = fopen(filename, "r");

    reader->line = 1;
    reader->column = 1;

    if (reader->file == nullptr) {
        reader->reached_end = true;
        reader->buffer = nullptr;
        return reader;   
    }

    reader->reached_end = false;
    reader->capacity = 256;
    reader->length = 0;
    reader->index = 0;
    reader->buffer = malloc(reader->capacity * sizeof(char));
    read_some(reader, 0);

    return reader;
}

void toml_reader_destroy(toml_reader_t reader)
{
    if (reader->file) 
        fclose(reader->file);
    free(reader->buffer);
    free(reader);
}

toml_string_t toml_reader_get_filename(toml_reader_t reader)
{
    return reader->filename;
}

size_t toml_reader_get_line(toml_reader_t reader)
{
    return reader->line;
}

size_t toml_reader_get_column(toml_reader_t reader)
{
    return reader->column;
}

toml_boolean_t toml_reader_reached_end(toml_reader_t reader)
{
    return reader->reached_end;
}

static inline void on_new_character(toml_reader_t reader, char c)
{
    if (c == '\n') {
        reader->line++;
        reader->column = 1;
    } else {
        reader->column++;
    }
}

char toml_reader_next(toml_reader_t reader)
{
    if (reader->reached_end)
        return 0;

    char c = reader->buffer[reader->index++];
    reader->reached_end = will_reach_end(reader, 0);

    if (reader->index == reader->length)
        read_some(reader, 0);

    on_new_character(reader, c);

    return c;
}

char toml_reader_peek(toml_reader_t reader, size_t offset)
{
    // return 0 if k >= capacity (we can't peek over the capacity of the buffer)
    if (offset >= reader->capacity)
        return 0;

    // return 0 if we reached end or will reach end on the k-th next character
    if (will_reach_end(reader, offset))
        return 0;
    
    // if k-th next character is beyond the buffer, move characters back and read enough to fulfil
    if (reader->index + offset >= reader->capacity) {
        my_memmove(reader->buffer, &reader->buffer[reader->index], reader->capacity - reader->index);
        read_some(reader, reader->capacity - reader->index);
    }
    
    return reader->buffer[reader->index + offset];
}
