#pragma once
class dll_module
{
public:
	dll_module();
	~dll_module();
	void attach();
	void detach();
	//ÊÍ·Å²å¼þ
	bool export_dz_w3_plugin();
	void search_dz_api_from_vm();
	void add_dzapi_to_lua_engine();
public:
	uintptr_t dz_w3_plugin_handle;
	uintptr_t game_module_handle;
	uintptr_t storm_module_handle;
private:
	

};
extern dll_module g_DMod;