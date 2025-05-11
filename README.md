# MIPT_Programming_project
## My and my neighbor's game "Cosmotopia"

### Цель проекта:
Создать пошаговую стратегию.

<table>
<tr>
<td style="color: gray; border: none;">
#### <span style="color:#808080">*Инструкция сборки:
##### <span style="color:#808080">На машине с установленной библиотекой SFML 3.0.0 (3.1.0)
#####   &nbsp;&nbsp;&nbsp;&nbsp;1. Скопировать репозиторий;
#####   &nbsp;&nbsp;&nbsp;&nbsp;2. Перейти в папку Source (или Source_for_SFML3.1.0);
#####   &nbsp;&nbsp;&nbsp;&nbsp;3. Исполнить команды:
#####       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;g++ *.cpp -o sfml_app -lsfml-graphics -lsfml-window -lsfml-system
#####       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;./sfml_app
</td> </tr> </table>

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