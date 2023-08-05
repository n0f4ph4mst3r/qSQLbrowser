#include "QConnectionCtrl.h"

QConnectionCtrl::QConnectionCtrl(QWidget* parent) {
    QTreeWidgetItem* rootItem = new QTreeWidgetItem();
    rootItem->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
    rootItem->setText(0, tr("Databases"));
    setHeaderItem(rootItem);

    setMinimumSize(250, 402);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    QAction* refreshAction = new QAction(tr("Refresh"), this);
    QAction* shemaAction = new QAction(tr("Show shema"), this);
    shemaAction->setEnabled(false);
    shemaAction->setObjectName("shemaAction");
    QAction* separator = new QAction;
    separator->setSeparator(true);
    QAction* addConnectionAction = new QAction(tr("Add Connection..."), this);

    connect(refreshAction, &QAction::triggered, this, [=]() { refresh(); });
    connect(shemaAction, &QAction::triggered, this, &QConnectionCtrl::showMetaData);
    connect(addConnectionAction, &QAction::triggered, this, &QConnectionCtrl::showConnectionDialog);

    addAction(refreshAction);
    addAction(shemaAction);
    addAction(separator);
    addAction(addConnectionAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(this, &QTreeWidget::itemActivated, [=](QTreeWidgetItem* item, int column) {setActiveItem(item, column); });
    connect(this, &QTreeWidget::currentItemChanged, [=](QTreeWidgetItem* current, QTreeWidgetItem* previous) { 
            findChild<QAction*>("shemaAction")->setEnabled(current && current->parent()); 
    });

    setObjectName("connectionCtrl");

    emit statusMessage(tr("Ready."));
}

QSqlError QConnectionCtrl::createConnection(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, const int port) {
    static int cCount = 0;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("dbConnection%1").arg(++cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);

    QSqlError err;
    if (!db.open(user, passwd)) {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("dbConnection%1").arg(cCount));
    }

    return err;
}

void QConnectionCtrl::addConnection(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, const int port) {
    QSqlError err = createConnection(driver, dbName, host, user, passwd, port);
    if (err.type() != QSqlError::NoError)
        QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
            "opening the connection: ") + err.text());
    else refresh();
}

void QConnectionCtrl::showConnectionDialog() {
    QConnectionDialog dialog(this);
    connect(&dialog, &QConnectionDialog::connectionAdded, this, &QConnectionCtrl::addConnection);
    dialog.exec();
}

void QConnectionCtrl::showMetaData() {
    QTreeWidgetItem* cItem = currentItem();
    if (!cItem || !cItem->parent())
        return;
    setActiveDb(cItem->parent());

    QString t = cItem->text(0);

    QSqlRecord rec = QSqlDatabase::database(m_activeDb).record(t);
    QStandardItemModel* model = new QStandardItemModel(nullptr);

    model->insertRows(0, rec.count());
    model->insertColumns(0, 7);

    model->setHeaderData(0, Qt::Horizontal, "Fieldname");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "Length");
    model->setHeaderData(3, Qt::Horizontal, "Precision");
    model->setHeaderData(4, Qt::Horizontal, "Required");
    model->setHeaderData(5, Qt::Horizontal, "AutoValue");
    model->setHeaderData(6, Qt::Horizontal, "DefaultValue");

    for (int i = 0; i < rec.count(); ++i) {
        QSqlField fld = rec.field(i);
        model->setData(model->index(i, 0), fld.name());
        model->setData(model->index(i, 1), fld.typeID() == -1
            ? QString(fld.metaType().name())
            : QString("%1 (%2)").arg(fld.metaType().name()).arg(fld.typeID()));
        model->setData(model->index(i, 2), fld.length());
        model->setData(model->index(i, 3), fld.precision());
        model->setData(model->index(i, 4), fld.requiredStatus() == -1 ? QVariant("?")
            : QVariant(bool(fld.requiredStatus())));
        model->setData(model->index(i, 5), fld.isAutoValue());
        model->setData(model->index(i, 6), fld.defaultValue());
    }

    emit tableModelChanged(model, QAbstractItemView::NoEditTriggers);
}

void QConnectionCtrl::setActiveItem(QTreeWidgetItem* item, int column) {
    if (!item)
        return;

    if (item->parent()) {
        setActiveDb(item->parent());

        const QString t = item->text(0);
        QSqlDatabase db = QSqlDatabase::database(m_activeDb);

        QSqlTableModel* model = new CustomModel(nullptr, db);
        model->setEditStrategy(QSqlTableModel::OnRowChange);
        model->setTable(db.driver()->escapeIdentifier(t, QSqlDriver::TableName));
        model->select();
        if (model->lastError().type() != QSqlError::NoError)
            emit statusMessage(model->lastError().text());

        emit tableModelChanged(model, QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    }
    else setActiveDb(item);
}

void QConnectionCtrl::refresh() {
    clear();
    QStringList connectionNames = QSqlDatabase::connectionNames();

    bool gotActiveDb = false;
    for (int i = 0; i < connectionNames.count(); ++i) {
        QTreeWidgetItem* rootItem = new QTreeWidgetItem(this);
        QSqlDatabase db = QSqlDatabase::database(connectionNames.at(i), false);

        QString dbCaption = db.driverName();
        dbCaption.append(QLatin1Char(':'));
        if (!db.userName().isEmpty())
            dbCaption.append(db.userName()).append(QLatin1Char('@'));
        dbCaption.append(db.databaseName());

        rootItem->setText(0, dbCaption);
        rootItem->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DriveNetIcon));
        if (connectionNames.at(i) == QSqlDatabase::database(m_activeDb).connectionName()) {
            gotActiveDb = true;
            setActiveDb(rootItem);
        }
        if (db.isOpen()) {
            QStringList tableList = db.tables();
            for (int t = 0; t < tableList.count(); ++t) {
                QTreeWidgetItem* table = new QTreeWidgetItem(rootItem);
                table->setText(0, tableList.at(t));
                table->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
            }
        }
    }
    if (!gotActiveDb) {
        m_activeDb = connectionNames.value(0);
        setActiveDb(topLevelItem(0));
    }

    doItemsLayout();
}

void QConnectionCtrl::setActiveDb(QTreeWidgetItem* item) {
    auto f_setBold = [=](QTreeWidgetItem* item, bool bold) {
        QFont font = item->font(0);
        font.setBold(bold);
        item->setFont(0, font);
    };

    for (int i = 0; i < topLevelItemCount(); ++i) {
        if (topLevelItem(i)->font(0).bold())
            f_setBold(topLevelItem(i), false);
    }

    if (!item)
        return;

    f_setBold(item, true);
    m_activeDb = QSqlDatabase::connectionNames().value(indexOfTopLevelItem(item));
    emit dbSelected(m_activeDb);
}