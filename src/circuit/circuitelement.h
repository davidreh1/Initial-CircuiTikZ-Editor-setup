#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QString>
#include <QPointF>

enum class ElementType {
    Resistor,
    Capacitor,
    Inductor,
    VoltageSource,
    CurrentSource,
    Ground,
    Node
};

class CircuitElement : public QGraphicsItem
{
public:
    CircuitElement(ElementType type, QGraphicsItem *parent = nullptr);
    
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    
    ElementType getType() const { return elementType; }
    QString getTikZCode() const;
    void setLabel(const QString &label) { elementLabel = label; }
    QString getLabel() const { return elementLabel; }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    ElementType elementType;
    QString elementLabel;
    static constexpr qreal ELEMENT_WIDTH = 60.0;
    static constexpr qreal ELEMENT_HEIGHT = 30.0;
    
    // Drawing methods for different elements
    void drawResistor(QPainter *painter);
    void drawCapacitor(QPainter *painter);
    void drawInductor(QPainter *painter);
    void drawVoltageSource(QPainter *painter);
    void drawCurrentSource(QPainter *painter);
    void drawGround(QPainter *painter);
    void drawNode(QPainter *painter);
};

#endif // CIRCUITELEMENT_H
