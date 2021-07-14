#pragma once


enum class RendererType
{
	Shape = 0,
	UI,
};

class BaseRenderer
{
public:
	virtual ~BaseRenderer() = default;
	virtual RendererType GetType() = 0;
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;

	virtual void SetProjection(float w, float h) = 0;
	virtual void SetCameraPosition(float x, float y)= 0;

protected:
	std::unique_ptr<ShaderProgram> m_Shader;
};


class ShapeRenderer : public BaseRenderer
{
public:
	ShapeRenderer();
	~ShapeRenderer();

	RendererType GetType() override;
	void BeginDraw() override;
	void DrawShape(const class Shape&, const glm::vec2& pos, float rotation);
	void EndDraw() override;

	void SetProjection(float w, float h) override;
	void SetCameraPosition(float x, float y) override;
};

class UIRenderer : public BaseRenderer
{

	struct UIVertex
	{
		glm::vec2* point;

		glm::vec2 anch;
		glm::vec2 pos;
	};

	std::vector<UIVertex> m_Points;

public:
	UIRenderer();
	~UIRenderer();

	RendererType GetType() override;
	void BeginDraw() override;
	void Draw(const class Shape&, const glm::vec2& pos, const glm::vec2& anchor, float rotation);
	void EndDraw() override;

	void SetProjection(float w, float h) override;
	void SetCameraPosition(float x, float y) override;
};

class FrameworkAPI BatchRenderer
{
public:
	BatchRenderer();
	~BatchRenderer();

	void Init();

	void BeginFrame();
	void DrawShape(const class Shape&, const glm::vec2& pos, float rotation);
	void DrawUI(const class Shape&, const glm::vec2& pos, const glm::vec2& anchor, float rotation);
	void EndFrame();

	void SetBackgroundColor(glm::vec3 color);

	void SetProjection(float w, float h);
	void SetCameraPosition(float x, float y);

private:

	void SwitchRenderers(RendererType type);

	std::unique_ptr<ShapeRenderer> m_ShapeRenderer;
	std::unique_ptr<UIRenderer> m_UIRenderer;
	BaseRenderer* m_ActiveRenderer = nullptr;
};
