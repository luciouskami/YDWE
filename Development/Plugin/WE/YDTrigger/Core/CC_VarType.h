#ifndef INCLUDE_CC_VARTYPE_H
#define INCLUDE_CC_VARTYPE_H

enum VARTYPE_We_Defined
{
  CC_VARTYPE_integer = 0,
  CC_VARTYPE_real,
  CC_VARTYPE_boolean,
  CC_VARTYPE_string,
  CC_VARTYPE_StringExt,
  CC_VARTYPE_boolexpr,
  CC_VARTYPE_boolcall,
  CC_VARTYPE_code,
  CC_VARTYPE_eventcall,
  CC_VARTYPE_unitcode,
  CC_VARTYPE_itemcode,
  CC_VARTYPE_techcode,
  CC_VARTYPE_abilcode,
  CC_VARTYPE_destructablecode,
  CC_VARTYPE_doodadcode,
  CC_VARTYPE_AnyGlobal,
  CC_VARTYPE_Null,
  CC_VARTYPE_AnyType,
  CC_VARTYPE_VarAsString_Real,
  CC_VARTYPE_ArithmeticOperator,
  CC_VARTYPE_ComparisonOperator,
  CC_VARTYPE_EqualNotEqualOperator,
  CC_VARTYPE_timer,
  CC_VARTYPE_dialog,
  CC_VARTYPE_weathereffectcode,
  CC_VARTYPE_scriptcode,
  CC_VARTYPE_integervar,
  CC_VARTYPE_heroskillcode,
  CC_VARTYPE_buffcode,
};

enum VARTYPE_User_Defined
{
  CC_TYPE__begin = 0,
  CC_TYPE_integer,
  CC_TYPE_real,
  CC_TYPE_boolean,
  CC_TYPE_string,
  CC_TYPE_timer,
  CC_TYPE_trigger,
  CC_TYPE_unit,
  CC_TYPE_unitcode,
  CC_TYPE_abilcode,
  CC_TYPE_item,
  CC_TYPE_itemcode,
  CC_TYPE_group,
  CC_TYPE_player,
  CC_TYPE_location,
  CC_TYPE_destructable,
  CC_TYPE_force,
  CC_TYPE_rect,
  CC_TYPE_region,
  CC_TYPE_sound,
  CC_TYPE_effect, 
  CC_TYPE_unitpool,
  CC_TYPE_itempool,
  CC_TYPE_quest,
  CC_TYPE_questitem,
  CC_TYPE_timerdialog,
  CC_TYPE_leaderboard,
  CC_TYPE_multiboard,
  CC_TYPE_multiboarditem,
  CC_TYPE_trackable,
  CC_TYPE_dialog,
  CC_TYPE_button,  
  CC_TYPE_texttag,
  CC_TYPE_lightning,
  CC_TYPE_image,
  CC_TYPE_fogstate,
  CC_TYPE_fogmodifier,
  CC_TYPE_radian,
  CC_TYPE_degree,
  CC_TYPE_frame,
  // LH Mark 逆天局部变量 种类
  CC_TYPE__end,
};

extern const char* TypeName[];

DWORD GetVarType(DWORD This, DWORD index);

#endif
