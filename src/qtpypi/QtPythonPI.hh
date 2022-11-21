#ifndef QT_PYTHON_PI_HH
#define QT_PYTHON_PI_HH
#pragma once

#include <QObject>
#include <QtPlugin>
#include "QtPythonInterface.hh"


class QtPythonPI : public QObject, QtPythonInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QtPythonInterface_iid FILE "qtpypi.json")
    Q_INTERFACES(QtPythonInterface)

public:
    QString echo(const QString &message) override;
};


#endif // Include guard
