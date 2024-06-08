#pragma once

#include <stdbool.h>

enum KeyValueIdentifier
{
    KVI_SCORE,
    KVI_COUNT,
};

void kv_clear_value(enum KeyValueIdentifier key);

void kv_set_value(enum KeyValueIdentifier key, int value);

bool kv_get_value(enum KeyValueIdentifier key, int** value);
