#ifndef DIRECTIONINDICATOR_H
#define DIRECTIONINDICATOR_H

#include <QWidget>
#include <QTimer>
#include <QPointF>
#include <QKeyEvent>

class DirectionIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit DirectionIndicator(QWidget *parent = nullptr); // Constructeur de la classe DirectionIndicator
    void startIndicator(); // Démarre le clignotement de l'indicateur
    void stopIndicator(); // Arrête le clignotement de l'indicateur
    bool isActive() const; // Vérifie si le clignotement est actif

    // Méthodes publiques pour gérer les événements de clavier
    void handleKeyPress(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

protected:
    void paintEvent(QPaintEvent *event) override; // Fonction pour dessiner les flèches
    void keyPressEvent(QKeyEvent *event) override; // Fonction pour gérer les appuis sur les touches
    void keyReleaseEvent(QKeyEvent *event) override; // Fonction pour gérer les relâchements de touches

private slots:
    void toggleVisibility(); // Fonction pour alterner la visibilité des flèches

private:
    QTimer *timer; // Timer pour gérer le clignotement
    bool visible; // État de visibilité des flèches
    bool gauche; // Indicateur pour la flèche gauche
    bool droite; // Indicateur pour la flèche droite
};

#endif // DIRECTIONINDICATOR_H
