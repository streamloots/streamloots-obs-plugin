#pragma once
#include <obs-module.h>

inline int getMetadataSeconds(obs_data_t *metadata)
{
    auto seconds = obs_data_get_int(metadata, "seconds");
    if (!seconds)
    {
        seconds = 5;
    }

    return seconds;
}