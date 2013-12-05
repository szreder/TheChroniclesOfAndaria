#ifndef BARWIDGET_H
#define BARWIDGET_H

#include <QtWidgets>

class BarWidget : public QWidget {

public:
	enum class Pattern : quint8 {
		None,
		Dither,
		Gradient
	};

private:
	class Layer {
		friend BarWidget;

	public:
		typedef void (BarWidget::*BarWidgetCallback)(Layer *);

		Layer(int value, QColor color, Pattern pattern, BarWidget *owner, BarWidgetCallback callback);

		QColor color() const;
		Pattern pattern() const;
		int value() const;

		void setColor(QColor color);
		void setPattern(Pattern pattern);
		void setValue(int value);

	private:
		void update();

		int value_;
		QColor color_;
		Pattern pattern_;
		BarWidget *owner_;
		BarWidgetCallback callback_;
	};

public:
	BarWidget(int minValue, int maxValue, QWidget *parent = nullptr);
	~BarWidget();

	const Layer * operator[](int index) const;
	Layer * operator[](int index);

	bool isValid() const;
	int minValue() const;
	int maxValue() const;
	int layerCount() const;
	QSize sizeHint() const;
	QSize minimumSizeHint() const;

	void setMinValue(int minValue);
	void setMaxValue(int maxValue);

	void addLayer(int value, QColor color, Pattern pattern = Pattern::None);
	void clear();

protected:
	void paintEvent(QPaintEvent *event);

private:
	void doClear();
	void drawLayer(QPainter &painter, const Layer *layer);
	int layerPixels(const Layer *layer) const;
	void recalcLayer(Layer *layer);
	void recalcLayers();
	void updateCallback(Layer *layer);

	static const int DefaultBarLength = 66;
	static const int DefaultBarThickness = 20;

	QPair <int, int> valueRange;
	QVector <Layer *> layers_;
};

#endif
