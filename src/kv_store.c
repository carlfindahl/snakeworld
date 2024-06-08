#include "kv_store.h"

static int kv_store[KVI_COUNT]         = {0};
static int kv_validity_mask[KVI_COUNT] = {0};

void kv_clear_value(enum KeyValueIdentifier key)
{
    kv_validity_mask[key] = 0;
    kv_store[key]         = 0;
}

void kv_set_value(enum KeyValueIdentifier key, int value)
{
    kv_store[key]         = value;
    kv_validity_mask[key] = 1;
}

bool kv_get_value(enum KeyValueIdentifier key, int** value)
{
    if (kv_validity_mask[key])
    {
        *value = &kv_store[key];
        return true;
    }

    return false;
}
