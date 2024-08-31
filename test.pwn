#include "action-text.inc"

#include <test-boilerplate>

main() {}

#if !defined KEY
	#define KEY: _:
#endif
public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys) {
	if(IsPlayerViewingActionText(playerid)) {
		SendClientMessage(playerid, -1, "ActionText is visible, hiding");
		HideActionText(playerid);
	} else {
		SendClientMessage(playerid, -1, "ActionText is not visible, showing");
		ShowActionText(playerid, "This message will self-destruct in 10 seconds!", 10000);
	}

	return 1;
}
