

#include "QtPythonPI.hh"
#include <QCoreApplication>
#include <QDir>


using namespace std;
namespace py = pybind11;
using namespace py::literals;

/*
int main2() {
    py::scoped_interpreter guard{};

    auto locals = py::dict("name"_a="World", "number"_a=42);
    py::exec(R"(
        message = "Hello, {name}! The answer is {number}".format(**locals())
    )", py::globals(), locals);

    auto message = locals["message"].cast<std::string>();
    std::cout << message;

  return 0;
}
*/

//
// Static members
//
QPluginLoader QtPythonPI::s_piloader{};
QtPythonInterface* QtPythonPI::s_qtpyif = nullptr;
shared_ptr<py::scoped_interpreter> QtPythonPI::s_pyint(nullptr);


//
// Methods
//
QString QtPythonPI::echo(const QString &message)
{
    return message;
}


//
// Class Methods
//
bool QtPythonPI::LoadPlugin()
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
    pluginsDir.cd("plugins");
    const QStringList entries = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entries) {
        //-QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        s_piloader.setFileName(pluginsDir.absoluteFilePath(fileName));
        // Get the root object in the plugin
        QObject *plugin = s_piloader.instance();
        if (plugin) {
            // Is the root object is castable to the designated interface?
            s_qtpyif = qobject_cast<QtPythonInterface *>(plugin);
            if (s_qtpyif) {
                // Instantiate the Python interpreter and start
                s_pyint = make_shared<py::scoped_interpreter>();
                return true;
            }
            s_piloader.unload();
        }
    }

    return false;
}


bool QtPythonPI::UnloadPlugin()
{
    bool rv = s_piloader.unload();
    if(rv) { 
        // If unload was successful, reset managed pointers
        s_qtpyif = nullptr;
        s_pyint.reset();
    }
    return rv;
}

