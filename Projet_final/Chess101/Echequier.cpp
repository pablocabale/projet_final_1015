#include "Echequier.h"
#include "EtatJeu.h"
//Faire des pieces
using namespace std;

Echequier::Echequier(EtatJeu* etatJeu){
    etatJeu_ = etatJeu;
    etatJeu_->setEchequier(this);
};

vector <Piece*> Echequier::getPieces(){return pieces_;};

QBoxLayout* Echequier::getBoite(){return boite_;};

void Echequier::piecesCreer(){
    // A faire en unique_ptr()
    Roi* roiBlanc = new Roi(false, 0, 3);
    Roi* roiNoir = new Roi(true, 7, 3);
    Reine* reineNoir = new Reine(true, 7, 4);
    pieces_.push_back(roiBlanc);
    pieces_.push_back(roiNoir);
    pieces_.push_back(reineNoir);
};

void Echequier::creerEchequier(){
    //faire les pieces
    piecesCreer();

    //placer les cases
    int compteur = 0;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
             Case* caseEchequier = new Case(i, j, etatJeu_);
             cases_.push_back(caseEchequier);
             if (compteur % 2 == 0)
                caseEchequier->setCouleurBase("color : black ; background-color: white");
             else
                caseEchequier->setCouleurBase("color : white ; background-color: black");

             caseEchequier->setStyleSheet(caseEchequier->getCouleurBase());

             addWidget(caseEchequier,i,j,1,1);
             compteur++;
             //placer piece
             for (Piece* p : pieces_){
                 if (p->getPosX() == i && p->getPosY() == j)
                    caseEchequier->ajouterPiece(p);
             }
        }
    compteur--;
    }

    // Caracteristiques du board
    QWidget *carre = new QWidget;
    carre->setLayout(this);
    carre->setMaximumHeight(800);
    carre->setMaximumWidth(800);
    QBoxLayout* boite = new QBoxLayout((QBoxLayout::LeftToRight));
    boite_ = boite;
    boite_->addWidget(carre);
};
