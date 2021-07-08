#include "GamePCH.h"
#include "GameObject.h"

using namespace Utils;
using namespace std;

GameObject::GameObject()
{
	m_Mesh = std::make_shared<Shape>();
	m_Position = { 0.0f,0.0f };

	L = luaL_newstate();
	luaL_openlibs(L);
}

GameObject::~GameObject()
{
	lua_close(L);
}

void GameObject::Init()
{
	glm::vec3 Color{ 1.0f,0.5f,0.2f };

	lua_getglobal(L, "color");

	if (lua_istable(L, -1))
	{
		lua_rawgeti(L, -1, 1);
		Color.r = lua_tonumber(L, -1);
		lua_pop(L, -1);

		lua_rawgeti(L, -1, 2);
		Color.g = lua_tonumber(L, -1);
		lua_pop(L, -1);

		lua_rawgeti(L, -1, 3);
		Color.b = lua_tonumber(L, -1);
		lua_pop(L, -1);
	}

	lua_getglobal(L, "pos");

	if (lua_istable(L, -1))
	{
		lua_rawgeti(L, -1, 1);
		m_Position.x = lua_tonumber(L, -1);
		lua_pop(L, -1);

		lua_rawgeti(L, -1, 2);
		m_Position.y = lua_tonumber(L, -1);
		lua_pop(L, -1);
	}

	lua_getglobal(L, "init");
	
	if (lua_isfunction(L, -1))
	{
		if (Utils::CheckLua(L, lua_pcall(L, 0, 0, 0)))
		{
			DEBUG_LOG_MESSAGE(LogGameObject, LogVerbosity::Success, "[C++] Called Lua Init function");
		}
		else
		{
			DEBUG_LOG_MESSAGE(LogGameObject, LogVerbosity::Error, "Init Error");
		}
	}

	lua_getglobal(L, "update");

	m_Mesh->MakeSqaure(40, Color, GL_TRIANGLE_FAN);
}

void GameObject::Update(double delta)
{
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, delta);
		if (Utils::CheckLua(L, lua_pcall(L, 1, 0, 0)))
		{

		}
		else
		{

		}
	}
	else
	{
		//CheckLua(L, lua_getglobal(L, "update"));
	}
}

void GameObject::Draw(const Renderer& renderer)
{
	renderer.Draw(*m_Mesh.get(), m_Position);
}

void GameObject::LoadLuaScript(const char* name)
{
	DEBUG_LOG_MESSAGE(LogGameObject, LogVerbosity::Log, "Loading lua script");
	cout << name << endl;
	std::string file = "Data/LuaScripts/";
	file.append(name);
	cout << file << endl;
	CheckLua(L, luaL_dofile(L, file.c_str()));
}
