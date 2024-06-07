#include "message_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static MessageQueue message_queue = {0};

void mq_init()
{
    if (message_queue.messages == NULL)
    {
        message_queue.capacity = 16;
        message_queue.messages = calloc(message_queue.capacity, sizeof(struct GameEvent*));
    }

    if (message_queue.observers == NULL)
    {
        message_queue.observer_capacity = 16;
        message_queue.observers         = calloc(message_queue.observer_capacity, sizeof(Observer));
    }
}

void mq_push(struct GameEvent msg)
{
    if (message_queue.size >= message_queue.capacity)
    {
        message_queue.capacity *= 2;
        message_queue.messages = realloc(message_queue.messages, message_queue.capacity * sizeof(struct GameEvent*));
    }

    memcpy(&message_queue.messages[message_queue.size], &msg, sizeof(struct GameEvent));
    message_queue.size++;
}

void mq_listen(Observer obs)
{
    if (message_queue.observer_size >= message_queue.observer_capacity)
    {
        message_queue.observer_capacity *= 2;
        message_queue.observers = realloc(message_queue.observers, message_queue.observer_capacity * sizeof(Observer));
    }

    memcpy(message_queue.observers + message_queue.observer_size, &obs, sizeof(Observer));
    message_queue.observer_size++;
}

void mq_unlisten(ObserverFn obs)
{
    uint64_t obs_idx = 0;
    for (uint64_t i = 0; i < message_queue.observer_size; i++)
    {
        if (message_queue.observers[i].fn == obs)
        {
            obs_idx = i;
            break;
        }
    }

    memmove(message_queue.observers + obs_idx,
            message_queue.observers + obs_idx + 1,
            (message_queue.observer_size - obs_idx - 1) * sizeof(Observer));

    // Now we're good
    --message_queue.observer_size;
}

void mq_process()
{
    for (uint64_t i = 0; i < message_queue.size; i++)
    {
        for (uint64_t j = 0; j < message_queue.observer_size; j++)
        {
            Observer* obs = &message_queue.observers[j];
            obs->fn(obs->context, &message_queue.messages[i]);
        }
    }

    message_queue.size = 0;
}

void mq_free()
{
    if (message_queue.messages != NULL)
    {
        free(message_queue.messages);
        message_queue.messages = NULL;
    }

    if (message_queue.observers != NULL)
    {
        free(message_queue.observers);
        message_queue.observers = NULL;
    }

    message_queue.size     = 0;
    message_queue.capacity = 0;
}