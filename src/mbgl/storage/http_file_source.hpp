#pragma once

#include <mbgl/storage/file_source.hpp>
#include <mbgl/storage/resource.hpp>
#include <mbgl/storage/resource_options.hpp>

namespace mbgl {

class HTTPFileSource : public FileSource {
public:
    HTTPFileSource(const ResourceOptions& options);
    ~HTTPFileSource() override;

    std::unique_ptr<AsyncRequest> request(const Resource&, Callback) override;
    bool canRequest(const Resource& resource) const override {
        return resource.hasLoadingMethod(Resource::LoadingMethod::Network);
    }

    class Impl;

private:
    std::unique_ptr<Impl> impl;
};

} // namespace mbgl
