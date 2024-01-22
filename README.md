# FlyWrapper [deprecated]
FlyWrapper is a high-level graphics API is written in C++ on top of `DirectX 12`, `Vulkan` and `Metal`.
[FlyCube](https://github.com/andrejnau/FlyCube) is used as a rendering backend.

### The high-level graphics API features
* Provides main features, but hide some details
* Automatic resource state tracking
  * Per command list resource state tracking
  * Creating patch command list for sync with global resource state on execute
* Build time generated shader helper
  * Based on shader reflection
  * Easy to use resources binding
  * Constant buffers proxy for compile time access to members

### Utilities
  * Camera
  * Geometry utils
    * 3D models loading with `assimp`
  * Texture utils
    * Images loading with `gli` and `SOIL`

### Cloning repository
```
git clone --recursive https://github.com/andrejnau/FlyWrapper.git
```

### Build requirements
* Windows SDK Version 10.0.19041.0

### An example of the high-level graphics API usage
```cpp
std::shared_ptr<RenderDevice> device = CreateRenderDevice(settings, app.GetNativeWindow(), rect.width, rect.height);
std::shared_ptr<RenderCommandList> upload_command_list = device->CreateRenderCommandList();
std::vector<uint32_t> ibuf = { 0, 1, 2 };
std::shared_ptr<Resource> index = device->CreateBuffer(BindFlag::kIndexBuffer | BindFlag::kCopyDest, sizeof(uint32_t) * ibuf.size());
upload_command_list->UpdateSubresource(index, 0, ibuf.data(), 0, 0);
std::vector<glm::vec3> pbuf = {
    glm::vec3(-0.5, -0.5, 0.0),
    glm::vec3(0.0,  0.5, 0.0),
    glm::vec3(0.5, -0.5, 0.0)
};
std::shared_ptr<Resource> pos = device->CreateBuffer(BindFlag::kVertexBuffer | BindFlag::kCopyDest, sizeof(glm::vec3) * pbuf.size());
upload_command_list->UpdateSubresource(pos, 0, pbuf.data(), 0, 0);
upload_command_list->Close();
device->ExecuteCommandLists({ upload_command_list });

ProgramHolder<PixelShader, VertexShader> program(*device);
program.ps.cbuffer.Settings.color = glm::vec4(1, 0, 0, 1);

std::vector<std::shared_ptr<RenderCommandList>> command_lists;
for (uint32_t i = 0; i < kFrameCount; ++i)
{
    RenderPassBeginDesc render_pass_desc = {};
    render_pass_desc.colors[program.ps.om.rtv0].texture = device->GetBackBuffer(i);
    render_pass_desc.colors[program.ps.om.rtv0].clear_color = { 0.0f, 0.2f, 0.4f, 1.0f };

    decltype(auto) command_list = device->CreateRenderCommandList();
    command_list->UseProgram(program);
    command_list->Attach(program.ps.cbv.Settings, program.ps.cbuffer.Settings);
    command_list->SetViewport(0, 0, rect.width, rect.height);
    command_list->IASetIndexBuffer(index, gli::format::FORMAT_R32_UINT_PACK32);
    command_list->IASetVertexBuffer(program.vs.ia.POSITION, pos);
    command_list->BeginRenderPass(render_pass_desc);
    command_list->DrawIndexed(3, 1, 0, 0, 0);
    command_list->EndRenderPass();
    command_list->Close();
    command_lists.emplace_back(command_list);
}

while (!app.PollEvents())
{
    device->ExecuteCommandLists({ command_lists[device->GetFrameIndex()] });
    device->Present();
}
device->WaitForIdle();
```

### Advanced sample
[SponzaPbr](https://github.com/andrejnau/SponzaPbr) was originally part of the repository. It is my sandbox for rendering techniques.
* Features
  * Deferred rendering
  * Physically based rendering
  * Image based lighting
  * Ambient occlusion
    * Raytracing
    * Screen space
  * Normal mapping
  * Point shadow mapping
  * Skeletal animation
  * Multisample anti-aliasing
  * Tone mapping
  * Simple imgui based UI settings

![sponza.png](screenshots/sponza.png)
