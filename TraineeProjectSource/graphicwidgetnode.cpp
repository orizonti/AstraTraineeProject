
#include "stdafx.h"
#include "graphicwidgetnode.h"

GraphicWidgetNode::GraphicWidgetNode(QGraphicsScene* Scene, int X_POS, int Y_POS,QWidget* Widget)
{
    this->NodePositionX = X_POS;
    this->NodePositionY = Y_POS;
//   wid->setWindowFlags(Qt::FramelessWindowHint);

//    wid->setAttribute(Qt::WA_NoSystemBackground);
//    wid->setAttribute(Qt::WA_TranslucentBackground);
//    wid->setAttribute(Qt::WA_TransparentForMouseEvents);
    Scene->addItem(this);

     WindowNode = Widget;

     this->setWidget(WindowNode);


 // this->setWindowFlags(Qt::Window);
  
  this->setFlag(QGraphicsItem::ItemIsMovable);


     InputNode = new Node(1); 
     OutputNode = new Node(2);

     InputNodeUp = new Node(3);
     OutputNodeDown = new Node(4);

Scene->addItem(InputNode);
Scene->addItem(OutputNode);
Scene->addItem(InputNodeUp);
Scene->addItem(OutputNodeDown);

int offset_x = -5;
int offset_y = 5;



     this->windowFlags();
     this->setPos(X_POS,Y_POS);
	QPointF pos = this->pos();
	QRectF rect = this->rect();

	QPointF InpP = QPointF(pos.x() + offset_x, pos.y() + rect.size().height() / 2);
	QPointF OutP = QPointF(pos.x() + rect.size().width() + offset_y, pos.y() + rect.size().height() / 2);
	InputNode->setPos(InpP.x(), InpP.y());
	OutputNode->setPos(OutP.x(), OutP.y());

     InputNodeUp->setPos(pos.x()+this->rect().width()/2,pos.y()+offset_x);
     OutputNodeDown->setPos(pos.x()+this->rect().width()/2,pos.y()+this->rect().height()+offset_y);
}

GraphicWidgetNode::~GraphicWidgetNode()
{
   delete InputNode;
   delete OutputNode;
   delete InputNodeUp;
   delete OutputNodeDown;
}

void GraphicWidgetNode::setWidget(QWidget *widget)
{
    QGraphicsProxyWidget::setWidget(widget);
}

void GraphicWidgetNode::ConnectNode(GraphicWidgetNode* Node)
{
	if (WindowNode == 0 || InputNode == 0 || OutputNode == 0)
		return;
	Node->OutputNodeDown->ConnectNode(this->InputNodeUp);
}

bool GraphicWidgetNode::sceneEvent(QEvent *event)
{
   this->NodePositionX = this->pos().x();
   this->NodePositionY = this->pos().y();
   //qDebug() << "Pos widget - " << NodePositionX << NodePositionY;
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
   //qDebug() << "itemChange";
 //  qDebug() << "Pos widget - " << this->pos();
int offset_x = 5;
int offset_y = -5;
if (this->isWindow())
{
	offset_x = 10;
	offset_y = -10;
}

if (InputNode != 0 && OutputNode != 0)
{
	QPointF pos = this->pos();
	QRectF rect = this->rect();

	QPointF InpP = QPointF(pos.x() + offset_x, pos.y() + rect.size().height() / 2);
	QPointF OutP = QPointF(pos.x() + rect.size().width() + offset_y, pos.y() + rect.size().height() / 2);
	InputNode->setPos(InpP.x(), InpP.y());
	OutputNode->setPos(OutP.x(), OutP.y());

     InputNodeUp->setPos(pos.x()+this->rect().width()/2,pos.y()+offset_x);
     OutputNodeDown->setPos(pos.x()+this->rect().width()/2,pos.y()+this->rect().height()+offset_y);
}
   return QGraphicsProxyWidget::itemChange(change,value);
}
