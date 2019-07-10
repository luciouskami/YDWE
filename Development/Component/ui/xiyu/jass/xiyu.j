
#include "YDWEBase.j"
library xiyu requires YDWEBase 
	function YDWEAddAIOrder___DeleteEffectOnTime_Delete takes nothing returns nothing
        call DestroyEffect(LoadEffectHandle(YDHT, GetHandleId(GetExpiredTimer()), 0x41A45E05))
        call FlushChildHashtable(YDHT, GetHandleId(GetExpiredTimer()))
        call DestroyTimer(GetExpiredTimer())
    endfunction
    function DeleteEffectOnTime takes string modelName,widget targetWidget,string attachPointName,real time returns effect
        local timer tempTimer=CreateTimer()
        set bj_lastCreatedEffect=AddSpecialEffectTarget(modelName, targetWidget, attachPointName)
        call TimerStart(tempTimer, time, false, function YDWEAddAIOrder___DeleteEffectOnTime_Delete)
        call SaveEffectHandle(YDHT, GetHandleId(tempTimer), 0x41A45E05, bj_lastCreatedEffect)
        set tempTimer=null
        return bj_lastCreatedEffect
    endfunction
	function YDWEAddAIOrder___Flyup_timer takes nothing returns nothing
		local timer t=GetExpiredTimer()
		local unit u=LoadUnitHandle(YDHT, GetHandleId(t), 1)
		local real r=LoadReal(YDHT, GetHandleId(t), 2)
		local integer i=LoadInteger(YDHT, GetHandleId(t), 3)
		set i=i - 1
		call SaveInteger(YDHT, GetHandleId(t), 3, i)
		if i < 0 then
			call FlushChildHashtable(YDHT,GetHandleId(t))
			call PauseTimer(t)
			call DestroyTimer(t)
		else
			call SetUnitFlyHeight(u, GetUnitFlyHeight(u) + r, 0.00)
		endif
	set t=null
	set u=null
	set r=0
	endfunction
	function Flyup takes unit u,real height,real time returns nothing
		local timer t=CreateTimer()
		local integer i=R2I(time / 0.02)
		local real fly= height / I2R(i)
		call SaveUnitHandle(YDHT, GetHandleId(t), 1, u)
		call SaveReal(YDHT, GetHandleId(t), 2, fly)
		call SaveInteger(YDHT, GetHandleId(t), 3, i)
		call TimerStart(t, 0.02, true, function YDWEAddAIOrder___Flyup_timer)
	set i=0
	set u=null
	set t=null
	endfunction
	function YDWEAddAIOrder___dummyEX_timer takes nothing returns nothing
	    local timer t= GetExpiredTimer()
	    local unit u= LoadUnitHandle(YDHT, GetHandleId(t), 1)
	    local real r= LoadReal(YDHT, GetHandleId(t), 2)
	    local integer i= LoadInteger(YDHT, GetHandleId(t), 3)
	    local real angle=LoadReal(YDHT, GetHandleId(t), 4)
	    local real damage= LoadReal(YDHT, GetHandleId(t), 6)
	    local real ban= LoadReal(YDHT, GetHandleId(t), 7)
	    local group ydl_group
	    local unit ydl_unit
	        set ydl_group=CreateGroup()
	        call GroupEnumUnitsInRange(ydl_group, GetUnitX(u), GetUnitY(u), ban, null)
	        loop
	            set ydl_unit=FirstOfGroup(ydl_group)
	            exitwhen ydl_unit == null
	            call GroupRemoveUnit(ydl_group, ydl_unit)
	                if ( ( IsUnitType(ydl_unit, UNIT_TYPE_STRUCTURE) == false ) and ( IsUnitAliveBJ(ydl_unit) == true ) and ( IsUnitEnemy(ydl_unit, GetOwningPlayer(u)) == true ) and ( IsUnitInGroup(ydl_unit, LoadGroupHandle(YDHT, GetHandleId(t), 5)) == false ) ) then
	                call UnitDamageTarget(u, ydl_unit, damage, false, false, ATTACK_TYPE_MAGIC, DAMAGE_TYPE_MAGIC, WEAPON_TYPE_WHOKNOWS)
	                call GroupAddUnit(LoadGroupHandle(YDHT, GetHandleId(t), 5), ydl_unit)
	                else
	                endif
	        endloop
	        call DestroyGroup(ydl_group)
	    	set i=i - 1
	        call SaveInteger(YDHT, GetHandleId(t), 3, i)
	        call SetUnitX(u, GetUnitX(u) + r * Cos(angle))
	        call SetUnitY(u, GetUnitY(u) + r * Sin(angle))
	            if i <= 0 then
		            call FlushChildHashtable(YDHT,GetHandleId(t))
		            call DestroyGroup(LoadGroupHandle(YDHT, GetHandleId(t), 5))
		            call PauseTimer(t)
	            	call DestroyTimer(t)
	            endif
	    set t=null
	    set u=null
	    set ydl_group=null
	    set ydl_unit=null
	endfunction
	function dummyEx takes unit u,real angle,real dis,real time,string eff,real tim,real ban,real damage returns nothing
	        local group g= CreateGroup()
	        local integer i= R2I(time / 0.01)
	        local real r= dis / I2R(i)
	        local timer t=CreateTimer()
	        local real ang= angle * bj_DEGTORAD
	            if ( tim != 0 ) then
	                call DeleteEffectOnTime(eff , u , "foot" , tim)
	            else
	                call DestroyEffect(AddSpecialEffectTarget(eff, u, "foot"))
	            endif
	        call SaveUnitHandle(YDHT, GetHandleId(t), 1, u)
	        call SaveReal(YDHT, GetHandleId(t), 2, r)
	        call SaveInteger(YDHT, GetHandleId(t), 3, i)
	        call SaveReal(YDHT, GetHandleId(t), 4, ang)
	        call SaveGroupHandle(YDHT, GetHandleId(t), 5, g)
	        call SaveReal(YDHT, GetHandleId(t), 6, damage)
	        call SaveReal(YDHT, GetHandleId(t), 7, ban)
	        call TimerStart(t, 0.01, true, function YDWEAddAIOrder___dummyEX_timer)
	    set t=null
	    set u=null
	endfunction
endlibrary 