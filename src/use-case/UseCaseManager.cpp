#include "UseCaseManager.h"
#include <QtCore/QString>
#include "../plugin-macros.generated.h"

void UseCaseManager::processUseCase(obs_data_t* request){
    blog(LOG_ERROR, "Procesing use case %s", obs_data_get_json(request));

    QString methodName = obs_data_get_string(request, "request-type");
    if(methodName=="possum"){
        create_source();
    }
}

//TODO: create utils for timeouts
//TODO: create scene manager/utils