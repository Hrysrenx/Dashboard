#include "batteryindicator.h"
#include <QPainter>
#include <QTimer>
#include <cmath>

// Constructeur de la classe BatteryIndicator
BatteryIndicator::BatteryIndicator(QWidget *parent) :
    QWidget(parent), batteryLevel(50000)
{
    setFixedSize(300, 300);  // Définir la taille fixe du widget
}

// Destructeur de la classe BatteryIndicator
BatteryIndicator::~BatteryIndicator() {}

// Méthode pour mettre à jour le niveau de batterie
void BatteryIndicator::updateBattery(double speed) {
    batteryLevel -= ((0.0024*speed*speed)-(0.3156*speed)+25.1); // equation de la puissance
    if (batteryLevel < 0) {
        batteryLevel = 0;
        emit batteryEmpty();
    }
    update(); // Demande de redessiner le widget
}

// Méthode pour vérifier si la batterie est vide
bool BatteryIndicator::isBatteryEmpty() const {
    return batteryLevel <= 0;
}

// Méthode pour dessiner le compteur de batterie
void BatteryIndicator::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Activer l'anti-aliasing

    // Dessiner le fond texturé en bleu marine
    painter.setBrush(QColor(0, 0, 0));  // Utiliser la couleur bleu marine
    painter.drawRect(0, 0, width(), height());

    // Dégradé pour le cadran
    QRadialGradient gradient(100, 100, 100, 100, 100);
    gradient.setColorAt(0, QColor(0, 0, 200));
    gradient.setColorAt(1, QColor(0, 0, 200));

    painter.setBrush(gradient);
    painter.drawEllipse(10, 10, 280, 280);

    // Dessiner les graduations
    painter.setPen(QPen(Qt::white, 2));
    for (int i = 0; i <= 100; i += 10) {
        int x1 = 150 + 120 * cos(M_PI * (i * 3.6 - 90) / 180);
        int y1 = 150 + 120 * sin(M_PI * (i * 3.6 - 90) / 180);
        int x2 = 150 + 140 * cos(M_PI * (i * 3.6 - 90) / 180);
        int y2 = 150 + 140 * sin(M_PI * (i * 3.6 - 90) / 180);
        painter.drawLine(x1, y1, x2, y2);

        // Afficher le pourcentage de batterie à chaque graduation
        QString batteryText = QString::number(i);
        int tx = 150 + 110 * cos(M_PI * (i * 3.6 - 90) / 180) - 10;
        int ty = 150 + 110 * sin(M_PI * (i * 3.6 - 90) / 180) + 5;
        painter.drawText(tx, ty, batteryText);
    }

    // Dessiner l'aiguille avec effet lumineux
    QPen needlePen(Qt::red, 3);
    needlePen.setCapStyle(Qt::RoundCap);
    painter.setPen(needlePen);
    painter.drawLine(150, 150,
                     150 + 100 * cos(M_PI * (batteryLevel/500 * 3.6 - 90) / 180),
                     150 + 100 * sin(M_PI * (batteryLevel/500 * 3.6 - 90) / 180));

    // Effet lumineux autour de l'aiguille
    painter.setPen(QPen(Qt::yellow, 1, Qt::DashLine));
    painter.drawLine(150, 150,
                     150 + 105 * cos(M_PI * (batteryLevel/500 * 3.6 - 90) / 180),
                     150 + 105 * sin(M_PI * (batteryLevel/500 * 3.6 - 90) / 180));

    // Afficher le pourcentage de batterie
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, QString("Batterie: %1%").arg(static_cast<int>(batteryLevel/500)));
}
