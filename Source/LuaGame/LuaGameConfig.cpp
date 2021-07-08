#include "GamePCH.h"
#include "LuaGameConfig.h"

LuaGameConfig::LuaGameConfig(Game* game)
{
	script = luaL_newstate();
	luaL_openlibs(script);

	if (!Utils::CheckLua(script, luaL_dofile(script, "Data/LuaScripts/GameConfig.lua")))
	{
		DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Error, "Couldn't load game config");
	}

	lua_getglobal(script, "GameObjectCount");

	if (lua_isnumber(script, -1))
	{
		int count = lua_tonumber(script, -1);

		for (int i = 0; i < count; i++)
		{
			GameObject* go = game->AddGameObject();

			lua_getglobal(script, "get_gameobject");

			if (lua_isfunction(script, -1))
			{
				lua_pushnumber(script, i);

				if (Utils::CheckLua(script, lua_pcall(script, 1, 1, 0)))
				{
					DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Success, "[C++] Called lua function get_gameobject");

					if (lua_istable(script, -1))
					{
						lua_pushstring(script, "file");
						lua_gettable(script, -2);

						std::string filename = lua_tostring(script, -1);
						DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, filename.c_str());
						go->LoadLuaScript(filename.c_str());

						//pop our string
						lua_pop(script, 1);

						//pop our table
						lua_pop(script, 1);
					}
				}
			}
		}
	}
}

LuaGameConfig::~LuaGameConfig()
{
}
