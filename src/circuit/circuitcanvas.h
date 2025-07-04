#ifndef CIRCUITCANVAS_H
#define CIRCUITCANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QList>
#include "circuitelement.h"

class CircuitCanvas : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CircuitCanvas(QWidget *parent = nullptr);
    
    void setActiveElementType(ElementType type);
    void clearCircuit();
    QList<CircuitElement*> getElements() const { return elements; }

signals:
    void circuitChanged();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsScene *scene;
    ElementType activeElementType;
    bool hasActiveElement;
    QList<CircuitElement*> elements;
    
    void setupGrid();
    QPointF snapToGrid(const QPointF &point);
    
    static constexpr qreal GRID_SIZE = 20.0;
};

#endif // CIRCUITCANVAS_H
