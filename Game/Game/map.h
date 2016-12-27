#pragma once
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;//������ ����� ������
const int WIDTH_MAP = 40;//������ ����� ������ 


sf::String TileMap[HEIGHT_MAP] = {
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"b                                      b",
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
};

void randomStoneMapGenerate() {//�������� ����������� �����

	int randomElementX = 0;//��������� ������� �� �����������
	int randomElementY = 0;//���� ��-� �� ���������
	srand(time(0));//������	
	int countStone = 50;//���������� ������
	while (countStone>0) {
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if  (TileMap[randomElementY][randomElementX] == ' ')
		{//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 's'; //�� ������ ���� ������.
														   //std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
			countStone--;
		}
	}
}

void randomHeartMapGenerate() 
{//�������� ����������� �����
	int randomElementX = 0;//��������� ������� �� �����������
	int randomElementY = 0;//���� ��-� �� ���������
	srand(time(0));//������	
	int countHeart = 2;//���������� ������
	while (countHeart>0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if (TileMap[randomElementY][randomElementX] == ' ')
		{//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 'h'; //�� ������ ���� ������.
												   //std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
			countHeart--;
		}
	}
}