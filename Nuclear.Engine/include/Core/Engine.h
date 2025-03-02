#pragma once
#include <Core\Client.h>
#include <Platform\Window.h>
#include <Diligent/Graphics/GraphicsEngine/interface/GraphicsTypes.h>

namespace Nuclear
{
	namespace Core
	{
		struct EngineStartupDesc
		{
			Platform::WindowDesc mEngineWindowDesc;
			Uint32 Samples = 2;

			bool DebugRenderAPI = false;
			bool VSync = true;
			bool AutoSelectRenderer = true;

			bool AutoInitGraphicsModule = true;
			bool AutoInitAudioModule = true;
			bool AutoInitPhysXModule = true;
			bool AutoInitScriptingModule = true;
			bool AutoInitRenderingModule = true;
			bool AutoInitThreadingModule = true;

			std::string mScriptingClientDllName = "ClientScripts.dll";
			std::string mScriptingAssemblyNamespace = "ClientScripts";
			std::string mAssetsLibraryPath = "Assets/";
			//Enables some debugging options that slows down performance in runtime
			bool Debug = DEBUG_TRUE_BOOL;
			bool EnableLogging = DEBUG_TRUE_BOOL;
		};

		class NEAPI Engine
		{
		public:
			Engine(Engine const&) = delete;
			void operator=(Engine const&) = delete;

			static Engine& Get();

			enum class State { Initializing, Loading, Rendering, ExitingRendering, Shuttingdown };

			bool Start(const EngineStartupDesc& desc);

			void Shutdown();

			void BeginFrame();

			void EndFrame();

			Platform::Window* GetMainWindow();

			void LoadClient(Client* client);
			void EndClient();

			void SetState(const State& state);

			bool ShouldClose();

			bool isDebug();

			Client* GetClient();

			FORCE_INLINE void SetSwapChainSyncInterval(Uint32 val)
			{
				SwapChainSyncInterval = val;
			}

		private:
			Engine();
			Client* pClient;
			Platform::Window MainWindow;

			Uint32 SwapChainSyncInterval;

			Engine::State Engine_State;
			bool gisDebug = DEBUG_TRUE_BOOL;
			bool mShouldClose = false;
			void MainLoop();
		};
	}
}