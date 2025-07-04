#include "circuitcanvas.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include <cmath>

CircuitCanvas::CircuitCanvas(QWidget *parent)
    : QGraphicsView(parent)
    , scene(nullptr)
    , activeElementType(ElementType::Resistor)
    , hasActiveElement(false)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    setScene(scene);
    
    setDragMode(QGraphicsView::RubberBandDrag);
    setRenderHint(QPainter::Antialiasing);
    
    setupGrid();
}

void CircuitCanvas::setActiveElementType(ElementType type)
{
    activeElementType = type;
    hasActiveElement = true;
    setCursor(Qt::CrossCursor);
}

void CircuitCanvas::clearCircuit()
{
    for (auto element : elements) {
        scene->removeItem(element);
        delete element;
    }
    elements.clear();
    
    scene->clear();
    setupGrid();
    
    emit circuitChanged();
}

void CircuitCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && hasActiveElement) {
        QPointF scenePos = mapToScene(event->pos());
        QPointF gridPos = snapToGrid(scenePos);
        
        CircuitElement *element = new CircuitElement(activeElementType);
        element->setPos(gridPos);
        element->setFlag(QGraphicsItem::ItemIsMovable);
        element->setFlag(QGraphicsItem::ItemIsSelectable);
        
        scene->addItem(element);
        elements.append(element);
        
        hasActiveElement = false;
        setCursor(Qt::ArrowCursor);
        
        emit circuitChanged();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void CircuitCanvas::wheelEvent(QWheelEvent *event)
{
    const double scaleFactor = 1.15;
    
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void CircuitCanvas::setupGrid()
{
    QPen gridPen(Qt::lightGray, 0.5, Qt::DotLine);
    
    for (int x = -1000; x <= 1000; x += GRID_SIZE) {
        scene->addLine(x, -1000, x, 1000, gridPen);
    }
    
    for (int y = -1000; y <= 1000; y += GRID_SIZE) {
        scene->addLine(-1000, y, 1000, y, gridPen);
    }
    
    QPen originPen(Qt::red, 2);
    scene->addLine(-10, 0, 10, 0, originPen);
    scene->addLine(0, -10, 0, 10, originPen);
}

QPointF CircuitCanvas::snapToGrid(const QPointF &point)
{
    qreal x = std::round(point.x() / GRID_SIZE) * GRID_SIZE;
    qreal y = std::round(point.y() / GRID_SIZE) * GRID_SIZE;
    return QPointF(x, y);
}
