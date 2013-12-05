#include "Gui/CustomWidgets/BarWidget.h"

BarWidget::Layer::Layer(int value, QColor color, BarWidget::Pattern pattern, BarWidget *owner, BarWidgetCallback callback)
	: value_(value), color_(color), pattern_(pattern), owner_(owner), callback_(callback)
{
}

QColor BarWidget::Layer::color() const
{
	return color_;
}

BarWidget::Pattern BarWidget::Layer::pattern() const
{
	return pattern_;
}

int BarWidget::Layer::value() const
{
	return value_;
}

void BarWidget::Layer::setColor(QColor color)
{
	this->color_ = color;
	update();
}

void BarWidget::Layer::setPattern(BarWidget::Pattern pattern)
{
	this->pattern_ = pattern;
	update();
}

void BarWidget::Layer::setValue(int value)
{
	this->value_ = value;
	update();
}

void BarWidget::Layer::update()
{
	(owner_->*callback_)(this);
}

BarWidget::BarWidget(int minValue, int maxValue, QWidget *parent)
	: QWidget(parent), valueRange(minValue, maxValue)
{
	Q_ASSERT(isValid());
}

BarWidget::~BarWidget()
{
	doClear();
}

const BarWidget::Layer * BarWidget::operator[](int index) const
{
	return layers_[index];
}

BarWidget::Layer * BarWidget::operator[](int index)
{
	return layers_[index];
}

bool BarWidget::isValid() const
{
	return valueRange.first <= valueRange.second;
}

int BarWidget::minValue() const
{
	return valueRange.first;
}

int BarWidget::maxValue() const
{
	return valueRange.second;
}

int BarWidget::layerCount() const
{
	return layers_.count();
}

QSize BarWidget::sizeHint() const
{
	return QSize(DefaultBarLength, DefaultBarThickness);
}

QSize BarWidget::minimumSizeHint() const
{
	return QSize(DefaultBarLength, DefaultBarThickness);
}

void BarWidget::setMinValue(int minValue)
{
	this->valueRange.first = minValue;
	recalcLayers();
}

void BarWidget::setMaxValue(int maxValue)
{
	this->valueRange.second = maxValue;
	recalcLayers();
}

void BarWidget::addLayer(int value, QColor color, Pattern pattern)
{
	value = qBound(valueRange.first, value, valueRange.second);
	layers_.append(new Layer(value, color, pattern, this, &BarWidget::updateCallback));
	update();
}

void BarWidget::clear()
{
	doClear();
	update();
}

void BarWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	const Layer *cur = layers_[0], *prev;
	drawLayer(painter, cur);
	for (int i = 1; i < layers_.count(); ++i) {
		prev = cur;
		cur = layers_[i];
		drawLayer(painter, cur);

		int left = layerPixels(cur), right = layerPixels(prev);
		switch (cur->pattern()) {
			case Pattern::Dither: {
				QBrush brush(cur->color(), Qt::Dense5Pattern);
				painter.fillRect(QRect(left, 0, right - left, DefaultBarThickness), brush);
				break;
			}

			case Pattern::Gradient: {
				QLinearGradient gradient(0, 0, 1, 0);
				gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
				gradient.setColorAt(0, cur->color());
				gradient.setColorAt(1, prev->color());

				QBrush brush(gradient);
				painter.fillRect(QRect(left, 0, (right - left) / 2, DefaultBarThickness), brush);
				break;
			}

			default: break;
		}
	}

	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::black);
	painter.drawRect(0, 0, width(), DefaultBarThickness);
}


void BarWidget::doClear()
{
	qDeleteAll(layers_);
	layers_.clear();
}

void BarWidget::drawLayer(QPainter &painter, const BarWidget::Layer *layer)
{
	QBrush brush(layer->color());
	painter.fillRect(QRect(0, 0, layerPixels(layer), DefaultBarThickness), brush);
}

int BarWidget::layerPixels(const BarWidget::Layer *layer) const
{
	int fillPercent = 100 * (layer->value() - valueRange.first) / (valueRange.second - valueRange.first);
	return width() * fillPercent / 100;
}

void BarWidget::recalcLayer(BarWidget::Layer *layer)
{
	//we modify the attribute value_ directly to avoid infinite looping on callback
	layer->value_ = qBound(valueRange.first, layer->value(), valueRange.second);
}

void BarWidget::recalcLayers()
{
	for (Layer *layer : layers_)
		recalcLayer(layer);
	update();
}

void BarWidget::updateCallback(BarWidget::Layer *layer)
{
	recalcLayer(layer);
	update();
}
