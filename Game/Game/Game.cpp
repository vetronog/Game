#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "map.h"
#include "View.h"
#include <sstream>
#include <string>
#include "mission.h"
#include <iostream>

using namespace sf;
class Player
{ // класс Игрока
private:
	float x, y;
public:
	float w, h, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir, playerScore, health; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	bool life;//переменная жизнь, логическая
	Player(String F, float X, float Y, float W, float H)
	{ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		playerScore = 0;
		dy = 0;
		speed = 0;
		dir = 0;
		health = 100;
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}

		x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy*time;//аналогично по игреку

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();
		if (health <= 0) { life = false; speed = 0; }
	}

	float getplayercoordinateX() {	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY() {	//этим методом будем забирать координату Y 	
		return y;
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == 'b')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy>0)//если мы шли вниз,
					{
						y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy<0)
					{
						y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx>0)
					{
						x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//аналогично идем влево
					}
				}

				if (TileMap[i][j] == 's')
				{ //если символ равен 's' (камень)
					TileMap[i][j] = ' ';//убираем камень
					playerScore++;
				}
				if (TileMap[i][j] == 'f') 
				{
					health -= 40;//если взяли ядовитейший в мире цветок,то переменная health=health-40;
					TileMap[i][j] = ' ';//убрали цветок
				}

				if (TileMap[i][j] == 'h') 
				{
					health += 20;//если взяли сердечко,то переменная health=health+20;
					TileMap[i][j] = ' ';//убрали сердечко
				}
			}
	}
};

int main()
{
	RenderWindow window(VideoMode(1280, 720), "");
	view.reset(sf::FloatRect(0, 0, 1280, 720));//размер "вида" камеры при создании объекта вида камеры.
	Clock clock;
	float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
	clock.restart(); //перезагружает время
	//time = time; //скорость игры

	Font font;//шрифт 
	font.loadFromFile("resources/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый

	bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране
	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше


	float CurrentFrame = 0;//хранит текущий кадр

	Player hero("hero.png", 250, 250, 96.0, 96.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота
	
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	randomStoneMapGenerate();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab))
				{
					switch (showMissionText)
					{//переключатель, реагирующий на логическую переменную showMissionText
						case true:
						{	
							text.setString("Здоровье:" + std::to_string(hero.health) + "\n" + getTextMission(getCurrentMission(hero.getplayercoordinateX())));//задаем строку тексту и вызываем сформированную выше строку методом .str() 
							text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
						s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
							showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
							break;//выходим , чтобы не выполнить условие "false" (которое ниже)
						}
						case false:
						{
							text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
							showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
							break;
						}
					}
				}
		}
		if (hero.life)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left)) 
			{
				hero.dir = 1; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				hero.dir = 0; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) 
			{
				hero.dir = 3; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));// 
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) 
			{
				hero.dir = 2; hero.speed = 1.f;
				CurrentFrame += 0.025*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				hero.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			}
		}
		getplayercoordinateforview(hero.getplayercoordinateX(), hero.getplayercoordinateY());
		hero.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигать
		window.setView(view);
		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == 'b')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//и сердечко
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);//рисуем квадратики на экран
			}
		if (!showMissionText)
		{ 
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока			
			window.draw(s_quest);
			window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		}
		
		window.draw(hero.sprite);
		
		if (!hero.life)
		{
			text.setString("Игра окончена\n Ваши очки: " + std::to_string(hero.playerScore));//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(view.getCenter().x, view.getCenter().y);//задаем позицию текста, отступая от центра камеры
			window.draw(text);//рисую этот текст
		}
		window.draw(text);//рисую этот текст
		window.display();
	}
	return 0;
}