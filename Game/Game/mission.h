#pragma once
int getCurrentMission(int x)//�-��� ������ ������, ������� ������ ����� ������, � ����������� �� ���������� ������ � (���� ����� ���������� ��� ����������)
{
	int mission = 0;
	if ((x>0) && (x<600)) { mission = 0; } //�������� ������ � �����
	if (x>400) { mission = 1; } //����� �� ������ ������
	if (x>700) { mission = 2; }//2��
	if (x>2200) { mission = 3; }//� ��

	return mission;//�-��� ���������� ����� ������
}
std::string getTextMission(int currentMission) {

	std::string missionText = "";//����� ������ � ��� �������������
	missionText = "\n �� ������ ����\n �����\n � �������� ������";
	return missionText;//�-��� ���������� �����
};