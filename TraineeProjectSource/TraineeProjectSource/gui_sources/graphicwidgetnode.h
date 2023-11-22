#ifndef GRAPHICWIDGETNODE_H
#define GRAPHICWIDGETNODE_H

#include "node.h"

#include "pidwindow.h"
#include <QGraphicsProxyWidget>

class GraphicWidgetNode : public QGraphicsProxyWidget
{
public:
    GraphicWidgetNode(QGraphicsScene* Scene, int X_POS, int Y_POS, QWidget *Widget);
    ~GraphicWidgetNode();


    std::vector<Node*> VisualNodes;

    QWidget* WindowNode = 0;
    void setWidget(QWidget* widget);
	void ConnectNode(GraphicWidgetNode* Node);

    bool sceneEvent(QEvent *event);
    int NodePositionX = 0;
    int NodePositionY = 0;

     QVariant itemChange(GraphicsItemChange change, const QVariant &value);
     void UpdateWidget();

	 void focusInEvent(QFocusEvent *event);
	 void focusOutEvent(QFocusEvent *event);

     static int CounterWidget;
     int NumberWidget = 0;

};

#endif // GRAPHICWIDGETNODE_H
