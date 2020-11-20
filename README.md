# GenMELCON
**Генератор модели электрических подключений (ГенМЭП):**

**Общее описание**

На базе уже существующих электрических схем,
генератор создает описание всей системы "в целом" для анализа построенной модели.

**Исходные данные**

Для построения модели электрических подключений:
- электрические схемы (в форматах dwg).
- база данных с электрическими элементами(разъемы, провода и т.д).
- таблица с функциональными элементами с описанием дополнительных атрибутов.
  - взаимное геометрическое расположение объектов.
  - идентификаторы объектов.
  - иерархические соотношения типа "родитель-потомок".

**Требования:**

ГенМЭП не должен вносить изменения в исходные данные. Исходные данные описывают конфигурацию объекта испытаний.
Должна быть возможность сравнения структуры сгенеренной для стенда и структуры с объектом испытаний.

**Обработка данных**

Обработка таблиц с электрическими соединениями состоит из следующих этапов:

- разбор строк таблиц, создание объектов и создание иерархии для каждой конкретной таблицы.
  - этап подключения проводов. Для каждого таблицы происходит связывание клемм на основании уникальных имен бирок.
  - этап корректировки интерфейсов для каждой таблицы.
  - этап корректировки названий бирок проводов. Предполагает, что бирка состоит из: "Имя_Система"-"Имя_разъема"-"Имя_клеммы", где символ "-" разделитель, а имя не должно содержать данный символ.
- этап объединения таблиц между собой. Этот этап необходим из-за того, что многие чертежи имеют дублирования и описывают соединения блоков между собой. Для этого и нужно максимально собрать воедино всю различающуюся информацию и устранить дублирования описаний.
- этап корректировки интерфейсов для всей системы в целом.
- этап подключения проводов между всеми блоками стенда.
- этап заполнения параметров "расположения" (шкаф1, шкаф 2, кабина и т.д), а так же признак стендового комплекта.
- этап проверки соединения интерфейсов (ARINC429, RK)
- этап сохранения данных в формате GraphViz
- этап сохранения всех соединений в файл.

**__Структура директорий__**

Исходные данные хранятся в директории csv и имеют следующую структуру:

 - **curcuit**  - директория с исходными файлами на объекта
 - **transform** - директория с файлом траснформации исходных данных с данными parsed
 - **parsed** - директория с уже обработанными данными на основе файлов из директории curcuit
   - **base** - директория c результирующими данными.
   - **export** - директория с файлами для загрузки в систему Андрея.
 - **spec**  - директория с спецификацией объектов которые входят в curcuit и parsed.
 - **libs** - директория с динамическими библиотеками для симуляции поведения сложных объектов.
 -  **report** - директория с файлами отчетами об ошибках.


**Графический интерфейс**

Должен при запуске:

- указывать какие данные загружать из curcuit или base.

**Поддерживаемые функции**

- сохранение всех соединений между системами в файл (функция saveConnectionLocations).
- генерация графа только для стендового комплекта.
- учет длины жгута.

**Экспорт данных**

Для загрузки в инструментальную среду "Арена", требуется сформировать след. файлы:
- сохранение всех соединений в файл wires.cvs.

**Анализ модели подключения данных**

- анализ совпадения типов интерфейсов (Arinc429, РК, аналоговые сигналы...) основываясь на всех представленных электрических схемах.
- анализ совпадения сечений и типов проводов, а так же допустимых сечений разъемов.
- анализ, что клеммы к одним и тем же системам совпадают на всех схемах(нет конфликтов).


**Редактор модели подключений:**  

Редактор должен позволять разрывать связи между блоками через функциональные элементы:
 - проходные разъемы.
 - коммутаторы сигналов.
 - клеммные колодки.

Иметь возможность выбора перечень блоков которые нужно пустить через переходные разъемы.
Формирование жгутов.

Каждому объекту может соответствовать внутренняя функция, которая может быть даже оформлена в виде dll.

При пропуске линий через проходной разъем пользователь должен выбрать список систем или список проводов 
или список интерфейсов которые необходимо пропустить через проходные разъемы. 
Проходные разъемы должны иметь соответствие между своими входными клеммами и выходными клеммами. 

Алгоритм вставки между системой1(sys1) и системой1(sys2):

1 Сбор всех контактов от sys1 в список.
2 Собираем только те провода, которые связывают Sys1 с sys2
3 Сбор всех контактов от транзитных систем
4 После шага 3 оставялем только свободные контакты транзитных систем
5 Основная фаза 
