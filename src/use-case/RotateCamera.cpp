#pragma once
#include "./include/RotateCamera.hpp"

#include "../plugin-macros.generated.h"

#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../utils/transforms.h"
#include "../requests/include/RotateCameraRequest.hpp"

using namespace requests;
using namespace responses;
using useCase::RotateCamera;

Response RotateCamera::invoke(obs_data_t *baseRequest)
{
	RotateCameraRequest request(baseRequest);

	OBSDataArrayAutoRelease items = getMediaItems();
	for (int i = 0; i < obs_data_array_count(items); i++) {
		OBSDataAutoRelease item = obs_data_array_item(items, i);
		auto name = obs_data_get_string(item, "sourceName");
		QString kind = obs_data_get_string(item, "sourceKind");
		if (kind == "dshow_input") {
			RotateCamera::source_rotate(name, request.seconds);
		}
	}

	return Response(request.messageId.toStdString());
}
void RotateCamera::source_rotate(const char *name, int seconds)
{
	blog(LOG_INFO, "rotating camera of source: %s", name);
	obs_source_t *source = obs_get_source_by_name(name);
	obs_source_set_async_rotation(source, 180);

	std::function<void()> func1 = [&]() {
		blog(LOG_INFO, "restoring rotation of source: %s", name);
		obs_source_set_async_rotation(source, 0);
	};

	setTimeOut(seconds * 1000, func1);
}
