// more callback stuff
void* wglSwapBuffers;

// orig callback
static std::add_pointer_t<BOOL WINAPI(HDC)> __o__wglSwapBuffers;

#include "../../Fonts/productsans_compressed.h"

#include <TlHelp32.h>

#define IMGUI_TEXT_NEWLINE() ImGui::Text(" ")
#define IMGUI_TEXT_VAR(member) [](const fpsent* plyr) { ImGui::Text(#member ": %d", plyr->member); }
#define IMGUI_TEXT_STRING(member) [](const fpsent* plyr) { ImGui::Text(#member ": %d", *plyr->member); }
#define IMGUI_TEXT_VEC(member) [](const fpsent* plyr) { ImGui::Text(#member ": %d, %d, %d", plyr->member.x, plyr->member.y, plyr->member.z); }

bool IsMouseButtonPressed(int button) {
	return GetAsyncKeyState(button) != 0;
}

void DrawFrame(ImDrawData* context)
{
	// trigger module draw events
	for (Module* mod : modules)
		if (mod->enabled)
			mod->OnUpdate(context);

	/*{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = Game::SDL::GetCursorPos();
	}*/

	if (Game::debugScreen)
	{
		ImGui::SetNextWindowSize(ImVec2(1920, 1080), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Echoify Menu by yeemi#0", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		// fix font default scale
		ImGui::SetWindowFontScale(0.30f);

		if (Game::GetLocalPlayer() == nullptr)
		{
			ImGui::Text("Not ingame..");
		}
		else
		{
			fpsent* plyr = Game::GetLocalPlayer();

			// physent variables first
			{
				// starting vecs
				IMGUI_TEXT_VEC(vel)(plyr);
				IMGUI_TEXT_VEC(deltapos)(plyr);
				IMGUI_TEXT_VEC(newpos)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_VAR(yaw)(plyr);
				IMGUI_TEXT_VAR(pitch)(plyr);
				IMGUI_TEXT_VAR(roll)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_VAR(radius)(plyr);
				IMGUI_TEXT_VAR(eyeheight)(plyr);
				IMGUI_TEXT_VAR(aboveeye)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_VAR(timeinair)(plyr);
				IMGUI_TEXT_VAR(inwater)(plyr);
				IMGUI_TEXT_VAR(jumping)(plyr);
				IMGUI_TEXT_VAR(move)(plyr);
				IMGUI_TEXT_VAR(strafe)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_VAR(physstate)(plyr);
				IMGUI_TEXT_VAR(state)(plyr);
				IMGUI_TEXT_VAR(editstate)(plyr);
				IMGUI_TEXT_VAR(type)(plyr);
				IMGUI_TEXT_VAR(collidetype)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_VAR(k_left)(plyr);
				IMGUI_TEXT_VAR(k_right)(plyr);
				IMGUI_TEXT_VAR(k_up)(plyr);
				IMGUI_TEXT_VAR(k_down)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_VAR(weight)(plyr);
				IMGUI_TEXT_VAR(ping)(plyr);
				IMGUI_TEXT_VAR(respawned)(plyr);
				IMGUI_TEXT_VAR(suicided)(plyr);
				IMGUI_TEXT_VAR(lastpain)(plyr);
				IMGUI_TEXT_VAR(attacking)(plyr);
				IMGUI_TEXT_VAR(flagpickup)(plyr);
				IMGUI_TEXT_VEC(lastcollect)(plyr);
				IMGUI_TEXT_VAR(frags)(plyr);
				IMGUI_TEXT_VAR(flags)(plyr);
				IMGUI_TEXT_VAR(deaths)(plyr);
				IMGUI_TEXT_VAR(totaldamage)(plyr);
				IMGUI_TEXT_VAR(totalshots)(plyr);

				IMGUI_TEXT_NEWLINE();
				IMGUI_TEXT_STRING(name)(plyr);
				IMGUI_TEXT_STRING(team)(plyr);
				IMGUI_TEXT_STRING(info)(plyr);
			}

			/*{
				ImGui::NextColumn();
				IMGUI_TEXT_VEC(o)(plyr);
			}*/
		}

		ImGui::End();
	}
	else // modules arraylist
	{
		ImVec2 dims = ImGui::GetIO().DisplaySize;//ImVec2(1920, 1080);

		ImGui::SetNextWindowSize(dims, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(0, dims.y/2));
		ImGui::Begin("Echoify Menu by yeemi#0", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		// fix font default scale
		ImGui::SetWindowFontScale(0.40f);

		// render MODULES
		for (Module* mod : modules) {
			std::stringstream ss;

			ss << mod->name.c_str() << " [" << mod->keybind.c_str() << "]";

			ImGui::TextColored(mod->enabled == true ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1), ss.str().c_str());
		}

		ImGui::End();

		//RenderModuleList();
	}
}

static BOOL wglSwapBuffersDetour(HDC hdc) {

	// imgui stuff here
	if (g_isRunning && ImGui::GetCurrentContext()) {
		if (!ImGui::GetIO().BackendRendererUserData)
		{
			ImGui_ImplOpenGL3_Init();
		}

		// new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//std::cout << "drawing custom overlay..." << std::endl;

		// draw basic imgui menu
		DrawFrame(ImGui::GetDrawData());

		// render imgui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	return __o__wglSwapBuffers(hdc);
}

class OpenGLHook : public FuncHook {
public:
	void* GetGameHWND() {
		return FindWindowA(nullptr, "Cube 2: Sauerbraten");
	}

	bool Initialize() override {
		HMODULE opengl32 = GetModuleHandleA("opengl32.dll");

		wglSwapBuffers = (void*)GetProcAddress(opengl32, "wglSwapBuffers");

		if (!ImGui::GetCurrentContext())
		{
			// create imgui context
			ImGui::CreateContext();
			ImGui_ImplWin32_Init(GetGameHWND());

			// set imgui io
			ImGuiIO& io = ImGui::GetIO();
			io.IniFilename = io.LogFilename = nullptr; // dont save
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // enable keyboard controls

			// load the compressed fonts (product sans)
			ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(ProductSans_compressed_data, ProductSans_compressed_size, 48.f);
			ImGui::GetIO().Fonts->Build();
		}

		if (not HookFunction((void*)wglSwapBuffers, &wglSwapBuffersDetour, &__o__wglSwapBuffers))
			return false;

		return true;
	}

	static OpenGLHook& Get() {
		static OpenGLHook single;
		return single;
	}
};