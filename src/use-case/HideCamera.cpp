#include "./include/HideCamera.hpp"

#include <graphics/matrix4.h>
#include "graphics/matrix3.h"
#include "graphics/vec3.h"

#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../plugin-macros.generated.h"
#include "../requests/include/HideCameraRequest.hpp"
#include "../responses/include/ResponseError.hpp"
#include "./utils/getSceneItemInScene.hpp"

using namespace requests;
using namespace responses;
using useCase::HideCamera;

Response HideCamera::invoke(obs_data_t *baseRequest)
{
	HideCameraRequest request(baseRequest);
	OBSDataArrayAutoRelease items = getMediaItems();
	for (int i = 0; i < obs_data_array_count(items); i++) {
		OBSDataAutoRelease item = obs_data_array_item(items, i);
		auto name = obs_data_get_string(item, "sourceName");
		QString kind = obs_data_get_string(item, "sourceKind");
		if (kind == "dshow_input") {
			hideSceneItem(name, request.seconds);
		}
	}

	return Response(request.messageId.toStdString());
}

void HideCamera::hideSceneItem(const char *name, int seconds)
{
	auto scene_item = getSceneItemInScene(name);

	obs_sceneitem_set_visible(scene_item, false);

	std::function<void()> func1 = [&]() {
		blog(LOG_INFO, "rotating again");
		obs_sceneitem_set_visible(scene_item, true);
	};

	setTimeOut(seconds * 1000, func1);
}
