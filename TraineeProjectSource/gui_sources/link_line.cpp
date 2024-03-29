/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "CommonHeaders.h"
#include "link_line.h"
#include "node.h"

#include <math.h>

#include <QPainter>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

//! [0]
LinkLine::LinkLine(Node *sourceNode, Node *destNode)
    : arrowSize(10)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addLinkLine(this);
    dest->addLinkLine(this);
    adjust();
}
//! [0]

//! [1]
Node *LinkLine::sourceNode() const
{
    return source;
}

Node *LinkLine::destNode() const
{
    return dest;
}
//! [1]

//! [2]
void LinkLine::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();
    //========================================
                    QPointF SourcePoint = mapFromItem(source,0,0);
                    QPointF EndPoint = mapFromItem(dest,0,0);

                   //double Cx1 = SourcePoint.x()/2+EndPoint.x()/2;
                   //double Cy1 = SourcePoint.y()/2+EndPoint.y()/2;

                   //double Cx2 = SourcePoint.x()/2+EndPoint.x()/2+40;
                   //double Cy2 = SourcePoint.y()/2+EndPoint.y()/2;

                   double Cx1 = SourcePoint.x();
                   double Cy1 = EndPoint.y();

                   double Cx2 = EndPoint.x();
                   double Cy2 = SourcePoint.y();

                   if (dest->Number == 1 || dest->Number == 2)
                   {
                   Cx1 = EndPoint.x();
                   Cy1 = SourcePoint.y();

                   Cx2 = SourcePoint.x();
                   Cy2 = EndPoint.y();
                   }

                    QPointF C1 = QPointF(Cx1,Cy1);
                    QPointF C2 = QPointF(Cx2,Cy2);

                    this->Curve = QPainterPath(mapFromItem(source,0,0));
                    Curve.cubicTo(C1, C2, EndPoint);

    //========================================
    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}
//! [2]

//! [3]
QRectF LinkLine::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

  /*  qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))*/

	int AvarageX = sourcePoint.x()/2 + destPoint.x()/2;
	int AvarageY = sourcePoint.y()/2 + destPoint.y()/2;

	int LengthX = abs(sourcePoint.x() - destPoint.x())+50;
	int LengthY = abs(sourcePoint.y() - destPoint.y())+50;
	int Lenght = sqrt(LengthX*LengthX + LengthY*LengthY)+50;

	QPoint TopLeft = QPoint(AvarageX - LengthX / 2, AvarageY - LengthY / 2);

	return QRect(TopLeft, QSize(LengthX, LengthY));
}
//! [3]

//! [4]
void LinkLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
//! [4]

//! [5]
    // Draw the line itself
    painter->setPen(QPen(this->LinkLineColor, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    painter->drawLine(line);
	painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    painter->drawPath(Curve);
//! [5]

//! [6]
    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

//    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,
//                                                  cos(angle + Pi / 3) * arrowSize);
//    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
//                                                  cos(angle + Pi - Pi / 3) * arrowSize);
//    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
//                                              cos(angle - Pi / 3) * arrowSize);
//    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
//                                              cos(angle - Pi + Pi / 3) * arrowSize);

//    painter->setBrush(Qt::black);
//    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
//    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
//! [6]
