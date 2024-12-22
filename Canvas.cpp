#include "Canvas.h"
#include "Garden.h"
#include "Snake.h"
#include "Apple.h"
#include <QPainter>
#include <QTimer>
#include <QSet>
#include <QRandomGenerator>

#define qrand QRandomGenerator::global()->generate

class Canvas::Private
{
    friend class Canvas;

    int cell = 32;
    int interval = 200;

    Garden garden = Garden();
    Snake snake = Snake(QPoint(garden.size().width() / 2, garden.size().height() / 2));
    Apple apple = Apple(QPoint(garden.size().width() / 2 + 4, garden.size().height() / 2));

    QTimer timer;
};

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), p(new Private)
{
    setFixedSize(p->garden.size() * p->cell + QSize(1, 1));

    p->timer.setInterval(p->interval);
    p->timer.setSingleShot(false);
    p->timer.start();

    connect(&p->timer, &QTimer::timeout, this, &Canvas::step);
}

Canvas::~Canvas()
{
}

void Canvas::step()
{
    auto apple = [this]() -> QPoint
    {
        return QPoint(qrand() % p->garden.size().width(), qrand() % p->garden.size().height());
    };

    auto head = p->snake.next();
    if(head.x() < 0 || head.x() >= p->garden.size().width())
    {
        head.setX(head.x() < 0 ? p->garden.size().width() - 1 : 0);
    }
    else if(head.y() < 0 || head.y() >= p->garden.size().height())
    {
        head.setY(head.y() < 0 ? p->garden.size().height() - 1 : 0);
    }

    bool eat = head == p->apple.position();
    p->snake.move(head, eat);
    if(eat)
        p->apple.move(apple());

    auto& snake = p->snake.body();
    auto unique = QSet<QPoint>(snake.begin(), snake.end());
    if(unique.size() != snake.size())
        p->timer.stop();

    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QColor background(96, 192, 64);
    QColor body(128, 128, 128);
    QColor head(64, 64, 64);
    QColor apple = Qt::red;
    QColor leaf  = Qt::green;

    QPainter painter(this);

    // Draw the garden background with a more realistic grass pattern
    QPixmap grassPattern(256, 256);
    grassPattern.fill(background);
    QPainter grassPainter(&grassPattern);

    // Draw random grass blades
    grassPainter.setPen(QPen(Qt::darkGreen, 1));
    for (int i = 0; i < 100; ++i) {
        int x = qrand() % 256;
        int y = qrand() % 256;
        int length = qrand() % 10 + 5;
        grassPainter.drawLine(x, y, x, y + length);
    }

    // Draw some lighter grass blades
    grassPainter.setPen(QPen(Qt::green, 1));
    for (int i = 0; i < 50; ++i) {
        int x = qrand() % 256;
        int y = qrand() % 256;
        int length = qrand() % 10 + 5;
        grassPainter.drawLine(x, y, x, y + length);
    }

    grassPainter.end();

    QBrush grassBrush(grassPattern);
    painter.setBrush(grassBrush);
    painter.drawRect(QRect(rect().topLeft(), p->garden.size() * p->cell));

    // Define extended rainbow colors using RGB values
    QList<QColor> rainbowColors = {
        QColor(255, 0, 0),    // Red
        QColor(255, 69, 0),   // Orange Red
        QColor(255, 140, 0),  // Dark Orange
        QColor(255, 165, 0),  // Orange
        QColor(255, 215, 0),  // Gold
        QColor(255, 255, 0),  // Yellow
        QColor(238, 232, 170),// Pale Goldenrod
        QColor(173, 255, 47), // Green Yellow
        QColor(0, 255, 0),    // Lime
        QColor(50, 205, 50),  // Lime Green
        QColor(0, 128, 0),    // Green
        QColor(0, 255, 127),  // Spring Green
        QColor(0, 255, 255),  // Cyan
        QColor(0, 206, 209),  // Dark Turquoise
        QColor(0, 191, 255),  // Deep Sky Blue
        QColor(0, 0, 255),    // Blue
        QColor(75, 0, 130),   // Indigo
        QColor(138, 43, 226), // Blue Violet
        QColor(148, 0, 211),  // Dark Violet
        QColor(186, 85, 211), // Medium Orchid
        QColor(238, 130, 238),// Violet
        QColor(255, 20, 147), // Deep Pink
        QColor(255, 105, 180),// Hot Pink
        QColor(255, 192, 203) // Pink
    };

    auto snake = p->snake.body();
    int colorIndex = 0;
    for (const auto& cell : snake)
    {
        painter.setBrush(rainbowColors[colorIndex % rainbowColors.size()]);
        painter.drawRect((cell.x()) * p->cell,
                         (cell.y()) * p->cell,
                         p->cell,
                         p->cell);
        colorIndex++;
    }

    // Draw a 10x10 sprite of a red apple with a green leaf
    QPoint applePosition = p->apple.position() * p->cell;

    // Draw the red apple
    painter.setBrush(apple);
    painter.drawEllipse(QRect(applePosition.x(), applePosition.y(), p->cell, p->cell));

    //Draw the green leaf
    painter.setBrush(leaf);
    painter.save(); // Save the current painter state
    painter.translate(applePosition.x() + p->cell / 2, applePosition.y()); // Move to the top of the apple
    painter.rotate(45); // Rotate 45 degrees to the upper right
    painter.drawEllipse(QRect(0, 0, 5, -7)); // Draw the oval leaf
    painter.restore(); // Restore the painter state

    event->accept();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Left:  p->snake.direction(Snake::Direction::Left);                 break;
        case Qt::Key_Up:    p->snake.direction(Snake::Direction::Up);                   break;
        case Qt::Key_Right: p->snake.direction(Snake::Direction::Right);                break;
        case Qt::Key_Down:  p->snake.direction(Snake::Direction::Down);                 break;
        case Qt::Key_Space: p->timer.isActive() ? p->timer.stop() : p->timer.start();   break;
        default:    break;
    }
    event->accept();
}
