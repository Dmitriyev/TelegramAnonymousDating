#include "handlers.h"

#include <trantor/utils/Utilities.h>

#include <unordered_set>


namespace {
    std::string str_toupper(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), 
            [](unsigned char c){
                return std::toupper(c);
            }
        );
        return s;
    }

    bool CheckMD5Sum(const std::string& data, const std::string& md5) {
        return trantor::utils::toHexString(trantor::utils::md5(data.c_str(), data.size())) == str_toupper(md5);
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
        const std::string& format,
        const std::string& md5
    ) {
        auto resp = HttpResponse::newHttpResponse();
        const std::string reqBody(req->getBody());

        if (reqBody.empty()) {
            LOG_ERROR << "No body passed in request";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        if (!AllowedImageFormats.count(str_toupper(format))) {
            LOG_ERROR << "Wrong image format";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        if (!CheckMD5Sum(reqBody, md5)) {
            LOG_ERROR << "Request body corrupted";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        const auto uploadResult = adapter.UploadImage(reqBody, format, md5, userId);
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
