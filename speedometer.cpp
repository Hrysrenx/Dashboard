#include "speedometer.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <cmath>

// Constructeur de la classe Speedometer
Speedometer::Speedometer(QWidget *parent, BatteryIndicator *battery) :
    QWidget(parent),
    speed(0),
    distance(0.0),

batteryIndicator(battery) // Initialiser la référence à BatteryIndicator

{
    setFixedSize(300, 350);  // Définir la taille fixe du widget, ajustée pour inclure la distance
    timer = new QTimer(this);  // Créer un QTimer
    connect(timer, &QTimer::timeout, this, &Speedometer::updateMetrics);  // Connecter le timer à la fonction updateMetrics
}

// Méthode pour gérer l'événement de pression d'une touche
void Speedometer::handleKeyPress(QKeyEvent *event) {
    keyPressEvent(event);  // Appeler la méthode protégée
}

// Méthode pour gérer l'événement de relâchement d'une touche
void Speedometer::handleKeyRelease(QKeyEvent *event) {
    keyReleaseEvent(event);  // Appeler la méthode protégée
}

// Gérer l'événement de pression de touche
void Speedometer::keyPressEvent(QKeyEvent *event) {

    if (batteryIndicator && batteryIndicator->isBatteryEmpty())
    { return; // Ne pas augmenter la vitesse si la batterie est vide
    }
        //
    if (event->key() == Qt::Key_Space) {  // Si la touche espace est pressée
        if (!timer->isActive()) {
            timer->start(100);  // Mettre à jour les métriques toutes les 100 ms
        }
        if (speed < 300) {
            speed += 3;  // Augmenter la vitesse
            update();  // Redessiner le widget
        }
    }
}

// Gérer l'événement de relâchement de touche
void Speedometer::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        // Continuer à décrémenter la vitesse et mettre à jour la distance lorsque la touche est relâchée
    }
}

// Mettre à jour les métriques (vitesse et distance)
void Speedometer::updateMetrics() {
    if (speed > 0) {
        // Distance = Vitesse (km/h) * Temps (h)
        distance += (speed / 36000.0);  // Temps (100 ms = 1/36000 h)
        speed -= 3;  // Réduire la vitesse
        update();  // Redessiner le widget
        emit distanceUpdated(distance);  // Émettre le signal de mise à jour de la distance
    } else {
        timer->stop();  // Arrêter le timer si la vitesse est 0
    }
}


void Speedometer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Activer l'anti-aliasing

    // Dessiner le fond avec un dégradé radial
    QRadialGradient backgroundGradient(width() / 2, height() / 2, 200);
    backgroundGradient.setColorAt(0, QColor(30, 30, 30));  // Centre noir-gris
    backgroundGradient.setColorAt(1, QColor(70, 70, 70));  // Bordures gris clair
    painter.setBrush(backgroundGradient);
    painter.drawEllipse(10, 10, 280, 280);

    // Dessiner les graduations principales et secondaires
    painter.setPen(QPen(Qt::white, 2));
    for (int i = 0; i <= 300; i += 10) {
        int adjustedAngle = (i + 210) % 360;  // Ajuste l'angle pour la nouvelle disposition
        int x1 = 150 + 120 * cos(M_PI * (adjustedAngle - 90) / 180);
        int y1 = 150 + 120 * sin(M_PI * (adjustedAngle - 90) / 180);
        int x2 = (i % 30 == 0) ? 150 + 140 * cos(M_PI * (adjustedAngle - 90) / 180) : 150 + 130 * cos(M_PI * (adjustedAngle - 90) / 180);
        int y2 = (i % 30 == 0) ? 150 + 140 * sin(M_PI * (adjustedAngle - 90) / 180) : 150 + 130 * sin(M_PI * (adjustedAngle - 90) / 180);
        painter.drawLine(x1, y1, x2, y2);

        // Afficher les valeurs pour les graduations principales
        if (i % 30 == 0) {
            QString speedText = QString::number(i);
            int tx = 150 + 110 * cos(M_PI * (adjustedAngle - 90) / 180) - 10;
            int ty = 150 + 110 * sin(M_PI * (adjustedAngle - 90) / 180) + 5;
            painter.setFont(QFont("Arial", 10, QFont::Bold));
            painter.drawText(tx, ty, speedText);
        }
    }

    // Dessiner l'aiguille sous forme triangulaire
    QPolygon needle;
    needle << QPoint(150, 150)  // Centre
           << QPoint(150 + 100 * cos(M_PI * ((speed + 210) % 360 - 90) / 180),
                     150 + 100 * sin(M_PI * ((speed + 210) % 360 - 90) / 180))  // Pointe
           << QPoint(150 + 20 * cos(M_PI * ((speed + 210 - 5) % 360 - 90) / 180),
                     150 + 20 * sin(M_PI * ((speed + 210 - 5) % 360 - 90) / 180));  // Base de l'aiguille
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(needle);






    // Zone centrale décorative
    painter.setBrush(QColor(50, 50, 50));
    painter.setPen(QPen(Qt::gray, 3));
    painter.drawEllipse(135, 135, 30, 30);

    // Afficher la vitesse
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, QString("Vitesse: %1 km/h").arg(speed));

    // Afficher la distance sous le cadran
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    int distanceYPosition = height() - 25;  // Position Y ajustée pour placer le texte en dessous du cadran
    painter.drawText(QRect(0, distanceYPosition, width(), 30), Qt::AlignCenter, QString("Distance: %1 km").arg(distance, 0, 'f', 2));
}
