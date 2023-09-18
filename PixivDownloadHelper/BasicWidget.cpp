#include "BasicWidget.h"
//TransparentWidget
TransparentWidget::TransparentWidget() {
	setWindowFlags(Qt::FramelessWindowHint);//无边框化
	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);//聚焦策略：点击聚焦
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

	//初始化滚动动画
	scrollAnimation = new QPropertyAnimation(this->verticalScrollBar(), "value");
	scrollAnimation->setDuration(200);
	scrollAnimation->setEasingCurve(QEasingCurve::OutCubic);

	//窗口透明化
	QPalette pal = this->viewport()->palette();
	pal.setColor(QPalette::Window, _transparentWidget_color);
	this->viewport()->setPalette(pal);

	setContentsMargins(0, 0, 0, 0);

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

TransparentScrollArea::~TransparentScrollArea() {
	delete scrollAnimation;
}

void TransparentScrollArea::wheelEvent(QWheelEvent* wheelEvent) {
	scrollAnimation->stop();
	scrollAnimation->setEndValue(this->verticalScrollBar()->value() - wheelEvent->angleDelta().y());
	scrollAnimation->start();
}

void TransparentScrollArea::keyPressEvent(QKeyEvent* ev) {
	scrollAnimation->stop();
	int changeValue{ 0 };
	if (ev->key() == Qt::Key_Up) {
		changeValue = _pixivDownloadItemWithoutPre_height;
	}
	else if (ev->key() == Qt::Key_Down) {
		changeValue = -_pixivDownloadItemWithoutPre_height;
	}
	else if (ev->key() == Qt::Key_PageUp) {
		changeValue = _pixivDownloadItemWithPre_height + 5;
	}
	else if (ev->key() == Qt::Key_PageDown) {
		changeValue = -_pixivDownloadItemWithPre_height - 5;
	}
	else{}

	scrollAnimation->setEndValue(this->verticalScrollBar()->value() - changeValue);
	scrollAnimation->start();
}

//StackedWidget
StackedWidget::StackedWidget() {
	//初始化切换动画
	posAnimation = new QPropertyAnimation;
	opacityAnimation = new QPropertyAnimation;

	switchGroup = new QParallelAnimationGroup;

	opacityEffect = new QGraphicsOpacityEffect;
	//初始化索引
	index = 0;

	//设置动画
	posAnimation->setDuration(150);
	posAnimation->setEasingCurve(QEasingCurve::InCubic);

	opacityAnimation->setDuration(150);
	opacityAnimation->setEasingCurve(QEasingCurve::InOutCubic);

	//切换动画完成切换窗口
	connect(this->switchGroup, &QParallelAnimationGroup::finished,
		this, &StackedWidget::setWidget);
}

StackedWidget::~StackedWidget() {

	delete opacityAnimation;
	delete posAnimation;
	delete switchGroup;
}

void StackedWidget::switchWidget(int _index) {
	if (_index == index) { return; }
	//绑定透明度遮罩
	this->currentWidget()->setGraphicsEffect(opacityEffect);
	//绑定动画
	posAnimation->setTargetObject(this->currentWidget());
	posAnimation->setPropertyName("pos");

	opacityAnimation->setTargetObject(opacityEffect);
	opacityAnimation->setPropertyName("opacity");

	//根据索引计算动画结束位置
	QPoint endValue{ 0,this->currentWidget()->height() / 2 };
	if (this->index > _index) {}
	else {
		endValue = -endValue;
	}
	posAnimation->setStartValue(QPoint(0, 0));
	posAnimation->setEndValue(endValue);

	opacityAnimation->setStartValue(1.0);
	opacityAnimation->setEndValue(0.0);

	switchGroup->addAnimation(posAnimation);
	switchGroup->addAnimation(opacityAnimation);

	switchGroup->start();

	//保存索引
	this->index = _index;
}

void StackedWidget::setWidget() {
	this->setCurrentIndex(this->index);
}

void StackedWidget::enterEvent(QEvent* event) {
	emit enterSignal();
}