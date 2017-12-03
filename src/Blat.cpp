#include "Blat.h"

#include <QDebug>
#include <numeric>
#include <algorithm>
#include <utility>
#include <cmath>

#include "main.h"

Blat::Blat(QObject *p) : QThread(p) {
	setObjectName("BlatThread");
    blat = new QUdpSocket(this);

    start();
}

static float step(float e, float x) {
    return x < e ? 0. : 1.;
}

static float sawtooth(float x, float t_up) {
    x = fmod(x + t_up, 1.);
    return x / t_up * step(x, t_up) +
           (1. - x) / (1. - t_up) * (1. - step(x, t_up));
}

void Blat::run() {
    // TODO: This is a hack to keep the pointer alive while we're still running
    QSharedPointer<Timebase> timebaseRef = timebase;

    while (true) {
	    float brightness = sawtooth(timebase->beat(), 0.3);
        int rawBrightness = (int)(brightness*255.);
        qDebug() << "dat: " << rawBrightness;
        char buf[1] = "";
        buf[0] = (char)rawBrightness;
        blat->writeDatagram(buf, 1, QHostAddress("192.168.0.177"), 8888);

        msleep(10);
    }
}