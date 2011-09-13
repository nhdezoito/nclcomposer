#ifndef QNSTVIEW_H
#define QNSTVIEW_H

#include "QGraphicsView"
#include "QVector"
#include "QMap"

#include "qnstscene.h"

#include <QWheelEvent>

class QnstView : public QGraphicsView
{
    Q_OBJECT

public:
    QnstView(QWidget* parent = 0);

    ~QnstView();



public slots:
    QString addEntity(const QString parentUID,
                      const QMap<QString, QString> attributes);

    void removeEntity(const QString entityUID);

    void changeEntity(const QString entityUID,
                      const QString parentUID,
                      const QMap<QString, QString> attributes);

    void selectEntity(const QString entityUID);

    void requestEntityAddition(QnstEntity* e);

    void requestEntitySelection(QnstEntity* e);

signals:
    void entitySelected(const QString entityUID);

    void bodyAdded(const QString entityUID,
                   const QString parentUID,
                   const QMap<QString, QString> attributes);

    void contextAdded(const QString entityUID,
                      const QString parentUID,
                      const QMap<QString, QString> attributes);

    void mediaAdded(const QString entityUID,
                    const QString parentUID,
                    const QMap<QString, QString> attributes);

    void switchAdded(const QString entityUID,
                     const QString parentUID,
                     const QMap<QString, QString> attributes);

    void portAdded(const QString entityUID,
                     const QString parentUID,
                     const QMap<QString, QString> attributes);

    void areaAdded(const QString entityUID,
                     const QString parentUID,
                     const QMap<QString, QString> attributes);

    void propertyAdded(const QString entityUID,
                     const QString parentUID,
                     const QMap<QString, QString> attributes);

    void linkAdded(const QString entityUID,
                     const QString parentUID,
                     const QMap<QString, QString> attributes);


//protected:
//    void wheelEvent( QWheelEvent * event );

private:
    void createConnection();

    QnstScene* scene;

    QncgEntity* selectedEntity;

    QMap<QString, QnstEntity*> entities;

    int media_count;
    int link_count;
    int context_count;
    int switch_count;
    int port_count;
    int area_count;
    int property_count;

};

#endif // QNSTVIEW_H