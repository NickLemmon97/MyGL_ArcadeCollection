
--A Game Object consists of a Filename,
GameObjectCount = 2;

GameObjects = {
	{ 
		file = "Example.lua",
	},
	{
		file = "Test.lua",
	}
}

function get_gameobject(idx)
	print("[LUA] Called get_gameobject")
	return GameObjects[idx]
end