#ifndef useCase_PressKey_hpp
#define useCase_PressKey_hpp
#include <obs-module.h>
#include <windows.h>
#include <winuser.h>
#include <QtCore/QStringList>

#include "../../responses/include/Response.hpp"

namespace useCase{
    class PressKey {
        public:
            static responses::Response invoke(obs_data_t *baseRequest);

        private:
            static inline void pressKeys(OBSDataArrayAutoRelease keys);
            static inline void pressKeyB(char mK);
            static inline void pressKeySeconds();
            static inline INPUT PressKey::getKey(QString key);
            static void pressEnter();
            static inline void ShowDesktop();
            static inline void ShowFilter();
        };
}

#endif