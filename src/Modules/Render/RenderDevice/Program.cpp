#include "RenderDevice/Program.h"

Program::Program(const std::vector<std::shared_ptr<Shader>>& shaders)
    : m_shaders(shaders)
{
    for (const auto& shader : m_shaders) {
        m_shaders_by_type[shader->GetType()] = shader;
        decltype(auto) reflection = shader->GetReflection();
        for (const auto& binding : reflection->GetBindings()) {
            BindKey bind_key = {
                .shader_type = shader->GetType(),
                .view_type = binding.type,
                .slot = binding.slot,
                .space = binding.space,
                .count = binding.count,
            };
            m_mapping[bind_key] = m_bindings.size();
            m_bindings.emplace_back(binding);
            m_binding_keys.emplace_back(bind_key);
        }
    }
}

bool Program::HasShader(ShaderType type) const
{
    return m_shaders_by_type.contains(type);
}

std::shared_ptr<Shader> Program::GetShader(ShaderType type) const
{
    auto it = m_shaders_by_type.find(type);
    if (it != m_shaders_by_type.end()) {
        return it->second;
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Shader>>& Program::GetShaders() const
{
    return m_shaders;
}

const std::vector<BindKey>& Program::GetBindings() const
{
    return m_binding_keys;
}

const ResourceBindingDesc& Program::GetResourceBinding(const BindKey& bind_key) const
{
    size_t index = m_mapping.at(bind_key);
    return m_bindings.at(index);
}
