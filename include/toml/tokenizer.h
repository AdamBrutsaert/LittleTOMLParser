#pragma once

#include "file_reader.h"
#include "token.h"

typedef struct toml_tokenizer toml_tokenizer_t;

toml_tokenizer_t *toml_tokenizer_create(toml_file_reader_t *file_reader, size_t capacity);
void toml_tokenizer_destroy(toml_tokenizer_t *tokenizer);

toml_token_t toml_tokenizer_next(toml_tokenizer_t *tokenizer);
toml_token_t toml_tokenizer_peek(toml_tokenizer_t *tokenizer, size_t n);
toml_boolean_t toml_tokenizer_end(toml_tokenizer_t *tokenizer);

void toml_tokenizer_push(toml_tokenizer_t *tokenizer, toml_token_t token);
void toml_tokenizer_on_comment(toml_file_reader_t *file_reader);
void toml_tokenizer_on_newline(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_equal(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_dot(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_comma(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_lbracket(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_rbracket(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_lbrace(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_rbrace(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_double_quote(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_single_quote(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
void toml_tokenizer_on_default(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer);
