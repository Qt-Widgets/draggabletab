#ifndef DRAGGABLETABWIDGET_H
#define DRAGGABLETABWIDGET_H

#include <QTabBar>
#include <QTabWidget>


class DraggableTabBar;

class DraggableTabWidget : public QTabWidget
{
	Q_OBJECT
	friend class DraggableTabBar;
public:
	
	struct TabInfo
	{
		TabInfo(int index, DraggableTabWidget *tabWidget) : index(index), tabWidget(tabWidget) {}
		
		int index;
		DraggableTabWidget *tabWidget;
	};
	
	explicit DraggableTabWidget(QWidget *parent = 0);
	
	static void moveTab(DraggableTabWidget *source, int sourceIndex, DraggableTabWidget *dest, int destIndex);
	static void moveTab(const TabInfo &source, const TabInfo &dest) { moveTab(source.tabWidget, source.index, dest.tabWidget, dest.index); }
	static TabInfo decodeTabDropEvent(QDropEvent *event);
	static bool eventIsTabDrag(QDragEnterEvent *event);
	
signals:
	
	void willBeDeleted();
	
public slots:
	
	void deleteIfEmpty();
};

class DraggableTabBar : public QTabBar
{
	Q_OBJECT
public:
	
	DraggableTabBar(DraggableTabWidget *tabWidget, QWidget *parent = 0);
	
	DraggableTabWidget *tabWidget() { return _tabWidget; }
	
protected:
	
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	
private:
	
	int insertionIndexAt(const QPoint &pos);
	
	DraggableTabWidget *_tabWidget;
	bool _isStartingDrag;
	QPoint _dragStartPos;
};

#endif // DRAGGABLETABWIDGET_H