#pragma once
#include <NE_Common.h>
#include <string>
#include <unordered_map>
#include <Serialization/Access.h>

namespace Nuclear
{
	namespace Graphics
	{
		class ShaderPipeline;
		struct ShaderPipelineVariant;

		class NEAPI ShaderPipelineSwitch
		{
		public:
			enum class Type {
				PostProcessingEffect,
				RenderingEffect,
				PostProcessingAndRenderingEffect,
				Unknown
			};
			ShaderPipelineSwitch(const std::string& name = "", bool InitialValue = true, Type type = Type::Unknown);
			~ShaderPipelineSwitch();

			void SetValue(bool value);
			bool GetValue() const;

			void SetName(const std::string& name);
			std::string GetName() const;

			void SetType(Type type);
			Type GetType() const;

			Uint32 GetID() const;

			constexpr static auto serialize(auto& archive, auto& self)
			{
				return archive(self.mID, self.mName, self.mType, self.mValue);
			}
		private:
			friend Serialization::Access;
			Uint32 mID = 0;
			std::string mName;
			Type mType;
			bool mValue;
		};

		struct NEAPI ShaderPipelineSwitchController
		{
		public:
			ShaderPipelineSwitchController();
			~ShaderPipelineSwitchController();

			void SetPipeline(ShaderPipeline* pipeline);
			bool SetSwitch(Uint32 switchId, bool value, bool controllersupport = true);
			void Update(bool ForceDirty = false);

			Uint32 GetRequiredHash();
			ShaderPipelineVariant* GetActiveVariant();
			ShaderPipeline* GetShaderPipeline();
			ShaderPipelineSwitch& GetSwitch(Uint32 SwitchID);
			std::unordered_map<Uint32, ShaderPipelineSwitch>& GetSwitches();

		protected:
			std::unordered_map<Uint32, ShaderPipelineSwitch> mSwitches;

			ShaderPipeline* pPipeline;
			ShaderPipelineVariant* pActiveVariant;

			Uint32 mRequiredHash = 0;
			bool mDirty = true;

		};
	}
}