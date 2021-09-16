#ifndef requests_metadata_hpp
#define requests_metadata_hpp
#include <obs-data.h>

namespace requests {
    inline int getMetadataSeconds(obs_data_t *metadata)
    {
        auto seconds = obs_data_get_int(metadata, "seconds");
        if (!seconds)
        {
            seconds = 5;
        }

        return seconds;
    }
}

#endif