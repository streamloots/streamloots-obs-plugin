#ifndef useCase_HideCamera_hpp
#define useCase_HideCamera_hpp
#include <obs-module.h>
#include "../../responses/include/Response.hpp"

namespace useCase {
class HideCamera {
public:
	static responses::Response invoke(obs_data_t *baseRequest);

private:
	static void hideSceneItem(const char *name, int seconds);
};
}

#endif