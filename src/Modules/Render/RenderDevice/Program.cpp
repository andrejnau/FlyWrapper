#include "RenderDevice/Program.h"

Program::Program(const std::vector<std::shared_ptr<Shader>>& shaders)
    : m_shaders(shaders)
{
    for (const auto& shader : m_shaders) {
        m_shaders_by_type[shader->GetType()] = shader;
        decltype(auto) bindings = shader->GetBindings();
        m_bindings.insert(m_bindings.begin(), bindings.begin(), bindings.end());
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
    return m_bindings;
}
