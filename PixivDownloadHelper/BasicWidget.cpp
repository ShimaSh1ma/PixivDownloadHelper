#include "BasicWidget.h"
//TransparentWidget
TransparentWidget::TransparentWidget() {
	setWindowFlags(Qt::FramelessWindowHint);//无边框化
}

void TransparentWidget::paintEvent(QPaintEvent* paintE) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
	painter.setPen(Qt::NoPen);
	painter.setBrush(_transparentWidget_color);//背景颜色
	
	painter.drawRect(rect());
}

//TranslucentWidget
TranslucentWidget::TranslucentWidget()
{
	setWindowFlags(Qt::FramelessWindowHint);	//无边框化
}

void TranslucentWidget::paintEvent(QPaintEvent* paintE) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
	painter.setPen(Qt::NoPen);
	painter.setBrush(_translucentWidget_color);//背景颜色

	QRect rt = this->rect();
	rt.setWidth(rt.width() - 1);
	rt.setHeight(rt.height() - 1);
	painter.drawRoundedRect(rt, 10, 10);//绘制圆角
}

//TransparentScrollArea
TransparentScrollArea::TransparentScrollArea() {
	setWindowFlags(Qt::FramelessWindowHint);//窗口无边框化
	setFrameStyle(Qt::FramelessWindowHint);

	//窗口透明化
	QPalette pal = this->viewport()->palette();
	pal.setColor(QPalette::Window, _transparentWidget_color);
	this->viewport()->setPalette(pal);

	//滚动条样式
	this->verticalScrollBar()->setStyleSheet(
		"QScrollBar:vertical{"
		"background-color:transparent;"
		"width:10px;"
		"}"
		"QScrollBar:handle:vertical{"
		"background:rgba(220,220,220,255);"
		"border-radius:5px;"
		"}"
		"QScrollBar:handle:vertical:hover{"
		"background:rgba(200,200,200,255);"
		"border-radius:5px;"
		"}"
		"QScrollBar:add-page:vertical{"
		"background-color:transparent;"
		"}"
		"QScrollBar:sub-page:vertical{"
		"background-color:transparent;"
		"}"
		"QScrollBar:sub-line:vertical{"
		"background:none;"
		"border:none;"
		"color:none;"
		"}"
		"QScrollBar:add-line:vertical{"
		"background:none;"
		"border:none;"
		"color:none;"
		"}"
	);
}