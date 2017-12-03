#pragma once

#include <QObject>
#include <QThread>
#include <QVector>
#include <QMutex>
#include <QUdpSocket>

class Blat : public QThread {
	Q_OBJECT

public:
	Blat(QObject *p = nullptr);
	~Blat() = default;

protected:
	void run() override;

private:
    QUdpSocket *blat;
};