#pragma once

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>

#include <memory>
#include <optional>
#include <string>


namespace aws_adapter {
    class TAdapter {
    public:
        TAdapter(
            const std::string& region,
            const std::string& endpoint,
            const std::string& keyId,
            const std::string& key,
            const std::string& bucket
        );
        ~TAdapter();

        std::optional<std::string> UploadImage(
            const std::string& data,
            const std::string& filename
        );

        std::optional<std::string> LoadImage(const std::string& id);

    private:
        Aws::SDKOptions Options;
        std::unique_ptr<Aws::S3::S3Client> Client;
        const std::string Bucket;
    };
}
