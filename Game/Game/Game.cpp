#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "map.h"
#include "View.h"
#include <sstream>
#include <string>

using namespace sf;
class Player
{ // ����� ������
private:
	float x, y;
public:
	float w, h, dx, dy, speed; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir, playerScore, health; //����������� (direction) �������� ������
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	bool life;//���������� �����, ����������
	Player(String F, float X, float Y, float W, float H)
	{ //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		playerScore = 0;
		dy = 0;
		speed = 0;
		dir = 0;
		health = 100;
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59));//������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
	}

	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		y += dy*time;//���������� �� ������

		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
		interactionWithMap();
		if (health <= 0) { life = false; speed = 0; }
	}

	float getplayercoordinateX() {	//���� ������� ����� �������� ���������� �	
		return x;
	}
	float getplayercoordinateY() {	//���� ������� ����� �������� ���������� Y 	
		return y;
	}

	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 32; j<(x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == 'b')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0)//���� �� ��� ����,
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy<0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx>0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}

				if (TileMap[i][j] == 's')
				{ //���� ������ ����� 's' (������)
					TileMap[i][j] = ' ';//������� ������
					playerScore++;
				}
				if (TileMap[i][j] == 'f') 
				{
					health -= 40;//���� ����� ����������� � ���� ������,�� ���������� health=health-40;
					TileMap[i][j] = ' ';//������ ������
				}

				if (TileMap[i][j] == 'h') 
				{
					health += 20;//���� ����� ��������,�� ���������� health=health+20;
					TileMap[i][j] = ' ';//������ ��������
				}
			}
	}
};

int main()
{
	RenderWindow window(VideoMode(1280, 720), "");
	view.reset(sf::FloatRect(0, 0, 1280, 720));//������ "����" ������ ��� �������� ������� ���� ������.
	Clock clock;
	float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
	clock.restart(); //������������� �����
	//time = time; //�������� ����

	Font font;//����� 
	font.loadFromFile("resources/CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	float CurrentFrame = 0;//������ ������� ����

	Player hero("hero.png", 250, 250, 96.0, 96.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������
	
	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (hero.life)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				hero.dir = 1; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));

			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				hero.dir = 0; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				hero.dir = 3; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));// 
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				hero.dir = 2; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));

			}
		}
		getplayercoordinateforview(hero.getplayercoordinateX(), hero.getplayercoordinateY());
		hero.update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� �������
		window.setView(view);
		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == 'b')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//�������� ������
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//� ��������
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);//������ ���������� �� �����
			}
		text.setString("��������:" + std::to_string(hero.health));//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//������ ������� ������, �������� �� ������ ������
		window.draw(hero.sprite);
		if (!hero.life)
		{
			text.setString("���� ��������\n ���� ����: " + std::to_string(hero.playerScore));//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
			text.setPosition(view.getCenter().x, view.getCenter().y);//������ ������� ������, �������� �� ������ ������
			window.draw(text);//����� ���� �����
		}
		window.draw(text);//����� ���� �����
		window.display();
	}
	return 0;
}