#include "framework.h"
#include "dll_module.h"
#include "dz_w3_plugin.h"
#include <fstream>
#include <warcraft3/jass/func_value.h>
#include "warcraft3/war3_searcher.h"
#include "warcraft3/hashtable.h"


extern unsigned char dz_w3_plugin_shellcode[];

dll_module::dll_module()
	: dz_w3_plugin_handle(0)
	, game_module_handle(0)
	, storm_module_handle(0)
{}


dll_module::~dll_module()
= default;

void dll_module::attach()
{
	this->export_dz_w3_plugin();
}

void dll_module::detach()
{
}

auto dll_module::export_dz_w3_plugin() -> bool
{
	using std::ios;
	using std::fstream;
	fstream v_temp_dz_w3_plugin_file;

	try
	{
		//ios::noreplace 
		v_temp_dz_w3_plugin_file.open("dz_w3_plugin.dll", ios::binary | ios::out);
		if (v_temp_dz_w3_plugin_file.is_open())
		{
			v_temp_dz_w3_plugin_file.write(reinterpret_cast<const char*>(dz_w3_plugin_shellcode),
			                               sizeof(dz_w3_plugin_shellcode));
			v_temp_dz_w3_plugin_file.close();
			dz_w3_plugin_handle = reinterpret_cast<uintptr_t>(LoadLibraryW(L"dz_w3_plugin.dll"));
			return NULL != dz_w3_plugin_handle;
		}
	}
	catch (...)
	{
		return false;
	}
	return false;
}

//.text:1002B853                 mov[ebp + var_1D8], offset sub_10029CF0
//.text:1002B85D                 mov[ebp + var_1D4], offset aDzapiMapMissio; "DzAPI_Map_MissionComplete"
//.text:1002B867                 mov[ebp + var_1D0], offset aHplayerSsV; "(Hplayer;SS)V"
//......
//.text:1002BC73                 mov[ebp + var_10], offset sub_1002B700
//.text:1002BC7A                 mov[ebp + var_C], offset aRequestextrare; "RequestExtraRealData"
//.text:1002BC81                 mov[ebp + var_8], offset aIhplayerSsbiii_2; "(IHplayer;SSBIII)R"
void dll_module::search_dz_api_from_vm()
{
	using warcraft3::hashtable::native_func_node;
	using warcraft3::get_war3_searcher;
	using warcraft3::get_native_function_hashtable;

	if (!get_war3_searcher().get_instance(5))
		return false;

	if (!old_proc_ptr)
		return false;

	native_func_node* node_ptr =get_native_function_hashtable()->find(proc_name);

	if (!node_ptr)
		return false;

	*old_proc_ptr = (uintptr_t)node_ptr->func_address_;
}

void dll_module::add_dzapi_to_lua_engine()
{
	//借一个引用过来
	auto& tmp_ref = warcraft3::jass::japi_function;
	
}

