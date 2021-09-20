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

    blog(LOG_INFO, "url to display %s seconds:%d", request.url, request.seconds);
    obs_data_t *settings = obs_data_create();
    obs_data_set_string(settings, "url", request.url);
    obs_data_set_bool(settings, "shutdown", true);
    
    obs_source_t *source = obs_source_create("browser_source", request.messageId.toStdString().c_str(), settings, NULL);
    set_source_full_screen(source);
    auto scene_item = add_source_to_current_scene(source);

    std::function<void()> func1 = [&]()
        {
            blog(LOG_INFO, "deleting source", request.url);
            obs_sceneitem_remove(scene_item);
        };      

    setTimeOut(request.seconds*1000, func1);
    return Response(request.messageId.toStdString());
}