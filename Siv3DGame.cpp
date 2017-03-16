#include "Siv3DGame.h"

//コンストラクタ
Siv3DGame::Siv3DGame() : Timer(true)
					, m_Ball(320, 400, 8)
					, m_Speed(8.0)
					, m_BallSpeed(0,-m_Speed)
					, m_Bar(60,10)
					, m_Row(5)
					, m_Score(0)
{
	AssetRegister();
	Initialize();
}

//デストラクタ
Siv3DGame::~Siv3DGame()
{
}

////クライアント情報を表示する関数
void Siv3DGame::ShowInfo() const throw()
{
	FontAsset(L"STATUS")(L"FPS : ", Profiler::FPS(),
		L" \nTIMER : ", Timer.ms(), L"ms\n",
		L"ver : Alpha\n").draw();
}

//アセットを登録する関数
void Siv3DGame::AssetRegister() const throw()
{
	FontAsset::Register(L"STATUS", 10, Typeface::Default);

	FontAsset::Register(L"DEFAULT", 30, Typeface::Default);

	FontAsset::Register(L"END", 30, Typeface::Default);
}

//ゲームタイトルの関数
void Siv3DGame::TitleData() 
{

	Initialize();
	FontAsset(L"DEFAULT")(L"ブロック崩し").drawCenter(Window::Center().x, 100);
	FontAsset(L"DEFAULT")(L"[Enter]でスタート").drawCenter(Window::Center().x, Window::Height() - 100);

}

//ゲーム中の関数
bool Siv3DGame::PlayData()
{
	bool ret = true;

	//ブロックを描画
	BlockDraw(m_Block);

	//バーの移動
	m_Bar.setCenter(Mouse::Pos().x, 420);

	//ボールを移動
	m_Ball.moveBy(m_BallSpeed);

	//衝突処理
	if (Collition() == false)
	{
		ret = false;
	}

	//ボールを描画
	m_Ball.draw();

	//バーを描画
	m_Bar.draw();

	return ret;
}

//ゲーム終了の関数
void Siv3DGame::EndData()
{
	
	FontAsset(L"DEFAULT")(L"ゲーム終了").drawCenter(Window::Center().x, 100);
	FontAsset(L"DEFAULT")(L"得点 : ",m_Score).drawCenter(Window::Center());
	FontAsset(L"DEFAULT")(L"[Enter]でタイトルに戻る").drawCenter(Window::Center().x,Window::Height() - 100);
}

//ブロックを作成する関数 //引数 幅,高さ
Array<Rect> Siv3DGame::BlockCreate(const Size blockSize) const throw()
{
	Array<Rect> blocks;

	for (auto p : step({ Window::Width() / blockSize.x , m_Row }))
	{
		blocks.emplace_back((p*blockSize).moveBy(0, 60), blockSize);
	}

	return blocks;
}

//ブロックを描画する関数 //引数 Array<Rect>型 ブロック
void Siv3DGame::BlockDraw(Array<Rect> blocks) const throw()
{
	for (auto const& block : blocks)
	{
		block.stretched(-1).draw(HSV(30));
	}
}

//衝突を処理する関数
bool Siv3DGame::Collition() throw()
{
	bool ret = true;

	// バーに当たると反射
	if (m_BallSpeed.y > 0 && m_Bar.intersects(m_Ball))
	{
		m_BallSpeed = Vec2((m_Ball.x - m_Bar.center.x) / 8, -m_BallSpeed.y).setLength(m_Speed);
	}


	for (auto it = m_Block.begin(); it != m_Block.end(); ++it)
	{
		// バーとボールが交差していたら
		if (it->intersects(m_Ball))
		{
			// 上下に衝突していたら y 方向, それ以外は x 方向の速度を反転
			(it->bottom.intersects(m_Ball) || it->top.intersects(m_Ball)
				? m_BallSpeed.y : m_BallSpeed.x) *= -1;

			// 衝突したブロックを削除
			m_Block.erase(it);
			
			//得点を加算
			m_Score++;

			//ブロックが全てなければfalseを返す
			if (m_Block.empty())
			{
				ret = false;
			}

			// 衝突したらこれ以上は判定しない
			break;
		}
	}

	// 天井&壁にあたると反射
	if (m_Ball.y < 0 && m_BallSpeed.y <  0)
	{
		m_BallSpeed.y *= -1;
	}else if ((m_Ball.x < 0 && m_BallSpeed.x < 0) || (Window::Width() < m_Ball.x && m_BallSpeed.x > 0))
	{
		m_BallSpeed.x *= -1;
	}else if (m_Ball.y > Window::Height())
	{
		ret = false;
	}


	return ret;
}