#include "../utils/timers.h"
#include "../utils/scene_manager.h"
#include "../plugin-macros.generated.h"
#include "./include/DisplayImage.hpp"
#include "../requests/include/DisplayImageRequest.hpp"
#include "../responses/include/ResponseError.hpp"

using namespace requests;
using namespace responses;
using useCase::DisplayImage;

Response DisplayImage::invoke(obs_data_t * baseRequest) {
    DisplayImageRequest request(baseRequest);

    blog(LOG_INFO, "Image url to display %s seconds:%d", request.url, request.seconds);
    obs_data_t *settings = obs_data_create();
    obs_data_set_string(settings, "url", request.url);
    obs_data_set_bool(settings, "shutdown", true);
    obs_data_set_string(settings, "css", "body { background-color: transparent!important; }");
    DisplayImage::set_source_full_screen(settings);
    
    obs_source_t *source = obs_source_create("browser_source", request.messageId.toStdString().c_str(), settings, NULL);    
    auto scene_item = add_source_to_current_scene(source);

    std::function<void()> func1 = [&]()
        {
            blog(LOG_INFO, "deleting source", request.url);
            obs_sceneitem_remove(scene_item);
        };      

    setTimeOut(request.seconds*1000, func1);
    return Response(request.messageId.toStdString());
}

void DisplayImage::set_source_full_screen(obs_data_t *settings){
    blog(LOG_INFO, "Trying to set image full screen resolution");
    obs_video_info ovi;
    bool videoSuccess = obs_get_video_info(&ovi);

    if (videoSuccess) {
        obs_data_set_int(settings, "width", ovi.base_width);
        obs_data_set_int(settings, "height", ovi.base_height);
        blog(LOG_INFO, "Change source to fit full screen resolution");
    }
    else {
        blog(LOG_ERROR, "Unable to set source to full screen resolution");
    }
}