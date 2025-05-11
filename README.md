# MIPT_Programming_project
## My and my neighbor's game "Cosmotopia"

### Цель проекта:
Создать пошаговую стратегию.

#### <span style="color:#808080">*Инструкция сборки:</span>
##### <span style="color:#808080">На машине с установленной библиотекой SFML 3.0.0 (3.1.0)</span>
#####   &nbsp;&nbsp;&nbsp;&nbsp;<span style="color:#808080">1. Скопировать репозиторий;</span>
#####   &nbsp;&nbsp;&nbsp;&nbsp;<span style="color:#808080">2. Перейти в папку Source (или Source_for_SFML3.1.0);</span>
#####   &nbsp;&nbsp;&nbsp;&nbsp;<span style="color:#808080">3. Исполнить команды:</span>
#####       &nbsp;&nbsp;&nbsp;&nbsp;<span style="color:#808080">g++ *.cpp -o sfml_app -lsfml-graphics -lsfml-window -lsfml-system</span>
#####       &nbsp;&nbsp;&nbsp;&nbsp;<span style="color:#808080">./sfml_app .</span>

### Этапы разработки:
Этап 1: Отрисовка карты.
![Отрисовка карты.](/Images/EmptyMap.png)

Этап 2: Реализация случайной генерации, масштабирования карты и перемещения камеры.
![Отрисовка карты.](/Images/ScaleMap.png)
[Смотреть видео](/Images/ScaleMap.mp4) 

Этап 3: Создание класса объектов и стандартизация уже созданных.
![Отрисовка карты.](/Images/Buildings.png)
[Смотреть видео](/Images/Buildings.mp4) 

Этап 4: Полная переработка обработки нажатия. (Все реализации перенесены в класс Map)
![Отрисовка карты.](/Images/Barracks.png)

Этап 5: Внедрение новых сущностей и их взаимодействие с окружением.
![Отрисовка карты.](/Images/Units.png)

Этап 6: Добавление пользовательского интерфейса.
![Отрисовка карты.](/Images/UI.png)

Этап 7: Мелкие правки и завершение обработки пользовательского ввода.
![Отрисовка карты.](/Images/USER.png)

Этап 8: Реализация игры 2ух игроков.
![Отрисовка карты.](/Images/2ndUser.png)