﻿#ifndef NAGRODA_H
#define NAGRODA_H
#include "przedmiot.h"
#include "gra.h"
#include <QList>

class Nagroda
{
public:
	Nagroda(int reputacja[LICZBA_KROLESTW], quint16 zloto, quint16 doswiadczenie, QStringList nazwyGrup, QList<int>* konkrety);
	~Nagroda();

	int* getReputacja();
	quint16 getZloto();
	quint16 getDoswiadczenie();
	QStringList getNazwyGrup();
	QList<int>* getKonkretnePrzedmioty();

private:
	int* reputacja;
	quint16 zloto;
	quint16 doswiadczenie;
	QStringList nazwyGrup;
	QList<int>* konkretnePrzedmioty;
};

#endif // NAGRODA_H