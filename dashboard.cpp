#include "dashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QPushButton>
#include <QApplication>
#include <QLCDNumber>
#include <QLabel>
#include <QDateTime>

// Constructeur de la classe Dashboard
Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent)
{
    // Créer un layout principal vertical
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Ajouter l'indicateur de niveau de batterie
    batteryIndicator = new BatteryIndicator(this);

    // Initialiser le thermomètre
    thermometer = new QLCDNumber(this);
    thermometer->setDigitCount(2); // Nombre de chiffres à afficher (sans le signe °)
    thermometer->display(25); // Température initiale
    thermometer->setFixedWidth(50); // Ajuster la largeur de l'afficheur
    thermometer->setFixedHeight(30); // Ajuster la hauteur de l'afficheur

    // Étiquette pour afficher le signe "°C"
    temperatureLabel = new QLabel("°C", this);
    temperatureLabel->setStyleSheet("font-size: 18px; color: white;");
    QHBoxLayout *tempLayout = new QHBoxLayout();
    tempLayout->addWidget(thermometer);
    tempLayout->addWidget(temperatureLabel);

    // Affichage de l'heure en direct
    clockLabel = new QLabel(this);
    clockLabel->setStyleSheet("font-size: 36px; color: white;");
    clockLabel->setFixedWidth(100); // Ajuster la largeur du QLabel selon les besoins
    clockLabel->setAlignment(Qt::AlignLeft); // Aligner à gauche
    updateTime(); // Mettre à jour l'heure initiale

    // Configurer le timer pour mettre à jour l'heure toutes les secondes
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dashboard::updateTime);
    timer->start(1000); // Mettre à jour toutes les secondes

    // Layout horizontal pour aligner les éléments en haut
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(clockLabel); // Ajouter l'afficheur d'heure en haut à gauche
    topLayout->addStretch(); // Ajouter un espace extensible après l'afficheur d'heure
    topLayout->addLayout(tempLayout); // Ajouter le layout de la température au layout

    // Initialisation des widgets
    speedometer = new Speedometer(this, batteryIndicator); // Passer la référence de BatteryIndicator au Speedometer
    directionIndicator = new DirectionIndicator(this);

    // Layout horizontal pour aligner les widgets principaux
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(speedometer);

    // Ajouter l'image entre les deux compteurs
    mapLabel = new QLabel(this);
    QPixmap mapPixmap("T:/tableau de bord/voiture/map.png");
    mapLabel->setPixmap(mapPixmap); // Ajouter l'image au QLabel
    hLayout->addWidget(mapLabel);

    hLayout->addStretch(); // Ajouter de l'espace extensible au milieu
    hLayout->addWidget(batteryIndicator);

    // Ajouter les widgets principaux et les flèches de direction au layout principal
    mainLayout->addLayout(topLayout); // Ajouter le layout du haut avec l'heure et la température
    mainLayout->addLayout(hLayout); // Ajouter le layout principal des widgets
    mainLayout->addWidget(directionIndicator); // Ajouter les flèches de direction en bas

    // Bouton de sortie
    QPushButton *exitButton = new QPushButton("Quitter", this);
    mainLayout->addWidget(exitButton);
    exitButton->setFocusPolicy(Qt::NoFocus); // Désactiver la prise de focus pour empêcher la touche espace de quitter l'application
    mainLayout->setAlignment(exitButton, Qt::AlignLeft | Qt::AlignBottom);

    setLayout(mainLayout);
    setWindowTitle("Tableau de Bord");
    setFixedSize(1000, 600);

    // Définir la palette de couleurs de la fenêtre
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(0, 0, 0));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // Connecter le signal de mise à jour de distance de Speedometer à la méthode updateBattery de BatteryIndicator
    connect(speedometer, &Speedometer::distanceUpdated, batteryIndicator, &BatteryIndicator::updateBattery);

    // Connecter le bouton de sortie au slot onExitButtonClicked
    connect(exitButton, &QPushButton::clicked, this, &Dashboard::onExitButtonClicked);
}

// Slot pour mettre à jour l'heure
void Dashboard::updateTime() {
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("HH:mm");
    clockLabel->setText(timeString);
}

// Surcharge des événements de clavier pour propager les événements aux widgets enfants
void Dashboard::keyPressEvent(QKeyEvent *event) {
    speedometer->handleKeyPress(event);
    directionIndicator->handleKeyPress(event);
}

// Surcharge des événements de clavier pour propager les événements aux widgets enfants
void Dashboard::keyReleaseEvent(QKeyEvent *event) {
    speedometer->handleKeyRelease(event);
    directionIndicator->handleKeyRelease(event);
}

// Slot pour gérer le clic du bouton "Quitter"
void Dashboard::onExitButtonClicked() {
    QApplication::quit();
}
