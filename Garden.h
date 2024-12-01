#ifndef GARDEN_H
#define GARDEN_H

#include <QWidget>
#include <QPaintEvent>
#include <QScopedPointer>

class Garden : public QWidget
{
public:
    Garden(QWidget* parent = nullptr);
    ~Garden();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // GARDEN_H
