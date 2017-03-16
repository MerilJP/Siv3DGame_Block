#include <Siv3D.hpp>
#include "Siv3DGame.h"

enum class GameScene
{
	Title,
	Playing,
	GameOver
};


void Main()
{

	System::SetExitEvent(WindowEvent::CloseButton);
	Siv3DGame *GameData = new Siv3DGame();
	GameScene gameScene = GameScene::Title;

	while (System::Update())
	{

		GameData->ShowInfo();
		switch (gameScene)
		{
		case GameScene::Title:
			GameData->TitleData();	
			
			if (Input::KeyEnter.clicked) 
			{
				//カーソルをウィンドウの中央へ
				Cursor::SetPos(Window::Center());
				gameScene = GameScene::Playing;
			}

			if (Input::KeyEscape.clicked) System::Exit();

			break;
		case GameScene::Playing:
			if (!GameData->PlayData()) gameScene = GameScene::GameOver;
			break;
		case GameScene::GameOver:
			GameData->EndData();
			if (Input::KeyEnter.clicked)
			{
				gameScene = GameScene::Title;
				GameData->Initialize();
			}
			
			if (Input::KeyEscape.clicked) System::Exit();

			break;
		}
	}

}
