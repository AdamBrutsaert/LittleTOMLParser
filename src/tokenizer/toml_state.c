#include "tokenizer/toml_state.h"

toml_state_t toml_state_dispatch(toml_state_t state, toml_tokenizer_t tokenizer, toml_reader_t reader)
{
    switch (state) {
        case TOML_STATE_DEFAULT:
            return toml_state_on_default(tokenizer, reader);
        case TOML_STATE_KEY:
            return toml_state_on_key(tokenizer, reader);
        case TOML_STATE_SET:
            return toml_state_on_set(tokenizer, reader);
        case TOML_STATE_VALUE:
            return toml_state_on_value(tokenizer, reader);
    }
    return TOML_STATE_DEFAULT;
}
