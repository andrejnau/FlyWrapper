#pragma once
#include "Instance/BaseTypes.h"

#include <gli/format.hpp>

#include <array>
#include <memory>

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
    uint32_t level = 0;
    uint32_t count = std::numeric_limits<uint32_t>::max();
    gli::format buffer_format = gli::format::FORMAT_UNDEFINED;
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

inline auto MakeTie(const LazyViewDesc& self)
{
    return std::tie(self.level, self.count, self.buffer_format);
}

inline auto MakeTie(const RasterizerDesc& self)
{
    return std::tie(self.fill_mode, self.cull_mode, self.depth_bias);
}

inline auto MakeTie(const BlendDesc& self)
{
    return std::tie(self.blend_enable, self.src_color_blend_factor, self.dst_color_blend_factor, self.color_blend_op,
                    self.src_alpha_blend_factor, self.dst_alpha_blend_factor, self.alpha_blend_op,
                    self.color_write_mask);
}

inline auto MakeTie(const StencilOpDesc& self)
{
    return std::tie(self.fail_op, self.depth_fail_op, self.pass_op, self.func);
}

inline auto MakeTie(const DepthStencilDesc& self)
{
    return std::tie(self.depth_test_enable, self.depth_func, self.depth_write_enable, self.depth_bounds_test_enable,
                    self.stencil_enable, self.stencil_read_mask, self.stencil_write_mask, self.front_face,
                    self.back_face);
}

inline auto MakeTie(const InputLayoutDesc& self)
{
    return std::tie(self.slot, self.semantic_name, self.format, self.stride, self.offset);
}

inline auto MakeTie(const GraphicsPipelineDesc& self)
{
    return std::tie(self.shaders, self.layout, self.input, self.color_formats, self.depth_stencil_format,
                    self.depth_stencil_desc, self.blend_desc, self.rasterizer_desc, self.sample_count);
}

inline auto MakeTie(const ComputePipelineDesc& self)
{
    return std::tie(self.shader, self.layout);
}

inline auto MakeTie(const RayTracingShaderGroup& self)
{
    return std::tie(self.type, self.general, self.closest_hit, self.any_hit, self.intersection);
}

inline auto MakeTie(const RayTracingPipelineDesc& self)
{
    return std::tie(self.shaders, self.layout, self.groups);
}

inline auto MakeTie(const BindingDesc& self)
{
    return std::tie(self.bind_key, self.view);
}

template <typename T>
auto operator<(const T& l, const T& r)
    -> std::enable_if_t<std::is_same_v<decltype(MakeTie(l) < MakeTie(r)), bool>, bool>
{
    return MakeTie(l) < MakeTie(r);
}
