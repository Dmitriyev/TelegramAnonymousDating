#include "adapter.h"

#include <aws/core/auth/AWSCredentials.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/PutObjectRequest.h>

#include <trantor/utils/Logger.h>

#include <sstream>

namespace aws_adapter {
    TAdapter::TAdapter(
        const std::string& region,
        const std::string& endpoint,
        const std::string& keyId,
        const std::string& key,
        const std::string& bucket
    )
        : Bucket(bucket)
    {
        Aws::InitAPI(Options);

        Aws::Client::ClientConfiguration config;
        config.region = region;
        config.endpointOverride = endpoint;

        Aws::Auth::AWSCredentials credentials;
        credentials.SetAWSAccessKeyId(keyId);
        credentials.SetAWSSecretKey(key);

        Client = std::make_unique<Aws::S3::S3Client>(
            credentials,
            std::make_shared<Aws::S3::S3EndpointProvider>(),
            config
        );
    }

    TAdapter::~TAdapter() {
        Client.reset();
        Aws::ShutdownAPI(Options);
    }

    std::optional<std::string> TAdapter::UploadImage(
            const std::string& data,
            const std::string& filename
    ) {
        //ToDo: upload images converted into .webp format
        if (data.size() > 2 * 1024 * 1024) { // 2 Mb
            LOG_ERROR << "File is too big";
            return std::nullopt;
        }

        const auto dataStream = std::make_shared<std::stringstream>(data);

        Aws::S3::Model::PutObjectRequest request;
        request.SetBucket(Bucket);
        request.SetKey(filename);
        request.SetBody(dataStream);

        const auto outcome = Client->PutObject(request);

        if (!outcome.IsSuccess()) {
            LOG_ERROR << outcome.GetError().GetMessage();
            return std::nullopt;
        }

        return filename;
    }

    std::optional<std::string> TAdapter::LoadImage(const std::string& id) {
        Aws::S3::Model::GetObjectRequest request;
        request.SetBucket(Bucket);
        request.SetKey(id);

        const auto outcome = Client->GetObject(request);

        if (!outcome.IsSuccess()) {
            LOG_ERROR << outcome.GetError().GetMessage();
            return std::nullopt;
        }

        std::stringstream result;
        result << outcome.GetResult().GetBody().rdbuf();
        return result.str();
    }
}
