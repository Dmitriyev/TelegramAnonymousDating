#include "handlers.h"

#include <trantor/utils/Utilities.h>

#include <unordered_set>


namespace {
    std::string StrToUpper(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), 
            [](unsigned char c){
                return std::toupper(c);
            }
        );
        return s;
    }

    static const std::unordered_set<std::string> AllowedImageFormats = {
        "JPG",
        "JPEG",
        "GIF",
        "PNG",
    };

    static const std::string ImageContentTypePrefix = "image/";
}

namespace handlers {
    using namespace drogon;

    void UploadHandler(
        aws_adapter::TAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId,
        const std::string& format
    ) {
        auto resp = HttpResponse::newHttpResponse();
        const std::string reqBody(req->getBody());

        if (reqBody.empty()) {
            LOG_ERROR << "No body passed in request";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        if (!AllowedImageFormats.count(StrToUpper(format))) {
            LOG_ERROR << "Wrong image format";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        const auto bodyMd5 = trantor::utils::toHexString(trantor::utils::md5(reqBody.c_str(), reqBody.size()));
        const auto userIdMd5 = trantor::utils::toHexString(trantor::utils::md5(userId.c_str(), userId.size()));
        const auto filename = userIdMd5 + "_" + bodyMd5 + "." + format;

        const auto uploadResult = adapter.UploadImage(reqBody, filename);
        if (!uploadResult.has_value()) {
            LOG_ERROR << "Error uploading file";
            resp->setCustomStatusCode(500);
            callback(resp);
            return;
        }

        Json::Value result;
        result["avatar_path"] = uploadResult.value();
        resp = toResponse(result);
        callback(resp);
    }

    void GetHandler(
        aws_adapter::TAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& id
    ) {
        auto resp = HttpResponse::newHttpResponse();
        const auto retData = adapter.LoadImage(id);

        if (!retData.has_value()) {
            LOG_ERROR << "Error loading file";
            resp->setCustomStatusCode(500);
            callback(resp);
            return;
        }

        resp->setBody(retData.value());
        const auto extension = std::filesystem::path(id).extension().string();
        
        if (extension.empty()) {
            LOG_ERROR << "Wrong file extension";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        resp->setContentTypeString(ImageContentTypePrefix + extension.substr(1)); // substr removes first dot in extension
        callback(resp);
    }
}
