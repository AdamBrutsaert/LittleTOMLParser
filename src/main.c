#include <stdio.h>

#include "tokenizer/toml_tokenizer.h"

int main()
{
    toml_reader_t reader = toml_reader_create("res/config.toml");
    toml_tokenizer_t tokenizer = toml_tokenizer_create(reader);
    
    toml_token_t token = toml_tokenizer_next(tokenizer);
    while (token.type != TOML_TOKEN_TYPE_END_OF_FILE) {
        toml_token_print(token);
        toml_token_destroy(token);
        token = toml_tokenizer_next(tokenizer);
    }
    toml_token_print(token);
    toml_token_destroy(token);

    toml_tokenizer_destroy(tokenizer);
    toml_reader_destroy(reader);

    return 0;
}
