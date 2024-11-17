#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->shapeCombo->addItem(tr("Polygon"), ShapeCanvas::Polygon);
    ui->shapeCombo->addItem(tr("Rectangle"), ShapeCanvas::Rect);
    ui->shapeCombo->addItem(tr("Rounded Rectanlge"), ShapeCanvas::RoundedRect);
    ui->shapeCombo->addItem(tr("Ellipse"), ShapeCanvas::Ellipse);
    ui->shapeCombo->addItem(tr("Pie"), ShapeCanvas::Pie);
    ui->shapeCombo->addItem(tr("Chord"), ShapeCanvas::Chord);
    ui->shapeCombo->addItem(tr("Text"), ShapeCanvas::Text);
    ui->shapeCombo->addItem(tr("Pixmap"), ShapeCanvas::Pixmap);


    ui->penStyleCombobox->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    ui->penStyleCombobox->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    ui->penStyleCombobox->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    ui->penStyleCombobox->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    ui->penStyleCombobox->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    ui->penStyleCombobox->addItem(tr("None"), static_cast<int>(Qt::NoPen));


    ui->penCapComboBox->addItem(tr("Flat"), Qt::FlatCap);
    ui->penCapComboBox->addItem(tr("Square"), Qt::SquareCap);
    ui->penCapComboBox->addItem(tr("Round"), Qt::RoundCap);

    ui->penCapComboBox->addItem(tr("Flat"), Qt::FlatCap);
    ui->penCapComboBox->addItem(tr("Square"), Qt::SquareCap);
    ui->penCapComboBox->addItem(tr("Round"), Qt::RoundCap);


    ui->penJoinComboBox->addItem(tr("Miter"), Qt::MiterJoin);
    ui->penJoinComboBox->addItem(tr("Bevel"), Qt::BevelJoin);
    ui->penJoinComboBox->addItem(tr("Round"), Qt::RoundJoin);

    ui->brushStyleComboBox->addItem(tr("Linear Gradient"),
                                    static_cast<int>(Qt::LinearGradientPattern));
    ui->brushStyleComboBox->addItem(tr("Radial Gradient"),
                                    static_cast<int>(Qt::RadialGradientPattern));
    ui->brushStyleComboBox->addItem(tr("Conical Gradient"),
                                    static_cast<int>(Qt::ConicalGradientPattern));
    ui->brushStyleComboBox->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->brushStyleComboBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->brushStyleComboBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->brushStyleComboBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->brushStyleComboBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->brushStyleComboBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->brushStyleComboBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->brushStyleComboBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    ui->brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));


    canvas = new ShapeCanvas(this);

    ui->canvasLayout->addWidget(canvas);

    penChanged();
    brushChanged();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_shapeCombo_activated(int index)
{
    ShapeCanvas::Shape shape = ShapeCanvas::Shape(index);
    canvas->setShape(shape);
}


void Widget::on_penWidth_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    penChanged();
}


void Widget::on_penStyleCombobox_activated(int index)
{
    Q_UNUSED(index);

    penChanged();

}


void Widget::on_penCapComboBox_activated(int index)
{
    Q_UNUSED(index);
    penChanged();

}


void Widget::on_penJoinComboBox_activated(int index)
{
    Q_UNUSED(index);
    penChanged();

}


void Widget::on_brushStyleComboBox_activated(int index)
{
    Q_UNUSED(index);
    brushChanged();
}


void Widget::on_antiCheckBox_toggled(bool checked)
{
    canvas->setAntialiased(checked);
}


void Widget::on_transformCheckBox_toggled(bool checked)
{
    canvas->setTransformed(checked);
}

void Widget::penChanged(){
    int penWidth = ui->penWidth->value();
    Qt::PenStyle style = Qt::PenStyle(ui->penStyleCombobox->itemData(
                                                              ui->penStyleCombobox->currentIndex()).toInt());

    Qt::PenCapStyle cap = Qt::PenCapStyle(ui->penCapComboBox->itemData(
                                                                ui->penCapComboBox->currentIndex()).toInt());


    Qt::PenJoinStyle join = Qt::PenJoinStyle(ui->penJoinComboBox->itemData(
                                                                ui->penJoinComboBox->currentIndex()).toInt());

    QPen pen;
    pen.setWidth(penWidth);
    pen.setStyle(style);
    pen.setJoinStyle(join);
    pen.setCapStyle(cap);
    canvas->setPen(pen);
}

void Widget::brushChanged(){
    Qt::BrushStyle style = Qt::BrushStyle(ui->brushStyleComboBox->itemData(
                                                                    ui->brushStyleComboBox->currentIndex()).toInt());

    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::red);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::blue);
        canvas->setBrush(linearGradient);
    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::red);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::blue);
        canvas->setBrush(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::red);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::blue);
        canvas->setBrush(conicalGradient);
    } else if (style == Qt::TexturePattern) {
        canvas->setBrush(QBrush(QPixmap(":/images/learnqt.png")));
    } else {
        canvas->setBrush(QBrush(Qt::blue, style));
    }
}

