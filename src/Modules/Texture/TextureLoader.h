#pragma once

#include "RenderCommandList/RenderCommandList.h"
#include "RenderDevice/RenderDevice.h"
#include "Texture/TextureInfo.h"

std::shared_ptr<Resource> CreateTexture(RenderDevice& device, RenderCommandList& command_list, const std::string& path);
