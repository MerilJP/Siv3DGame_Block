#include "Siv3DGame.h"

//�R���X�g���N�^
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

//�f�X�g���N�^
Siv3DGame::~Siv3DGame()
{
}

////�N���C�A���g����\������֐�
void Siv3DGame::ShowInfo() const throw()
{
	FontAsset(L"STATUS")(L"FPS : ", Profiler::FPS(),
		L" \nTIMER : ", Timer.ms(), L"ms\n",
		L"ver : Alpha\n").draw();
}

//�A�Z�b�g��o�^����֐�
void Siv3DGame::AssetRegister() const throw()
{
	FontAsset::Register(L"STATUS", 10, Typeface::Default);

	FontAsset::Register(L"DEFAULT", 30, Typeface::Default);

	FontAsset::Register(L"END", 30, Typeface::Default);
}

//�Q�[���^�C�g���̊֐�
void Siv3DGame::TitleData() 
{

	Initialize();
	FontAsset(L"DEFAULT")(L"�u���b�N����").drawCenter(Window::Center().x, 100);
	FontAsset(L"DEFAULT")(L"[Enter]�ŃX�^�[�g").drawCenter(Window::Center().x, Window::Height() - 100);

}

//�Q�[�����̊֐�
bool Siv3DGame::PlayData()
{
	bool ret = true;

	//�u���b�N��`��
	BlockDraw(m_Block);

	//�o�[�̈ړ�
	m_Bar.setCenter(Mouse::Pos().x, 420);

	//�{�[�����ړ�
	m_Ball.moveBy(m_BallSpeed);

	//�Փˏ���
	if (Collition() == false)
	{
		ret = false;
	}

	//�{�[����`��
	m_Ball.draw();

	//�o�[��`��
	m_Bar.draw();

	return ret;
}

//�Q�[���I���̊֐�
void Siv3DGame::EndData()
{
	
	FontAsset(L"DEFAULT")(L"�Q�[���I��").drawCenter(Window::Center().x, 100);
	FontAsset(L"DEFAULT")(L"���_ : ",m_Score).drawCenter(Window::Center());
	FontAsset(L"DEFAULT")(L"[Enter]�Ń^�C�g���ɖ߂�").drawCenter(Window::Center().x,Window::Height() - 100);
}

//�u���b�N���쐬����֐� //���� ��,����
Array<Rect> Siv3DGame::BlockCreate(const Size blockSize) const throw()
{
	Array<Rect> blocks;

	for (auto p : step({ Window::Width() / blockSize.x , m_Row }))
	{
		blocks.emplace_back((p*blockSize).moveBy(0, 60), blockSize);
	}

	return blocks;
}

//�u���b�N��`�悷��֐� //���� Array<Rect>�^ �u���b�N
void Siv3DGame::BlockDraw(Array<Rect> blocks) const throw()
{
	for (auto const& block : blocks)
	{
		block.stretched(-1).draw(HSV(30));
	}
}

//�Փ˂���������֐�
bool Siv3DGame::Collition() throw()
{
	bool ret = true;

	// �o�[�ɓ�����Ɣ���
	if (m_BallSpeed.y > 0 && m_Bar.intersects(m_Ball))
	{
		m_BallSpeed = Vec2((m_Ball.x - m_Bar.center.x) / 8, -m_BallSpeed.y).setLength(m_Speed);
	}


	for (auto it = m_Block.begin(); it != m_Block.end(); ++it)
	{
		// �o�[�ƃ{�[�����������Ă�����
		if (it->intersects(m_Ball))
		{
			// �㉺�ɏՓ˂��Ă����� y ����, ����ȊO�� x �����̑��x�𔽓]
			(it->bottom.intersects(m_Ball) || it->top.intersects(m_Ball)
				? m_BallSpeed.y : m_BallSpeed.x) *= -1;

			// �Փ˂����u���b�N���폜
			m_Block.erase(it);
			
			//���_�����Z
			m_Score++;

			//�u���b�N���S�ĂȂ����false��Ԃ�
			if (m_Block.empty())
			{
				ret = false;
			}

			// �Փ˂����炱��ȏ�͔��肵�Ȃ�
			break;
		}
	}

	// �V��&�ǂɂ�����Ɣ���
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