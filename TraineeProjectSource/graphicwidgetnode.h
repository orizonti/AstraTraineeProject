#ifndef GRAPHICWIDGETNODE_H
#define GRAPHICWIDGETNODE_H

#include "node.h"

#include "pidwindow2.h"
#include <QGraphicsProxyWidget>

class GraphicWidgetNode : public QGraphicsProxyWidget
{
public:
    GraphicWidgetNode(QGraphicsScene* Scene, int X_POS, int Y_POS, QWidget *Widget);
    ~GraphicWidgetNode();

    Node* InputNode = 0;
    Node* OutputNode = 0;

    Node* InputNodeUp = 0;
    Node* OutputNodeDown = 0;

    QWidget* WindowNode = 0;
    void setWidget(QWidget* widget);
	void ConnectNode(GraphicWidgetNode* Node);

    bool sceneEvent(QEvent *event);
    int NodePositionX = 0;
    int NodePositionY = 0;

     QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	 void focusInEvent(QFocusEvent *event);
	 void focusOutEvent(QFocusEvent *event);

};

#endif // GRAPHICWIDGETNODE_H
