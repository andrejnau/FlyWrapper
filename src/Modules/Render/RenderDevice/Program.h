#pragma once

#include "Instance/BaseTypes.h"
#include "Shader/Shader.h"

#include <map>
#include <vector>

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>>& shaders);

    bool HasShader(ShaderType type) const;
    std::shared_ptr<Shader> GetShader(ShaderType type) const;
    const std::vector<std::shared_ptr<Shader>>& GetShaders() const;
    const std::vector<BindKey>& GetBindings() const;
    const ResourceBindingDesc& GetResourceBinding(const BindKey& bind_key) const;

private:
    std::vector<std::shared_ptr<Shader>> m_shaders;
    std::map<ShaderType, std::shared_ptr<Shader>> m_shaders_by_type;
    std::vector<BindKey> m_binding_keys;
    std::map<BindKey, size_t> m_mapping;
    std::vector<ResourceBindingDesc> m_bindings;
};
