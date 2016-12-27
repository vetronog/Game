#pragma once
int getCurrentMission(int x)//ф-ция номера миссия, которая меняет номер миссии, в зависимости от координаты игрока Х (сюда будем передавать эту координату)
{
	int mission = 0;
	if ((x>0) && (x<600)) { mission = 0; } //знакомим игрока с игрой
	if (x>400) { mission = 1; } //игрок на первой миссии
	if (x>700) { mission = 2; }//2ой
	if (x>2200) { mission = 3; }//и тд

	return mission;//ф-ция возвращает номер миссии
}
std::string getTextMission(int currentMission) {

	std::string missionText = "";//текст миссии и его инициализация
	missionText = "\n Вы должны есть\n кошек\n и избегать врагов";
	return missionText;//ф-ция возвращает текст
};