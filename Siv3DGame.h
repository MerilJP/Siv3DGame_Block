#pragma once
#ifndef __Siv3DGame_h_
#define __Siv3DGame_h_
#include <Siv3D.hpp>

class Siv3DGame {

public :
	//コンストラクタ
	explicit Siv3DGame();

	//デストラクタ
	~Siv3DGame();

	//ゲームタイトルの関数
	void TitleData();
	
	//ゲーム中の関数
	bool PlayData();

	//ゲーム終了の関数
	void EndData();
	
	//ボールスピードを変更する関数
	void setBallSpeed(double speed)
	{
		m_Speed = speed;
	}
	
	//ブロックの列数を変更する関数
	void setBlockRow(int row)
	{
		m_Row = row;
		//再度作成
		m_Block = BlockCreate(Size(40, 20));
	}

	//壊したブロックの数を返す関数
	int getScore() const throw()
	{
		return m_Score;
	}

	//クライアント情報を表示する関数
	void ShowInfo() const throw();

	//初期化
	void Initialize() throw()
	{
		m_Block = BlockCreate(Size(40, 20));
		m_Ball.setPos(Window::Center());
		m_Score = 0;
		m_BallSpeed = Vec2(0, -m_Speed);
	}

private:

	//アセットを登録する関数
	void AssetRegister() const throw();

	//ブロックを作成する関数
	Array<Rect> BlockCreate(Size blockSize) const throw();

	//ブロックを描画する関数
	void BlockDraw(Array<Rect>) const throw();

	//衝突を処理する関数
	bool Collition() throw();

	
	Stopwatch Timer;
	
	int m_Row;
	Rect m_Bar;
	Array<Rect> m_Block;
	Circle m_Ball;
	double m_Speed;
	Vec2 m_BallSpeed;
	int m_Score;

};


#endif
