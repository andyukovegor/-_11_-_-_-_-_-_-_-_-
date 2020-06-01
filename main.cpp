#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>Ы
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "Graph.h" //класс вершин
#include "Link.h" //класс рёбер

using namespace sf;
using namespace std;



bool MouseOnNode(CircleShape &param,RenderWindow &window) { //функция отслеживания нажатия на узел графа
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	if ((mouseX > param.getPosition().x && mouseY > param.getPosition().y) && (mouseX < (param.getPosition().x + param.getGlobalBounds().width)) && (mouseY < (param.getPosition().y + param.getGlobalBounds().height))) {
		return true;
	} else {
		return false;
	}
}



int MAX(int k,int s,int *H,int *T,int*F,int M) { // функция определения максимального потока данных

	int tH = k, tT = s, tF = 0;

	if (k != s) {
		for (int i = 0; i < M; ++i) {
			if (H[i] == tH && T[i] == s) { return F[i]; }
		}

		for (int i = 0; i < M; ++i) {
			if (H[i] == tH) {
				tH = H[i]; tT = T[i];

				tF = F[i];

				cout << tH << " " << tT << " " << tF << endl;
				break;
			}
		}

		for (int j = 0; j < M; ++j) {

			for (int i = 0; i < M; ++i) {
				if (H[i] == tT && T[i] == s) {
					if (tF < F[i]) {
						return tF;
					}else{
						return F[i];
					}

				}
			}

			for (int i = 0; i < M; ++i) {
				if (H[i] == tT) {
					tH = H[i]; tT = T[i];

					if (F[i] < tF)
						tF = F[i];

					cout << tH << " " << tT << " " << tF << endl;
					break;
				}
			}

		}
		//return tF;
	} else {
		return -1;
	}
	cout << endl;
	return 0;
}



int main() {
	/*Считываем данные из фала о графе*/

	int N; //число вершин
	int M; //число рёбер

	string info; //переменная информации о топологии на экране

	ifstream f; //входной поток для считывания данных из file.txt
	f.open("file.txt"); //открываем поток
	f >> N; //считываем число вершин
	info += to_string(N) + " nodes\n\n";

	Graph* Graphs = new Graph[N]; //создаём N вершин

	for (int i = 0; i < N; i++) { //забиваем вершины данными
		Graphs[i].N = i + 1; //идентификатор вершины
		f >> Graphs[i].x; //коорд-ы
		f >> Graphs[i].y; //коорд-ы

		info += "(" + to_string(Graphs[i].N) + ") [" + to_string(Graphs[i].x) + ";" + to_string(Graphs[i].y) + "]\n";
	}

	f >> M; //считываем число рёбер
	info += "\n" + to_string(M) + " links\n\n";

	Link* Links = new Link[M]; //создаём M рёбер

	int A, B; //вспомогалка
	int *H = new int[M]; //для алгоритма
	int* T = new int[M];
	int* F = new int[M];

	for (int i = 0; i < M; i++) { //забиваем рёбра данными
		Links[i].M = i + 1; //идентификатор ребра

		f >> A; //начало ребра
		H[i] = A;
		A--; //корректировка
		Links[i].A = Graphs[A];

		f >> B; //конец ребра
		T[i] = B;
		B--; //корректировка
		Links[i].B = Graphs[B];

		f >> Links[i].F; //пропускная способность ребра
		F[i] = Links[i].F;

		info += "(" + to_string(Links[i].M) + ") [" + to_string(Graphs[A].N) + ";" + to_string(Graphs[B].N) + "] = " + to_string(Links[i].F) + "\n";
	}

	f.close(); //закрываем поток данных






	/*Текстовое поле для графов*/

	Font font; //переменная шрифта
	font.loadFromFile("arial.ttf"); //подгружаем шрифт из ресурсов

	Text infoText; //информация о топологии на экране
	infoText.setCharacterSize(12); //размер шрифта
	infoText.setFillColor(Color::White); //белый цвет текста
	infoText.setFont(font); //применяем подгруженный шрифт
	infoText.setPosition(20,20); //позиционируем объект на сцене
	infoText.setString(info); //задаём начальный текст

	Text istok; //информация об истоке
	istok.setCharacterSize(12);
	istok.setFillColor(Color::White);
	istok.setFont(font);
	istok.setPosition(190, 20);
	istok.setString("istok: ");

	Text stok; //информация о стоке
	stok.setCharacterSize(12);
	stok.setFillColor(Color::White);
	stok.setFont(font);
	stok.setPosition(190, 40);
	stok.setString("stok: ");

	Text answer;  //информация о максимальном потоке данных
	answer.setCharacterSize(12);
	answer.setFillColor(Color::White);
	answer.setFont(font);
	answer.setPosition(190, 60);
	answer.setString("Max flow: ");








	/* Создаем и рсуем узлы графа*/

	Graphs->GraphicNodes = new CircleShape[N]; //круг вершины
	Text* TextNodes = new Text[N]; //номера вершин

	for (int i = 0; i < N; i++) { //перебираем вершины
		Graphs->GraphicNodes[i].setFillColor(Color::Blue); //задаём цвет вершины
		Graphs->GraphicNodes[i].setRadius(10); //задаём радиус вершины
		Graphs->GraphicNodes[i].setPosition((Graphs[i].x * 12) + 500, (Graphs[i].y * 12)+ 150); //позиционирование вершины

		TextNodes[i].setCharacterSize(10);
		TextNodes[i].setFillColor(Color::White);
		TextNodes[i].setFont(font);
		TextNodes[i].setPosition((Graphs[i].x * 12) + 505, (Graphs[i].y * 12) + 153);
		TextNodes[i].setString(to_string(i+1));
	}


	/*Создаем и рсуем ребра графа */

	RectangleShape* GraphicLinks = new RectangleShape[M]; //прямоугольник для отрисовки ребра

	for (int i = 0; i < M; i++) { //перебираем рёбра
		GraphicLinks[i].setFillColor(Color::Yellow);
		float width = sqrtf(powf(Links[i].B.x - Links[i].A.x,2)+ powf(Links[i].B.y - Links[i].A.y, 2)) * 12; //вычисляем гипотенузу
		GraphicLinks[i].setSize(Vector2f(width-20, 4)); //задаём длину
		float katet = sqrtf(powf(Links[i].B.x - Links[i].A.x, 2) + powf(Links[i].A.y - Links[i].A.y, 2)) * 12; //длина катета
		float angle;
		if ((Links[i].B.x >= Links[i].A.x) && (Links[i].B.y >= Links[i].A.y)) { //4 координатные четверти
			angle = acosf(katet / width) * 180 / 3.14; //вычисляем угол
			GraphicLinks[i].rotate(angle); //задаём угол
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160); //позиционируем
		} else if ((Links[i].B.x <= Links[i].A.x) && (Links[i].B.y >= Links[i].A.y)) {
			angle = 180 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		} else if ((Links[i].B.x >= Links[i].A.x) && (Links[i].B.y <= Links[i].A.y)) {
			angle = 360 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		} else if ((Links[i].B.x <= Links[i].A.x) && (Links[i].B.y <= Links[i].A.y)) {
			angle = 270 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		}
	}





	/* Создаем и рисуем окно */

	RenderWindow window(VideoMode(900, 500), "GRAPHS", Style::Titlebar); //переменная окна, задаём размер и название окна
	int clicks = 0; //для выбора истока и стока
	int I_istok, I_stok; //текущий исток и сток

	while (window.isOpen()) { //пока окно открыта

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Delete)) {  //закрываем окно по Delete
				window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //проверяем нажатие на вершину
				Graph* clicableNode = NULL; //временная переменная
				for (int i = 0; i < N; ++i) {
					if (MouseOnNode(Graphs->GraphicNodes[i], window) && Graphs->GraphicNodes[i].getFillColor() == Color::Red) {
						Graphs->GraphicNodes[i].setFillColor(Color::Blue);
						clicableNode = &Graphs[i];
						if (clicks == 0) {
							istok.setString("istok: " + to_string(clicableNode->N)); //вбиваем исток
							I_istok = clicableNode->N;
						}else if (clicks == 1) {
							stok.setString("stok: " + to_string(clicableNode->N)); //вбиваем сток
							I_stok = clicableNode->N;
							clicks = -1;

							string s = "Max flow: " + to_string(MAX(I_istok,I_stok,H,T,F,M)); //вычисляем пропускную способность потока
							answer.setString(s);
						}
						++clicks;
					} else if(MouseOnNode(Graphs->GraphicNodes[i], window) && Graphs->GraphicNodes[i].getFillColor() == Color::Blue){ //повторное нажатие на активную вершину
						Graphs->GraphicNodes[i].setFillColor(Color::Red);
						istok.setString("istok: " + to_string(0));
						stok.setString("stok: " + to_string(0));
						answer.setString("Max flow: infinity");
					} else {
						Graphs->GraphicNodes[i].setFillColor(Color::Red);
					}
				}
			}
		}
		//отрисовываем всё

		window.clear(); //очищаем экран

		for (int i = 0; i < M; i++) { //отрисовываем линки
			window.draw(GraphicLinks[i]);
		}

		for (int i = 0; i < N; i++) { //отрисовываем графы
			window.draw(Graphs->GraphicNodes[i]);
			window.draw(TextNodes[i]);
		}

		window.draw(istok); //отрисовываем текст
		window.draw(stok);
		window.draw(infoText);
		window.draw(answer);

		window.display();
	}

	delete Graphs; //освобождаем динамически выделенную память
	delete Links;

	return 0;
}

