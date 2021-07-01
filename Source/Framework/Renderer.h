#pragma once

class FrameworkAPI Renderer
{
public:
	Renderer();
	~Renderer();

	void DrawTriangle(/*required params*/) const;
	void Draw(const class Mesh&) const;

	void DrawMyMesh() const;

	Mesh m;
};