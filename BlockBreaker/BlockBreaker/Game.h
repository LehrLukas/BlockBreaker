#pragma once
class Game
{
public:
	Game();
	~Game();
	int Run();
private:
	bool CreateMainWindow();
	void ProcessInput();
	void Update();
	void Render(float);
	bool close;
	const int windowWidth;
	const int windowHeight;
	const int tickPerSecond;
	const int maxFrameLoss;
};

