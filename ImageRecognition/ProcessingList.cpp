#include "ProcessingList.h"
#include "Processors/FakeProcessor.h"


ProcessingList::ProcessingList(QObject *parent) :
	QAbstractItemModel(parent)
{
	m_processors.push_back( new FakeProcessor );
}

ProcessingList::~ProcessingList()
{
	for( auto processor : m_processors )
		delete processor;
}


QModelIndex 	ProcessingList::index	( int row, int column, const QModelIndex& parent ) const
{
	if( m_processors.size() == 0 )
		return QModelIndex();

	if( parent.parent() == QModelIndex() )
		return createIndex( row, column, m_processors[ row ] );
	return QModelIndex();
}

QVariant		ProcessingList::data	( const QModelIndex& index, int role ) const
{
	if ( role != Qt::DisplayRole )
		return QVariant();

	if( index.isValid() )
		return QVariant( static_cast<ImageProcessor*>( index.internalPointer() )->GetName().c_str() );
	return QVariant();
}

QModelIndex 	ProcessingList::parent	( const QModelIndex& /*index*/ ) const
{
	return QModelIndex();
}


int				ProcessingList::columnCount	( const QModelIndex& parent ) const
{
	if( parent.parent() == QModelIndex() )
		return 1;
	return 1;
}

int				ProcessingList::rowCount	( const QModelIndex& parent ) const
{
	if( parent.parent() == QModelIndex() )
		return (int)m_processors.size();
	return 0;
}

// ================================================================== //
bool			ProcessingList::AddProcessor	( ImageProcessor* processor, unsigned int listNumber )
{
	// Mamy na razie tylko jedną listę.
	if( listNumber != 0 )
		return false;

	m_processors.push_back( processor );
	return true;
}

