#include "Canvas.h"
#include "Garden.h"
#include "Snake.h"
#include "Apple.h"
#include <QPainter>
#include <QTimer>
#include <QSet>
#include <random>

class Canvas::Private
{
    friend class Canvas;

    int cell = 16;
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
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> distX(0, p->garden.size().width() - 1);
        std::uniform_int_distribution<int> distY(0, p->garden.size().height() - 1);
        return QPoint(distX(rng), distY(rng));
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
    QColor background(224, 224, 224);
    QColor body(128, 128, 128);
    QColor head(64, 64, 64);
    QColor highlight = Qt::red;

    QPainter painter(this);
    painter.setBrush(background);
    painter.drawRect(QRect(rect().topLeft(), p->garden.size() * p->cell));

    auto snake = p->snake.body();
    painter.setBrush(head);
    for (const auto& cell : snake)
    {
        if(cell == snake.first())
            painter.setBrush(head);
        else
            painter.setBrush(body);
        painter.drawRect((cell.x()) * p->cell,
                         (cell.y()) * p->cell,
                         p->cell,
                         p->cell);
    }

    painter.setBrush(highlight);
    painter.drawRect((p->apple.position().x()) * p->cell,
                     (p->apple.position().y()) * p->cell,
                     p->cell,
                     p->cell);

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
