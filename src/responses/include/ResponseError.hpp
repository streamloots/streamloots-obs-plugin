#ifndef responses_ResponseError_hpp
#define responses_ResponseError_hpp
#include <string>
#include "./Response.hpp"

namespace responses {
    class ResponseError : public Response {
        public:
            const char * error;

            ResponseError(std::string error);
            ResponseError(std::string error, std::string messageId);

            virtual std::string toJson();
    };
}

#endif