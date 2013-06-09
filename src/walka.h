﻿#ifndef WALKA_H
#define WALKA_H

#include <QDialog>
#include <QtGui>

#include "mojpasek.h"
#include "mistrzgry.h"
#include "gracz.h"
#include "gra.h"
#include "przeciwnik.h"

class MistrzGry;

class Walka : public QDialog
{
	Q_OBJECT
public:
	explicit Walka(Gracz* gracz, Przeciwnik* przeciwnik, MistrzGry* mistrzGry);

private:
	MistrzGry* mistrzGry;
	Gracz* gracz;
	Przeciwnik* przeciwnik;

	QHBoxLayout* layoutGlowny;
	QVBoxLayout* layoutPrzeciwnika;
	QVBoxLayout* layoutGracza;

//------Przeciwnik
	QLabel* obrazekPrzeciwnika;
	QLabel* nazwaPrzeciwnika;
	QLabel* opisPrzeciwnika;

	MojPasek* pasekZdrowiaPrzeciwnika;
	QLabel* punktyZdrowiaPrzeciwnika;
	QHBoxLayout* linijkaZdrowiaPrzeciwnika;

	QLabel* ikonkaAtakuPrzeciwnika;
	QLabel* atakPrzeciwnika;
	QLabel* ikonkaObronyPrzeciwnika;
	QLabel* obronaPrzeciwnika;
	QLabel* ikonkaPercepcjiPrzeciwnika;
	QLabel* percepcjaPrzeciwnika;
	QHBoxLayout* linijkaDanychPrzeciwnika;

//------Gracz
	QTextBrowser* log;

	QLabel* nazwaGracza;

	MojPasek* pasekZdrowiaGracza;
	QLabel* punktyZdrowiaGracza;
	QHBoxLayout* linijkaZdrowiaGracza;

	QLabel* ikonkaObronyGracza;
	QLabel* obronaGracza;
	QLabel* ikonkaPercepcjiGracza;
	QLabel* percepcjaGracza;
	QHBoxLayout* linijkaDanychGracza;

	QPushButton* przyciskAtakuWrecz;
	QPushButton* przyciskAtakuDystansowego;
	QPushButton* przyciskAtakuMagicznego;
	QHBoxLayout* linijkaAtakowGracza;

	QPushButton* przyciskMalejMikstury;
	QPushButton* przyciskDuzejMikstury;
	QPushButton* przyciskUcieczki;
	QHBoxLayout* linijkaPrzyciskowGracza;

	quint8 aktualneZdrowiePrzeciwnika;
	void ruchPrzeciwnika();
	void atakGracza(int atak);

signals:

private slots:
	void atakWrecz();
	void atakDystansowy();
	void atakMagiczny();
	void uciekaj();
	void uzyjDuzejMikstury();
	void uzyjMalejMikstury();

};

#endif // WALKA_H
