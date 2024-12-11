#include "directionindicator.h"
#include <QPainter>
#include <QLinearGradient>

// Constructeur de la classe DirectionIndicator
DirectionIndicator::DirectionIndicator(QWidget *parent) : QWidget(parent), visible(true), gauche(false), droite(false)
{
    timer = new QTimer(this); // Création d'une instance de QTimer
    connect(timer, &QTimer::timeout, this, &DirectionIndicator::toggleVisibility); // Connexion du signal timeout du timer à la méthode toggleVisibility pour gérer le clignotement
}

// Méthode pour démarrer le clignotement de l'indicateur
void DirectionIndicator::startIndicator()
{
    timer->start(500); // Démarrage du timer avec un intervalle de 500 ms pour le clignotement
}

// Méthode pour arrêter le clignotement de l'indicateur
void DirectionIndicator::stopIndicator()
{
    timer->stop(); // Arrêt du timer
    visible = true; // Rendre les flèches visibles
    gauche = false; // Désactiver l'indicateur gauche
    droite = false; // Désactiver l'indicateur droit
    update(); // Redessiner le widget
}

// Méthode pour vérifier si le clignotement est actif
bool DirectionIndicator::isActive() const
{
    return timer->isActive(); // Retourner l'état d'activation du timer
}

// Méthode pour gérer les appuis sur les touches
void DirectionIndicator::handleKeyPress(QKeyEvent *event)
{
    keyPressEvent(event); // Appeler la méthode protégée
}

// Méthode pour gérer les relâchements de touches
void DirectionIndicator::handleKeyRelease(QKeyEvent *event)
{
    keyReleaseEvent(event); // Appeler la méthode protégée
}

// Méthode pour dessiner les flèches en utilisant des polygones pour un effet plus moderne
void DirectionIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // Éviter les avertissements sur l'utilisation du paramètre event

    QPainter painter(this); // Créer un objet QPainter pour dessiner
    painter.setRenderHint(QPainter::Antialiasing); // Activer l'anti-aliasing pour des bords plus lisses

    QPen pen(Qt::black, 3); // Créer un stylo noir avec une épaisseur de 3 pour la bordure
    painter.setPen(pen); // Appliquer le stylo au painter

    int largeur = 65;  // Largeur réduite pour les flèches
    int hauteur = 50; // Hauteur fixe pour les flèches
    int marge = 300; // Distance fixe par rapport aux bords du widget

    if (gauche && visible) {
        // Dessiner une flèche gauche plus stylisée avec taille réduite
        QLinearGradient gradient(0, 0, largeur, hauteur); // Créer un dégradé linéaire
        gradient.setColorAt(0, Qt::yellow); // Définir la couleur de début du dégradé (jaune)
        gradient.setColorAt(1, Qt::green); // Définir la couleur de fin du dégradé (vert)
        painter.setBrush(gradient); // Appliquer le dégradé comme brosse

        QPolygonF arrowLeft; // Créer un polygone pour la flèche gauche
        arrowLeft << QPointF(marge, height() / 2) // Point central de la flèche
                  << QPointF(marge + largeur, height() / 2 - hauteur / 2) // Point supérieur gauche de la flèche
                  << QPointF(marge + largeur, height() / 2 + hauteur / 2); // Point inférieur gauche de la flèche
        painter.drawPolygon(arrowLeft); // Dessiner le polygone de la flèche gauche
    }

    if (droite && visible) {
        // Dessiner une flèche droite plus stylisée avec taille réduite
        QLinearGradient gradient(0, 0, largeur, hauteur); // Créer un dégradé linéaire
        gradient.setColorAt(0, Qt::yellow); // Définir la couleur de début du dégradé (jaune)
        gradient.setColorAt(1, Qt::green); // Définir la couleur de fin du dégradé (vert)
        painter.setBrush(gradient); // Appliquer le dégradé comme brosse

        QPolygonF arrowRight; // Créer un polygone pour la flèche droite
        arrowRight << QPointF(width() - marge, height() / 2) // Point central de la flèche
                   << QPointF(width() - marge - largeur, height() / 2 - hauteur / 2) // Point supérieur droit de la flèche
                   << QPointF(width() - marge - largeur, height() / 2 + hauteur / 2); // Point inférieur droit de la flèche
        painter.drawPolygon(arrowRight); // Dessiner le polygone de la flèche droite
    }
}

// Méthode pour gérer les appuis sur les touches
void DirectionIndicator::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) { // Si la touche gauche est pressée
        gauche = !gauche; // Inverser l'état de l'indicateur gauche
        droite = false; // Désactiver l'indicateur droit
        startIndicator(); // Démarrer le clignotement
    } else if (event->key() == Qt::Key_Right) { // Si la touche droite est pressée
        droite = !droite; // Inverser l'état de l'indicateur droit
        gauche = false; // Désactiver l'indicateur gauche
        startIndicator(); // Démarrer le clignotement
    } else { // Pour toute autre touche
        stopIndicator(); // Arrêter le clignotement
    }
    update(); // Redessiner le widget
}

// Méthode pour gérer les relâchements de touches
void DirectionIndicator::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event); // Si nécessaire, tu peux gérer les relâchements ici
}

// Méthode pour alterner l'état de visibilité des flèches
void DirectionIndicator::toggleVisibility()
{
    visible = !visible; // Inverser l'état de visibilité
    update(); // Redessiner le widget
}
