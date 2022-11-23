#include <iostream>
#include <gtest/gtest.h>
//-include "QtPythonPI.hh"

#include <QObject>
#include <QDir>
#include <QtPlugin>
#include <QPluginLoader>
#include <QCoreApplication>
#include "QtPythonInterface.hh"


using namespace std;


static QtPythonInterface* Qtpyif = nullptr;
static QPluginLoader PluginLoader{};


bool QtPythonPI_LoadPlugin(const string& piName = "qtpypi"s)
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    //-pluginsDir.cd("plugins");
    const QStringList entries = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entries) {
        PluginLoader.setFileName(pluginsDir.absoluteFilePath(fileName));
        // Get the root object in the plugin
        QObject *plugin = PluginLoader.instance();
        if (plugin) {
            // Is the root object is castable to the designated interface?
            Qtpyif = qobject_cast<QtPythonInterface *>(plugin);
            if (Qtpyif) {
                cout << "Plugin: " << fileName.toLatin1().data() << endl;
                return true;
            }
            PluginLoader.unload();
        }
    }

    return false;
}


bool QtPythonPI_UnloadPlugin()
{
    bool rv = PluginLoader.unload();
    if(rv) { 
        // If unload was successful, reset managed pointers
        Qtpyif = nullptr;
    }
    return rv;
}


TEST(QtPythonPI_test, Load)
{
  bool rv = QtPythonPI_LoadPlugin();
  ASSERT_TRUE(rv);
  ASSERT_TRUE(nullptr != Qtpyif);
}


