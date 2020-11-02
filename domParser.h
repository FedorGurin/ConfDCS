#ifndef DOMPARSER_H_
#define DOMPARSER_H_

#include <QDomElement>
#include <QDomDocument>
#include <QObject>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <functional>
#include "Node.h"
#include "pinNode.h"
#include "unitNode.h"

class DomParser : public QObject {

public:

    //! поля таблицы с описанием расположения систем и блоков
    enum{
        E_GEO_FULL  ,
        E_GEO_SHORT ,
        E_GEO_STEND ,
        E_GEO_INSTALL,
        E_GEO_TRANSIT,
        E_GEO_ID    ,
        E_GEO_LOCATION,
        E_GEO_PARENT_SYS, // родительская система
        E_GEO_SIZE  ,
        E_GEO_POS,
        E_GEO_CLASS, //! класс объекта
        E_GEO_ALIAS,
        E_GEO_NAME_COORD //! имя жгута
    };
    typedef  struct TGeometry_
    {
        //! полное имя системы
        QString fullName;
        //! короткое имя системы
        QString shortName;
        //! признак того, что данный модуль входит в стендовый комлект
        bool isStend;
        //! идентификатор системы
        QString id;
        //! родительский блок
        QString parent;
        //! габариты
        QString size;
        //! координаты блока
        QString coord;
    }TGeometry;
    enum {
        E_NAME                  = 0,   //! имя сигнала
        E_UNIT_NAME                ,   //! имя блока
        //E_ID_SYSTEM                ,   //! идентификатор системы
        E_ID_UNIT                  ,   //! идентификатор блока
        E_CONNECTOR                ,   //! идентификатор разъема
        E_PIN                      ,   //! идентификатор контакта
        E_MULT                     ,   //! кол-во размножений
        E_IO                       ,   //! каналы входа/выхода
        E_LABEL                    ,   //! имя бирки
        E_SW                       ,   //! сигнал должен быть пропущен через коммутацию
        E_TYPE_I                   ,   //! тип интерфейса
        E_TYPE_CONNECTOR_BLOCK     ,   //! тип разъема со стороны блока
        E_TYPE_CONNECTOR_WIRE      ,   //! тип разъема со стороны жгута
        E_TYPE_WIRE                ,   //! тип провода
        E_TYPE_WIRE_PIN            ,   //! тип жилы провода
        E_ID_WIRE                  ,   //! идентификатор провода
        E_CURCUIT                  ,   //! имя схемы
        E_SET_TYPE_I               ,   //! идентификатор интерфейса
        E_CORD                         //! имя жгута
    };
    enum EDirection
    {
        E_UP,
        E_DOWN
    };
    enum EPropertySaveToGV
    {
        E_WIRES,
        E_INTERFACES,
        E_CORDS
    };

    DomParser(QObject *parent = nullptr);

    //! загрузка из
    void loadData(QString dir, EPropertySaveToGV type);

    //! загрузка протоколов информационного взаимодействия (PIC)
    void loadDataPIC(QString dir);

    void pasteUnitBetween(Node *unitFrom, QList<Node* > unitTransit, Node *unitTo );
    //! вставить блок через список блоков
    void pasteUnitThrough(Node *unitFrom, QList<Node* > unitTransit,QVector<PinNode::TYPE_INTERFACE> listInterfaces);

    //! поиск узла по типу
    Node* findNodeByType(Node* node, Node::Type t, EDirection dir);
    Node* findNodeByIdName(QString nameItem, Node *node, Node::Type t=Node::E_EMPTY);
    Node* recFindNodeWithIdName(QString &idName,Node *startNode, Node::Type t=Node::E_EMPTY);
    //! дерево с описательной частью данных
    Node *dataNodes;

    //! корень для дерева с всех данных описанием данных
    Node* rootItemData;
    //! сохранение в файл соединений
    void saveCSVCon(Node *startNode, QTextStream& out);
    void recSaveCSVCoords(Node *startNode, QTextStream& out);
    void saveCoordToFile(Node *unitNode);

    //! список деревьев для каждого файла
    QList<Node* > listRootItemNode;
    QList<Node* > listRootUnit;
    QList<TGeometry> listGeo;
    void fillGeometryUnit(Node* root);

    //! вернуть указатель на корень для дерева с описанием данных
    //Node* rootNodeData(){return rootItemData;}

    void recFindWire(Node *startNode, Node *rootNode);
    void recFindWireWithout(Node *without, Node *startNode);
    void saveForGraphviz(QString namePath, QString nameFile, Node* rootNode, std::function<void(DomParser&,Node *, QTextStream&)> funcSave);
    void saveCSVConnection(Node* rootNode, QTextStream&);
    void saveCSVCoords(Node* rootNode, QTextStream&);

    void saveForGraphvizForNode(QString nameFile, Node* rootNode);
    void saveForGraphvizForNode(QString nameFile, Node* rootNode,Node* rootNode2);
    //! сохранение данных в один файл для в внешнюю БД
    void saveDataToCVS(QString nameFile, Node* rootNode,std::function<void(DomParser&, Node*, QTextStream&)>);
    void saveAllInfo( Node* rootNode, QTextStream& out);
    void saveAllUnit( Node* rootNode, QTextStream& out);
    void recSaveAllUnit(Node* rootNode, QTextStream& out);
    bool checkConnectionUnit(Node* sampleNode, Node *node);
    //! получить список пинов которые соединяют блок checkForUnit c Unit1
    QList<Node* > findConnectionPins(Node* unit1, Node* checkForUnit);
    void saveWires(Node *startNode, QTextStream& out);
    void saveInterface(Node *startNode, QTextStream& out);

    void saveSubGraph(Node *unit,Node* con,QList<Node* > listPin, QTextStream& out);

    QList<Node* > selectConnector( QList<Node* > listPin);
    void saveNeighborsToGV(Node* rootNode, QList<Node* > listUnit, QTextStream& out);
    void saveNeighborsToGV(Node* rootNode, Node* rootNode2, QTextStream& out);
    void saveDataBase();
    //! Показать список соединений между двумя группой блоков
    //! ..соединения внутри в рамках одной группы игнорируются
    void showConnectionBetween(QString group1, QString group2);
    //! деструктор
    virtual ~DomParser();
private:
    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(QString line, Node *parent);//рекурсивная
    void parseLocation(QString line, Node *parent);

    void recSaveLocationBetween(Node* rootNode, QTextStream&, QString filter);
    //! открыть XML файл с описанием данных
    bool openFileDesData(const QString&,QList<Node* > &list,std::function<void(DomParser&, QString,Node*)>);
    void recFindConnectedUnit(Node* node, QList<Node* > &listUnit);
    //! подсоединение проводов
    bool connectWires(Node* rootNode);
    //! объединение деревьев
    void mergeNodes(Node *root,Node* from);
    void grabberNodeByType(Node *root,Node::Type t,QList<Node* > &list);
    bool checkAvalibleLinkLeft(Node *wire, Node *toPin);
    //! заполнение информацией о расположении блоков

    void recFillGeometry(Node* node, TGeometry geo);
    void checkConnectionInterfaces(Node *startNode);
    //! сохранение в CVS
    void saveToCVS(Node *startNode, QTextStream& out,QVector<QString> *str);

    void saveNode(Node *startNode, QTextStream& out);
    void saveNodeWiresGW(Node *startNode, QTextStream& out);
    void saveNodeInterfaceGW(Node *startNode, QTextStream& out);
    void saveNodeVarWithNe(Node *startNode, QTextStream& out);
    void saveGraphConnector(Node *startNode, QTextStream& out);
    void saveGraphWire(Node *startNode, QTextStream& out);
    //! коррекция имен бирок
    void correctWire(Node *startNode);
    //! коррекция имен проводов
    void correctInterface(Node *startNode);
    void joingInterface(Node *startNode);
    //! коррекция имен жгутов
    void correctCoords(Node* startNode);
    void calcNumInterface(Node *startNode);
    //! засгрузить описание внтуренних подлкючений
    void loadInternalConnection(void);
    void parseInCon(UnitNode *);
    //! найти блоки которые ссылаются на указанный, или данный блок на них
    void findNeighborUnit(Node* unitNode,QList<Node*> &listNode);
    //! найти список проводов выходящих в другие контейнеры(например все првода выходящие из кабины)
    void saveConnectionLocations(Node *root,QString loacation1);
    QProcess procDot;
    QFile fileLog;
    QTextStream outLog;
//   ! Соединение двух деревьев(дерево с данными и с вариантами)
//    void joiningTrees(GenericNode*,VariantNode*);// Стыковка двух деревьев

//    //! Соединение двух деревьев(дерево с вариантами состояния и с вариантами программных модулей)
//    void joiningVariantsTrees(VariantNode* variantNodes,VariantState *variantState);// рекурсивная
};

#endif /* DOMPARSER_H_ */
