#ifndef TIKZGENERATOR_H
#define TIKZGENERATOR_H

#include <QObject>
#include <QString>
#include <QList>

class CircuitCanvas;
class CircuitElement;

class TikzGenerator : public QObject
{
    Q_OBJECT

public:
    explicit TikzGenerator(QObject *parent = nullptr);
    
    QString generateFromCanvas(CircuitCanvas *canvas);
    QString generateHeader();
    QString generateFooter();

private:
    QString generateElementCode(CircuitElement *element);
    QString formatCoordinate(qreal x, qreal y);
    
    static constexpr qreal GRID_TO_TIKZ_SCALE = 0.05; // 20 pixels = 1 TikZ unit
};

#endif // TIKZGENERATOR_H
