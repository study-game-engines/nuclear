#include "Components\MeshComponent.h"
#include "Assets\Material.h"
#include "Assets\Shader.h"
#include "Assets\Mesh.h"

namespace Nuclear 
{
	namespace Components
	{
		MeshComponent::MeshComponent()
		{
			RenderQueue = 1;
			pMesh = nullptr;
			pMaterial = nullptr;
			pAnimator = nullptr;
		}
		MeshComponent::MeshComponent(Assets::Mesh* mesh, Assets::Material* material, Animation::Animator* Animator)
		{
			RenderQueue = 1;
			pMesh = mesh;
			pMaterial = material;
			pAnimator = Animator;
		}
		MeshComponent::~MeshComponent()
		{
			RenderQueue = 1;
			pMesh = nullptr;
			pMaterial = nullptr;
			pAnimator = nullptr;
		}
		void MeshComponent::Update(bool forcedirty)
		{
			if (mDirty)
			{
				if (mEnableRendering)
				{
					bool invalid = false;
					if (pMesh && pMaterial)
					{
						if (pMesh->GetState() != Assets::IAsset::State::Created)
						{
							invalid = true;
						}
						else
						{
							if (pMaterial->GetShader())
							{
								if (mMaterialDirty)
								{
									auto assetptr = pMaterial->GetShader();
									mPipelineCntrl.SetPipeline(&assetptr->GetShaderPipeline());
									mMaterialDirty = false;
								}

								if (mRenderSystemHasDefferedPass)
									mRequestDeffered = false;

								if (mRenderSystemHasShadowPass)
									mReceiveShadows = false;

								Uint32 mDefferedPipeline = Utilities::Hash("NE_DEFFERED");
								Uint32 mAnimationHash = Utilities::Hash("NE_ANIMATION");
								Uint32 mRecieveShadowHash = Utilities::Hash("NE_SHADOWS");

								mPipelineCntrl.SetSwitch(mAnimationHash, bool(pAnimator));
								mPipelineCntrl.SetSwitch(mRecieveShadowHash, mReceiveShadows);
								mPipelineCntrl.SetSwitch(mDefferedPipeline, mRequestDeffered);

								for (auto& i : mCustomSwitches)
								{
									mPipelineCntrl.SetSwitch(i.first, i.second);
								}
								mPipelineCntrl.Update();
								RenderQueue = mPipelineCntrl.GetActiveVariant()->mRenderQueue;
								mDirty = false;

							}
							else
							{
								invalid = true;
							}
						}
					}
					else
					{
						invalid = true;
					}

					if (invalid)
					{
						mDirty = true;
						RenderQueue = 0;
					}
				}
				else
				{
					RenderQueue = 0;
				}				
			}
		}
		Uint32 MeshComponent::GetRenderQueue() const
		{
			return RenderQueue;
		}
		Graphics::ShaderPipelineVariant* MeshComponent::GetRenderingVariant()
		{
			return mPipelineCntrl.GetActiveVariant();
		}
		void MeshComponent::SetVariantSwitch(Uint32 VariantID, bool val)
		{
			if (VariantID == Utilities::Hash("NE_DEFFERED"))
			{
				mRequestDeffered = val;
			}

			mCustomSwitches[VariantID] = val;
			mDirty = true;
		}
		void MeshComponent::SetEnableRendering(bool val)
		{
			if (mEnableRendering != val)
			{
				mEnableRendering = val;
				mDirty = true;
			}
		}
		void MeshComponent::SetCastShadow(bool val)
		{
			if (mCastShadow != val)
			{
				mCastShadow = val;
				mDirty = true;
			}
		}
		void MeshComponent::SetReceiveShadows(bool val)
		{
			if (mReceiveShadows != val)
			{
				mReceiveShadows = val;
				mDirty = true;
			}
		}

		bool MeshComponent::GetEnableRendering() const
		{
			return mEnableRendering;
		}
		bool MeshComponent::GetCastShadow() const
		{
			return mCastShadow;
		}
		bool MeshComponent::GetReceiveShadows() const
		{
			return mReceiveShadows;
		}

		void MeshComponent::SetMesh(Assets::Mesh* mesh)
		{
			pMesh = mesh;
			mDirty = true;
		}

		void MeshComponent::SetMaterial(Assets::Material* material)
		{
			pMaterial = material;
			mDirty = true;
			mMaterialDirty = true;
		}
		Assets::Mesh* MeshComponent::GetMesh()
		{
			return pMesh;
		}
		Assets::Material* MeshComponent::GetMaterial()
		{
			return pMaterial;
		}
		Animation::Animator* MeshComponent::GetAnimator()
		{
			return pAnimator;
		}
		void MeshComponent::SetRenderSystemFlags(bool hasdefferedpass, bool hasshadowpass)
		{
			if (mRenderSystemHasDefferedPass != hasdefferedpass)
			{
				mRenderSystemHasDefferedPass = hasdefferedpass;
				mDirty = true;
			}

			if (mRenderSystemHasShadowPass != hasshadowpass)
			{
				mRenderSystemHasShadowPass = hasshadowpass;
				mDirty = true;
			}
		}
	}
}