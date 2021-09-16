#ifndef responses_Response_hpp
#define responses_Response_hpp
#include <string>

namespace responses {
    class Response {
        public:
            const char * messageId;            
            virtual std::string toJson();

            Response(std::string messageId);

        protected:
            bool success; 
            obs_data_t* getBaseResponseData();
    };
}

#endif