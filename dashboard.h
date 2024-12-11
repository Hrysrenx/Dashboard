#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QProgressBar>
#include <QLCDNumber>
#include <QLabel>
#include <QTimer> // pour obtenir l'heure
#include <QPixmap> // pour l'image de la map
#include "speedometer.h"
#include "directionindicator.h"
#include "batteryindicator.h"

class Dashboard : public QWidget {
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void onExitButtonClicked();
    void updateTime(); // Slot pour mettre à jour l'heure

private:
    Speedometer *speedometer;
    DirectionIndicator *directionIndicator;
    BatteryIndicator *batteryIndicator;
    QProgressBar *batteryProgressbar;
    QLCDNumber *thermometer;
    QLabel *temperatureLabel;
    QLabel *clockLabel; // Ajouter un QLabel pour afficher l'heure
    QTimer *timer; // Ajouter un QTimer pour mettre à jour l'heure
    QLabel *mapLabel; // Ajouter un QLabel pour afficher l'image
};

#endif // DASHBOARD_H
