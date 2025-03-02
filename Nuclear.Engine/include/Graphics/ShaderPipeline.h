#pragma once
#include <NE_Common.h>
#include <Diligent/Graphics/GraphicsEngine/interface/PipelineState.h>
#include <Diligent/Graphics/GraphicsEngine/interface/ShaderResourceBinding.h>
#include <Diligent/Common/interface/RefCntAutoPtr.hpp>
#include <unordered_map>
#include <Core\Path.h>
#include <Graphics/ShaderPipelineVariant.h>
#include <Graphics/ShaderPipelineSwitch.h>
#include "Rendering/GBuffer.h"
#include <Serialization/Access.h>

namespace Nuclear
{
	namespace Assets
	{
		class Shader;
	}
	namespace Rendering
	{
		class ImageBasedLighting;
	}
	namespace Graphics
	{			
		class NEAPI ShaderPipeline
		{
		public:
			ShaderPipeline(Assets::Shader* parent);
			ShaderPipeline(ShaderPipelineDesc& desc);

			~ShaderPipeline();

			void BuildVariants();

			bool Bake(ShaderPipelineBakingDesc& bakingdesc);

			Uint32 GetHashedKey(const std::string& Key);
			ShaderPipelineVariant* GetVariant(Uint32 Key);

			const std::vector<ShaderPipelineSwitch>& GetSwitches() const;

			Assets::Shader* GetShaderAsset();
			Rendering::GBuffer* GetGBuffer();

			constexpr static auto serialize(auto& archive, auto& self)
			{
				ISLOADING(archive)
				{
					Core::UUID shaderuuid;
					auto result = archive(shaderuuid, self.mVariantsInfo);
					self.pParentShader = static_cast<Assets::Shader*>(Serialization::SerializationModule::Get().DeserializeUUID(Assets::AssetType::Shader, shaderuuid));
					return result;
				}
				else
				{
					Core::UUID uuid;
					if (self.pParentShader)
					{
						uuid = self.pParentShader->GetUUID();
					}
					return archive(uuid, self.mVariantsInfo);
				}

			}
		protected:
			friend Serialization::Access;
			friend class ShaderPipelineVariantFactory;

			Assets::Shader* pParentShader;
			std::unordered_map<Uint32, ShaderPipelineVariant> mVariants;
			std::vector<ShaderPipelineVariantDesc> mVariantsInfo;

			ShaderPipelineDesc& mDesc;
			Rendering::GBuffer mGBuffer;
		};
	}
}