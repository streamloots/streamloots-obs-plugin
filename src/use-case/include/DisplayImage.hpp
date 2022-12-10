#ifndef useCase_DisplayImage_hpp
#define useCase_DisplayImage_hpp
#include <obs-module.h>
#include "../../responses/include/Response.hpp"

namespace useCase {
class DisplayImage {
public:
	static responses::Response invoke(obs_data_t *baseRequest);

private:
	static void set_source_full_screen(obs_data_t *settings);
};
}

#endif