#ifndef useCase_RotateCamera_hpp
#define useCase_RotateCamera_hpp
#include <obs-module.h>
#include "../../responses/include/Response.hpp"

namespace useCase {
class RotateCamera {
public:
	static responses::Response invoke(obs_data_t *baseRequest);

private:
	static void source_rotate(const char *name, int seconds);
};
}

#endif
