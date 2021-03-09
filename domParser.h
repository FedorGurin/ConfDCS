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

    //! Поля таблицы с описанием расположения систем и блоков
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
    //! Свойства блока полученные из спецификации
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
    typedef  struct TTransitRecord_
    {
        QString nameSys1;
        QStringList nameTr;
        QStringList namesSys2;
    }TTransitRecord;
    enum {
        E_NAME                  = 0,   /*!< Enum имя сигнала                                      */
        E_UNIT_NAME                ,   /*!< Enum имя блока                                        */
        E_ID_UNIT                  ,   /*!< Enum идентификатор блока                              */
        E_CONNECTOR                ,   /*!< Enum идентификатор разъема                            */
        E_PIN                      ,   /*!< Enum идентификатор контакта                           */
        E_MULT                     ,   /*!< Enum кол-во размножений                               */
        E_IO                       ,   /*!< Enum каналы входа/выхода                              */
        E_LABEL                    ,   /*!< Enum имя бирки                                        */
        E_SW                       ,   /*!< Enum сигнал должен быть пропущен через коммутацию     */
        E_TYPE_I                   ,   /*!< Enum тип интерфейса                                   */
        E_TYPE_CONNECTOR_BLOCK     ,   /*!< Enum тип разъема со стороны блока                     */
        E_TYPE_CONNECTOR_WIRE      ,   /*!< Enum тип разъема со стороны жгута                     */
        E_TYPE_WIRE                ,   /*!< Enum тип провода                                      */
        E_TYPE_WIRE_PIN            ,   /*!< Enum тип жилы провода                                 */
        E_ID_WIRE                  ,   /*!< Enum идентификатор провода                            */
        E_CURCUIT                  ,   /*!< Enum имя схемы                                        */
        E_SET_TYPE_I               ,   /*!< Enum идентификатор интерфейса                         */
        E_CORD                         /*!< Enum имя жгута                                        */
    };
    //! Направление поиска в древовидной структуре
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
    void loadData(QString dir, EPropertySaveToGV type,bool isAutoGraph = false);

    //! загрузка протоколов информационного взаимодействия (PIC)
    void loadDataPIC(QString dir);
    void loadTransitFile(QString nameDir);

    /*! Вставить транзитные системы между блоками unitFrom_ и unitTo_
     * \param unitFrom - 1ая система
     * \param unitTo_ - 2ая система
     * \param unitTransit - список систем через которые будут проходит линии соединения
     * \param listInterfaces - список интерфейсов которые будут проходить через системы
    */
    void pasteUnitBetween(Node *unitFrom,
                          QList<Node* > unitTransit,
                          QList<Node *> unitTo,
                          QVector<PinNode::TYPE_INTERFACE> listInterfaces );
    //! Проверка того, что контакты комплементарны
    //! \param pin1 - 1 сравнивемый контакт
    //! \param pin2 - 2ой сравниваемый контакт
    //! \return true - если контакты комплементарны, false - если нет
    bool checkInOutPins(PinNode *pin1,PinNode *pin2);

    Node* tracePinToFindFreePin(Node* pin,
                                Node *prevNode = nullptr,
                                Node *fPin = nullptr,
                                QVector<QPair<PinNode *, PinNode * > > *table = nullptr);

    //! вставить блок через список блоков
    void pasteUnitThrough(Node *unitFrom, QList<Node* > unitTransit,QVector<PinNode::TYPE_INTERFACE> listInterfaces);
    //! подключение к блокам
    void connectToUnits(Node *unitFrom_,   QList<Node* > unitTransit);

    QString findLength(Node* idSys1,Node *idSys2);
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
    void saveCoordToFile(Node *unitNode = nullptr);
    void saveTransform(QString sys1,QString sys2,QVector<PinNode::TYPE_INTERFACE> listInterfaces);

    void updateCoords();
    bool hasPinInListWires(Node *pin,QList<Node *> &wireNode);
    //! список деревьев для каждого файла
    QList<Node* > listRootItemNode;
    QList<Node* > listRootUnit;
    QList<TGeometry> listGeo;
    void fillGeometryUnit(Node* root);

    //! вернуть указатель на корень для дерева с описанием данных
    //Node* rootNodeData(){return rootItemData;}
    QString mergeString(QString &value1,QString &value2);
    void recFindWire(Node *startNode, Node *rootNode);
    void recFindWireWithout(Node *without, Node *startNode);
    void saveForGraphviz(QString namePath, QString nameFile, Node* rootNode, std::function<void(DomParser&,Node *, QTextStream&)> funcSave);
    void saveCSVConnection(Node* rootNode, QTextStream&);
    void saveCSVCoords(Node* rootNode, QTextStream&);
    void saveRP(Node* rootNode, QTextStream&);
    void saveRP_BD(Node* rootNode, QTextStream&);
    void saveRP_BD_Title(Node* rootNode, QTextStream&);

    //! создание перечислений
    void genEnum_title(Node* rootNode, QTextStream& out);
    void genChEnum(Node* rootNode, QTextStream& out);
    void saveChEnum();
    //! создание описаний каналов
    void saveCh();
    void genCh(Node* rootNode, QTextStream& out);

    //! создание описаний каналов
    void savePackEnum();
    void saveParamEnum();
    void savePack();
    void saveParam();
    void savePackingCode();

    void genParamTable(Node* rootNode, QTextStream& out);
    void genPackEnum(Node* rootNode, QTextStream& out);
    void genPackEnum_title(Node* rootNode, QTextStream& out);
    void genParamEnum_title(Node* rootNode, QTextStream& out);
    void genParamEnum(Node* rootNode, QTextStream& out, QStringList &listStr);
    void genPackTable(Node* rootNode, QTextStream& out);
    //! генерация кода для каждой модели
    void genPackingCode(Node* rootNode, QTextStream& out);

    void saveForGraphvizForNode(QString nameFile, Node* rootNode);
    void saveForGraphvizForCoords(QString nameFile, Node* rootNode);
    void saveForGraphvizForNode(QString nameFile, Node* rootNode,Node* rootNode2);
    //! сохранение данных в один файл для в внешнюю БД
    void saveDataToCVS(QString nameFile, Node* rootNode,std::function<void(DomParser&, Node*, QTextStream&)>, QString strCodec = "UTF-8");
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
    //! подрекурсия для сохранения жгутов в формате Graphviz
    void saveCoordsToGV(Node* rootNode, Node* rootNode2, QTextStream& out);
    void saveDataBase();
    void saveForRP();
    //! Показать список соединений между двумя группой блоков
    //! ..соединения внутри в рамках одной группы игнорируются
    void showConnectionBetween(QString group1, QString group2);
    //! деструктор
    virtual ~DomParser();
    QVector<QStringList> vecTransform;
    QVector<QPair<QString,QString> > vecAlias;
    QVector<QStringList> vecLength;

    QList<TTransitRecord> listTransitFromFile;
    //! поиск проблем в данных
    void searchProblems();
 QTextStream outLog;
 struct TPackCode
 {
     QStringList enumStr;
     QStringList codeStr;
 }packCode;

private:
    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(QString line, Node *parent);//рекурсивная
    void parseLocation(QString line, Node *parent);
    //! зачитать файл с трансформациями
    void parseTransData(QString line, Node *parent = nullptr);
    void parseAlias(QString line, Node *parent = nullptr);
    void findLength(QString idSys1,QString idSys2);
    void parseLength(QString line, Node *parent = nullptr);

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
    bool hasConnectThrough(WireNode* wire,QList<Node*> unitTransit);
    bool hasFullConnected(PinNode *pin);
    void traceWiresFromPin(Node *pin, Node* sampleUnit, QList<Node *> &curUnit,QList<Node *> *prohibSys=nullptr);
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
    void clearCoords(Node* startNode);
    void renameCoords(Node* startNode);
    void calcNumInterface(Node *startNode);
    //! засгрузить описание внтуренних подлкючений
    void loadInternalConnection(void);
    //! разбор файла с внутренними соединиями
    void parseInCon(UnitNode *);
    //! найти блоки которые ссылаются на указанный, или данный блок на них
    void findNeighborUnit(Node* unitNode,QList<Node*> &listNode);
    //! найти все уникальные жгуты в блоках unitNode
    void findAllCoordsUnit(Node* unitNode, QList<CoordNode* > &listCoords);
    //! найти список проводов выходящих в другие контейнеры(например все првода выходящие из кабины)
    void saveConnectionLocations(Node *root,QString loacation1);
    bool checkInListCoords(CoordNode *i,QList<CoordNode*> &listCoords);
    QProcess procDot;
    QFile fileLog;

    int indexEnum;

    //QFile fileTransform;
    //QTextStream outTransform;
//   ! Соединение двух деревьев(дерево с данными и с вариантами)
//    void joiningTrees(GenericNode*,VariantNode*);// Стыковка двух деревьев

//    //! Соединение двух деревьев(дерево с вариантами состояния и с вариантами программных модулей)
//    void joiningVariantsTrees(VariantNode* variantNodes,VariantState *variantState);// рекурсивная
};

#endif /* DOMPARSER_H_ */
