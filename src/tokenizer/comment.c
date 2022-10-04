#include "toml/tokenizer.h"

void toml_tokenizer_on_comment(toml_file_reader_t *file_reader)
{
    while (!toml_file_reader_end(file_reader)) {
        char c = toml_file_reader_peek(file_reader, 0);
        if (c == '\n')
            break;
        toml_file_reader_next(file_reader);
    }
}
