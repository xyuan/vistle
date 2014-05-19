#ifndef MODULEBROWSER_H
#define MODULEBROWSER_H

#include <QDockWidget>
#include <QStringList>
#include <QListWidget>

class QMimeData;
class QListWidgetItem;

namespace gui {

namespace Ui {
class ModuleBrowser;

} //namespace Ui

class ModuleListWidget: public QListWidget {
   Q_OBJECT

public:
   ModuleListWidget(QWidget *parent=nullptr);

public slots:
   void setFilter(QString filter);

protected:
   QMimeData *mimeData(const QList<QListWidgetItem *> dragList) const;

};

class ModuleBrowser: public QWidget {
   Q_OBJECT

public:
   static const char *mimeFormat();
   static int nameRole();

   ModuleBrowser(QWidget *parent=nullptr);
   ~ModuleBrowser();

public slots:
   void addModule(QString module);
   void setFilter(QString filter);

private:
   QLineEdit *filterEdit() const;

   Ui::ModuleBrowser *ui;
};

} // namespace gui
#endif
