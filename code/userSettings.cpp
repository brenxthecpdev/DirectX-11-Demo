
#define STRINGIFY(n) #n
#define STRINGIFY_MACRO(n) STRINGIFY(n)
#define APP_NAME STRINGIFY_MACRO(A_NAME)

#define SHADER_DEBUG 0
#define HOTRELOAD_SHADERS 1
#define WINDOW_TOPMOST_DEBUG 1

//

#define Editor_Executable_Path "C:\\Program Files\\Sublime Text 3\\sublime_text.exe"
#define Windows_Font_Folder "\\Fonts\\"
#define Windows_Font_Path_Variable "windir"
	
#define App_Session_File   ".\\session.tmp"
#define Game_Settings_File ".\\settings.tmp"
#define Saves_Folder       ".\\saves\\"
#define Save_State1        "saveState1.sav"

#ifdef SHIPPING_MODE
#define DATA_FOLDER(str)  ".\\data\\" str
#else 
#define DATA_FOLDER(str) "..\\data\\" str
#endif

#define Gui_Session_File    DATA_FOLDER("guiSettings.tmp")
#define App_Font_Folder     DATA_FOLDER("Fonts\\")
#define App_Audio_Folder    DATA_FOLDER("Audio\\")
#define App_Texture_Folder  DATA_FOLDER("Textures\\")
#define App_Material_Folder DATA_FOLDER("Materials\\")
#define App_Mesh_Folder     DATA_FOLDER("Meshes\\")

//

struct AppSessionSettings {
	Rect windowRect;
};

void appWriteSessionSettings(char* filePath, AppSessionSettings* at) {
	writeDataToFile((char*)at, sizeof(AppSessionSettings), filePath);
}

void appReadSessionSettings(char* filePath, AppSessionSettings* at) {
	readDataFromFile((char*)at, filePath);
}

void saveAppSettings(AppSessionSettings at) {
	if(fileExists(App_Session_File)) {
		appWriteSessionSettings(App_Session_File, &at);
	}
}

//

struct DebugSessionSettings {
	Rect menuPanel;
	int menuPanelActiveSection;
	Rect profilerPanel;
	int profilerPanelActiveSection;
	int panelHierarchy[2];
};

void debugWriteSessionSettings(DebugSessionSettings* at) {
	writeDataToFile((char*)at, sizeof(DebugSessionSettings), Gui_Session_File);
}

void debugReadSessionSettings(DebugSessionSettings* at) {
	readDataFromFile((char*)at, Gui_Session_File);
}