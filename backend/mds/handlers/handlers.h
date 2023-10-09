#pragma once

#include "aws_adapter/adapter.h"

#include <drogon/drogon.h>

#include <string>


namespace handlers {
    void UploadHandler(
        aws_adapter::TAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId,
        const std::string& format
    );

    void GetHandler(
        aws_adapter::TAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& id
    );
}
