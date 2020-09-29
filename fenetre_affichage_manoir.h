#ifndef FENETRE_AFFICHAGE_MANOIR_H
#define FENETRE_AFFICHAGE_MANOIR_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QDebug>
#include <QString>

#include "environement_manoir.h"
#include "salle_manoir.h"

class Fenetre_affichage_manoir : public QOpenGLWindow
{
public:
    Fenetre_affichage_manoir(Environnement_manoir* manoir, QWidget *parent = nullptr);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;
    Environnement_manoir* manoir;

public slots:
    void rafraichissement_image(void);
};

#endif // FENETRE_AFFICHAGE_MANOIR_H
