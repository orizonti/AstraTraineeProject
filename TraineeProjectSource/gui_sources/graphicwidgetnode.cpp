
#include "node.h"
#include "CommonHeaders.h"
#include "graphicwidgetnode.h"
int GraphicWidgetNode::CounterWidget = 0;

GraphicWidgetNode::GraphicWidgetNode(QGraphicsScene* Scene, int X_POS, int Y_POS,QWidget* Widget)
{
WindowNode = Widget; NumberWidget = CounterWidget; CounterWidget++;

Scene->addItem(this);

this->setWidget(WindowNode); this->setFlag(QGraphicsItem::ItemIsMovable);

VisualNodes.push_back(new Node(1));
VisualNodes.push_back(new Node(2));
VisualNodes.push_back(new Node(3));
VisualNodes.push_back(new Node(4));

Scene->addItem(VisualNodes[0]); Scene->addItem(VisualNodes[1]); Scene->addItem(VisualNodes[2]); Scene->addItem(VisualNodes[3]);

this->windowFlags(); this->setPos(X_POS,Y_POS);

this->NodePositionX = X_POS; this->NodePositionY = Y_POS;
QPointF pos = this->pos(); QRectF rect = this->rect();

int offset_x = -5; int offset_y = 5;
QPointF InpP = QPointF(pos.x() + offset_x, pos.y() + rect.size().height() / 2);
QPointF OutP = QPointF(pos.x() + rect.size().width() + offset_y, pos.y() + rect.size().height() / 2);
VisualNodes[0]->setPos(InpP.x(), InpP.y());
VisualNodes[1]->setPos(OutP.x(), OutP.y());

VisualNodes[2]->setPos(pos.x()+this->rect().width()/2,pos.y()+offset_x);
VisualNodes[3]->setPos(pos.x()+this->rect().width()/2,pos.y()+this->rect().height()+offset_y);
}

GraphicWidgetNode::~GraphicWidgetNode()
{
   delete VisualNodes[0];
   delete VisualNodes[1];
   delete VisualNodes[2];
   delete VisualNodes[3];
}

void GraphicWidgetNode::setWidget(QWidget *widget)
{
    QGraphicsProxyWidget::setWidget(widget);
}

void GraphicWidgetNode::ConnectNode(GraphicWidgetNode* Node)
{
	if (WindowNode == 0 || VisualNodes[0] == 0 || VisualNodes[1] == 0)
		return;
	Node->VisualNodes[3]->ConnectNode(this->VisualNodes[2]);
}

bool GraphicWidgetNode::sceneEvent(QEvent *event)
{
   if(event->type() == QEvent::UngrabMouse)
   {
      this->NodePositionX = this->pos().x();
      this->NodePositionY = this->pos().y();
      qDebug() << "POS WIDGET - " << NodePositionX << NodePositionY << " NUMBER: " << NumberWidget;
   }


   return QGraphicsProxyWidget::sceneEvent(event);

}

void GraphicWidgetNode::focusInEvent(QFocusEvent *event)
{
	this->setWindowFlags(Qt::Window);
   return QGraphicsProxyWidget::focusInEvent(event);
}
 void GraphicWidgetNode::focusOutEvent(QFocusEvent *event)
{

	this->scene()->update(this->scene()->sceneRect());
	this->setWindowFlags(Qt::Widget);
   return QGraphicsProxyWidget::focusOutEvent(event);
}
QVariant GraphicWidgetNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
   UpdateWidget();
   return QGraphicsProxyWidget::itemChange(change,value);
}


void GraphicWidgetNode::UpdateWidget()
{
int offset_x = 5;
int offset_y = -5;
if (this->isWindow())
{
	offset_x = 10;
	offset_y = -10;
}

if (VisualNodes.size() == 4)
{
	QPointF pos = this->pos();
	QRectF rect = this->rect();

	QPointF InpP = QPointF(pos.x() + offset_x, pos.y() + rect.size().height() / 2);
	QPointF OutP = QPointF(pos.x() + rect.size().width() + offset_y, pos.y() + rect.size().height() / 2);
	VisualNodes[0]->setPos(InpP.x(), InpP.y());
	VisualNodes[1]->setPos(OutP.x(), OutP.y());

     VisualNodes[2]->setPos(pos.x()+this->rect().width()/2,pos.y()+offset_x);
     VisualNodes[3]->setPos(pos.x()+this->rect().width()/2,pos.y()+this->rect().height()+offset_y);
}
}

void GraphicWidgetNode::SetScenePosition(int PosX, int PosY) {this->setPos(PosX,PosY); NodePositionX = PosX; NodePositionY = PosY; }