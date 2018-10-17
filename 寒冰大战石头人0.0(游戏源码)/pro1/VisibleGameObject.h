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
	//==============测试
	//void showBox(sf::RenderWindow &rw);

	sf::Texture &GetTexture();

	sf::FloatRect Get_box();//获取边框
	float getStrength() const;//获取当前攻击力
	void setStrength(float strength);//设置当前攻击力
	float get_Hp() const;//获取当前血量
	void update_Hp(float strength=20.0f);//更新血量

protected:

	sf::Sprite &GetSprite();
	//==============速度
	float _velocity;
	//==============血量
	float _Hp;
	sf::RectangleShape _rectHp;
	sf::Texture Hptexture;
	//==============攻击力
	float _Strength;
	//==============边框
	sf::FloatRect _box;
	
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;

	//=====测试
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

	//=======音效
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

	void Update(VisibleGameObject &p, VisibleGameObject &Enemy);//=======更新属于玩家的子弹
	void Update_Boss(Enemy &p, Player &Player);//========更新属于BOSS的技能
	void Update_I(VisibleGameObject &p, Enemy &Enemy);//=======更新属于玩家的技能子弹

	void Draw(sf::RenderWindow &rw);

	bool if_draw_player();
	bool if_draw_enemy();

	void Set_initpos(VisibleGameObject&);
	void Set_velocity(float velocity);

	bool if_Space;//玩家空格操控
	static bool if_I;//技能I
	static bool I_enemy;
	bool if_Fire;//BOSS第二个技能释放条件

	bool Is_hit(VisibleGameObject &);

	int CD;

	int U_CD;//玩家的攻速 30一秒一发
private:
	int count;

	bool is_draw_I;
	int I_CD;//技能I的CD
	sf::Sprite I_s;
	sf::Texture I_t;

	sf::Vector2f pos;
	float B_angle;

	//=========音效
	sf::SoundBuffer buffer_Space;
	sf::SoundBuffer buffer_I;
	sf::Sound sound_Space;
	sf::Sound sound_I;

	sf::SoundBuffer buffer_Fire;
	sf::Sound sound_Fire;
};

#endif // !VISIBLEGAMEOBJECT


