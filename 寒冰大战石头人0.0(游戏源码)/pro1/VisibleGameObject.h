#pragma once

#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>

#ifndef VISIBLEGAMEOBJECT
#define VISIBLEGAMEOBJECT


class VisibleGameObject
{

public:
	VisibleGameObject(float vec = 2.0f);
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Update();

	void SetPosition(float x, float y);
	void SetSize(float x, float y,bool z);
	void SetOrigin();
	void RotAngle(float x);
	void SetVelocity(float x);

	sf::Vector2f GetPosition() const;
	bool IsLoaded() const;

	float GetVelocity() const;

	enum Head
	{
		Up, Up_Right, Up_Left,
		Down, Down_Right, Down_Left,
		Left,Right
	};
	Head _head;
	//==============����
	//void showBox(sf::RenderWindow &rw);

	sf::Texture &GetTexture();

	sf::FloatRect Get_box();//��ȡ�߿�
	float getStrength() const;//��ȡ��ǰ������
	void setStrength(float strength);//���õ�ǰ������
	float get_Hp() const;//��ȡ��ǰѪ��
	void update_Hp(float strength=20.0f);//����Ѫ��

protected:

	sf::Sprite &GetSprite();
	//==============�ٶ�
	float _velocity;
	//==============Ѫ��
	float _Hp;
	sf::RectangleShape _rectHp;
	sf::Texture Hptexture;
	//==============������
	float _Strength;
	//==============�߿�
	sf::FloatRect _box;
	
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;

	//=====����
	sf::FloatRect boundingBox;
};


class Bullet;

class Player :public VisibleGameObject
{
public:
	Player(float vec = 10.0f, float Hp=1000.0f, float strength=20.f);
	~Player();

	void Update();
	void Draw(sf::RenderWindow &rw);

	void  show_Hp(sf::RenderWindow &rw);

	void skill_1(Bullet &p);
	void skill_2();

private:
	bool can_move_ver;
	bool can_move_hor;

	bool is_U;
	bool is_draw_U;
	sf::Sprite U_s;
	sf::Texture U_t;

	bool is_O;
	bool is_draw_O;
	sf::Sprite O_s;
	sf::Texture O_t;

};


class Enemy :public VisibleGameObject
{
public:
	Enemy(float vec = 3.0f, float Hp = 1000.0f, float strength = 1.0f);
	~Enemy();

	void Update(Player &p);
	void Draw(sf::RenderWindow &rw);

	void skill_1(Player &p);
	void skill_2(Player &p);
	void skill_3();

	void show_Hp(sf::RenderWindow &rw);

	float get_angle();

	bool can_move;
private:

	bool is_P_ed;
	sf::Vector2f _target;

	int counts;

	float _angle;

	sf::CircleShape Cir;
	sf::Texture temp_texture;
	bool is_Cir;

	sf::CircleShape Cir2;
	sf::Texture temp_texture2;
	bool is_Cir2;


	float skill_1_strength;
	int skill_1_CD;
	int skill_2_CD;

	//=======��Ч
	sf::SoundBuffer buffer_break;
	sf::SoundBuffer buffer_rotate;

	sf::Sound sound_break;
	sf::Sound sound_rotate;
};


class Bullet :public VisibleGameObject
{
public:
	Bullet(float vec = 50.0f);
	~Bullet();

	void Update(VisibleGameObject &p, VisibleGameObject &Enemy);//=======����������ҵ��ӵ�
	void Update_Boss(Enemy &p, Player &Player);//========��������BOSS�ļ���
	void Update_I(VisibleGameObject &p, Enemy &Enemy);//=======����������ҵļ����ӵ�

	void Draw(sf::RenderWindow &rw);

	bool if_draw_player();
	bool if_draw_enemy();

	void Set_initpos(VisibleGameObject&);
	void Set_velocity(float velocity);

	bool if_Space;//��ҿո�ٿ�
	static bool if_I;//����I
	static bool I_enemy;
	bool if_Fire;//BOSS�ڶ��������ͷ�����

	bool Is_hit(VisibleGameObject &);

	int CD;

	int U_CD;//��ҵĹ��� 30һ��һ��
private:
	int count;

	bool is_draw_I;
	int I_CD;//����I��CD
	sf::Sprite I_s;
	sf::Texture I_t;

	sf::Vector2f pos;
	float B_angle;

	//=========��Ч
	sf::SoundBuffer buffer_Space;
	sf::SoundBuffer buffer_I;
	sf::Sound sound_Space;
	sf::Sound sound_I;

	sf::SoundBuffer buffer_Fire;
	sf::Sound sound_Fire;
};

#endif // !VISIBLEGAMEOBJECT


