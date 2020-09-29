#include "fenetre_affichage_manoir.h"

Fenetre_affichage_manoir::Fenetre_affichage_manoir(Environnement_manoir* manoir, QWidget *parent)
{
    //Je ne sais pas tros a quoi tous ça sert
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);

    setFormat(format);
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    openGLFunctions = context->functions();

    //Là je comprend mieux a quoi ça sert
    this->setTitle("Manoir de l'Aspirateur ");
    this->resize(640, 480);
    this->manoir = manoir;

    QObject::connect(manoir, &Environnement_manoir::rafraichissement_image, this, &Fenetre_affichage_manoir::rafraichissement_image);
}


void Fenetre_affichage_manoir::initializeGL()
{

}

void Fenetre_affichage_manoir::resizeGL(int w, int h)
{

}

void Fenetre_affichage_manoir::paintGL()
{
    //On colore le fond en blanc
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //On construe les cases pour les salles du plateau
    QVector<QVector<Salle_manoir>> manoir_tableau;
    manoir_tableau = this->manoir->get_tableau();

    int manoir_dimention_x = manoir_tableau[0].size();
    int manoir_dimention_y = manoir_tableau.size();

    double taille_salle_x = 2/(double)(manoir_dimention_x);
    double taille_salle_y = 2/(double)(manoir_dimention_y);

    //On desiinge les lignes verticale du plateau
    for(int i = 0; i < manoir_dimention_x; i++)
    {
        glLineWidth(taille_salle_x/10);
        glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        double position_point_x = taille_salle_x * i - 1;
        glVertex2f(position_point_x, -1);
        glVertex2f(position_point_x, 1);
        glEnd();
    }

    //On desiinge les lignes horizontal du plateau
    for(int i = 0; i < manoir_dimention_y; i++)
    {
        glLineWidth(taille_salle_x/10);
        glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        double position_point_y = taille_salle_y * i - 1;
        glVertex2f(-1, position_point_y);
        glVertex2f(1, position_point_y);
        glEnd();
    }

    //On parcoure toutes les cellules du tableau est on affiche les entités
    for(int i = 0; i < manoir_dimention_x; i++)
    {
        for(int j = 0; j < manoir_dimention_y; j++)
        {
            //On regarde pour chaque entité qui ce trouve dans la salle
            for(int k = 0; k < manoir_tableau[i][j].liste_entite.size(); k++ )
            {
                //On affiche les aspirateurs
                if(manoir_tableau[i][j].liste_entite[k]->type_entite == "aspirateur"){
                    glBegin(GL_POLYGON);
                    glColor3f(1,0,0);
                    glVertex2f(i*taille_salle_x-1,j*taille_salle_y-1);
                    glVertex2f((i+1)*taille_salle_x-1,j*taille_salle_y-1);
                    glVertex2f((i+1)*taille_salle_x-1,(j+1)*taille_salle_y-1);
                    glVertex2f(i*taille_salle_x-1,(j+1)*taille_salle_y-1);
                    glEnd();
                }
            }
        }
    }
}

void Fenetre_affichage_manoir::rafraichissement_image(void)
{
    resize(width(), height()-1);
    resize(width(), height()+1);
}
