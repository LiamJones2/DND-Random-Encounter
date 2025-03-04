#pragma once

#ifndef DNDRANDOMENCOUNTER_H_
#define DNDRANDOMENCOUNTER_H_

#include <QtWidgets/QMainWindow>
#include <QResizeEvent>
#include <QMainWindow>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QVBoxLayout>
#include <QtGlobal>
#include <QPropertyAnimation>
#include <QTimer>
#include "ui_DNDRandomEncounter.h"
#include <vector>
#include <thread>
#include <QImageReader>
#include "EncounterType.h"
#include "MainMenuPage.h"
#include "Encounter.h"
#include "EncounterTypesPage.h"
#include "EncountersPage.h"
#include "SingleEncounterPage.h"
#include "Database.h"
#include "CreateEncounterTypePage.h"
#include "Main.h"

class DNDRandomEncounter : public QMainWindow
{
    Q_OBJECT

public:
    DNDRandomEncounter(QWidget *parent = nullptr);
    ~DNDRandomEncounter();

    Ui::DNDRandomEncounterClass ui;

    void resizeEvent(QResizeEvent* event);

    void SwitchPageToEncounterTypes();
    void SwitchPageToMainMenu();
    void SwitchPageToSingleEncounterType();
    void SwitchPageToEncounter(int id);
    void SwitchPageToCreateEncounterType();

    void SetupEncounterTypes();
    void SetupEncounters();

    void SubmitInsertEncounterType();

    void ButtonPressed();
    void ButtonReleased(int encounterType);
    void LongPressDetected();

    void OnGroupBoxClicked();

    void CloseApp();

    void UpdateEncounterTypesScrollBar();
    void UpdateEncountersScrollBar();
//signals:
//    void appMaximized(const QSize& size);
//protected:
//    void showEvent(QShowEvent* event) override {
//        QMainWindow::showEvent(event);
//        if (isMaximized()) {
//            emit appMaximized(size());
//        }
//    }

private:

    QStackedWidget* stackedWidget;

    QScrollBar* EncounterTypesScrollBar;
private:
    QTimer pressTimer;
    bool clicked = false;
};

#endif // !DNDRANDOMENCOUNTER_H_