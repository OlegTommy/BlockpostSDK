#include "WallHack.h"
#include "framework/il2cpp-appdata.h"

void WallHack::Render()
{
	app::Client_send_changeteam(0,1,nullptr);
	
	return;
}