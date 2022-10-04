#include "toml/tokenizer.h"

void toml_tokenizer_on_lbrace(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer)
{
    size_t line = toml_file_reader_get_line(file_reader);
    size_t column = toml_file_reader_get_column(file_reader);

    toml_tokenizer_push(tokenizer, toml_token_create_lbrace(line, column));
    toml_file_reader_next(file_reader);
}
