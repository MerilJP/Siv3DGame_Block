#pragma once
#ifndef __Siv3DGame_h_
#define __Siv3DGame_h_
#include <Siv3D.hpp>

class Siv3DGame {

public :
	//�R���X�g���N�^
	explicit Siv3DGame();

	//�f�X�g���N�^
	~Siv3DGame();

	//�Q�[���^�C�g���̊֐�
	void TitleData();
	
	//�Q�[�����̊֐�
	bool PlayData();

	//�Q�[���I���̊֐�
	void EndData();
	
	//�{�[���X�s�[�h��ύX����֐�
	void setBallSpeed(double speed)
	{
		m_Speed = speed;
	}
	
	//�u���b�N�̗񐔂�ύX����֐�
	void setBlockRow(int row)
	{
		m_Row = row;
		//�ēx�쐬
		m_Block = BlockCreate(Size(40, 20));
	}

	//�󂵂��u���b�N�̐���Ԃ��֐�
	int getScore() const throw()
	{
		return m_Score;
	}

	//�N���C�A���g����\������֐�
	void ShowInfo() const throw();

	//������
	void Initialize() throw()
	{
		m_Block = BlockCreate(Size(40, 20));
		m_Ball.setPos(Window::Center());
		m_Score = 0;
		m_BallSpeed = Vec2(0, -m_Speed);
	}

private:

	//�A�Z�b�g��o�^����֐�
	void AssetRegister() const throw();

	//�u���b�N���쐬����֐�
	Array<Rect> BlockCreate(Size blockSize) const throw();

	//�u���b�N��`�悷��֐�
	void BlockDraw(Array<Rect>) const throw();

	//�Փ˂���������֐�
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
