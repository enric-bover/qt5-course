#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    setUpPillarTimer();


}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/images/bird_blue_up.png"));
    addItem(bird);
}

void Scene::startGame()
{
    //Bird
    bird->startFlying();
    //Pillars

    if(!pillarTimer->isActive()){
        pillarTimer->start(1000);
    }

}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    QObject::connect(pillarTimer, &QTimer::timeout,[=](){
        PillarItem * pillarItem = new PillarItem();
        addItem(pillarItem);

    });

}


void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        bird->shootUp();
    }

    QGraphicsScene::mousePressEvent(event);
}
