#include "jassbind.h"
#include "class_array.h"
#include "libs_runtime.h"
#include "common.h"
#include "callback.h"
#include <warcraft3/hashtable.h>
#include <warcraft3/war3_searcher.h>
#include <warcraft3/jass.h>
#include <warcraft3/jass/func_value.h>
#include <warcraft3/jass/global_variable.h>
#include <warcraft3/jass/hook.h>
#include <bee/lua/range.h>



namespace bee::lua {
	template <>
	int convert_to_lua(lua_State* L, const std::string& v)
	{
		lua_pushlstring(L, v.data(), v.size());
		return 1;
	}

	template <>
	int convert_to_lua(lua_State* L, const std::string_view& v)
	{
		lua_pushlstring(L, v.data(), v.size());
		return 1;
	}
}

namespace warcraft3::lua_engine { 

	namespace globals {
		void jass_get_global_variable(lua_State* L, jass::OPCODE_VARIABLE_TYPE opt, uint32_t value);
	}

	namespace common {

	int jass_get(lua_State* L)
	{
		const char* name = lua_tostring(L, 2);

		jass::func_value const* nf = jass::jass_func(name);
		if (nf && nf->is_valid())
		{
			lua_pushinteger(L, (uint32_t)(uintptr_t)nf);
			lua_pushcclosure(L, jass_call_closure, 1);
			return 1;
		}

		if (!is_gaming())
		{
			lua_pushnil(L);
			return 1;
		}

		jass::global_variable gv(name);
		if (gv.is_vaild())
		{
			if (!gv.is_array())
			{
				globals::jass_get_global_variable(L, gv.type(), gv);
				return 1;
			}
			else
			{
				switch (gv.type())
				{
				case jass::OPCODE_VARIABLE_INTEGER_ARRAY:
				case jass::OPCODE_VARIABLE_REAL_ARRAY:
				case jass::OPCODE_VARIABLE_STRING_ARRAY:
				case jass::OPCODE_VARIABLE_HANDLE_ARRAY:
				case jass::OPCODE_VARIABLE_BOOLEAN_ARRAY:
					return jarray_create(L, (uintptr_t)gv.ptr());
				default:
					lua_pushnil(L);
					return 1;
				}
			}
		}

		lua_pushnil(L);
		return 1;
	}

	int jass_set(lua_State* L)
	{
		if (!is_gaming())
		{
			return 0;
		}

		const char* name = luaL_checkstring(L, 2);
		jass::global_variable gv(name);
		if (gv.is_vaild())
		{
			if (!gv.is_array())
			{
				gv = jass_read(L, jass::opcode_type_to_var_type(gv.type()), 3);
			}
			else
			{
				switch (gv.type())
				{
				case jass::OPCODE_VARIABLE_INTEGER_ARRAY:
				case jass::OPCODE_VARIABLE_REAL_ARRAY:
				case jass::OPCODE_VARIABLE_STRING_ARRAY:
				case jass::OPCODE_VARIABLE_HANDLE_ARRAY:
				case jass::OPCODE_VARIABLE_BOOLEAN_ARRAY:
					break;
				default:
					break;
				}
			}
		}

		return 0;
	}

	int jass_pairs(lua_State* L)
	{
		return bee::lua::make_range(L, jass::jass_function);
	}

	static void init_sleep_function(const char* name)
	{
		auto it = jass::jass_function.find(name);
		if (it == jass::jass_function.end() || !it->second.is_valid())
		{
			return;
		}
		it->second.set_sleep(true);
	}

#define DZTEST

#ifdef DZTEST
	int register_japi_func(lua_State* L)
	{
		if (!lua_isstring(L, 1) || !lua_isstring(L, 2))
			return 0;
		const char* name = lua_tostring(L, 1);
		const char* params = lua_tostring(L, 2);
		if (!name || !params)
			return 0;
		jass::func_value const* nf = jass::japi_func(name);
		if (nf)
			return 0;

		auto* ptr = get_native_function_hashtable()->find(name);
		if (!ptr || !ptr->func_address_)
			return 0;
		jass::japi_table_add(ptr->func_address_, name, params);

		return 1;
	}
#endif

	int open(lua_State* L)
	{
		init_sleep_function("TriggerSleepAction");
		init_sleep_function("TriggerWaitForSound");
		init_sleep_function("TriggerSyncReady");
		init_sleep_function("SyncSelections");
#ifdef DZTEST
		const char* script = "\n"
			"local storm = require 'jass.storm' \n"
			"function register_japi(str) \n"
			"if str == nil then return end \n"
			"local type_map = { integer = 'I', real = 'R', string = 'S', boolean = 'B', code = 'C' } \n"
			"str:gsub('native%s+([%w_]+)%s+takes%s+(.-)%s+returns%s+([%w_]+)%s-\\n', \n"
			"function(name, params, rettype) \n"
			"local param_type = { '(' } \n"
			"if parameter == 'nothing' then \n"
			"return \n"
			"end \n"
			"params : gsub('(%w+)%s+(%w+)', \n"
			"function(type, name) \n"
			"if type_map[type]~= nil then \n"
			"table.insert(param_type, type_map[type]) \n"
			"else \n"
			"table.insert(param_type, 'H'..type..';') \n"
			"end \n"
			"end) \n"
			"table.insert(param_type, ')') \n"
			"if rettype == 'nothing' then \n"
			"table.insert(param_type, 'V') \n"
			"else \n"
			"if type_map[rettype]~= nil then \n"
			"table.insert(param_type, type_map[rettype]) \n"
			"else \n"
			"table.insert(param_type, 'H'..rettype..';') \n"
			"end \n"
			"end \n"
			"register_japi_func(name, table.concat(param_type)) \n"
			"end) \n"
			"end \n"
			"local script = storm.load('war3map.j') \n"
			"register_japi(script)\n"
			"";
		lua_register(L, "register_japi_func", register_japi_func);
		luaL_loadbuffer(L, script, strlen(script) - 1, "initfunc");
		safe_call(L, 0, 0, true);
#endif

		lua_newtable(L);
		{
			lua_newtable(L);
			{
				lua_pushstring(L, "__index");
				lua_pushcclosure(L, jass_get, 0);
				lua_rawset(L, -3);

				lua_pushstring(L, "__newindex");
				lua_pushcclosure(L, jass_set, 0);
				lua_rawset(L, -3);

				lua_pushstring(L, "__pairs");
				lua_pushcclosure(L, jass_pairs, 0);
				lua_rawset(L, -3);
			}
			lua_setmetatable(L, -2);
		}
		return 1;
	}
}}
