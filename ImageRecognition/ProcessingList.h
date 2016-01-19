#ifndef PROCESSINGLIST_H
#define PROCESSINGLIST_H

#include <QAbstractItemModel>

#include "ImageProcessor.h"

#include <vector>

class ProcessingList : public QAbstractItemModel
{
	Q_OBJECT
private:
	std::vector<ImageProcessor*>	m_processors;
	int								m_commonProc;
public:
	explicit ProcessingList(QObject *parent = 0);
	~ProcessingList();

	// Funkcje obsługujące model - widok
	virtual QModelIndex 	index	( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
	virtual QVariant		data	( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
	virtual QModelIndex 	parent	( const QModelIndex& index ) const override;

	virtual int				columnCount	( const QModelIndex & parent = QModelIndex() ) const override;
	virtual int				rowCount	( const QModelIndex & parent = QModelIndex() ) const override;


	// Funkcje do zarzadzania procesorami
	bool					AddProcessor	( ImageProcessor* processor, unsigned int listNumber );



	std::vector<ImageProcessor*>&		GetProcessors()	{ return m_processors; }
	int									GetNumCommonProc();
};

#endif // PROCESSINGLIST_H
