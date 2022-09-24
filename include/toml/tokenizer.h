#pragma once

#include "reader.h"
#include "token.h"

typedef struct toml_tokenizer *toml_tokenizer_t;

toml_tokenizer_t toml_tokenizer_create(toml_reader_t reader);
void toml_tokenizer_destroy(toml_tokenizer_t tokenizer);

toml_boolean_t toml_tokenizer_reached_end(toml_tokenizer_t tokenizer);
toml_token_t toml_tokenizer_next(toml_tokenizer_t tokenizer);
toml_token_t toml_tokenizer_peek(toml_tokenizer_t tokenizer, size_t offset);
