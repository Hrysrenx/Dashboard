#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H

#include <QWidget>
#include <QProgressBar>

// Déclaration de la classe BatteryIndicator, héritant de QWidget
class BatteryIndicator : public QWidget {
    Q_OBJECT

public:
    // Constructeur explicit de la classe BatteryIndicator
    explicit BatteryIndicator(QWidget *parent = nullptr);

    // Destructeur de la classe BatteryIndicator
    ~BatteryIndicator();

    // Méthode pour mettre à jour le niveau de batterie en fonction de la distance parcourue
    void updateBattery(double distance);

    // Méthode pour vérifier si la batterie est vide
    bool isBatteryEmpty() const;

protected:
    // Surcharge de la méthode paintEvent pour dessiner le widget
    void paintEvent(QPaintEvent *event) override;



private:
    double batteryLevel;  // Variable membre pour stocker le niveau de batterie

signals:
    void batteryEmpty();  // Signal émis lorsque la batterie est vide
};

#endif // BATTERYINDICATOR_H
