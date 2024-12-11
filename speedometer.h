#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "batteryindicator.h" // bibliothèque pour gérer la batteire quand elle est à 0


// Déclaration de la classe Speedometer héritant de QWidget
class Speedometer : public QWidget {
    Q_OBJECT  // Macro Qt pour activer les signaux et slots

public:
    // Constructeur de la classe Speedometer
    Speedometer(QWidget *parent = nullptr, BatteryIndicator *batteryIndicator = nullptr);

    // Méthodes publiques pour gérer les événements de clavier
    void handleKeyPress(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);


    signals: void distanceUpdated(double distance);


protected:
    // Surcharge de la méthode pour gérer l'événement de pression d'une touche
    void keyPressEvent(QKeyEvent *event) override;

    // Surcharge de la méthode pour gérer l'événement de relâchement d'une touche
    void keyReleaseEvent(QKeyEvent *event) override;

    // Surcharge de la méthode pour gérer l'événement de peinture du widget
    void paintEvent(QPaintEvent *event) override;

private slots:
    // Slot pour mettre à jour les métriques (vitesse et distance)
    void updateMetrics();

private:
    int speed;  // Variable pour stocker la vitesse actuelle
    double distance;  // Variable pour stocker la distance parcourue
    QLabel *speedLabel;  // Étiquette pour afficher la vitesse
    QTimer *timer;  // Timer pour gérer les mises à jour périodiques
    BatteryIndicator *batteryIndicator; // Ajouter une référence à BatteryIndicator

};

#endif // SPEEDOMETER_H
