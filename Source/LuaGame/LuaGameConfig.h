#pragma once

class LuaGameConfig
{
public:
	LuaGameConfig(class Game* game);
	~LuaGameConfig();

private:
	lua_State* script;

};
