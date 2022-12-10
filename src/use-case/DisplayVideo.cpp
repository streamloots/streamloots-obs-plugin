#include "./include/DisplayVideo.hpp"

#include "../plugin-macros.generated.h"
#include "../Config.hpp"

#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../plugin-macros.generated.h"
#include "../requests/include/DisplayVideoRequest.hpp"
#include "../responses/include/ResponseError.hpp"

using namespace requests;
using namespace responses;
using useCase::DisplayVideo;

Response DisplayVideo::invoke(obs_data_t *baseRequest)
{
	DisplayVideoRequest request(baseRequest);

	blog(LOG_INFO, "Video url to display %s seconds:%d", request.url, request.seconds);
	obs_data_t *settings = obs_data_create();

	obs_data_set_string(settings, "input", request.url);
	obs_data_set_bool(settings, "clear_on_media_end", true);
	obs_data_set_bool(settings, "looping", false);
	obs_data_set_bool(settings, "is_local_file", false);

	obs_source_t *source =
		obs_source_create("ffmpeg_source", request.messageId.toStdString().c_str(), settings, NULL);
	configure_settings(source);

	auto scene_item = add_source_to_current_scene(source);
	DisplayVideo::set_source_full_screen(scene_item);

	std::function<void()> func1 = [&]() {
		blog(LOG_INFO, "deleting source", request.url);
		obs_sceneitem_remove(scene_item);
	};

	setTimeOut(request.seconds * 1000, func1);
	return Response(request.messageId.toStdString());
}

void DisplayVideo::configure_settings(obs_source_t *source)
{
	auto conf = GetConfig();
	auto monitoringType = conf->MonitoringType;
	obs_source_set_monitoring_type(source, (obs_monitoring_type)monitoringType);

	auto percent = conf->Volume;
	float volume = (float)percent / 100.0f;
	obs_source_set_volume(source, volume);
}

void DisplayVideo::set_source_full_screen(obs_sceneitem_t *scene_item)
{
	blog(LOG_INFO, "Trying to set video to full screen resolution");
	obs_video_info ovi;
	bool videoSuccess = obs_get_video_info(&ovi);

	if (videoSuccess) {
		vec2 boundingBoxSize;
		boundingBoxSize.x = ovi.base_width;
		boundingBoxSize.y = ovi.base_height;
		obs_sceneitem_set_bounds_type(scene_item, OBS_BOUNDS_SCALE_INNER);
		obs_sceneitem_set_bounds(scene_item, &boundingBoxSize);
		blog(LOG_INFO, "Change source to fit full screen resolution");
	} else {
		blog(LOG_ERROR, "Unable to set source to full screen resolution");
	}
}
