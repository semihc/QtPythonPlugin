#ifndef QT_PYTHON_PI_HH
#define QT_PYTHON_PI_HH
#pragma once

#include <QObject>
#include <QtPlugin>
#include <QPluginLoader>
#include "QtPythonInterface.hh"

// https://stackoverflow.com/questions/23068700/embedding-python3-in-qt-5
#pragma push_macro("slots")
#undef slots
#include <pybind11/embed.h>
#pragma pop_macro("slots")
#include <memory>


// QtPython PlugIn Class
class QtPythonPI : public QObject, QtPythonInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QtPythonInterface_iid FILE "qtpypi.json")
    Q_INTERFACES(QtPythonInterface)

public:
    // MEMBERS

    // CREATORS
    QtPythonPI() {}
    ~QtPythonPI() {}

    // MODIFIERS
    //-QString echo(const QString &message) override;
    virtual void exec(const std::string& pstr);
    virtual void eval(const std::string& pstr);
    virtual void eval_file(const std::string& pfile);


    // STATIC MEMBERS
    // Plugin Loader
    static QPluginLoader s_piloader;
    // Qt-Python Interface object
    static QtPythonInterface* s_qtpyif;
    // Python interpreter
    static std::shared_ptr<pybind11::scoped_interpreter> s_pyint;

    // Load the plugin from shared library to memory
    static bool LoadPlugin();
    // Unload the plugin from memory
    static bool UnloadPlugin();
};



#endif // Include guard
