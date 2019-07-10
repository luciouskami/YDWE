#include <windows.h>
#include <BlizzardStorm.h>
#include "Common.h"
#include "Core/CC_GUIID.h"
#include <algorithm>
#include <map>
#include <vector>

struct multiple 
{
	int icon;
	std::string name;
};

typedef std::vector<multiple> multiples;
typedef std::map<int, multiples> multiples_mgr;

static multiples_mgr mgr = {
	{
		CC_GUIID_YDWETimerStartMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_YDWERegisterTriggerMultiple,
		{
			{ CC_GUI_TYPE_EVENT, "WESTRING_EVENTS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_DzTriggerRegisterMouseEventMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
		{
		CC_GUIID_DzTriggerRegisterKeyEventMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_DzTriggerRegisterMouseWheelEventMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_DzTriggerRegisterMouseMoveEventMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_DzTriggerRegisterWindowResizeEventMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_DzFrameSetUpdateCallbackMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_DzFrameSetScriptMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_YDWEEnumUnitsInRangeMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_YDWEForLoopLocVarMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_TRIGSUBFUNC_FORLOOPACTIONS" },
		}
	},
	{
		CC_GUIID_YDWERegionMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_ACTIONS" },
		}
	},
	{
		CC_GUIID_YDWEExecuteTriggerMultiple,
		{
			{ CC_GUI_TYPE_ACTION, "WESTRING_PARAMETERS" },
		}
	},
};

int _fastcall
GetGUICount_Hook(DWORD This)
{
	uint32_t ui = *(uint32_t*)(This + 0x138);
	auto it = mgr.find(ui);
	if (it == mgr.end())
	{
		return GetGUICount(This);
	}
	return it->second.size();
}

int _fastcall
GetGUIString_Hook(DWORD This, DWORD EDX, int index, char* buff, int len)
{
	uint32_t ui = *(uint32_t*)(This + 0x138);
	auto it = mgr.find(ui);
	if (it == mgr.end())
	{
		return GetGUIString(This, EDX, index, buff, len);
	}
	index = (std::min)(index, (int)it->second.size()-1);
	return GetWEString(it->second[index].name.c_str(), buff, len, 0);
}

int _fastcall
GetGUIIcon_Hook(DWORD This, DWORD EDX, int index)
{
	uint32_t ui = *(uint32_t*)(This + 0x138);
	auto it = mgr.find(ui);
	if (it == mgr.end())
	{
		return GetGUIIcon(This, EDX, index);
	}
	index = (std::min)(index, (int)it->second.size() - 1);
	return it->second[index].icon;
}
