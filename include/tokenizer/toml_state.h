#pragma once

#include "toml_tokenizer.h"

typedef enum {
    TOML_STATE_DEFAULT,
    TOML_STATE_KEY,
    TOML_STATE_SET,
    TOML_STATE_VALUE
} toml_state_t;

toml_state_t toml_state_dispatch(toml_state_t state, toml_tokenizer_t tokenizer, toml_reader_t reader);

toml_state_t toml_state_on_default(toml_tokenizer_t tokenizer, toml_reader_t reader);
toml_state_t toml_state_on_key(toml_tokenizer_t tokenizer, toml_reader_t reader);
toml_state_t toml_state_on_set(toml_tokenizer_t tokenizer, toml_reader_t reader);
toml_state_t toml_state_on_value(toml_tokenizer_t tokenizer, toml_reader_t reader);
