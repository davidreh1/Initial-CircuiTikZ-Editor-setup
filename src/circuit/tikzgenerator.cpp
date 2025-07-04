#include "tikzgenerator.h"
#include "circuitcanvas.h"
#include "circuitelement.h"
#include <QTextStream>

TikzGenerator::TikzGenerator(QObject *parent)
    : QObject(parent)
{
}

QString TikzGenerator::generateFromCanvas(CircuitCanvas *canvas)
{
    if (!canvas) {
        return generateHeader() + "\n" + generateFooter();
    }
    
    QString tikzCode;
    QTextStream stream(&tikzCode);
    
    stream << generateHeader() << "\n";
    
    QList<CircuitElement*> elements = canvas->getElements();
    
    if (elements.isEmpty()) {
        stream << "% No elements in circuit\n";
    } else {
        stream << "% Circuit elements\n";
        
        QList<CircuitElement*> resistors, capacitors, inductors, sources, nodes, grounds;
        
        for (auto element : elements) {
            switch (element->getType()) {
                case ElementType::Resistor:
                    resistors.append(element);
                    break;
                case ElementType::Capacitor:
                    capacitors.append(element);
                    break;
                case ElementType::Inductor:
                    inductors.append(element);
                    break;
                case ElementType::VoltageSource:
                case ElementType::CurrentSource:
                    sources.append(element);
                    break;
                case ElementType::Node:
                    nodes.append(element);
                    break;
                case ElementType::Ground:
                    grounds.append(element);
                    break;
            }
        }
        
        if (!resistors.isEmpty()) {
            stream << "% Resistors\n";
            for (auto resistor : resistors) {
                stream << generateElementCode(resistor) << "\n";
            }
            stream << "\n";
        }
        
        if (!capacitors.isEmpty()) {
            stream << "% Capacitors\n";
            for (auto capacitor : capacitors) {
                stream << generateElementCode(capacitor) << "\n";
            }
            stream << "\n";
        }
        
        if (!inductors.isEmpty()) {
            stream << "% Inductors\n";
            for (auto inductor : inductors) {
                stream << generateElementCode(inductor) << "\n";
            }
            stream << "\n";
        }
        
        if (!sources.isEmpty()) {
            stream << "% Sources\n";
            for (auto source : sources) {
                stream << generateElementCode(source) << "\n";
            }
            stream << "\n";
        }
        
        if (!nodes.isEmpty()) {
            stream << "% Nodes\n";
            for (auto node : nodes) {
                stream << generateElementCode(node) << "\n";
            }
            stream << "\n";
        }
        
        if (!grounds.isEmpty()) {
            stream << "% Ground connections\n";
            for (auto ground : grounds) {
                stream << generateElementCode(ground) << "\n";
            }
            stream << "\n";
        }
        
        if (elements.size() > 1) {
            stream << "% Example connections (manually adjust as needed)\n";
            stream << "% \\draw (0,0) to[R, l=$R_1$] (2,0) to[C, l=$C_1$] (4,0);\n";
        }
    }
    
    stream << generateFooter();
    
    return tikzCode;
}

QString TikzGenerator::generateHeader()
{
    return QString("\\begin{circuitikz}[scale=1.0]\n");
}

QString TikzGenerator::generateFooter()
{
    return QString("\\end{circuitikz}");
}

QString TikzGenerator::generateElementCode(CircuitElement *element)
{
    if (!element) {
        return "";
    }
    
    QPointF pos = element->scenePos();
    qreal x = pos.x() * GRID_TO_TIKZ_SCALE;
    qreal y = -pos.y() * GRID_TO_TIKZ_SCALE;
    
    QString label = element->getLabel();
    if (label.isEmpty()) {
        label = "?";
    }
    
    switch (element->getType()) {
        case ElementType::Resistor:
            return QString("\\draw %1 to[R, l=$%2$] ++(2,0);")
                   .arg(formatCoordinate(x, y))
                   .arg(label);
            
        case ElementType::Capacitor:
            return QString("\\draw %1 to[C, l=$%2$] ++(2,0);")
                   .arg(formatCoordinate(x, y))
                   .arg(label);
            
        case ElementType::Inductor:
            return QString("\\draw %1 to[L, l=$%2$] ++(2,0);")
                   .arg(formatCoordinate(x, y))
                   .arg(label);
            
        case ElementType::VoltageSource:
            return QString("\\draw %1 to[V, l=$%2$] ++(0,-2);")
                   .arg(formatCoordinate(x, y))
                   .arg(label);
            
        case ElementType::CurrentSource:
            return QString("\\draw %1 to[I, l=$%2$] ++(0,-2);")
                   .arg(formatCoordinate(x, y))
                   .arg(label);
            
        case ElementType::Ground:
            return QString("\\node[ground] at %1 {};")
                   .arg(formatCoordinate(x, y));
            
        case ElementType::Node:
            return QString("\\node[circ] at %1 {};")
                   .arg(formatCoordinate(x, y));
            
        default:
            return QString("% Unknown element at %1")
                   .arg(formatCoordinate(x, y));
    }
}

QString TikzGenerator::formatCoordinate(qreal x, qreal y)
{
    return QString("(%1,%2)").arg(x, 0, 'f', 2).arg(y, 0, 'f', 2);
}
