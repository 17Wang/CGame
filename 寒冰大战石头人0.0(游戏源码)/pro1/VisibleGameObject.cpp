#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
#include"VisibleGameObject.h"
#include"Game.h"
#include<cmath>


//===============VisibleGameObject 基类============================

VisibleGameObject::VisibleGameObject(float vec) {
	_isLoaded = false;
	_head = Up;
	_velocity = vec;
	_box = _sprite.getGlobalBounds();
}

VisibleGameObject::~VisibleGameObject() {

}

void VisibleGameObject::Load(std::string filename) {
	if (_texture.loadFromFile(filename) == false)
	{
		std::cout << "打开player失败" << std::endl;
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow &renderWindow) {
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
		//showBox(renderWindow);
	}
}

void VisibleGameObject::Update() {

}

void VisibleGameObject::SetPosition(float x, float y) {   //也设置物体的中心
	if (_isLoaded)
	{
		//_sprite.setScale(0.1f, 0.1f);
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::SetSize(float x, float y,bool z) {
	_sprite.setScale(x, y);
	if (z)
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width*(0.5 / x), _sprite.getGlobalBounds().height*(0.5 / y));
	}
}
	
void VisibleGameObject::SetOrigin() {
	_sprite.setOrigin(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}
void VisibleGameObject::RotAngle(float x) {
	_sprite.rotate(x);
}

void VisibleGameObject::SetVelocity(float x) {
	_velocity = x;
}

sf::Vector2f VisibleGameObject::GetPosition()const {
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite() {
	return _sprite;
}

sf::Texture &VisibleGameObject::GetTexture() {
	return _texture;
}

bool VisibleGameObject::IsLoaded()const {
	return _isLoaded;
}

float VisibleGameObject::GetVelocity() const {
	return _velocity;
}

//测试
/*void VisibleGameObject::showBox(sf::RenderWindow &window) {
	boundingBox = _sprite.getGlobalBounds();
	sf::RectangleShape rectangle(sf::Vector2f(boundingBox.width, boundingBox.height));
	rectangle.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
	rectangle.setFillColor(sf::Color(0, 0, 0, 0));
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(sf::Color::Red);
	window.draw(rectangle);

	sf::CircleShape shape(5);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(_sprite.getPosition());
	window.draw(shape);
}*/

sf::FloatRect VisibleGameObject::Get_box() {
	return _box;
}

float VisibleGameObject::get_Hp() const{
	return  _Hp;
}

void VisibleGameObject::update_Hp(float strength){
	_Hp -= strength;
}

float VisibleGameObject::getStrength() const {
	return _Strength;
}

void VisibleGameObject::setStrength(float strength) {
	_Strength = strength;
}

//==================================================================

//===============Player类===========================================

Player::Player(float vec,float Hp,float strength) {
	_Hp = Hp;
	_Strength = strength;
	_velocity = vec;

	_box = GetSprite().getGlobalBounds();

	can_move_ver=true;
	can_move_hor = true;

	if (!Hptexture.loadFromFile("./bin/血量纹理1.png"))
	{
		std::cout << "打开血量纹理失败" << std::endl;
	}

	is_U = false;
	is_draw_U = true;
	if (!U_t.loadFromFile("./bin/技能图标1.png"))
	{
		std::cout << "打开技能图标1失败" << std::endl;
	}
	U_s.setTexture(U_t);
	U_s.setPosition(660.0f,720.0f);

	is_O = false;
	is_draw_O = true;
	if (!O_t.loadFromFile("./bin/技能图标3.png"))
	{
		std::cout << "打开技能图标3失败" << std::endl;
	}
	O_s.setTexture(O_t);
	O_s.setPosition(360.0f, 720.0f);
}

Player::~Player() {

}

void Player::Draw(sf::RenderWindow &rw) {
	VisibleGameObject::Draw(rw);
	show_Hp(rw);
	if(is_draw_U)
		rw.draw(U_s);
	if (is_draw_O)
		rw.draw(O_s);
}

void Player::Update() {
	float xt = GetSprite().getPosition().x;
	float yt = GetSprite().getPosition().y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if ((GetSprite().getGlobalBounds().left) <= 0) can_move_hor = false;
		else can_move_hor = true;
		if (can_move_hor)
		{
			xt -= _velocity;
			SetPosition(xt, yt);
		}
		switch (_head)
		{
		case Up:RotAngle(-90); _head = Left; break;
		case Down:RotAngle(90); _head = Left; break;
		case Right:RotAngle(180); _head = Left; break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if ((GetSprite().getGlobalBounds().left+GetSprite().getGlobalBounds().width) >= Game::SCREEN_WIDTH) can_move_hor = false;
		else can_move_hor = true;
		if (can_move_hor)
		{
			xt += _velocity;
			SetPosition(xt, yt);
		}
		switch (_head)
		{
		case Up:RotAngle(90); _head = Right; break;
		case Down:RotAngle(-90); _head = Right; break;
		case Left:RotAngle(180); _head = Right; break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		
		if (GetSprite().getGlobalBounds().top <= 0)can_move_ver = false;
		else can_move_ver = true;
		if (can_move_ver)
		{
			yt -= _velocity;
			SetPosition(xt, yt);
		}
		switch (_head)
		{
		case Left:RotAngle(90);	_head = Up; break;
		case Right:RotAngle(-90);_head = Up; break;
		case Down:RotAngle(180); _head = Up; break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if ((GetSprite().getGlobalBounds().top+GetSprite().getGlobalBounds().height) >= Game::SCREEN_HEIGHT)can_move_ver = false;
		else can_move_ver = true;
		if (can_move_ver) 
		{
			yt += _velocity;
			SetPosition(xt, yt);
		}
		SetPosition(xt, yt);
		switch (_head)
		{
		case Left:RotAngle(-90); _head = Down; break;
		case Right:RotAngle(90); _head = Down; break;
		case Up:RotAngle(180); _head = Down; break;
		}

	}

	_box = GetSprite().getGlobalBounds();//每次更新完获取边框位置

	//std::cout << xt << " " << yt << std::endl;

}

void Player::show_Hp(sf::RenderWindow &rw) {
	if (_Hp>0.0f)
		_rectHp.setSize(sf::Vector2f(_Hp*0.5, 20));
	_rectHp.setPosition(sf::Vector2f(335, 680));
	//_rectHp.setOutlineThickness(2);
	_rectHp.setOutlineColor(sf::Color(255, 0, 0, 200));
	_rectHp.setTexture(&Hptexture);
	rw.draw(_rectHp);

	//判断血量，进入结算画面
}

void Player::skill_1(Bullet &p) {
	static int index = 120;//30一秒
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && !is_U && is_draw_U)
	{
		is_U = true;
		index = 0;
		is_draw_U = false;
	}

	if (is_U)
	{
		p.U_CD = 15;
		p.setStrength(p.getStrength() * 2);
	}
	else
	{
		p.U_CD = 30;
		p.setStrength(p.getStrength() / 2);
	}

	if (index >= 120)//技能持续时间
	{
		is_U = false;
	}
	if (index >= 270)//技能CD时间 270-120
	{
		is_draw_U = true;
	}

	index++;
	//std::cout << index << std::endl;
}

void Player::skill_2() {
	static int index = 0;
	float Long = 300.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && !is_O && is_draw_O)
	{
		is_O = true;
		index = 0;
		is_draw_O = false;
	}
	if (is_O)
	{
		switch (_head)
		{
		case Up:
			if (GetPosition().y >= Long)
				GetSprite().move(0, -Long);
			else
				GetSprite().move(0, -GetPosition().y);
			break;

		case Down:
			if (GetPosition().y <= Game::SCREEN_HEIGHT - Long)
				GetSprite().move(0, Long);
			else
				GetSprite().move(0, Game::SCREEN_HEIGHT - GetPosition().y);
			break;

		case Left:
			if (GetPosition().x >= Long)
				GetSprite().move(-Long, 0);
			else
				GetSprite().move(-GetPosition().x, 0);
			break;

		case Right:
			if (GetPosition().x <= Game::SCREEN_WIDTH - Long)
				GetSprite().move(Long, 0);
			else
				GetSprite().move(Game::SCREEN_WIDTH - GetPosition().x, 0);
		}
		is_O = false;
	}

	if (index >= 240)
	{
		is_draw_O = true;
	}

	index++;

	//std::cout << index << std::endl;
}

//==================================================================

//===============Enemy类============================================

Enemy::Enemy(float vec,float Hp,float strength) {
	_velocity = vec;
	_Hp = Hp;
	_Strength = strength;

	_box = GetSprite().getGlobalBounds();

	can_move = true;
	is_P_ed = false;
	_head = Up;
	_angle = 0;
	counts = 0;
	if (!temp_texture.loadFromFile("./bin/裂纹.png"))
	{
		std::cout << "打开裂纹失败" << std::endl;
	}
	if (!temp_texture2.loadFromFile("./bin/火焰旋涡.png")) 
	{
		std::cout << "打开火焰裂纹失败" << std::endl;
	}

	if (!Hptexture.loadFromFile("./bin/BOSS血量纹理.png"))
	{
		std::cout << "打开BOSS血量纹理失败" << std::endl;
	}

	is_Cir = false;//*********************************
	is_Cir2 = false;


	//======伤害
	skill_1_strength = 100.0f;
	skill_1_CD = 200;
	skill_2_CD = 240;

	//========音效
	if (!buffer_break.loadFromFile("./music/破碎.wav"))
	{
		std::cout << "打开破碎失败" << std::endl;
	}
	if (!buffer_rotate.loadFromFile("./music/旋转火焰.wav"))
	{
		std::cout << "打开旋转火焰失败" << std::endl;
	}
	sound_break.setBuffer(buffer_break);
	sound_rotate.setBuffer(buffer_rotate);
}

Enemy::~Enemy() {

}

float Enemy::get_angle() {
	return _angle;
}

void Enemy::Draw(sf::RenderWindow &rw) {
	
	if (is_Cir)
	{
		rw.draw(Cir);
	}
	if (is_Cir2)
	{
		rw.draw(Cir2);
	}
	VisibleGameObject::Draw(rw);
	show_Hp(rw);
}

void Enemy::Update(Player &p) {
	float xt = GetPosition().x;
	float yt = GetPosition().y;

	float target_x = p.GetPosition().x;
	float target_y = p.GetPosition().y;

	int random = rand() % 50 - 25;
	int temp = 50;

	static int _move = 0;
	int time1 = 6, time2 = 12, time3 = 18, time4 = 24;

	_angle = atan((target_y - yt) / (target_x - xt));
	_angle = _angle * 180 / 3.1415;

	if (can_move)
	{
		if (xt != target_x)
		{
			if (xt - target_x >= _velocity)
			{
				_head = Left;
				if ((_angle >= -1.0f && _angle <= 1.0f) || _angle >= 89.0f || _angle <= -89.0f)
				{
					GetSprite().move(-_velocity, 0);
				}
				else
				{
					GetSprite().move(-_velocity / sqrt(2), 0);
				}

			}
			if (xt - target_x <= -_velocity)
			{
				_head = Right;
				if ((_angle >= -1.0f && _angle <= 1.0f) || _angle >= 89.0f || _angle <= -89.0f)
				{
					GetSprite().move(_velocity, 0);
				}
				else
				{
					GetSprite().move(_velocity / sqrt(2), 0);
				}
			}
		}
		if (yt != target_y)
		{
			if (yt - target_y >= _velocity)
			{
				_head = Up;
				if ((_angle >= -1.0f && _angle <= 1.0f) || _angle >= 89.0f || _angle <= -89.0f)
				{
					GetSprite().move(0, -_velocity);
				}
				else
				{
					GetSprite().move(0, -_velocity / sqrt(2));
				}

			}
			if (yt - target_y <= -_velocity)
			{
				_head = Down;
				if ((_angle >= -1.0f && _angle <= 1.0f) || _angle >= 89.0f || _angle <= -89.0f)
				{
					GetSprite().move(0, _velocity);
				}
				else
				{
					GetSprite().move(0, _velocity / sqrt(2));
				}
			}
		}

		//==========判断方向加载不同方向的人物模型
		if (yt < target_y)
		{
			if (_move <= time1)
			{
				GetTexture().loadFromFile("./bin/石头_正面1.png");
			}
			if (_move <= time2&&_move > time1)
			{
				GetTexture().loadFromFile("./bin/石头_正面1.png");
			}
			if (_move <= time3 && _move > time2)
			{
				GetTexture().loadFromFile("./bin/石头_正面2.png");
			}
			if (_move <= time4 && _move > time3)
			{
				GetTexture().loadFromFile("./bin/石头_正面2.png");
			}
		}
		else
		{
			if (_move <= time1)
			{
				GetTexture().loadFromFile("./bin/石头_背面1.png");
			}
			if (_move <= time2 && _move > time1)
			{
				GetTexture().loadFromFile("./bin/石头_背面1.png");
			}
			if (_move <= time3 && _move > time2)
			{
				GetTexture().loadFromFile("./bin/石头_背面2.png");
			}
			if (_move <= time4 && _move > time3)
			{
				GetTexture().loadFromFile("./bin/石头_背面2.png");
			}
		}

		_move++;
		if (_move == time4 + 1)
		{
			_move = 0;
		}

		if (target_x - xt < 0)
		{
			GetSprite().setRotation(_angle - 90.0f);
		}
		else
		{
			GetSprite().setRotation(90.0f + _angle);
		}

	}
	else
	{
		if (yt < target_y)
		{
			if (Bullet::I_enemy)
				GetTexture().loadFromFile("./bin/石头_正面_冷冻.png");
			else
				GetTexture().loadFromFile("./bin/石头_正面.png");
		}
		else
		{
			if (Bullet::I_enemy)
				GetTexture().loadFromFile("./bin/石头_背面_冷冻.png");
			else
				GetTexture().loadFromFile("./bin/石头_背面.png");
		}
	}

	//============一定范围内不可重叠
	float det_x = target_x - xt;
	float det_y = target_y - yt;

	if (sqrt(det_x*det_x + det_y*det_y) <= 150.0f)
	{
		can_move = false;
	}
	else
	{
		can_move = true;
	}

	//==================技能条件

		//=====BOSS   技能1
	counts++;
	if (counts >= skill_1_CD)
	{
		is_P_ed = true;
		counts = 0;
	}
	if (is_P_ed)
	{
		skill_1(p);
	}
	//=====BOSS   技能2
	skill_2(p);
	//=====BOSS   技能3
	skill_3();

	_box = GetSprite().getGlobalBounds();//每次更新完获取边框位置


}

void Enemy::skill_1(Player &p) {
	//如果玩家I技能命中
	static int count = 0;
	if (!Bullet::if_I)
	{
		count++;
	}
	else
		return;

	static bool is_inside = true;//技能命中伤害只产生一次

	static int i = 0, index = 0;
	static sf::Vector2f size(0.6,0.6);
	static bool _judge = false;
	static int R_number, R_minus;

	static int R = 300;
	Cir.setRadius(R);
	Cir.setOrigin(R, R);
	//Cir.setOutlineThickness(2);
	//Cir.setOutlineColor(sf::Color::Black);
	Cir.setTexture(&temp_texture);


	if (!_judge)
	{
		R_number = rand() % 101 + 50;
		R_minus = rand() % 2;
		if (R_minus == 0)
		{
			R_number = -R_number;
		}
		_judge = true;
	}
	
	
	if (count <= 25)
	{
		_target.x = p.GetPosition().x;
		_target.y = p.GetPosition().y;
	}
	if (count < 50)//飞天
	{
		can_move = false;
		if (count >= 25 && size.x <= 1.0 && size.y <= 1.0)
		{
			size.x += 0.05f;
			size.y += 0.05f;
			SetSize(size.x, size.y,false);
			i++;
		}
	}
	else
	{
		if (_judge)
		{
			SetPosition(_target.x + R_number, _target.y + R_number);
			Cir.setPosition(_target.x + R_number, _target.y + R_number);
		}
		if (index <= i)//落地
		{
			size.x -= 0.05f;
			size.y -= 0.05f;
			SetSize(size.x, size.y, false);
			index++;
		}
		if (size.x<0.61)
		{
			if (sound_break.getStatus() != sound_break.Playing)
			{
				sound_break.play();
			}
			is_Cir = true;
			float dex = p.GetPosition().x - Cir.getPosition().x;
			float dey = p.GetPosition().y - Cir.getPosition().y;
			
			if (sqrt(dex*dex + dey*dey) <= R&&is_inside)//===========命中伤害加减速
			{
				is_inside = false;
				//std::cout << "技能1命中" << std::endl;
				p.update_Hp(skill_1_strength);
				p.SetVelocity(7.0f);//减速百分之30
			}
		}
		if (count==80)
		{
			can_move = true;
			is_Cir = false;
			is_P_ed = false;

			_judge = false;

			is_inside = true;
			p.SetVelocity(10.0f);//回复速度

			count = 0;
		}
	}
	
}

void Enemy::skill_2(Player &p) {
	static int count = 0;
	static int R = 250;
	Cir2.setRadius(R);
	Cir2.setOrigin(R, R);
	//Cir2.setOutlineThickness(2);
	//Cir2.setOutlineColor(sf::Color::Black);
	Cir2.setTexture(&temp_texture2);
	Cir2.setPosition(GetPosition().x, GetPosition().y);
	static float temp_angle=2.0f;
	Cir2.rotate(temp_angle);

	if (count <= skill_2_CD/3.0)
	{
		if (sound_rotate.getStatus() != sound_rotate.Playing)
		{
			sound_rotate.play();
		}
		is_Cir2 = true;
		Cir2.setPosition(GetPosition());
	}
	else
	{
		is_Cir2 = false;
	}
	if (count >= skill_2_CD)
	{
		count = 0;
	}


	float dex = p.GetPosition().x - GetPosition().x;
	float dey = p.GetPosition().y - GetPosition().y;

	//std::cout << GetPosition().x<<"　"<< GetPosition().y << std::endl;

	if (sqrt(dex*dex + dey*dey) <= R && is_Cir2)//===========命中伤害
	{
		//std::cout << "技能2命中" << std::endl;
		p.update_Hp(5.0f);
	}

	count++;
}

void Enemy::skill_3() {
	if (_Hp <= 333.3f)
	{
		SetVelocity(5.0f);
		skill_1_CD = 150.0f;
		skill_2_CD = 180.0f;
	}
}

void Enemy::show_Hp(sf::RenderWindow &rw) {
	if(_Hp>0.0f)
		_rectHp.setSize(sf::Vector2f(_Hp*0.8, 40));
	_rectHp.setPosition(sf::Vector2f(235, 40));
	//_rectHp.setOutlineThickness(2);
	//_rectHp.setOutlineColor(sf::Color(255, 0, 0, 200));
	_rectHp.setTexture(&Hptexture);
	rw.draw(_rectHp);

	//判断血量，进入结算画面
}

//================Bullet类===========================================

bool Bullet::if_I = false;
bool Bullet::I_enemy = false;
Bullet::Bullet(float vec) {
	_velocity = vec;
	if_Space = false;
	if_Fire = false;

	is_draw_I = false;
	if (!I_t.loadFromFile("./bin/技能图标2.png"))
	{
		std::cout << "打开技能图标1失败" << std::endl;
	}
	I_s.setTexture(I_t);
	I_s.setPosition(760.0f, 720.0f);



	count = 0;

	_head = Up;
	_box = GetSprite().getGlobalBounds();

	U_CD = 30;

	//==============音效
	if (!buffer_Space.loadFromFile("./music/空格.wav"))
	{
		std::cout << "打开空格音效失败" << std::endl;
	}
	if (!buffer_I.loadFromFile("./music/技能_I.wav"))
	{
		std::cout << "打开I音效失败" << std::endl;
	}
	if (!buffer_Fire.loadFromFile("./music/火焰.wav"))
	{
		std::cout << "打开火焰失败" << std::endl;
	}

	sound_Space.setBuffer(buffer_Space);
	sound_I.setBuffer(buffer_I);
	sound_Fire.setBuffer(buffer_Fire);
}

Bullet::~Bullet() {

}

void Bullet::Draw(sf::RenderWindow &rw) {
	if (if_draw_player())
	{
		//std::cout <<pos.x<< "shut"<<pos.y << std::endl;
		VisibleGameObject::Draw(rw);
	}
	if (if_draw_enemy())
	{
		VisibleGameObject::Draw(rw);
	}
	if (is_draw_I)
	{
		rw.draw(I_s);
	}
	if (if_I)
	{
		VisibleGameObject::Draw(rw);
	}
}

//=========对player类
void Bullet::Update(VisibleGameObject &p, VisibleGameObject &Enemy) {
	//elapsed_time = clock.getElapsedTime();
	count++;

	//std::cout << count << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!if_Space)
	{
		if_Space = true;
	}

	if (count <= U_CD)
	{
		if_Space = false;
	}

	if (if_Space)
	{
		if(sound_Space.getStatus() != sound_Space.Playing)
			sound_Space.play();
		switch (_head)
		{
		case Up:pos.y -= _velocity; GetSprite().setRotation(0); SetPosition(pos.x, pos.y); break;
		case Down:pos.y += _velocity; GetSprite().setRotation(180); SetPosition(pos.x, pos.y); break;
		case Left:pos.x -= _velocity; GetSprite().setRotation(-90); SetPosition(pos.x, pos.y); break;
		case Right:pos.x += _velocity; GetSprite().setRotation(90); SetPosition(pos.x, pos.y); break;
		}
		p.GetTexture().loadFromFile("./bin/寒冰2.png");
	}
	else if(!if_Space)
	{
		Set_initpos(p);
		_head = p._head;
		if (count > U_CD)
			p.GetTexture().loadFromFile("./bin/寒冰1.png");
	}

	_box = GetSprite().getGlobalBounds();//每次更新完获取边框位置

	if (Is_hit(Enemy)&&if_Space==true)
	{
		if_Space = false;
		count = 0;
		Enemy.update_Hp(p.getStrength());
	}

	//std::cout << elapsed1.asSeconds() << std::endl;
}
bool Bullet::if_draw_player() {
	if (if_Space)
	{
		if (GetPosition().x >= 0 && GetPosition().x<= Game::SCREEN_WIDTH
			&& GetPosition().y >= 0 && GetPosition().y<= Game::SCREEN_HEIGHT)
		{
			return true;
		}
		else
		{
			count = 0;
		}
	}

	if_Space = false;
	return false;
}

void Bullet::Set_initpos(VisibleGameObject &p) {
	pos.x=p.GetPosition().x;
	pos.y=p.GetPosition().y;
	//std::cout << pos.x << " " << pos.y << std::endl;
}
void Bullet::Set_velocity(float velocity) {
	_velocity = velocity;
}

bool Bullet::Is_hit(VisibleGameObject &p) {
	if (_box.intersects(p.Get_box()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Bullet::Update_I(VisibleGameObject &p, Enemy &Enemy) {
	count++;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && !if_I && is_draw_I)
	{
		if_I = true;
		count = 0;
		is_draw_I = false;
		sound_I.play();
	}

	if (if_I)
	{
		switch (_head)
		{
		case Up:pos.y -= _velocity; GetSprite().setRotation(0); SetPosition(pos.x, pos.y); break;
		case Down:pos.y += _velocity; GetSprite().setRotation(180); SetPosition(pos.x, pos.y); break;
		case Left:pos.x -= _velocity; GetSprite().setRotation(-90); SetPosition(pos.x, pos.y); break;
		case Right:pos.x += _velocity; GetSprite().setRotation(90); SetPosition(pos.x, pos.y); break;
		}
	}
	else
	{
		Set_initpos(p);
		_head = p._head;
	}

	if (count >= 120)//技能持续时间
	{
		if_I = false;
	}
	if (count >= 270)//技能CD时间 270-90
	{
		is_draw_I = true;
	}

	_box = GetSprite().getGlobalBounds();//每次更新完获取边框位置


	//===========判定命中\定住
	static int I_Last = 0;

	if (Is_hit(Enemy) && if_I == true)
	{
		Enemy.update_Hp(100.0f);
		if_I = false;
		I_enemy = true;
	}
	if (I_enemy)
	{
		I_Last++;
		Enemy.can_move = false;//====不能动
	}
	if (I_Last >= 60)
	{
		I_Last = 0;
		I_enemy = false;
		Enemy.can_move = true;
	}

}

//=========对enemy类
void Bullet::Update_Boss(Enemy &p, Player &Player) {

	static float target_x;
	static float target_y;

	static float xt;
	static float yt;
	
	float R = 500;
	count++;

	//std::cout << GetPosition().x << " " << GetPosition().y <<" "<<count<< std::endl;

	if (sqrt((xt - target_x)*(xt - target_x) + (yt - target_y)*(yt - target_y)) <= R-100 && count >= rand()%41+90)
	{
		if_Fire = true;
	}
	
	if (!if_Fire)
	{
		B_angle = p.get_angle();//获取BOSS的角度
		Set_initpos(p);
		SetPosition(pos.x, pos.y);

		target_x = Player.GetPosition().x;
		target_y = Player.GetPosition().y;

		xt = p.GetPosition().x;
		yt = p.GetPosition().y;

		
	}
	else
	{
		/*===========设置子弹角度
		if (target_x - xt < 0)
		{
			GetSprite().setRotation(B_angle - 90.0f);
		}
		else
		{
			GetSprite().setRotation(90.0f + B_angle);
		}*/
		if (sound_Fire.getStatus() != sound_Fire.Playing)
		{
			sound_Fire.play();
		}

		GetSprite().rotate(8.0f);

		//===========更新坐标
		if (xt - target_x >= _velocity)
		{
			_head = Left;
			if ((B_angle >= -1.0f && B_angle <= 1.0f) || B_angle >= 89.0f || B_angle <= -89.0f)
			{
				GetSprite().move(-_velocity, 0);
			}
			else
			{
				GetSprite().move(-_velocity / sqrt(2), 0);
			}

		}
		if (xt - target_x <= -_velocity)
		{
			_head = Right;
			if ((B_angle >= -1.0f && B_angle <= 1.0f) || B_angle >= 89.0f || B_angle <= -89.0f)
			{
				GetSprite().move(_velocity, 0);
			}
			else
			{
				GetSprite().move(_velocity / sqrt(2), 0);
			}
		}
		if (yt - target_y >= _velocity)
		{
			_head = Up;
			if ((B_angle >= -1.0f && B_angle <= 1.0f) || B_angle >= 89.0f || B_angle <= -89.0f)
			{
				GetSprite().move(0, -_velocity);
			}
			else
			{
				GetSprite().move(0, -_velocity / sqrt(2));
			}

		}
		if (yt - target_y <= -_velocity)
		{
			_head = Down;
			if ((B_angle >= -1.0f && B_angle <= 1.0f) || B_angle >= 89.0f || B_angle <= -89.0f)
			{
				GetSprite().move(0, _velocity);
			}
			else
			{
				GetSprite().move(0, _velocity / sqrt(2));
			}
		}
	}

	

	//============射程
	float det_x = GetPosition().x - xt;
	float det_y = GetPosition().y - yt;

	if (sqrt(det_x*det_x + det_y*det_y)>=R)
	{
		if_Fire = false;
		count = 0;
	}

	_box = GetSprite().getGlobalBounds();
	//============子弹命中判定
	if (Is_hit(Player) && if_Fire == true)
	{
		Player.update_Hp(10.0f);
		//std::cout << "命中" << "          " << Player.get_Hp() << std::endl;
	}
}
bool Bullet::if_draw_enemy() {
	if (if_Fire)
	{
		return true;
	}
	return false;
}