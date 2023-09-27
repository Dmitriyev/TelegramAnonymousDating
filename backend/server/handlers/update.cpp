#include "handlers.h"
#include "common/common_structures.h"


namespace handlers {
    using namespace common;
    using namespace db_adapter;

    void UpdateHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback
    ) {
        
    }
}

