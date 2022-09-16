#pragma once

#include "reader/toml_reader.h"
#include "toml_token.h"

typedef struct toml_tokenizer *toml_tokenizer_t;

toml_tokenizer_t toml_tokenizer_create(toml_reader_t reader);
void toml_tokenizer_destroy(toml_tokenizer_t tokenizer);

void toml_tokenizer_push(toml_tokenizer_t tokenizer, toml_token_t token);
toml_token_t toml_tokenizer_next(toml_tokenizer_t tokenizer);
