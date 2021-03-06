#ifndef PAINT_FORM_H
#define PAINT_FORM_H

#include <QtWidgets>

namespace Ui {
class paint_form;
}

class paint_form : public QWidget
{
    Q_OBJECT


public:
    explicit paint_form(QWidget *parent = nullptr);
    ~paint_form() override;

    bool openImage(const QString &fileName);
    void saveImage(const QString& fileName);
    void setPenWidth(int newWidth);
    void setPenColor(const QColor& newColor);
    int penWidth() const {return myPenWidth;}
    QColor penColor() const {return myPenColor;}
    void rect_clicked();
    void line_clicked();
    void ellipse_clicked();
    void clearImage();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Updates the scribble area where we are painting
    void paintEvent(QPaintEvent *event) override;

    // Makes sure the area we are drawing on remains
    // as large as the widget
    void resizeEvent(QResizeEvent *event) override;


private:
    Ui::paint_form *ui;

    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint, startPoint, endPoint;
    QRect rectangle;
    QLine line;

    bool scribbling, rect_is_checked, line_is_checked, ellipse_is_checked;

    void resizeImage(QImage *image, const QSize &newSize);
    void drawLineTo(const QPoint& endPoint);

};

#endif // PAINT_FORM_H
