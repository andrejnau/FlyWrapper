#pragma once
#include <memory>
#include <array>
#include <gli/format.hpp>
#include <Instance/BaseTypes.h>

class Resource;
class RenderCommandList;
struct ResourceLazyViewDesc;

class DeferredView {
public:
    virtual ~DeferredView() = default;
    virtual std::shared_ptr<ResourceLazyViewDesc> GetView(RenderCommandList& command_list) = 0;
    virtual void OnDestroy(ResourceLazyViewDesc& view_desc) = 0;
};

struct LazyViewDesc {
    size_t level = 0;
    size_t count = static_cast<size_t>(-1);
    gli::format buffer_format = gli::format::FORMAT_UNDEFINED;

    auto MakeTie() const
    {
        return std::tie(level, count, buffer_format);
    }
};

struct ResourceLazyViewDesc {
    ResourceLazyViewDesc(DeferredView& deferred_view, const std::shared_ptr<Resource>& resource)
        : m_deferred_view(deferred_view)
        , resource(resource)
    {
    }

    ~ResourceLazyViewDesc()
    {
        m_deferred_view.OnDestroy(*this);
    }

    std::shared_ptr<Resource> resource;
    LazyViewDesc view_desc;
    DeferredView& m_deferred_view;
};

struct RenderPassBeginColorDesc {
    std::shared_ptr<Resource> texture;
    LazyViewDesc view_desc;
    RenderPassLoadOp load_op = RenderPassLoadOp::kClear;
    RenderPassStoreOp store_op = RenderPassStoreOp::kStore;
    glm::vec4 clear_color = {};
};

struct RenderPassBeginDepthStencilDesc {
    std::shared_ptr<Resource> texture;
    LazyViewDesc view_desc;
    RenderPassLoadOp depth_load_op = RenderPassLoadOp::kClear;
    RenderPassStoreOp depth_store_op = RenderPassStoreOp::kStore;
    RenderPassLoadOp stencil_load_op = RenderPassLoadOp::kClear;
    RenderPassStoreOp stencil_store_op = RenderPassStoreOp::kStore;
    float clear_depth = 1.0f;
    uint8_t clear_stencil = 0;
};

struct RenderPassBeginDesc {
    std::array<RenderPassBeginColorDesc, 8> colors = {};
    RenderPassBeginDepthStencilDesc depth_stencil;
};
