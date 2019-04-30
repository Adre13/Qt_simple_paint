#include "paint_form.h"
#include "ui_paint_form.h"


paint_form::paint_form(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    scribbling = false;
    rect_is_checked = false;
    myPenWidth = 1;
    myPenColor = Qt::black;

}

paint_form::~paint_form()
{
    delete ui;
}

bool paint_form::openImage(const QString &fileName)
{
    QImage loadedImage;

    if(!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    update();
    return true;
}

void paint_form::saveImage(const QString &fileName)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    visibleImage.save(fileName);
}

void paint_form::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void paint_form::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void paint_form::rect_clicked()
{
    if(rect_is_checked)
    {
        rect_is_checked = false;
    }else
    {
        rect_is_checked = true;
    }
}

void paint_form::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    update();
}

void paint_form::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        rectangle.setTopLeft(event->pos());
        rectangle.setBottomRight(event->pos());
        scribbling = true;
    }
}

void paint_form::mouseMoveEvent(QMouseEvent *event)
{
    if((event->type() == QEvent::MouseMove) && scribbling)
    {
        if(!rect_is_checked)
        {
            drawLineTo(event->pos());
        }else
        {
            rectangle.setBottomRight(event->pos());
            //drawLineTo(rectangle.bottomRight());
            update();
        }
    }
}

void paint_form::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)
    {
        if(!rect_is_checked)
        {
            drawLineTo(event->pos());
        }else
        {
            rectangle.setBottomRight(event->pos());
            drawLineTo(rectangle.bottomRight());
            update();
        }
        scribbling = false;
    }
}

void paint_form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);


        QRect dirtyRect = event->rect();
        painter.drawImage(dirtyRect, image, dirtyRect);
//    }else
//    {
        if(rect_is_checked)
        painter.drawRect(rectangle);
//    }
}

void paint_form::resizeEvent(QResizeEvent *event)
{
    if(width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void paint_form::resizeImage(QImage *image, const QSize &newSize)
{
    if(image->size() ==newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}

void paint_form::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if(!rect_is_checked)
    {
        painter.drawLine(lastPoint, endPoint);
        int rad = (myPenWidth / 2) + 2;
        update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
        lastPoint = endPoint;
    }else
    {
        painter.drawRect(rectangle);
    }
}
