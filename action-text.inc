// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_action_text
	#undef _inc_action_text
#endif
// custom include-guard to ensure we don't duplicate
#if defined _action_text_included
	#endinput
#endif
#define _action_text_included

#include <a_samp>
#include <YSI_Coding\y_hooks>


forward ShowActionText(playerid, const message[], time=0, width=200);
/*
# Description
Display a small message in the center of the player's screen.
*/

forward HideActionText(playerid);
/*
# Description
Hide the message displayed by ShowActionText.
*/


static
	PlayerText:actionTextUI[MAX_PLAYERS],
	bool:viewingActionText[MAX_PLAYERS],
	hideTimer[MAX_PLAYERS];

forward _actionText_Hide(playerid);

hook OnPlayerConnect(playerid) {
	_actionText_CreateUI(playerid);
}

hook OnPlayerDisconnect(playerid) {
	_actionText_DeleteUI(playerid);
}

#if defined FILTERSCRIPT
hook OnFilterScriptInit() {
	for(new i; i < MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i))
			_actionText_CreateUI(i);
	}
}
hook OnFilterScriptExit() {
	for(new i; i < MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i))
			_actionText_DeleteUI(i, true);
	}
}
#endif

_actionText_CreateUI(playerid) {
	actionTextUI[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 320.000000, "_");
	PlayerTextDrawAlignment(playerid, actionTextUI[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, actionTextUI[playerid], 255);
	PlayerTextDrawFont(playerid, actionTextUI[playerid], 1);
	PlayerTextDrawLetterSize(playerid, actionTextUI[playerid], 0.300000, 1.499999);
	PlayerTextDrawColor(playerid, actionTextUI[playerid], -1);
	PlayerTextDrawSetOutline(playerid, actionTextUI[playerid], 1);
}

_actionText_DeleteUI(playerid, doTD = false) {
	if(doTD) {
		PlayerTextDrawHide(playerid, actionTextUI[playerid]);
		PlayerTextDrawDestroy(playerid, actionTextUI[playerid]);
	}
}

stock ShowActionText(playerid, const message[], time=0, width=200) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	PlayerTextDrawSetString(playerid, actionTextUI[playerid], message);
	PlayerTextDrawTextSize(playerid, actionTextUI[playerid], width, 300);
	PlayerTextDrawShow(playerid, actionTextUI[playerid]);

	viewingActionText[playerid] = true;

	if(time != 0) {
		KillTimer(hideTimer[playerid]);
		hideTimer[playerid] = SetTimerEx("_actionText_Hide", time, false, "d", playerid);
	}

	return 0;
}

public _actionText_Hide(playerid) {
	if(!IsPlayerConnected(playerid)) {
		return;
	}

	HideActionText(playerid);

	return;
}

stock HideActionText(playerid) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	PlayerTextDrawHide(playerid, actionTextUI[playerid]);
	viewingActionText[playerid] = false;

	return 0;
}

stock bool:IsPlayerViewingActionText(playerid) {
	if(!IsPlayerConnected(playerid)) {
		return false;
	}

	return viewingActionText[playerid];
}
