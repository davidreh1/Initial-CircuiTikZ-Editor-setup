#include "circuitelement.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

CircuitElement::CircuitElement(ElementType type, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , elementType(type)
    , elementLabel("")
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    
    switch (type) {
        case ElementType::Resistor:
            elementLabel = "R";
            break;
        case ElementType::Capacitor:
            elementLabel = "C";
            break;
        case ElementType::Inductor:
            elementLabel = "L";
            break;
        case ElementType::VoltageSource:
            elementLabel = "V";
            break;
        case ElementType::CurrentSource:
            elementLabel = "I";
            break;
        case ElementType::Ground:
            elementLabel = "GND";
            break;
        case ElementType::Node:
            elementLabel = "";
            break;
    }
}

QRectF CircuitElement::boundingRect() const
{
    return QRectF(-ELEMENT_WIDTH/2, -ELEMENT_HEIGHT/2, ELEMENT_WIDTH, ELEMENT_HEIGHT);
}

void CircuitElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    QPen pen(Qt::black, 2);
    if (isSelected()) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
    }
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    
    switch (elementType) {
        case ElementType::Resistor:
            drawResistor(painter);
            break;
        case ElementType::Capacitor:
            drawCapacitor(painter);
            break;
        case ElementType::Inductor:
            drawInductor(painter);
            break;
        case ElementType::VoltageSource:
            drawVoltageSource(painter);
            break;
        case ElementType::CurrentSource:
            drawCurrentSource(painter);
            break;
        case ElementType::Ground:
            drawGround(painter);
            break;
        case ElementType::Node:
            drawNode(painter);
            break;
    }
    
    if (!elementLabel.isEmpty()) {
        painter->setPen(Qt::black);
        QFont font = painter->font();
        font.setPointSize(8);
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, elementLabel);
    }
}

void CircuitElement::drawResistor(QPainter *painter)
{
    QPolygonF zigzag;
    qreal width = ELEMENT_WIDTH * 0.6;
    qreal height = ELEMENT_HEIGHT * 0.3;
    qreal step = width / 6;
    
    zigzag << QPointF(-width/2, 0);
    for (int i = 0; i < 6; ++i) {
        qreal x = -width/2 + i * step;
        qreal y = (i % 2 == 0) ? -height/2 : height/2;
        zigzag << QPointF(x, y);
    }
    zigzag << QPointF(width/2, 0);
    
    painter->drawPolyline(zigzag);
    
    painter->drawLine(-ELEMENT_WIDTH/2, 0, -width/2, 0);
    painter->drawLine(width/2, 0, ELEMENT_WIDTH/2, 0);
}

void CircuitElement::drawCapacitor(QPainter *painter)
{
    qreal gap = 4;
    qreal height = ELEMENT_HEIGHT * 0.6;
    
    painter->drawLine(-gap/2, -height/2, -gap/2, height/2);
    painter->drawLine(gap/2, -height/2, gap/2, height/2);
    
    painter->drawLine(-ELEMENT_WIDTH/2, 0, -gap/2, 0);
    painter->drawLine(gap/2, 0, ELEMENT_WIDTH/2, 0);
}

void CircuitElement::drawInductor(QPainter *painter)
{
    qreal width = ELEMENT_WIDTH * 0.6;
    qreal radius = width / 8;
    int coils = 4;
    
    for (int i = 0; i < coils; ++i) {
        qreal x = -width/2 + i * (width / coils);
        QRectF rect(x, -radius, width/coils, 2*radius);
        painter->drawArc(rect, 0, 180 * 16);
    }
    
    painter->drawLine(-ELEMENT_WIDTH/2, 0, -width/2, 0);
    painter->drawLine(width/2, 0, ELEMENT_WIDTH/2, 0);
}

void CircuitElement::drawVoltageSource(QPainter *painter)
{
    qreal radius = ELEMENT_HEIGHT * 0.4;
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);
    
    painter->setPen(QPen(Qt::black, 1));
    painter->drawLine(-radius/2, 0, radius/2, 0);
    painter->drawLine(0, -radius/2, 0, radius/2);
    painter->drawLine(-radius/4, 0, radius/4, 0);
    
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(-ELEMENT_WIDTH/2, 0, -radius, 0);
    painter->drawLine(radius, 0, ELEMENT_WIDTH/2, 0);
}

void CircuitElement::drawCurrentSource(QPainter *painter)
{
    qreal radius = ELEMENT_HEIGHT * 0.4;
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);
    
    painter->drawLine(-radius/2, 0, radius/2, 0);
    painter->drawLine(radius/4, -radius/4, radius/2, 0);
    painter->drawLine(radius/4, radius/4, radius/2, 0);
    
    painter->drawLine(-ELEMENT_WIDTH/2, 0, -radius, 0);
    painter->drawLine(radius, 0, ELEMENT_WIDTH/2, 0);
}

void CircuitElement::drawGround(QPainter *painter)
{
    qreal width = ELEMENT_WIDTH * 0.3;
    painter->drawLine(0, 0, 0, ELEMENT_HEIGHT/4);
    painter->drawLine(-width/2, ELEMENT_HEIGHT/4, width/2, ELEMENT_HEIGHT/4);
    painter->drawLine(-width/3, ELEMENT_HEIGHT/3, width/3, ELEMENT_HEIGHT/3);
    painter->drawLine(-width/6, ELEMENT_HEIGHT/2.5, width/6, ELEMENT_HEIGHT/2.5);
}

void CircuitElement::drawNode(QPainter *painter)
{
    qreal radius = 3;
    painter->setBrush(Qt::black);
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);
}

QString CircuitElement::getTikZCode() const
{
    QPointF pos = scenePos();
    qreal x = pos.x() / 20.0;
    qreal y = -pos.y() / 20.0;
    
    QString tikzElement;
    switch (elementType) {
        case ElementType::Resistor:
            tikzElement = QString("R, l=$%1$").arg(elementLabel);
            break;
        case ElementType::Capacitor:
            tikzElement = QString("C, l=$%1$").arg(elementLabel);
            break;
        case ElementType::Inductor:
            tikzElement = QString("L, l=$%1$").arg(elementLabel);
            break;
        case ElementType::VoltageSource:
            tikzElement = QString("V, l=$%1$").arg(elementLabel);
            break;
        case ElementType::CurrentSource:
            tikzElement = QString("I, l=$%1$").arg(elementLabel);
            break;
        case ElementType::Ground:
            return QString("\\node[ground] at (%1,%2) {};").arg(x).arg(y);
        case ElementType::Node:
            return QString("\\node[circ] at (%1,%2) {};").arg(x).arg(y);
    }
    
    return QString("(%1,%2) to[%3] ").arg(x).arg(y).arg(tikzElement);
}

QVariant CircuitElement::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        qreal gridSize = 20.0;
        qreal x = qRound(newPos.x() / gridSize) * gridSize;
        qreal y = qRound(newPos.y() / gridSize) * gridSize;
        return QPointF(x, y);
    }
    
    return QGraphicsItem::itemChange(change, value);
}
