#include <stdio.h>

#include "tokenizer/toml_tokenizer.h"

int main()
{
    toml_reader_t reader = toml_reader_create("res/config.toml");
    toml_tokenizer_t tokenizer = toml_tokenizer_create(reader);
    
    toml_tokenizer_push(tokenizer, toml_token_create_key("var"));
    toml_tokenizer_push(tokenizer, toml_token_create_set());
    toml_tokenizer_push(tokenizer, toml_token_create_numeric("3"));
    toml_tokenizer_push(tokenizer, toml_token_create_boolean("3"));
    toml_tokenizer_push(tokenizer, toml_token_create_string("3"));
    toml_tokenizer_push(tokenizer, toml_token_create_end_of_statement());
    toml_tokenizer_push(tokenizer, toml_token_create_end_of_file());

    for (size_t i = 0; i < 7; i++)
        toml_token_print(toml_tokenizer_next(tokenizer));

    toml_tokenizer_destroy(tokenizer);
    toml_reader_destroy(reader);

    return 0;
}
