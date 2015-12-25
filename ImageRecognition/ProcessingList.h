#ifndef PROCESSINGLIST_H
#define PROCESSINGLIST_H

#include <QAbstractListModel>

class ProcessingList : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit ProcessingList(QObject *parent = 0);

signals:

public slots:

};

#endif // PROCESSINGLIST_H
