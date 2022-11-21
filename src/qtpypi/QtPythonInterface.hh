#ifndef QT_PYTHON_INTERFACE_HH
#define QT_PYTHON_INTERFACE_HH
#pragma once

#include <QObject>
#include <QString>



class QtPythonInterface
{
public:
    virtual ~QtPythonInterface() = default;
    virtual QString echo(const QString &message) = 0;
};


QT_BEGIN_NAMESPACE

#define QtPythonInterface_iid "org.qt-project.Qt.Python-Interface/1.0"

Q_DECLARE_INTERFACE(QtPythonInterface, QtPythonInterface_iid)

QT_END_NAMESPACE


#endif // Include guard
